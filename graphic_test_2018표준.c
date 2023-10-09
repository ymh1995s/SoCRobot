#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <math.h>
#include "amazon2_sdk.h"
#include "graphic_api.h"
#include <termios.h>

/////////////////////로봇 통신부분 전처리
#include <getopt.h>
#include <unistd.h>

#include "uart_api.h"
#include "uart_api.c"
#include "robot_protocol.c"
#include "robot_protocol.h"
#include <termios.h>

#define AMAZON2_GRAPHIC_VERSION		"v0.5"

#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define MASKR 0x001F
#define MASKG 0x003F
#define MASKB 0x001F

#define MASKV 0x00FF
#define MASKS 0x007F

#define MIN 100
#define MID	350
#define MAX 500
#define MAX2 1000

//#define MIN 400
//#define MID 800
//#dfefine MAX 900

//#define MIN 500
//#define MID 900
//#define MAX 1000

int count1 = 0; //왼쪽
int count2 = 0;	//가운데 위
int count3 = 0;	//오른쪽
int count5 = 0;	//가운데 아래
int count7 = 0;	//왼쪽 위
int count8 = 0;	//가운데 위
int count9 = 0; //오른쪽 위
int countBlack = 0;
//int ymin = 70, ymax = 160, cbmin = -15, cbmax = 15, crmin = -15, crmax = 15;
//사거리 멀면 여기값 줄이기, 가까우면 늘리기
int ymin = 70, ymax = 140, cbmin = -10, cbmax = 10, crmin = -10, crmax = 10;
//좀 줄이기 int ymin = 75, ymax = 135, cbmin = -10, cbmax = 10, crmin = -10, crmax = 10;
//좀 늘이기 int ymin = 65, ymax = 145, cbmin = -10, cbmax = 10, crmin = -10, crmax = 10;
//내가 찾은 값 int ymin = 50, ymax = 120, cbmin = -8, cbmax = 0, crmin = -8, crmax = 2;

int big_punch = 0, kick_state = 0;
//////////////////////////////////////////YCbCr변환 룩업테이블 변수
int table_077[256];
int table_150[256];
int table_029[256];
int table_043[256];
int table_128[256];
int table_085[256];
int table_107[256];
int table_021[256];

void Delay(int delay_time)
{
	//delay_time /= 5;
	while (delay_time)
		delay_time--;
}
int kbhit(void)
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int getch(void)
{
	int r;
	unsigned char c;
	if ((r = read(0, &c, sizeof(c))) < 0) {
		return r;
	}
	else {
		return c;
	}
}

typedef struct {
	int R, G, B;
} sRGB;

sRGB mRGB;

typedef struct {
	int S, V;
}	sSV;

sSV mSV;

void bitParsing(sRGB *ret, unsigned short org)
{
	sRGB tmp;

	tmp.R = (int)((org >> 11) & MASKR);
	tmp.G = (int)((org >> 5) & MASKG);
	tmp.B = (int)((org >> 0) & MASKB);

	(*ret) = tmp;
}

void bitParsingSV(sSV *ret, unsigned short org)
{
	sSV tmp;

	tmp.S = (int)((org >> 0) & MASKS);
	tmp.V = (int)((org >> 7) & MASKV);

	(*ret) = tmp;
}

int getAbit(unsigned short x, int n) { // getbit()
	return (x & (1 << n)) >> n;
}

void RGBtoYCbCr(int *r, int *g, int *b, int *y, int *cb, int *cr) {
	*y = (table_077[*r] + table_150[*g] + table_029[*b] + 128) >> 8;	//0~255 
	*cb = (-table_043[*r] - table_085[*g] + table_128[*b] - 128) >> 8;	//-128~127
	*cr = (table_128[*r] - table_107[*g] - table_021[*b] - 128) >> 8;	//-128~127
}

void show_help(void)
{
	printf("================================================================\n");
	printf("Graphic API Example (Ver : %s)\n", AMAZON2_GRAPHIC_VERSION);
	printf("================================================================\n");
	printf("h : show this message\n");
	printf("0 : flip \n");
	printf("a : direct camera display on\n");
	printf("d : direct camera display off\n");
	printf("c : clear screen \n");
	printf("y : capture \n");
	printf("f : fullsize display\n");
	printf("1 : input Y data\n");
	printf("2 : input Cb data\n");
	printf("3 : input Cr data\n");
	printf("l : YCbCr_Capture\n");
	printf("t : twoLine \n");
	printf("p : input s data\n");
	printf("o : input v data\n");
	printf("m : SV_Capture \n");
	printf("q : exit \n");
	printf("================================================================\n");
}
//YCbCr사용한 이진화 (int 최소 y축 값)
static void binaryYCbCr(int min_y, int max_y) {
	U16* fpga_videodata = (U16*)malloc(180 * 120 * 2);
	int r, g, b;
	int y, cb, cr;
	int mid_y = (min_y+max_y)/2;
	printf("capture Start\n");
	clear_screen();									//화면 하얀색으로 만듬
	read_fpga_video_data(fpga_videodata);			//fpga로부터 데이터 가져오기
	int i, j;
	//for (i = 0; i < min_y; i++) {                        //세로크기 0~120
	//	for (j = 0; j < 180; j++) {                     //가로크기 0~180
	//		fpga_videodata[i * 180 + j] = fpga_videodata[i * 180 + j] & 0x0000;
	//	}
	//}
	for (i = min_y; i < max_y; i++) {                   //세로크기 0~120
		for (j = 0; j < 180; j++) {                     //가로크기 0~180
			bitParsing(&mRGB, fpga_videodata[i * 180 + j]);   // ex) i번째 행 j번째 열  
			r = mRGB.R * 8;								//5->8비트
			g = mRGB.G * 4;								//6->8비트
			b = mRGB.B * 8;								//5->8비트
			RGBtoYCbCr(&r, &g, &b, &y, &cb, &cr);		//RGB를 이용하여 ycbcr값 만듬
			if (y >= ymin && y <= ymax && cb >= cbmin && cb <= cbmax && cr >= crmin && cr <= crmax) {            //회색잡기
				if (i >= 80) {
					if (j < 60) count1++;                  //왼쪽 카운트
					else if (j < 120 && i < 100) count2++;			   //가운데 카운트
					else if (j < 120) count5++;
					else if (j < 180) count3++;            //오른쪽 카운트
					fpga_videodata[i * 180 + j] = fpga_videodata[i * 180 + j] | 0x07E0;            //잡은 회색값은 하얀으로
				}
				else {
					if (j < 60) count7++;					//왼쪽 카운트
					else if (j < 120) count8++;				//가운데 카운트
					else if (j < 180) count9++;				//오른쪽 카운트
					fpga_videodata[i * 180 + j] = fpga_videodata[i * 180 + j] | 0x07E0;            //잡은 회색값은 하얀으로
				}
			}
			else if (y <= 20 && cb >= cbmin && cb <= cbmax && cr >= crmin && cr <= crmax)
			{
				countBlack++;
			}
			// else fpga_videodata[i * 180 + j] = fpga_videodata[i * 180 + j] & 0x0000;         //아닌 값은 검은색으로
		}
	}
	printf("count1 : %d count2 : %d count5 : %d	count3 : %d\n", count1, count2, count5, count3);
	printf("count7 : %d count8 : %d count9 : %d countBlack : %d\n", count7, count8, count9, countBlack);
	printf("ymin : %d ymax : %d \nCbmin : %d Cbmax : %d\nCrmin : %d Crmax : %d\n", ymin, ymax, cbmin, cbmax, crmin, crmax);
	draw_fpga_video_data_full(fpga_videodata);
	flip();
	free(fpga_videodata);
}

static void twoLine(void) {
	U16* fpga_videodata = (U16*)malloc(180 * 120 * 2);
	int r, g, b;
	//float h, s, v;
	int y, cb, cr;
	printf("capture Start\n");
	clear_screen();
	read_fpga_video_data(fpga_videodata);
	int i = 0;
	int j = 0;
	for (i = 0; i < 1; i++) {
		for (j = 0; j < 180; j++) {
			bitParsing(&mRGB, fpga_videodata[i * 180 + j]);
			r = mRGB.R * 8;
			g = mRGB.G * 4;
			b = mRGB.B * 8;
			printf("R : %d	G : %d	B : %d	", r, g, b);
			RGBtoYCbCr(&r, &g, &b, &y, &cb, &cr);
			printf("Y : %d	Cb : %d	Cr : %d", y, cb, cr);
			//RGBtoHSV(&r, &g, &b, &h, &s, &v);
			//printf("H : %f	S : %f	V : %f", h, s, v);
			printf("\n");
		}
	}
	draw_fpga_video_data(fpga_videodata, 10, 10);
	flip();
	free(fpga_videodata);
	printf("capture End\n");
}

void LUT(void) {  //YCbCr 룩업테이블
	int i;
	for (i = 0; i < 256; i++)
	{
		table_077[i] = 77 * i;
		table_150[i] = 150 * i;
		table_029[i] = 29 * i;
		table_043[i] = 43 * i;
		table_128[i] = 128 * i;
		table_085[i] = 85 * i;
		table_107[i] = 107 * i;
		table_021[i] = 21 * i;
	}
}

void drawfull(void)
{
	int i = 100;
	U16* fpga_videodata = (U16*)malloc(180 * 120 * 2);
	while (i--) {
		clear_screen();
		read_fpga_video_data(fpga_videodata);
		draw_fpga_video_data_full(fpga_videodata);
		flip();
	}
	free(fpga_videodata);

}

void Logo(void)
{
	printf("\n\n");
	printf("            *****************************************\n");
	printf("              Welcome to Eagle Robot Platform Board \n");
	printf("            *****************************************\n");
}

void PrintBannerRobot(void)
{
	printf("\n");
	printf("================================================================\n");
	printf("              <<<< Robot Body TEST Selection >>>>               \n");
	printf("----------------------------------------------------------------\n");
	printf("   1. Hello            -[a]   |  3. One Forward walk -[c] \n");
	printf("   2. Half Forward walk    -[b]   |  4. Two Forward walk   -[d] \n");
	printf("----------------------------------------------------------------\n");
	printf("   19. Quit            -[z]         \n");
	printf("================================================================\n");

}

int TestItemSelectRobot(void)
{
	char Item;

	while (1) {
		PrintBannerRobot();
		printf("\nSelected Test Item :  ");
		Item = getchar();
		putchar(Item);

		switch (Item) {
		case 'a': case 'A': init();				break;
		case 'b': case 'B': InitSlow();				break;
		case 'z': case 'Z': return 0;
		default: printf("\nNo Test Item Selected");	break;
		}
	}
	return 0;
}

void findGray(void) {
	printf("find Gray\n");
}

int findRedBlue(void) {
	int x = 0;
	printf("hh\n");
	return x;
}

void stand(void) {
	Send_Command(0x01, 0xfe);
	Delay(3000000);
}

void turnL(int num) {
	if (num == 1) { Send_Command(0x02, 0xfd); Delay(770000); }
	else if (num == 2) { Send_Command(0x03, 0xfc); Delay(1540000); }
}

void turnR(int num) {
	if (num == 1) { Send_Command(0x04, 0xfb); Delay(770000); }
	else if (num == 2) { Send_Command(0x05, 0xfa); Delay(1540000); }
}

void walkF(int num) {
	if (num == 1) { Send_Command(0x06, 0xf9); Delay(1100000); }	//느린걷기
	else if (num == 2) { Send_Command(0x07, 0xf8); Delay(2200000); }
	else if (num == 3) { Send_Command(0x08, 0xf7); Delay(3300000); }
}

void walkB(int num) {
	if (num == 1) { Send_Command(0x09, 0xf6); Delay(1100000); }
	else if (num == 2) { Send_Command(0x0a, 0xf5); Delay(2200000); }
	else if (num == 3) { Send_Command(0x0b, 0xf4); Delay(3300000); }
}

void punch(int num) {

	if (num == 1) { Send_Command(0x0f, 0xf0); Delay(3100000);}			//앞뒤공격
	//else if (num == 2) { Send_Command(0x0d, 0xf2); Delay(1600000); }	//기존위아래
	else if (num == 2) { Send_Command(0x0d, 0xf2); Delay(900000); }	//2018위아래
	else if (num == 3) { Send_Command(0x10, 0xef); Delay(1700000); big_punch=1; }	//2018주먹추가
	else if (num == 4) { Send_Command(0x14, 0xeb); Delay(2200000); }	//머리떄림
	//1라운드때는 1,2,4썼었음
}

void kick(int num) {
	Delay(1000000);
	if (num == 1) { Send_Command(0x11, 0xee); Delay(10000000); } //안씀
	else if (num == 2) { Send_Command(0x13, 0xec); Delay(4000000); }
}

void newWalkF(int num){

	if (num == 1) { Send_Command(0x15, 0xea); Delay(860000); } 
	else if (num == 2) { Send_Command(0x16, 0xe9); Delay(1970000); }
	else if (num == 3) { Send_Command(0x17, 0xe8); Delay(3000000); }
	else if (num == 4) { Send_Command(0x18, 0xe7); Delay(3000000); }

}

int exist = 0;			//방금전 인식했는지 판단
int turn_num = 0;		//몇번돌았는지 판단

#include <termios.h>
static struct termios inittio, newtio;
int start = 2;		//0 : 검은화면일때, 1 : 검은화면에서 새로운것을 인식했을 때, 2 : 가운데로 갔다고 가정, 인식 시작
void init_console(void)
{
	tcgetattr(0, &inittio);
	newtio = inittio;
	newtio.c_lflag &= ~ICANON;
	newtio.c_lflag &= ~ECHO;
	newtio.c_lflag &= ~ISIG;
	newtio.c_cc[VMIN] = 1;
	newtio.c_cc[VTIME] = 0;

	cfsetispeed(&newtio, B115200);

	tcsetattr(0, TCSANOW, &newtio);
}
int pre_count1 = 0, pre_count2 = 0, pre_count3 = 0, pre_count5 = 0;

int black = 0;

int main(void)
{
	LUT();
	int ret;

	init_console();

	ret = uart_open();
	if (ret < 0) return EXIT_FAILURE;

	uart_config(UART1, 57600, 8, UART_PARNONE, 1);

	//BOOL b_loop = TRUE;
	if (open_graphic() < 0) {
		return -1;
	}

	SURFACE* bmpsurf = 0;
	U16* fpga_videodata = (U16*)malloc(180 * 120 * 2);
	/*if (kbhit())
	{
		return 0;
	}*/
	direct_camera_display_off();	//카메라 끄기
	while (0) {
		if (kbhit())
		{
			if (getchar() == 'z')
				break;
		}
		count1 = 0;
		count2 = 0;
		count3 = 0;
		count5 = 0;
		count7 = 0;
		count8 = 0;
		count9 = 0;
		binaryYCbCr(80, 120);
	}
	Delay(3000000);
	stand();
	int state = 1;
	
	while (1) {
		if (kbhit())
		{
			if (getchar() == 'z')
				break;
		}
		////////////////////////////////////////////////픽셀카운트 초기화
		count1 = 0;
		count2 = 0;
		count3 = 0;
		count5 = 0;
		count7 = 0;
		count8 = 0;
		count9 = 0;
		countBlack = 0;
		///////////////////////////////////////////////
		//binaryYCbCr(0, 120);
		//continue;
		////////////////////////////////////////////////
		if (state == 0 || state == 1) {			//시작 
			printf("state = %d", state);
			binaryYCbCr(60, 120);
		}
		else if (state == 2) {		//못잡았을때 위에 확인
			printf("state = %d", state);
			binaryYCbCr(60, 120);
		}
		else if (state == 3) {		//제일위에 확인
			printf("state = %d", state);
			binaryYCbCr(0, 120);
		}
		else if (state == 4) {
			printf("state = %d", state);
			binaryYCbCr(0, 60);
			if ((count7 + count8 + count9) > 30) 
			{ 
				state = 5; 
				continue;
			}
			else {
				stand();
				continue;
			}
		}
		else if (state == 5) {							//시작하고 가운데로 움직임
			printf("state = %d", state);
			Delay(1000000);
			turnR(1);
			turnR(1);
			turnR(1);
			turnR(1);
			turnR(1);
			turnR(1);
			binaryYCbCr(60, 120);
			walkF(1);
			walkF(1);
			walkF(1);
			walkF(1);
			walkF(1);

			binaryYCbCr(60, 120);
			state = 0;
		}
		if (countBlack > 5000)
		{
			state = 4;
			continue;
		}
		if (count1 < MIN && count2 + count5 < MIN && count3 < MIN) {	//인식 못했을 때
			if (state == 0) //가운데인 상태에서 인식 못하면 
			{
				if ((count7 + count8 + count9) < 30) {
					turnR(1);
					turnR(1);
					state = 1;
				}
				else 
				{
					walkF(1);
					state = 1;
				}
			}
			else if (state == 1)
			{
				walkB(1);
				walkB(1);
				state = 2;
			}
			else if (state == 2) //중간까지 보는 상태
			{
				if ((count7 + count8 + count9) > 30) 
				{
					walkF(1);
				}
				else
				{
					state = 3;
				}
			}
			else if (state == 3) {
				if ((count7 + count8 + count9) > 30)
				{
					turnR(1);
					turnR(1);
				}
			}
			else if (exist == 0) {					//바로전에 인식을 하지 않았을때
				turnR(1);
				turnR(1);
			}
			else if (exist == 1) {		//바로전에 인식을 했지만 지금은 못했을때
				exist = 0;
				walkB(2);				//뒤로 두걸음
			}
		}
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		//////////////////////////////공격파트/총 7개////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		else {			//잡았을때
			exist = 1;
			state = 1;
			////////////////////////////////////////////////////////////////////위에는 인식을 못했을때
			if (count2+count5 > MAX && count5-count2 <100) {	//가운데 가까이 있을떄
				if (count8 > MAX2) {
					walkB(1);
					walkB(1);
					walkB(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					state = 2;
				}
				else
				{
					//punch(4);
					kick(2);
					walkB(1);
				}
			}
			else if (count1 > MAX) {	//왼쪽에 가까이있을때
				if (count7 > MAX2) {
					walkB(1);
					walkB(1);
					walkB(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					state = 2;
				}
				else {
					walkB(1);
					turnL(1);
					//punch(1);
					punch(3);

				}
			}
			else if (count3 > MAX) {	//오른쪽 가까이 있을때
				if (count9 > MAX2) {
					walkB(1);
					walkB(1);
					walkB(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					state = 2;
				}
				else {
					walkB(1);
					//turnR(1);//punch4를 쓸때는 주석 처리 펀치4 안쓸때는 다른거 안거드리고 이거만 주석 해제
					//kick(2);//발차기 빈도 늘리기1
					//turnl과 punch4는 세트
					punch(4);

				}
			}
			else if (count2 + count5 > MID) {	//가운데 있을 떄
				walkF(1);
				turnL(1);//turnL와 punch4는 세트
				punch(4);
				//kick(2);//발차기 빈도 늘리기2
				//walkB(1);
			}
			else if (count2  > MIN) {			//가운데 멀리 있을때
				walkF(1);
			}
			else if (count1 > MIN) {	//왼쪽에 있을 때
				turnL(1);
			}
			else if (count3 > MIN) {	//오른쪽 있을 때
				turnR(1);
			}
			else if ((count1 + count2 + count5) > MAX) {	//왼쪽과 가운데사이에 있을때
				turnL(1);
				punch(2);
			}
			else if ((count2 + count5 + count3) > MAX) {	//가운데와 오른쪽사이에 있을때
				turnR(1);
				punch(3);
			}
			else if ((count1 + count2 + count5 + count3) > MAX * 2) {		//너무 가까이 있을때
				if (count7 + count8 +count9> MAX2) {
					walkB(1);
					walkB(1);
					walkB(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					turnR(1);
					state = 2;
				}
				punch(3);
			}
			pre_count1 = count1;
			pre_count2 = count2;
			pre_count3 = count3;
			pre_count5 = count5;
		}
	}
	free(fpga_videodata);
	if (bmpsurf != 0)
		release_surface(bmpsurf);
	close_graphic();
	uart_close();

	return 0;
}