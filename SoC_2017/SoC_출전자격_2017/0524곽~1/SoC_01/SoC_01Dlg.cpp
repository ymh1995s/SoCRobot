
// SoC_01Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SoC_01.h"
#include "SoC_01Dlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////Cb �� �ּҰ��� �ִ밪 ����///////////////////////////////////////
int Min_cb_red = 200;
int Max_cb_red = 250;

int Min_cb_green = 240;
int Max_cb_green = 255;

int Min_cb_blue = 30;
int Max_cb_blue = 53;

int Min_cb_yellow = 175;
int Max_cb_yellow = 220;
////////////////////////Cr �� �ּҰ��� �ִ밪 ����///////////////////////////////////////
int Min_cr_red = 35;
int Max_cr_red = 100;

int Min_cr_green = 120;
int Max_cr_green = 230;

int Min_cr_blue = 10;
int Max_cr_blue = 250;

int Min_cr_yellow = 0;
int Max_cr_yellow = 10;

int rgby = 1;
//////////////////////////////////////////////////////////////////////////////////////

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSoC_01Dlg ��ȭ ����

//////////////////////////////////////////////////////// ���� ���� ����
BITMAPINFO BmInfo_Color, *BmInfo_Gray;
LPBYTE pImageBuffer, pImageBuffer_Red, pImageBuffer_Red2, pImageBuffer_Red3,
pImageBuffer_Green, pImageBuffer_Green2, pImageBuffer_Green3,
pImageBuffer_Blue, pImageBuffer_Blue2, pImageBuffer_Blue3,
pImageBuffer_Yellow, pImageBuffer_Yellow2, pImageBuffer_Yellow3;
LPBYTE Erosion_R, Erosion_R2, Dilation_R;
LPBYTE Erosion_G, Erosion_G2, Dilation_G;
LPBYTE Erosion_B, Erosion_B2, Dilation_B;
LPBYTE Erosion_Y, Erosion_Y2, Dilation_Y;
LPBYTE pHSVImageBuffer, pYCbCrImageBuffer;

//////////////////////////////////////////////////////// �߽ɰ��� ���� ���� �ʱ�ȭ
int xcenter_R = 0, xcenter_R2 = 0, xcenter_R3 = 0;
int ycenter_R = 0, ycenter_R2 = 0, ycenter_R3 = 0;
int xcenter_G = 0, xcenter_G2 = 0, xcenter_G3 = 0;
int ycenter_G = 0, ycenter_G2 = 0, ycenter_G3 = 0;
int xcenter_B = 0, xcenter_B2 = 0, xcenter_B3 = 0;
int ycenter_B = 0, ycenter_B2 = 0, ycenter_B3 = 0;
int xcenter_Y = 0, xcenter_Y2 = 0, xcenter_Y3 = 0;
int ycenter_Y = 0, ycenter_Y2 = 0, ycenter_Y3 = 0;
int xcenter4 = 0, ycenter4 = 0;
int t = 0;

int s = 0;
//////////////////////////////////////////////////////////////////////////////////////
bool m_IsRed = TRUE;
bool m_IsGreen = TRUE;
bool m_IsBlue = TRUE;
bool m_IsYellow = TRUE;

int count = 0;		//�������� ���� ī���ͺ���
clock_t start, end;
//////////////////////////////////////////////////////////////////////////////////////


CSoC_01Dlg::CSoC_01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoC_01Dlg::IDD, pParent)
	, m_Min_Value()
	, m_Max_Value()
	, m_Fps(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//////////////////////////////////////////////////////////////////////////////////////������� �ʱ�ȭ
	pImageBuffer = NULL;
	pImageBuffer_Red = NULL;	pImageBuffer_Red2 = NULL;	pImageBuffer_Red3 = NULL;
	pImageBuffer_Green = NULL;	pImageBuffer_Green2 = NULL;	pImageBuffer_Green3 = NULL;
	pImageBuffer_Blue = NULL;	pImageBuffer_Blue2 = NULL;	pImageBuffer_Blue3 = NULL;
	pImageBuffer_Yellow = NULL;	pImageBuffer_Yellow2 = NULL; pImageBuffer_Yellow3 = NULL;
	Erosion_R = NULL;	Dilation_R = NULL;	Erosion_R2 = NULL;
	Erosion_G = NULL;	Dilation_G = NULL;	Erosion_G2 = NULL;
	Erosion_B = NULL;	Dilation_B = NULL;	Erosion_B2 = NULL;
	Erosion_Y = NULL;	Dilation_Y = NULL;	Erosion_Y2 = NULL;
	BmInfo_Gray = NULL;

	////////////////////////////////////////////////////////////////////////////////////// �������� ������ ���� ���� �ʱ�ȭ
	m_AllocStructureElementBinary(2);
	m_SetStructureElementBinary(0, 5, 0);
	m_SetStructureElementBinary(1, 0, 0);
	m_SetStructureElementBinary(2, 0, 1);
	m_SetStructureElementBinary(3, 1, 0);
	m_SetStructureElementBinary(4, 1, 1);
	//////////////////////////////////////////////////////////////////////////////////////

}

void CSoC_01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAM_1, m_cam1);
	DDX_Control(pDX, IDC_CAM_2, m_cam2);
	DDX_Control(pDX, IDC_CAM_3, m_cam3);
	DDX_Control(pDX, IDC_CAM_4, m_cam4);
	DDX_Control(pDX, IDC_CAM_5, m_cam5);
	DDX_Control(pDX, IDC_Max_EDIT, m_Max_Value);
	DDX_Control(pDX, IDC_Min_EDIT, m_Min_Value);
	DDX_Control(pDX, IDC_Max_Cr_EDIT, m_max_value);
	DDX_Control(pDX, IDC_Min_Cr_EDIT, m_min_value);
	DDX_Text(pDX, IDC_Fps, m_Fps);
}

BEGIN_MESSAGE_MAP(CSoC_01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_start, &CSoC_01Dlg::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTON_RED, &CSoC_01Dlg::OnBnClickedButtonRed)
	ON_BN_CLICKED(IDC_BUTTON_GREEN, &CSoC_01Dlg::OnBnClickedButtonGreen)
	ON_BN_CLICKED(IDC_BUTTON_BLUE, &CSoC_01Dlg::OnBnClickedButtonBlue)
	ON_BN_CLICKED(IDC_BUTTONT_YELLOW, &CSoC_01Dlg::OnBnClickedButtonYellow)
	ON_EN_CHANGE(IDC_Max_Cb_EDIT, &CSoC_01Dlg::OnEnChangeMaxCbEdit)
	ON_EN_CHANGE(IDC_Min_Cb_EDIT, &CSoC_01Dlg::OnEnChangeMinCbEdit)
	ON_EN_CHANGE(IDC_Max_Cr_EDIT, &CSoC_01Dlg::OnEnChangeMaxCrEdit)
	ON_EN_CHANGE(IDC_Min_Cr_EDIT, &CSoC_01Dlg::OnEnChangeMinCrEdit)
	ON_BN_CLICKED(IDC_RADIO1, &CSoC_01Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSoC_01Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSoC_01Dlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CSoC_01Dlg::OnBnClickedRadio4)

END_MESSAGE_MAP()


// CSoC_01Dlg �޽��� ó����

BOOL CSoC_01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CRect rect;
	m_cam1.GetClientRect(rect);	//��Ʈ���� ũ��޾ƿ���

	m_hWndCap = capCreateCaptureWindow(_T("Capture Window"), WS_CHILD | WS_VISIBLE, rect.TopLeft().x, rect.TopLeft().y, rect.BottomRight().x, rect.BottomRight().y, m_cam1, NULL);
	//�� ������ ĸó�� ���� ���� ������ ����.

	if (capSetCallbackOnFrame(m_hWndCap, capCallbackOnFrame) == FALSE) return FALSE;	//�ݹ��Լ��� �θ�	//ķ������ FALSE ����.

	if (capDriverConnect(m_hWndCap, 0) == FALSE) return FALSE;		//0��ī�޶� ? ���� �� ķ �����Ѱ��� 0���� ��

	capDlgVideoFormat(m_hWndCap);
	capGetVideoFormat(m_hWndCap, &BmInfo_Color, sizeof(BITMAPINFO));

	if (BmInfo_Color.bmiHeader.biBitCount != 24)
	{
		BmInfo_Color.bmiHeader.biBitCount = 24;
		BmInfo_Color.bmiHeader.biCompression = 0;
		BmInfo_Color.bmiHeader.biSizeImage = BmInfo_Color.bmiHeader.biWidth * BmInfo_Color.bmiHeader.biHeight * 3;
		capSetVideoFormat(m_hWndCap, &BmInfo_Color, sizeof(BITMAPINFO));
	}

	BmInfo_Gray = (BITMAPINFO*)new BITMAPINFO[(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD))];
	BmInfo_Gray->bmiHeader.biBitCount = 8;
	BmInfo_Gray->bmiHeader.biCompression = 0;
	BmInfo_Gray->bmiHeader.biSizeImage = 320 * 240;
	BmInfo_Gray->bmiHeader.biWidth = 320;
	BmInfo_Gray->bmiHeader.biHeight = 240;
	BmInfo_Gray->bmiHeader.biSize = sizeof(BITMAPINFO);
	BmInfo_Gray->bmiHeader.biClrImportant = 0;
	BmInfo_Gray->bmiHeader.biClrUsed = 0;
	BmInfo_Gray->bmiHeader.biPlanes = 1;
	BmInfo_Gray->bmiHeader.biXPelsPerMeter = 0;
	BmInfo_Gray->bmiHeader.biYPelsPerMeter = 0;
	for (int i = 0; i < 256; i++)
	{
		BmInfo_Gray->bmiColors[i].rgbRed = i;
		BmInfo_Gray->bmiColors[i].rgbGreen = i;
		BmInfo_Gray->bmiColors[i].rgbBlue = i;
		BmInfo_Gray->bmiColors[i].rgbReserved = 0;

	}

	capPreviewRate(m_hWndCap, 10);	//ķ�� 33���������� ���
	capOverlay(m_hWndCap, true);
	capPreviewScale(m_hWndCap, true);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSoC_01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSoC_01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		if (pImageBuffer_Red != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_cam2.GetDC();
			m_cam2.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_Red, BmInfo_Gray);
			ReleaseDC(pDC);	//������ ġ��.
		}

		if (pImageBuffer_Green != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_cam3.GetDC();
			m_cam3.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_Green, BmInfo_Gray);
			ReleaseDC(pDC);
		}

		if (pImageBuffer_Blue != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_cam4.GetDC();
			m_cam4.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_Blue, BmInfo_Gray);
			ReleaseDC(pDC);
		}


		if (pImageBuffer_Yellow != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_cam5.GetDC();
			m_cam5.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_Yellow, BmInfo_Gray);
			ReleaseDC(pDC);
		}
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSoC_01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CALLBACK capCallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	start = clock();
	BYTE pixel;
	int i, j;
	int xCenter = 0, yCenter = 0, index = 0;;
	int H = BmInfo_Gray->bmiHeader.biHeight;
	int W = BmInfo_Gray->bmiHeader.biWidth;
	int State_R = 0;
	CString Color;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////���� �Ҵ�
	if (pImageBuffer == NULL)
	{
		pImageBuffer = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth * 3];
	}

	//RGBtoHSV(lpVHdr->lpData, pHSVImageBuffer, H, W);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// RGB -> YCbCr ��ȯ
	if (pYCbCrImageBuffer == NULL)
	{
		pYCbCrImageBuffer = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth * 3];
	}
	RGBtoYCbCr(lpVHdr->lpData, pYCbCrImageBuffer, H, W);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (m_IsRed) {
		Color = "R";
		if (pImageBuffer_Red == NULL)
			pImageBuffer_Red = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Red2 == NULL)
			pImageBuffer_Red2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Red3 == NULL)
			pImageBuffer_Red3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_R == NULL)
			Erosion_R = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_R2 == NULL)
			Erosion_R2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_R == NULL)
			Dilation_R = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];

		for (int i = 0; i < H * W; i++)  // 0 - Y 1 - Cb 2 - Cr ����
		{
			if (/*((*(pYCbCrImageBuffer + (i * 3)) > 110)) && ((*(pYCbCrImageBuffer + (i * 3)) < 145)) &&*/
				((*(pYCbCrImageBuffer + (i * 3) + 1) > Min_cb_red)) && ((*(pYCbCrImageBuffer + (i * 3) + 1) < Max_cb_red)) &&
				((*(pYCbCrImageBuffer + (i * 3) + 2) > Min_cr_red)) && ((*(pYCbCrImageBuffer + (i * 3) + 2) < Max_cr_red)))
			{
				*(pImageBuffer_Red + i) = (BYTE)255;
			}
			else *(pImageBuffer_Red + i) = (BYTE)0;

			if (count == 0)
			{
				*(pImageBuffer_Red2 + i) = (BYTE)0;
				*(pImageBuffer_Red3 + i) = (BYTE)0;
			}
		}

		//////////////////////////////////////////////////////////////////////////////��������
		m_MorphologyBinaryErosion(H, W, pImageBuffer_Red, Erosion_R);
		m_MorphologyBinaryErosion(H, W, Erosion_R, Erosion_R2);
		m_MorphologyBinaryErosion(H, W, Erosion_R2, Erosion_R);
		m_MorphologyBinaryErosion(H, W, Erosion_R, Erosion_R2);

		/////////////////////////////////////////////////////////////////////////////////������
		if (count % 2 + 1 >= 2)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_Red3 + i) = *(pImageBuffer_Red + i) - *(pImageBuffer_Red2 + i);
				if (*(pImageBuffer_Red3 + i) < 0)
					*(pImageBuffer_Red3 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_Red2 + i) = 0;
		}
		else
		{
			for (int i = 0; i < H*W; i++)
			{
				*(pImageBuffer_Red2 + i) += *(pImageBuffer_Red + i);
				if (*(pImageBuffer_Red2 + i) >= 255)
					*(pImageBuffer_Red2 + i) = 255;
			}
		}
		//////////////////////////////////////////////////////////////////////////////�����ȷο�
		m_BorderFollow(H, W, Erosion_R2, lpVHdr->lpData, Color);
		m_BorderFollow2(H, W, pImageBuffer_Red3, lpVHdr->lpData, Color);

		if (t == 0)
		{
			xcenter_R3 = xcenter_R2;
			ycenter_R3 = ycenter_R2;
		}

		if (s == 0)
		{
			xcenter_R3 = (xcenter_R + xcenter_R2) / 2;
			ycenter_R3 = (ycenter_R + ycenter_R2) / 2;
		}
		if (t != 0 && s != 0)
		{
			xcenter_R3 = (xcenter_R + xcenter_R2) / 2;
			ycenter_R3 = (ycenter_R + ycenter_R2) / 2;
		}

		for (int i = xcenter_R3 - 15; i <= xcenter_R3 + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + ycenter_R3) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + ycenter_R3) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + ycenter_R3) + 2) = 255;
		}

		index = xcenter_R3*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = ycenter_R3 - 15; j < ycenter_R3 + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 255;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (m_IsGreen)
	{
		Color = "G";
		if (pImageBuffer_Green == NULL)
			pImageBuffer_Green = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Green2 == NULL)
			pImageBuffer_Green2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Green3 == NULL)
			pImageBuffer_Green3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_G == NULL)
			Erosion_G = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_G2 == NULL)
			Erosion_G2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_G == NULL)
			Dilation_G = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];

		for (int i = 0; i < H * W; i++)  // 0 - Y 1 - Cb 2 - Cr ����
		{
			if (/*((*(pYCbCrImageBuffer + (i * 3)) > 110)) && ((*(pYCbCrImageBuffer + (i * 3)) < 255)) &&*/
				((*(pYCbCrImageBuffer + (i * 3) + 1) > Min_cb_green)) && ((*(pYCbCrImageBuffer + (i * 3) + 1) < Max_cb_green)) &&
				((*(pYCbCrImageBuffer + (i * 3) + 2) > Min_cr_green)) && ((*(pYCbCrImageBuffer + (i * 3) + 2) < Max_cr_green)))
			{
				*(pImageBuffer_Green + i) = (BYTE)255;
			}
			else *(pImageBuffer_Green + i) = (BYTE)0;
			if (count == 0)
			{
				*(pImageBuffer_Green2 + i) = (BYTE)0;
				*(pImageBuffer_Green3 + i) = (BYTE)0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////��������
		m_MorphologyBinaryErosion(H, W, pImageBuffer_Green, Erosion_G);
		m_MorphologyBinaryErosion(H, W, Erosion_G, Erosion_G2);
		m_MorphologyBinaryDilation(H, W, Erosion_G2, Dilation_G);
		/////////////////////////////////////////////////////////////////////////////////������
		if (count % 2 + 1 >= 2)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_Green3 + i) = *(pImageBuffer_Green + i) - *(pImageBuffer_Green2 + i);
				if (*(pImageBuffer_Green3 + i) < 0) *(pImageBuffer_Green3 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_Green2 + i) = 0;
		}
		else
		{
			for (int i = 0; i < H*W; i++)
			{
				*(pImageBuffer_Green2 + i) += *(pImageBuffer_Green + i);
				if (*(pImageBuffer_Green2 + i) >= 255)
					*(pImageBuffer_Green2 + i) = 255;
			}
		}
		////////////////////////////////////////////////////////////////////�����ȷο�
		m_BorderFollow(H, W, Dilation_G, lpVHdr->lpData, Color);
		m_BorderFollow2(H, W, pImageBuffer_Green3, lpVHdr->lpData, Color);

		if (t == 0)
		{
			xcenter_G3 = xcenter_G2;
			ycenter_G3 = ycenter_G2;
		}

		if (s == 0)
		{
			xcenter_G3 = (xcenter_G + xcenter_G2) / 2;
			ycenter_G3 = (ycenter_G + ycenter_G2) / 2;
		}
		if (t != 0 && s != 0)
		{
			xcenter_G3 = (xcenter_G + xcenter_G2) / 2;
			ycenter_G3 = (ycenter_G + ycenter_G2) / 2;
		}

		for (int i = xcenter_G3 - 15; i <= xcenter_G3 + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + ycenter_G3) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + ycenter_G3) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + ycenter_G3) + 2) = 0;
		}

		index = xcenter_G3*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = ycenter_G3 - 15; j < ycenter_G3 + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 0;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (m_IsBlue)
	{
		Color = "B";
		if (pImageBuffer_Blue == NULL)
			pImageBuffer_Blue = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Blue2 == NULL)
			pImageBuffer_Blue2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Blue3 == NULL)
			pImageBuffer_Blue3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_B == NULL)
			Erosion_B = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_B2 == NULL)
			Erosion_B2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_B == NULL)
			Dilation_B = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];

		for (int i = 0; i < H * W; i++)  // 0 - Y 1 - Cb 2 - Cr ����
		{
			if (/*((*(pYCbCrImageBuffer + (i * 3)) > 80)) && ((*(pYCbCrImageBuffer + (i * 3)) < 135)) &&*/
				((*(pYCbCrImageBuffer + (i * 3) + 1) > Min_cb_blue)) && ((*(pYCbCrImageBuffer + (i * 3) + 1) < Max_cb_blue)) &&
				((*(pYCbCrImageBuffer + (i * 3) + 2) > Min_cr_blue)) && ((*(pYCbCrImageBuffer + (i * 3) + 2) < Max_cr_blue)))
			{
				*(pImageBuffer_Blue + i) = (BYTE)255;
			}
			else *(pImageBuffer_Blue + i) = (BYTE)0;

			if (count == 0)
			{
				*(pImageBuffer_Blue2 + i) = (BYTE)0;
				*(pImageBuffer_Blue3 + i) = (BYTE)0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////������
		if (count % 2 + 1 >= 2)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_Blue3 + i) = *(pImageBuffer_Blue + i) - *(pImageBuffer_Blue2 + i);
				if (*(pImageBuffer_Blue3 + i) < 0)
					*(pImageBuffer_Blue3 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_Blue2 + i) = 0;
		}
		else
		{
			for (int i = 0; i < H*W; i++)
			{
				*(pImageBuffer_Blue2 + i) += *(pImageBuffer_Blue + i);
				if (*(pImageBuffer_Blue2 + i) >= 255)
					*(pImageBuffer_Blue2 + i) = 255;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////��������
		m_MorphologyBinaryErosion(H, W, pImageBuffer_Blue3, Erosion_B2);
		m_MorphologyBinaryDilation(H, W, Erosion_B2, pImageBuffer_Blue3);
		m_MorphologyBinaryErosion(H, W, pImageBuffer_Blue3, Erosion_B2);
		m_MorphologyBinaryDilation(H, W, Erosion_B2, pImageBuffer_Blue3);

		////////////////////////////////////////////////////////////////�����ȷο� + �߽ɰ� ǥ��
		m_BorderFollow3(H, W, pImageBuffer_Blue3, lpVHdr->lpData);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (m_IsYellow)
	{
		Color = "Y";
		if (pImageBuffer_Yellow == NULL)
			pImageBuffer_Yellow = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Yellow2 == NULL)
			pImageBuffer_Yellow2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_Yellow3 == NULL)
			pImageBuffer_Yellow3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_Y == NULL)
			Erosion_Y = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_Y2 == NULL)
			Erosion_Y2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_Y == NULL)
			Dilation_Y = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];

		for (int i = 0; i < H * W; i++)  // 0 - Y 1 - Cb 2 - Cr ����
		{
			if (((*(pYCbCrImageBuffer + (i * 3)) > 140)) && ((*(pYCbCrImageBuffer + (i * 3)) < 205)) &&
				((*(pYCbCrImageBuffer + (i * 3) + 1) > Min_cb_yellow)) && ((*(pYCbCrImageBuffer + (i * 3) + 1) < Max_cb_yellow)) &&
				((*(pYCbCrImageBuffer + (i * 3) + 2) > Min_cr_yellow)) && ((*(pYCbCrImageBuffer + (i * 3) + 2) < Max_cr_yellow)))
			{
				*(pImageBuffer_Yellow + i) = (BYTE)255;
			}
			else *(pImageBuffer_Yellow + i) = (BYTE)0;
			if (count == 0)
			{
				*(pImageBuffer_Yellow2 + i) = (BYTE)0;
				*(pImageBuffer_Yellow3 + i) = (BYTE)0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////��������
		m_MorphologyBinaryErosion(H, W, pImageBuffer_Yellow, Erosion_Y);
		m_MorphologyBinaryErosion(H, W, Erosion_Y, Erosion_Y2);
		m_MorphologyBinaryErosion(H, W, Erosion_Y2, Erosion_Y);
		m_MorphologyBinaryErosion(H, W, Erosion_Y, Erosion_Y2);

		/////////////////////////////////////////////////////////////////////////////////������
		if (count % 2 + 1 >= 2)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_Yellow3 + i) = *(pImageBuffer_Yellow + i) - *(pImageBuffer_Yellow2 + i);
				if (*(pImageBuffer_Yellow3 + i) < 0)
					*(pImageBuffer_Yellow3 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_Yellow2 + i) = 0;
		}
		else
		{
			for (int i = 0; i < H*W; i++)
			{
				*(pImageBuffer_Yellow2 + i) += *(pImageBuffer_Yellow + i);
				if (*(pImageBuffer_Yellow2 + i) >= 255)
					*(pImageBuffer_Yellow2 + i) = 255;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////�����ȷο�
		m_BorderFollow(H, W, Erosion_Y2, lpVHdr->lpData, Color);
		m_BorderFollow2(H, W, pImageBuffer_Yellow3, lpVHdr->lpData, Color);

		////////////////////////////////////////////////////////////////�߽ɰ� ã��
		if (t == 0)
		{
			xcenter_Y3 = xcenter_Y2;
			ycenter_Y3 = ycenter_Y2;
		}
		if (s == 0)
		{
			xcenter_Y3 = (xcenter_Y + xcenter_Y2) / 2;
			ycenter_Y3 = (ycenter_Y + ycenter_Y2) / 2;
		}
		if (t != 0 && s != 0)
		{
			xcenter_Y3 = (xcenter_Y + xcenter_Y2) / 2;
			ycenter_Y3 = (ycenter_Y + ycenter_Y2) / 2;
		}

		////////////////////////////////////////////////////////////////�߽ɰ� ǥ��
		for (int i = xcenter_Y3 - 15; i <= xcenter_Y3 + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + ycenter_Y3) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + ycenter_Y3) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + ycenter_Y3) + 2) = 0;
		}

		index = xcenter_Y3*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = ycenter_Y3 - 15; j < ycenter_Y3 + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 0;
		}
	}

	end = clock();	//������ �ð� ����

	///////////////////////////////////////////////////////////////////////////////////////////////////�������� ���� ī����
	if (count >= 8)
		count = 1;
	else count++;

	CSoC_01Dlg *pDlg = (CSoC_01Dlg*)AfxGetMainWnd();
	pDlg->Invalidate(false);

	pDlg->m_Fps.Format(_T("FPS : %f"), 1 / (((double)end - (double)start) / CLOCKS_PER_SEC));
	pDlg->UpdateData(FALSE);
	return (LRESULT)TRUE;
}



void CSoC_01Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	capDriverDisconnect(m_hWndCap);
	if (pImageBuffer != NULL) delete[] pImageBuffer;
	if (pImageBuffer_Red != NULL) delete[] pImageBuffer_Red;
	if (pImageBuffer_Red2 != NULL) delete[] pImageBuffer_Red2;
	if (pImageBuffer_Red3 != NULL) delete[] pImageBuffer_Red3;
	if (pImageBuffer_Green != NULL) delete[] pImageBuffer_Green;
	if (pImageBuffer_Green2 != NULL) delete[] pImageBuffer_Green2;
	if (pImageBuffer_Green3 != NULL) delete[] pImageBuffer_Green3;
	if (pImageBuffer_Blue != NULL) delete[] pImageBuffer_Blue;
	if (pImageBuffer_Blue2 != NULL) delete[] pImageBuffer_Blue2;
	if (pImageBuffer_Blue3 != NULL) delete[] pImageBuffer_Blue3;
	if (pImageBuffer_Yellow != NULL) delete[] pImageBuffer_Yellow;
	if (pImageBuffer_Yellow2 != NULL) delete[] pImageBuffer_Yellow2;
	if (pImageBuffer_Yellow3 != NULL) delete[] pImageBuffer_Yellow3;

	if (Erosion_R != NULL) delete[] Erosion_R;
	if (Erosion_R2 != NULL) delete[] Erosion_R;
	if (Dilation_R != NULL) delete[] Dilation_R;
	if (Erosion_G != NULL) delete[] Erosion_R;
	if (Erosion_G2 != NULL) delete[] Erosion_R;
	if (Dilation_G != NULL) delete[] Dilation_R;
	if (Erosion_B != NULL) delete[] Erosion_R;
	if (Erosion_B2 != NULL) delete[] Erosion_R;
	if (Dilation_B != NULL) delete[] Dilation_R;
	if (Erosion_Y != NULL) delete[] Erosion_R;
	if (Erosion_Y2 != NULL) delete[] Erosion_R;
	if (Dilation_Y != NULL) delete[] Dilation_R;
	m_FreeStructureElementBinary();
}


void CSoC_01Dlg::OnBnClickedButtonstart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_IsRed) m_IsRed = FALSE;
	else m_IsRed = TRUE;
}


void CSoC_01Dlg::OnBnClickedButtonRed()
{
	if (m_IsRed) m_IsRed = FALSE;
	else m_IsRed = TRUE;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CSoC_01Dlg::OnBnClickedButtonGreen()
{
	if (m_IsGreen) m_IsGreen = FALSE;
	else m_IsGreen = TRUE;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CSoC_01Dlg::OnBnClickedButtonBlue()
{
	if (m_IsBlue) m_IsBlue = FALSE;
	else m_IsBlue = TRUE;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CSoC_01Dlg::OnBnClickedButtonYellow()
{
	if (m_IsYellow) m_IsYellow = FALSE;
	else m_IsYellow = TRUE;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CSoC_01Dlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

void CSoC_01Dlg::OnBnClickedRadio1()
{
	rgby = 1;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString tmp;
	tmp.Format(_T("%d"), Max_cb_red);
	m_Max_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cb_red);
	m_Min_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cr_red);
	m_min_value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Max_cr_red);
	m_max_value.SetWindowTextW(tmp);

	//UpdateData();
}

void CSoC_01Dlg::OnBnClickedRadio2()
{
	rgby = 2;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString tmp;
	tmp.Format(_T("%d"), Max_cb_green);
	m_Max_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cb_green);
	m_Min_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Max_cr_green);
	m_max_value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cr_green);
	m_min_value.SetWindowTextW(tmp);

	//UpdateData();
}

void CSoC_01Dlg::OnBnClickedRadio3()
{
	rgby = 3;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString tmp;
	tmp.Format(_T("%d"), Max_cb_blue);
	m_Max_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cb_blue);
	m_Min_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Max_cr_blue);
	m_max_value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cr_blue);
	m_min_value.SetWindowTextW(tmp);

	//UpdateData();
}

void CSoC_01Dlg::OnBnClickedRadio4()
{
	rgby = 4;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString tmp;
	tmp.Format(_T("%d"), Max_cb_yellow);
	m_Max_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cb_yellow);
	m_Min_Value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Max_cr_yellow);
	m_max_value.SetWindowTextW(tmp);

	tmp.Format(_T("%d"), Min_cr_yellow);
	m_min_value.SetWindowTextW(tmp);

	//UpdateData();
}

void CSoC_01Dlg::OnEnChangeMaxCbEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strstring;
	m_Max_Value.GetWindowTextW(m_strstring);

	switch (rgby)
	{
	case 1:
		Max_cb_red = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 2:
		Max_cb_green = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 3:
		Max_cb_blue = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 4:
		Max_cb_yellow = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
	default:
		break;
	}
}

void CSoC_01Dlg::OnEnChangeMinCbEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strstring;

	m_Min_Value.GetWindowTextW(m_strstring);

	switch (rgby)
	{
	case 1:
		Min_cb_red = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 2:
		Min_cb_green = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 3:
		Min_cb_blue = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 4:
		Min_cb_yellow = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	default:
		break;
	}
}

void CSoC_01Dlg::OnEnChangeMaxCrEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strstring;
	m_max_value.GetWindowTextW(m_strstring);

	switch (rgby)
	{
	case 1:
		Max_cr_red = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 2:
		Max_cr_green = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 3:
		Max_cr_blue = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 4:
		Max_cr_yellow = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
	default:
		break;
	}
}

void CSoC_01Dlg::OnEnChangeMinCrEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strstring;

	m_min_value.GetWindowTextW(m_strstring);

	switch (rgby)
	{
	case 1:
		Min_cr_red = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 2:
		Min_cr_green = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 3:
		Min_cr_blue = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	case 4:
		Min_cr_yellow = _wtoi(m_strstring);			// ���ڿ��� ���ڷ�
		break;
	default:
		break;
	}
}

void m_BorderFollow(int height, int width, LPBYTE src, LPBYTE dest, CString Color)
{
	// ������ ��������� �����ϱ� ���� ����ü �޸� 
	typedef struct tagBORDERINFO { short *x, *y; short n, dn; } BORDERINFO;
	BORDERINFO stBorderInfo[1000];

	// ���� �ִ� �ȼ��� �湮�� �������� ��ũ�ϱ� ���� ���� �޸� �Ҵ� 
	unsigned char *visited = new unsigned char[height*width];
	memset(visited, 0, height*width * sizeof(char)); // �޸� �ʱ�ȭ 

													 // �������� �ӽ÷� �����ϱ� ���� �޸� 
	short *xchain = new short[10000];
	short *ychain = new short[10000];

	// ���� �ȼ��� �ð�������� �������� ��Ÿ���� ���� ��ǥ ���� 
	const POINT nei[8] =           // clockwise neighbours
	{
		{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 }
	};

	int x0, y0, x, y, k, n;
	int numberBorder = 0, border_count, diagonal_count;
	unsigned char c0, c1;
	int index = 0, xCenter = 0, yCenter = 0, counter = 0; //center�� ������� ���� �߰�
	for (x = 1; x < height; x++)
	{
		for (y = 1; y < width; y++)
		{
			c0 = src[x * width + y];
			c1 = src[(x - 1) * width + y];

			if (c0 != c1&&c0 == (unsigned char)255 && visited[x*width + y] == 0)  //c0!=c1(����̰�)
			{
				border_count = 0;  // ������� ������ ���� ���� ī����
				diagonal_count = 0;  // 

				x0 = x;
				y0 = y;
				n = 4;
				do
				{
					// ������ �������� ���� Į�� ���� ������� ã�� ���� 
					for (k = 0; k < 8; k++, n = ((n + 1) & 7))  // 01234567
					{									 // 12345670
						short  u = (short)(x + nei[n].x);
						short  v = (short)(y + nei[n].y);
						if (u < 0 || u >= height || v < 0 || v >= width) continue;
						if (src[u * width + v] == c0) break; // �������� ������ ���ٰ� ���� �����     
															 // ��踦 ������ �������� ������ ���� �ȴ�. 
					}
					if (k == 8) break;    // isolated point occurs

					visited[x*width + y] = 255;  // �湮�� ������ ��ũ 
					xchain[border_count] = x;
					ychain[border_count++] = y;

					if (border_count >= 10000) break;

					x = x + nei[n].x;
					y = y + nei[n].y;

					if (n % 2 == 1) diagonal_count++;
					// 01234567 
					n = (n + 5) & 7; // 56701234
				} while (!(x == x0  &&  y == y0));

				if (k == 8) continue;    // isolated point occurs

										 // ��������� ���� 
				if ((border_count <200) /*|| (border_count>300)*/) continue; // �ʹ����� ũ�ų� ���� ������ ����̸� �����Ѵ�.  

				stBorderInfo[numberBorder].x = new short[border_count];
				stBorderInfo[numberBorder].y = new short[border_count];

				for (k = 0; k < border_count; k++)
				{
					stBorderInfo[numberBorder].x[k] = xchain[k];
					stBorderInfo[numberBorder].y[k] = ychain[k];
				}
				stBorderInfo[numberBorder].n = border_count;
				stBorderInfo[numberBorder++].dn = diagonal_count;

				if (numberBorder >= 1000) break;
			}
		}
	}




	// ȭ�鿡 ��踦 ����ϱ� ���� m_OutImg�迭�� �̿�����. 
	//memset(dest, 255, height*width*sizeof(char));
	for (k = 0; k < numberBorder; k++)
	{

		TRACE("(%d: %d %d, %d)\r\n", k, stBorderInfo[k].n, stBorderInfo[k].dn,
			(int)(sqrt(2.0)*stBorderInfo[k].dn) + (stBorderInfo[k].n - stBorderInfo[k].dn));

		for (int i = 0; i < stBorderInfo[k].n; i++)
		{
			x = x + stBorderInfo[k].x[i];
			y = y + stBorderInfo[k].y[i];
			counter++;
		}
		for (k = 0; k < numberBorder; k++) {
			xCenter += (int)((float)x / (float)counter);
			yCenter += (int)((float)y / (float)counter);
		}
		xCenter = xCenter / numberBorder;
		yCenter = yCenter / numberBorder;
		if (Color == "R") {
			xcenter_R = xCenter;
			ycenter_R = yCenter;
		}
		else if (Color == "G") {
			xcenter_G = xCenter;
			ycenter_G = yCenter;
		}
		else if (Color == "B") {
			xcenter_B = xCenter;
			ycenter_B = yCenter;
		}
		else if (Color == "Y") {
			xcenter_Y = xCenter;
			ycenter_Y = yCenter;
		}
	}

	if (numberBorder >= 1)
	{
		if (Color == "R") {
			xcenter_R = xCenter;
			ycenter_R = yCenter;
		}
		else if (Color == "G") {
			xcenter_G = xCenter;
			ycenter_G = yCenter;
		}
		else if (Color == "B") {
			xcenter_B = xCenter;
			ycenter_B = yCenter;
		}
		else if (Color == "Y") {
			xcenter_Y = xCenter;
			ycenter_Y = yCenter;
		}
		s = 0;				//�����ȷο� �����ϸ� s�� 0���� �ٲ�
	}
	if (numberBorder == 0)	//�����ȷο� �����ϸ� s�� 1�ιٲ�
	{

		s = 1;
	}

	for (k = 0; k < numberBorder; k++) { delete[]stBorderInfo[k].x; delete[]stBorderInfo[k].y; }
	delete[]visited; delete[]xchain; delete[]ychain;
}

void m_BorderFollow2(int height, int width, LPBYTE src, LPBYTE dest, CString Color)
{
	// ������ ��������� �����ϱ� ���� ����ü �޸� 
	typedef struct tagBORDERINFO { short *x, *y; short n, dn; } BORDERINFO;
	BORDERINFO stBorderInfo[1000];

	// ���� �ִ� �ȼ��� �湮�� �������� ��ũ�ϱ� ���� ���� �޸� �Ҵ� 
	unsigned char *visited = new unsigned char[height*width];
	memset(visited, 0, height*width * sizeof(char)); // �޸� �ʱ�ȭ 

													 // �������� �ӽ÷� �����ϱ� ���� �޸� 
	short *xchain = new short[10000];
	short *ychain = new short[10000];

	// ���� �ȼ��� �ð�������� �������� ��Ÿ���� ���� ��ǥ ���� 
	const POINT nei[8] =           // clockwise neighbours
	{
		{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 }
	};

	int x0, y0, x, y, k, n;
	int numberBorder = 0, border_count, diagonal_count;
	unsigned char c0, c1;
	int index = 0, xCenter = 0, yCenter = 0, counter = 0; //center�� ������� ���� �߰�
	for (x = 1; x < height; x++)
	{
		for (y = 1; y < width; y++)
		{
			c0 = src[x * width + y];
			c1 = src[(x - 1) * width + y];

			if (c0 != c1&&c0 == (unsigned char)255 && visited[x*width + y] == 0)  //c0!=c1(����̰�)
			{
				border_count = 0;  // ������� ������ ���� ���� ī����
				diagonal_count = 0;  // 

				x0 = x;
				y0 = y;
				n = 4;
				do
				{
					// ������ �������� ���� Į�� ���� ������� ã�� ���� 
					for (k = 0; k < 8; k++, n = ((n + 1) & 7))  // 01234567
					{									 // 12345670
						short  u = (short)(x + nei[n].x);
						short  v = (short)(y + nei[n].y);
						if (u<0 || u >= height || v<0 || v >= width) continue;
						if (src[u * width + v] == c0) break; // �������� ������ ���ٰ� ���� �����     
															 // ��踦 ������ �������� ������ ���� �ȴ�. 
					}
					if (k == 8) break;    // isolated point occurs

					visited[x*width + y] = 255;  // �湮�� ������ ��ũ 
					xchain[border_count] = x;
					ychain[border_count++] = y;

					if (border_count >= 10000) break;

					x = x + nei[n].x;
					y = y + nei[n].y;

					if (n % 2 == 1) diagonal_count++;
					// 01234567 
					n = (n + 5) & 7; // 56701234
				} while (!(x == x0  &&  y == y0));

				if (k == 8) continue;    // isolated point occurs


										 // ��������� ���� 
				if ((border_count<50) /*|| (border_count>400)*/) continue; // �ʹ����� ������ ����̸� �����Ѵ�.  

				stBorderInfo[numberBorder].x = new short[border_count];
				stBorderInfo[numberBorder].y = new short[border_count];

				for (k = 0; k<border_count; k++)
				{
					stBorderInfo[numberBorder].x[k] = xchain[k];
					stBorderInfo[numberBorder].y[k] = ychain[k];
				}
				stBorderInfo[numberBorder].n = border_count;
				stBorderInfo[numberBorder++].dn = diagonal_count;

				if (numberBorder >= 1000) break;
			}
		}
	}





	//memset(dest, 255, height*width*sizeof(char));
	for (k = 0; k < numberBorder; k++)
	{

		TRACE("(%d: %d %d, %d)\r\n", k, stBorderInfo[k].n, stBorderInfo[k].dn,
			(int)(sqrt(2.0)*stBorderInfo[k].dn) + (stBorderInfo[k].n - stBorderInfo[k].dn));

		for (int i = 0; i < stBorderInfo[k].n; i++)
		{
			x = x + stBorderInfo[k].x[i];
			y = y + stBorderInfo[k].y[i];
			counter++;
		}

		xCenter = (int)((float)x / (float)counter);
		yCenter = (int)((float)y / (float)counter);


		/*if (numberBorder >= 1)
		{
		xcenter2 = xCenter;
		ycenter2 = yCenter;
		}
		if (numberBorder == 0)
		{
		xCenter = xcenter2;
		yCenter = ycenter2;
		}
		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
		if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
		index = i*BmInfo_Gray->bmiHeader.biWidth;
		*(dest + 3 * (index + yCenter) + 0) = 0;
		*(dest + 3 * (index + yCenter) + 1) = 255;
		*(dest + 3 * (index + yCenter) + 2) = 0;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
		if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
		*(dest + 3 * (index + j) + 0) = 0;
		*(dest + 3 * (index + j) + 1) = 255;
		*(dest + 3 * (index + j) + 2) = 0;
		}*/
		if (Color == "R") {
			xcenter_R2 = xCenter;
			ycenter_R2 = yCenter;
		}
		else if (Color == "G") {
			xcenter_G2 = xCenter;
			ycenter_G2 = yCenter;
		}
		else if (Color == "B") {
			xcenter_B2 = xCenter;
			ycenter_B2 = yCenter;
		}
		else if (Color == "Y") {
			xcenter_Y2 = xCenter;
			ycenter_Y2 = yCenter;
		}
	}
	if (numberBorder >= 1)
	{
		if (Color == "R") {
			xcenter_R2 = xCenter;
			ycenter_R2 = yCenter;
		}
		else if (Color == "G") {
			xcenter_G2 = xCenter;
			ycenter_G2 = yCenter;
		}
		else if (Color == "B") {
			xcenter_B2 = xCenter;
			ycenter_B2 = yCenter;
		}
		else if (Color == "Y") {
			xcenter_Y2 = xCenter;
			ycenter_Y2 = yCenter;
		}
		t = 0;					//�����ȷο� �����ϸ�  t�� 0�ιٲ�
	}

	if (numberBorder == 0)		//�����ȷο� �����ϸ�  t�� 1�ιٲ�
	{
		t = 1;
	}

	for (k = 0; k<numberBorder; k++) { delete[]stBorderInfo[k].x; delete[]stBorderInfo[k].y; }
	delete[]visited; delete[]xchain; delete[]ychain;
}

void m_BorderFollow3(int height, int width, LPBYTE src, LPBYTE dest)
{
	// ������ ��������� �����ϱ� ���� ����ü �޸� 
	typedef struct tagBORDERINFO { short *x, *y; short n, dn; } BORDERINFO;
	BORDERINFO stBorderInfo[1000];

	// ���� �ִ� �ȼ��� �湮�� �������� ��ũ�ϱ� ���� ���� �޸� �Ҵ� 
	unsigned char *visited = new unsigned char[height*width];
	memset(visited, 0, height*width * sizeof(char)); // �޸� �ʱ�ȭ 

													 // �������� �ӽ÷� �����ϱ� ���� �޸� 
	short *xchain = new short[10000];
	short *ychain = new short[10000];

	// ���� �ȼ��� �ð�������� �������� ��Ÿ���� ���� ��ǥ ���� 
	const POINT nei[8] =           // clockwise neighbours
	{
		{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 }
	};

	int x0, y0, x, y, k, n;
	int numberBorder = 0, border_count, diagonal_count;
	unsigned char c0, c1;
	int index = 0, xCenter = 0, yCenter = 0, counter = 0; //center�� ������� ���� �߰�
	for (x = 1; x < height; x++)
	{
		for (y = 1; y < width; y++)
		{
			c0 = src[x * width + y];
			c1 = src[(x - 1) * width + y];

			if (c0 != c1&&c0 == (unsigned char)255 && visited[x*width + y] == 0)  //c0!=c1(����̰�)
			{
				border_count = 0;  // ������� ������ ���� ���� ī����
				diagonal_count = 0;  // 

				x0 = x;
				y0 = y;
				n = 4;
				do
				{
					// ������ �������� ���� Į�� ���� ������� ã�� ���� 
					for (k = 0; k < 8; k++, n = ((n + 1) & 7))  // 01234567
					{									 // 12345670
						short  u = (short)(x + nei[n].x);
						short  v = (short)(y + nei[n].y);
						if (u < 0 || u >= height || v < 0 || v >= width) continue;
						if (src[u * width + v] == c0) break; // �������� ������ ���ٰ� ���� �����     
															 // ��踦 ������ �������� ������ ���� �ȴ�. 
					}
					if (k == 8) break;    // isolated point occurs

					visited[x*width + y] = 255;  // �湮�� ������ ��ũ 
					xchain[border_count] = x;
					ychain[border_count++] = y;

					if (border_count >= 10000) break;

					x = x + nei[n].x;
					y = y + nei[n].y;

					if (n % 2 == 1) diagonal_count++;
					// 01234567 
					n = (n + 5) & 7; // 56701234
				} while (!(x == x0  &&  y == y0));

				if (k == 8) continue;    // isolated point occurs

										 // ��������� ���� 
				if ((border_count < 150) || (border_count > 400)) continue; // �ʹ����� ������ ����̸� �����Ѵ�.  

				stBorderInfo[numberBorder].x = new short[border_count];
				stBorderInfo[numberBorder].y = new short[border_count];

				for (k = 0; k < border_count; k++)
				{
					stBorderInfo[numberBorder].x[k] = xchain[k];
					stBorderInfo[numberBorder].y[k] = ychain[k];
				}
				stBorderInfo[numberBorder].n = border_count;
				stBorderInfo[numberBorder++].dn = diagonal_count;

				if (numberBorder >= 1000) break;
			}
		}
	}

	// ȭ�鿡 ��踦 ����ϱ� ���� m_OutImg�迭�� �̿�����. 
	//memset(dest, 255, height*width*sizeof(char));
	for (k = 0; k < numberBorder; k++)
	{
		TRACE("(%d: %d %d, %d)\r\n", k, stBorderInfo[k].n, stBorderInfo[k].dn, (int)(sqrt(2.0)*stBorderInfo[k].dn) + (stBorderInfo[k].n - stBorderInfo[k].dn));

		for (int i = 0; i < stBorderInfo[k].n; i++)
		{
			x = x + stBorderInfo[k].x[i];
			y = y + stBorderInfo[k].y[i];
			counter++;
		}
		for (k = 0; k < numberBorder; k++) {
			xCenter += (int)((float)x / (float)counter);
			yCenter += (int)((float)y / (float)counter);
		}
		xCenter = xCenter / numberBorder;
		yCenter = yCenter / numberBorder;
	}
	if (numberBorder >= 1)
	{
		xcenter4 = xCenter;
		ycenter4 = yCenter;
	}
	if (numberBorder == 0)
	{
		xCenter = xcenter4;
		yCenter = ycenter4;
	}
	for (int i = xCenter - 15; i <= xCenter + 15; i++)
	{
		if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
		index = i*BmInfo_Gray->bmiHeader.biWidth;
		*(dest + 3 * (index + yCenter) + 0) = 255;
		*(dest + 3 * (index + yCenter) + 1) = 255;
		*(dest + 3 * (index + yCenter) + 2) = 255;
	}

	index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

	for (int j = yCenter - 15; j < yCenter + 15; j++)
	{
		if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
		*(dest + 3 * (index + j) + 0) = 255;
		*(dest + 3 * (index + j) + 1) = 255;
		*(dest + 3 * (index + j) + 2) = 255;
	}

	for (k = 0; k < numberBorder; k++) { delete[]stBorderInfo[k].x; delete[]stBorderInfo[k].y; }
	delete[]visited; delete[]xchain; delete[]ychain;
}