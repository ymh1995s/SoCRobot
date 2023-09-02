#include "stdafx.h"
#include "imgpro.h"
#include <iostream>

int WW ,HH; // 카메라 너비 높이
#define set(x , y) ((HH-(y)-1)*WW+(x))
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))  
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))  
typedef struct{
	int row, col;
}StructureElementBinary, *pStructureElementBinary;
pStructureElementBinary m_pSEBinary;

void m_AllocStructureElementBinary(int HowMany)
{
	m_pSEBinary = new StructureElementBinary[HowMany];
}
void m_FreeStructureElementBinary()
{
	if (m_pSEBinary != NULL)
		delete[] m_pSEBinary;
}
void m_SetStructureElementBinary(int which, int row, int col)
{
	m_pSEBinary[which].row = row;
	m_pSEBinary[which].col = col;
}

void img_copy(LPBYTE scr,LPBYTE dst,int H,int W,int channel)
{
	for (int i = 0; i <W*H*channel; i++)
	{
		dst[i] = scr[i];
	}
}
void DrawToHDC( HDC hDCDst, CRect rect , unsigned char * lpVHdr ,BITMAPINFO *BmInfo )
{
	///////////////////////////////////////////////////////////////////////////////////////
	int width = rect.Width();
	int height = rect.Height();
	if( BmInfo->bmiHeader.biWidth > rect.Width() ) 
	{ 
		SetStretchBltMode( 
			hDCDst,           // handle to device context 
			HALFTONE ); 
	} 
	else 
	{ 
		SetStretchBltMode( 
			hDCDst,           // handle to device context 
			COLORONCOLOR ); 
	}
	StretchDIBits(
		hDCDst,
		0, 0, width, height,
		0, 0, BmInfo->bmiHeader.biWidth, BmInfo->bmiHeader.biHeight, 
		lpVHdr,BmInfo, DIB_RGB_COLORS, SRCCOPY); 
	/////////////////////////////////////////////////////////////////////////////////////////
}

static void CONVRGB2HSV(float r, float g, float b, float &h, float &s, float &v)
{
    float K = 0.f;
    if (g < b)
    {
         std::swap(g, b);
        K = -1.f;
    }
    float min_gb = b;
    if (r < g)
    {
        std::swap(r, g);
        K = -2.f / 6.f - K;
        min_gb = min(g, b);
    }
    float chroma = r - min_gb;
    h = fabs(K + (g - b) / (6.f * chroma + 1e-20f));
    s = chroma / (r + 1e-20f);
    v = r;
}

void RGBtoHSV(LPBYTE scr,LPBYTE dst,int H,int W)
{
	float R,G,B,h,s,v;

	for(int i = 0 ; i < H ; i++)
	{
		for(int j = 0; j < W ;j ++)
		{
			B = scr[3*(i*W+j)+0];
			G = scr[3*(i*W+j)+1];
			R = scr[3*(i*W+j)+2];

			CONVRGB2HSV(R,G,B,h,s,v);

			dst[3*(i*W+j)+0]=(BYTE)(h*255);
			dst[3*(i*W+j)+1]=(BYTE)(s*255);
			dst[3*(i*W+j)+2]=(BYTE)(v);

		}
	}
}
void RGBtoGRAY(LPBYTE scr,LPBYTE dst,int H,int W)
{
	float R,G,B;

	for(int i = 0 ; i < H ; i++)
	{
		for(int j = 0; j < W ;j ++)
		{
			B = scr[3*(i*W+j)+0];
			G = scr[3*(i*W+j)+1];
			R = scr[3*(i*W+j)+2];

			dst[(i*W+j)]=(BYTE)(R+G+B)/3;
		}
	}

}
void m_MorphologyBinaryDilation(int height, int width, const LPBYTE src, LPBYTE dest)
{
	int flagPassed;
	int r, i;
	int mx, my;
	float mean, sum;
	
	sum = 0;
	/*for (r = 0; r < height*width; r++)
	
		sum += *(src+r);
	mean = sum / (height*width);
	for (r = 0; r < height*width; r++)
	if (*(src + r)>mean) *(src + r) = (BYTE)0;
	else *(src + r) = (BYTE)255;
*/
	for (r = 0; r < height*width; r++)
		*(dest + r) = (BYTE)255;

	for (r = 0; r < height*width; r++)
	{
		flagPassed = 0;
		for (i = 1; i < m_pSEBinary[0].row; i++){
			mx = r%width + m_pSEBinary[i].col;
			my = r/width + m_pSEBinary[i].row;

			if (mx >= 0 && mx < width &&my >= 0 && my < height)
			if (*(src+width*my+mx) == (BYTE)0)
			{
				flagPassed = 1;
				break;
			}
		}

		if (flagPassed)
			*(dest+r) = (BYTE)0;
	}

}
void m_MorphologyBinaryErosion(int height, int width, const LPBYTE src, LPBYTE dest)
{
	int flagPassed;
	int r, i;
	int mx, my;
	float mean, sum;


	for (r = 0; r < height*width; r++)
		*(dest + r) = (BYTE)255;
	for (r = 0; r < height*width; r++)
	{
		flagPassed = 1;
		for (i = 1; i < m_pSEBinary[0].row; i++){
			mx = r%width + m_pSEBinary[i].col;
			my = r/width + m_pSEBinary[i].row;

			if (mx >= 0 && mx < width &&my >= 0 && my < height)
			if (*(src+my*width+mx) == (BYTE)255)
			{
				flagPassed = 0;
				break;
			}
		}
		if (flagPassed)
			*(dest + r) = (BYTE)0;
	}

}