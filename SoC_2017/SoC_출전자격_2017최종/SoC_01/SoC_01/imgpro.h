
#pragma once
#include "stdafx.h"
#include "afxdialogex.h"
#define MAX_CORNER_NUM 5000
void m_MorphologyBinaryerosion(int height, int width);

struct HIST
{
	int ch1[256];
	int ch2[256];
	int ch3[256];
	int max;
	int min;
	HIST()
	{
		max = 0;
		min = 9000;
		ch1[0] = 0;
		ch2[0] = 0;
		ch3[0] = 0;
	}
};

typedef struct _CornerArr
{
	int count;
	int x[MAX_CORNER_NUM];
	int y[MAX_CORNER_NUM];
} CornerArr;
void m_SetStructureElementBinary(int which, int row, int col);
void m_FreeStructureElementBinary();
void m_AllocStructureElementBinary(int HowMany);


void img_copy(LPBYTE scr,LPBYTE dst,int H,int W,int channel);

void DrawToHDC( HDC hDCDst, CRect rect, unsigned char * lpVHdr ,BITMAPINFO *BmInfo);

static void CONVRGB2HSV(float r, float g, float b, float &h, float &s, float &v);

void RGBtoHSV(LPBYTE scr,LPBYTE dst,int H,int W);
void RGBtoGRAY(LPBYTE scr,LPBYTE dst,int H,int W);				
void m_MorphologyBinaryDilation(int height, int width, LPBYTE src, LPBYTE dest);
void m_MorphologyBinaryErosion(int height, int width, LPBYTE src, LPBYTE dest);
void RGBtoYCbCr(LPBYTE scr, LPBYTE dst, int H, int W);
static void CONVRGB2YCbCr(float r, float g, float b, float &Y, float &Cb, float &Cr);