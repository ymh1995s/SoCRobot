
// MFCDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include <ctime>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
int xcenter2 = 0;
int ycenter2 = 0;
int xcenter3 = 0;
int ycenter3 = 0;
int xcenter4 = 0;
int ycenter4 = 0;
int t = 0;
int s = 0;

int count4 = 0, count5 = 0, count6 = 0, count7 = 0;
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
public:
//	afx_msg void OnDestroy();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCDlg ��ȭ ����


BITMAPINFO BmInfo_Color, *BmInfo_Gray;
LPBYTE pImageBuffer_red_1, pImageBuffer_red_2, pImageBuffer_blue_1, pImageBuffer_blue_2, pImageBuffer_blue_3, pImageBuffer_blue_4, pImageBuffer_blue_5, pImageBuffer_blue_6, pImageBuffer_blue_7, pImageBuffer_blue_8, pImageBuffer_green_1, pImageBuffer_green_2, pImageBuffer_yellow_1, pImageBuffer_yellow_2;
LPBYTE pImageBuffer1, pImageBuffer2, pImageBuffer3, pImageBuffer4;
LPBYTE pHSVImageBuffer, Erosion_G, Erosion_R, Erosion_B, Erosion_Y, Dilation_G, Dilation_R, Dilation_B, Dilation_Y;

bool m_IsRed = TRUE;
bool m_IsBlue = TRUE;
bool m_IsGreen = TRUE;
bool m_IsYellow = TRUE;
int count = 0;
clock_t start, end;

CMFCDlg::CMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCDlg::IDD, pParent)

	, m_Fps(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pImageBuffer_red_1 = NULL; 
	pImageBuffer_red_2 = NULL;
	pImageBuffer_blue_1 = NULL;
	pImageBuffer_blue_2 = NULL;
	pImageBuffer_green_1 = NULL;
	pImageBuffer_green_2 = NULL;
	pImageBuffer_yellow_1 = NULL;
	pImageBuffer_yellow_2 = NULL;
	pImageBuffer1 = NULL;
	pImageBuffer2 = NULL;
	pImageBuffer3 = NULL;
	pImageBuffer4 = NULL;
	BmInfo_Gray = NULL;

}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAM1, m_Cam1);
	DDX_Control(pDX, IDC_BLUECAM, m_Blue);
	DDX_Control(pDX, IDC_GREENCAM, m_Green);
	DDX_Control(pDX, IDC_YELLOWCAM, m_Yellow);
	DDX_Control(pDX, IDC_REDCAM, m_Red);
	DDX_Control(pDX, IDC_SUBTRACTCAM, m_subtract);
	DDX_Text(pDX, IDC_FpsOut, m_Fps);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCDlg::OnBnClickedButton4)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CMFCDlg::OnBnClickedCancel)
	ON_STN_CLICKED(IDC_CAM1, &CMFCDlg::OnStnClickedCam1)
END_MESSAGE_MAP()


// CMFCDlg �޽��� ó����

BOOL CMFCDlg::OnInitDialog()
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
	m_Cam1.GetClientRect(rect);	//��Ʈ���� ũ��޾ƿ���

	m_hWndCap = capCreateCaptureWindow(_T("Capture Window"), WS_CHILD | WS_VISIBLE, rect.TopLeft().x, rect.TopLeft().y, rect.BottomRight().x, rect.BottomRight().y, m_Cam1, NULL);
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

	BmInfo_Gray = (BITMAPINFO*)new BITMAPINFO[(sizeof(BITMAPINFO)+256 * sizeof(RGBQUAD))];
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
	for (int i = 0; i<256; i++)
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

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDlg::OnPaint()
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
		if (m_IsRed != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_subtract.GetDC();
			m_subtract.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_red_2, BmInfo_Gray);
			ReleaseDC(pDC);	//������ ġ��.
		}

		else if (m_IsBlue != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_subtract.GetDC();
			m_subtract.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_blue_2, BmInfo_Gray);
			ReleaseDC(pDC);
		}
		else if (m_IsGreen != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_subtract.GetDC();
			m_subtract.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_green_2, BmInfo_Gray);
			ReleaseDC(pDC);
		}
		else if (m_IsYellow != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_subtract.GetDC();
			m_subtract.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer_yellow_2, BmInfo_Gray);
			ReleaseDC(pDC);
		}
		//if (pImageBuffer_red_1 != NULL)
		//{
		//	CDC *pDC;
		//	CRect rect;
		//	pDC = m_subtract.GetDC();
		//	m_subtract.GetClientRect(&rect);
		//	DrawToHDC(pDC->m_hDC, rect, pImageBuffer_red_1, BmInfo_Gray);
		//	ReleaseDC(pDC);
		//}
		//if (pImageBuffer_blue_1 != NULL)
		//{
		//	CDC *pDC;
		//	CRect rect;
		//	pDC = m_subtract.GetDC();
		//	m_subtract.GetClientRect(&rect);
		//	DrawToHDC(pDC->m_hDC, rect, pImageBuffer_blue_1, BmInfo_Gray);
		//	ReleaseDC(pDC);
		//}
		//if (pImageBuffer_green_1 != NULL)
		//{
		//	CDC *pDC;
		//	CRect rect;
		//	pDC = m_subtract.GetDC();
		//	m_subtract.GetClientRect(&rect);
		//	DrawToHDC(pDC->m_hDC, rect, pImageBuffer_green_1, BmInfo_Gray);
		//	ReleaseDC(pDC);
		//}
		//if (pImageBuffer_green_2 != NULL)
		//{
		//	CDC *pDC;
		//	CRect rect;
		//	pDC = m_subtract.GetDC();
		//	m_subtract.GetClientRect(&rect);
		//	DrawToHDC(pDC->m_hDC, rect, pImageBuffer_green_2, BmInfo_Gray);
		//	ReleaseDC(pDC);
		//}
		//if (pImageBuffer_yellow_1 != NULL)
		//{
		//	CDC *pDC;
		//	CRect rect;
		//	pDC = m_subtract.GetDC();
		//	m_subtract.GetClientRect(&rect);
		//	DrawToHDC(pDC->m_hDC, rect, pImageBuffer_yellow_1, BmInfo_Gray);
		//	ReleaseDC(pDC);
		//}
		//if (pImageBuffer_yellow_2 != NULL)
		//{
		//	CDC *pDC;
		//	CRect rect;
		//	pDC = m_subtract.GetDC();
		//	m_subtract.GetClientRect(&rect);
		//	DrawToHDC(pDC->m_hDC, rect, pImageBuffer_yellow_1, BmInfo_Gray);
		//	ReleaseDC(pDC);
		//}
		if (Dilation_R != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_Red.GetDC();
			m_Red.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, Dilation_R, BmInfo_Gray);
			ReleaseDC(pDC);
		}
		if (pImageBuffer2 != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_Blue.GetDC();
			m_Blue.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, pImageBuffer2, BmInfo_Gray);
			ReleaseDC(pDC);
		}
		if (Dilation_G != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_Green.GetDC();
			m_Green.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, Dilation_G, BmInfo_Gray);
			ReleaseDC(pDC);
		}
		if (Dilation_Y != NULL)
		{
			CDC *pDC;
			CRect rect;
			pDC = m_Yellow.GetDC();
			m_Yellow.GetClientRect(&rect);
			DrawToHDC(pDC->m_hDC, rect, Dilation_Y, BmInfo_Gray);
			ReleaseDC(pDC);
		}
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CALLBACK capCallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	start = clock();
	int xCenter = 0, yCenter = 0, index = 0;;
	int H = BmInfo_Gray->bmiHeader.biHeight;
	int W = BmInfo_Gray->bmiHeader.biWidth;
	//////////////////////////
	if (pHSVImageBuffer == NULL)
	{
		pHSVImageBuffer = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth * 3];
	}

	RGBtoHSV(lpVHdr->lpData, pHSVImageBuffer, H, W);
	
	if (m_IsRed)
	{
		if (pImageBuffer1 == NULL)
			pImageBuffer1 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_red_1 == NULL)
			pImageBuffer_red_1 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_red_2 == NULL)
			pImageBuffer_red_2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];

		if (Erosion_R == NULL)
			Erosion_R = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_R == NULL)
			Dilation_R = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];

		for (int i = 0; i < H * W; i++)  // 0 - H 1 - S 2 - V ����
		{
			if (((*(pHSVImageBuffer + (i * 3)) > 245)) || ((*(pHSVImageBuffer + (i * 3)) < 10)) &&
				((*(pHSVImageBuffer + (i * 3) + 1) > 85)) && ((*(pHSVImageBuffer + (i * 3) + 1) < 130)))
			{
				*(pImageBuffer1 + i) = (BYTE)255;
			}
			else *(pImageBuffer1 + i) = (BYTE)0;

			if (count == 0)
			{
				*(pImageBuffer_red_1 + i) = (BYTE)0;
				*(pImageBuffer_red_2 + i) = (BYTE)0;
			}
		}

		m_AllocStructureElementBinary(4);
		m_SetStructureElementBinary(0, 4, 0);
		m_SetStructureElementBinary(1, 0, -1);
		m_SetStructureElementBinary(2, 0, 0);
		m_SetStructureElementBinary(3, 0, 1);

		m_MorphologyBinaryErosion(H, W, pImageBuffer1, Erosion_R);
		m_MorphologyBinaryDilation(H, W, Erosion_R, Dilation_R);
		/*for (int i = 0; i < H * W; i++)
			*(Dilation_R + i) = *(Dilation_R + i) + *(pImageBuffer_red_2 + i);*/
		m_BorderFollow2(H, W, pImageBuffer_red_2, lpVHdr->lpData);
		m_BorderFollow(H, W, Dilation_R, lpVHdr->lpData);

		if (t == 0)
		{
			xCenter = xcenter3;
			yCenter = ycenter3;
		}

		if (s == 0)
		{
			xCenter = (xcenter2 + xcenter3) / 2;
			yCenter = (ycenter2 + ycenter3) / 2;
		}
		if (t != 0 && s != 0)
		{
			xCenter = (xcenter2 + xcenter3) / 2;
			yCenter = (ycenter2 + ycenter3) / 2;
		}

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 255;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 255;
		}
		if (count >= 3)
		{
			for (int i = 0; i < H*W; i++){
				*(pImageBuffer_red_2 + i) = *(pImageBuffer1 + i) - *(pImageBuffer_red_1 + i);
				if (*(pImageBuffer_red_2 + i) < 0) *(pImageBuffer_red_2 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_red_1 + i) = 0;
			count = 1;
		}

		else
		{
			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_red_1 + i) += *(pImageBuffer1 + i);
				if (*(pImageBuffer_red_1 + i) >= 255){
					*(pImageBuffer_red_1 + i) = 255;
				}

			}
			count++;
		}

		/*int index = 0, xCenter = 0, yCenter = 0, counter = 0;
		for (int i = 0; i < BmInfo_Gray->bmiHeader.biHeight; i++)
		{
		index = i*BmInfo_Gray->bmiHeader.biWidth;
		for (int j = 0; j < BmInfo_Gray->bmiHeader.biWidth; j++)
		{
		if (*(pImageBuffer1 + index + j) == 255)
		{
		xCenter += i;
		yCenter += j;
		counter++;
		}
		}
		}

		xCenter = (int)((float)xCenter / (float)counter);
		yCenter = (int)((float)yCenter / (float)counter);

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
		if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
		index = i*BmInfo_Gray->bmiHeader.biWidth;
		*(lpVHdr->lpData + 3 * (index + yCenter) + 0) = 0;
		*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 0;
		*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 255;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
		if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
		*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
		*(lpVHdr->lpData + 3 * (index + j) + 1) = 0;
		*(lpVHdr->lpData + 3 * (index + j) + 2) = 255;
		}
		*/
	}

	if (m_IsBlue)
	{
		if (pImageBuffer2 == NULL)
			pImageBuffer2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_B == NULL)
			Erosion_B = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_B == NULL)
			Dilation_B = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_1 == NULL)
			pImageBuffer_blue_1 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_2 == NULL)
			pImageBuffer_blue_2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_3 == NULL)
			pImageBuffer_blue_3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_4 == NULL)
			pImageBuffer_blue_4 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_5 == NULL)
			pImageBuffer_blue_5 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_6 == NULL)
			pImageBuffer_blue_6 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_7 == NULL)
			pImageBuffer_blue_7 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_blue_8 == NULL)
			pImageBuffer_blue_8 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		for (int i = 0; i < H * W; i++)  // 0 - H 1 - S 2 - V ����
		{
			if (((*(pHSVImageBuffer + (i * 3)) < 155) && (*(pHSVImageBuffer + (i * 3)) > 145)) &&
				((*(pHSVImageBuffer + (i * 3) + 1) > 130)))
			{
				*(pImageBuffer2 + i) = (BYTE)255;
			}
			else *(pImageBuffer2 + i) = (BYTE)0;
			if (count4 == 0)
			{
				*(pImageBuffer_blue_1 + i) = (BYTE)0;
				*(pImageBuffer_blue_2 + i) = (BYTE)0;
				*(pImageBuffer_blue_3 + i) = (BYTE)0;
				*(pImageBuffer_blue_4 + i) = (BYTE)0;
				*(pImageBuffer_blue_5 + i) = (BYTE)0;
				*(pImageBuffer_blue_6 + i) = (BYTE)0;
				*(pImageBuffer_blue_7 + i) = (BYTE)0;
				*(pImageBuffer_blue_8 + i) = (BYTE)0;
			}
		}
		m_BorderFollow3(H, W, pImageBuffer_blue_2, lpVHdr->lpData);
		m_BorderFollow3(H, W, pImageBuffer_blue_4, lpVHdr->lpData);
		m_BorderFollow3(H, W, pImageBuffer_blue_6, lpVHdr->lpData);
		m_BorderFollow3(H, W, pImageBuffer_blue_8, lpVHdr->lpData);

		if (count4 >= 5)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_blue_2 + i) = *(pImageBuffer2 + i) - *(pImageBuffer_blue_1 + i);
				if (*(pImageBuffer_blue_2 + i) < 0) *(pImageBuffer_blue_2 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_blue_1 + i) = 0;

			count4 = 1;
		}

		if (count5 >= 6)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_blue_4 + i) = *(pImageBuffer2 + i) - *(pImageBuffer_blue_3 + i);
				if (*(pImageBuffer_blue_4 + i) < 0) *(pImageBuffer_blue_4 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_blue_3 + i) = 0;

			count5 = 2;
		}

		if (count6 >= 7)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_blue_6 + i) = *(pImageBuffer2 + i) - *(pImageBuffer_blue_5 + i);
				if (*(pImageBuffer_blue_6 + i) < 0) *(pImageBuffer_blue_6 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_blue_5 + i) = 0;

			count6 = 3;
		}

		if (count7 >= 8)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_blue_8 + i) = *(pImageBuffer2 + i) - *(pImageBuffer_blue_7 + i);
				if (*(pImageBuffer_blue_8 + i) < 0) *(pImageBuffer_blue_8 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_blue_7 + i) = 0;

			count7 = 4;
		}

		else
		{
			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_blue_1 + i) += *(pImageBuffer2 + i);
				if (*(pImageBuffer_blue_1 + i) >= 255)
				{
					*(pImageBuffer_blue_1 + i) = 255;
				}

			}
			count4++;
			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_blue_3 + i) += *(pImageBuffer2 + i);
				if (*(pImageBuffer_blue_3 + i) >= 255)
				{
					*(pImageBuffer_blue_3 + i) = 255;
				}

			}
			count5++;

			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_blue_5 + i) += *(pImageBuffer2 + i);
				if (*(pImageBuffer_blue_5 + i) >= 255)
				{
					*(pImageBuffer_blue_5 + i) = 255;
				}

			}
			count6++;
			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_blue_7 + i) += *(pImageBuffer2 + i);
				if (*(pImageBuffer_blue_7 + i) >= 255)
				{
					*(pImageBuffer_blue_7 + i) = 255;
				}

			}
			count7++;
		}
		/*int index = 0, xCenter = 0, yCenter = 0, counter = 0;
		for (int i = 0; i < BmInfo_Gray->bmiHeader.biHeight; i++)
		{
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			for (int j = 0; j < BmInfo_Gray->bmiHeader.biWidth; j++)
			{
				if (*(pImageBuffer2 + index + j) == 255)
				{
					xCenter += i;
					yCenter += j;
					counter++;
				}
			}
		}

		xCenter = (int)((float)xCenter / (float)counter);
		yCenter = (int)((float)yCenter / (float)counter);

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 0) = 255;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 0;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 255;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 0;
		}*/
	}

/*
	if(m_IsBlue)
	{
		if (pImageBuffer2 == NULL)
			pImageBuffer2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth * 3];

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if ((((pHSVImageBuffer[3 * (i * W + j) + 0] > 145)) && ((pHSVImageBuffer[3 * (i * W + j) + 0] < 155))) &&
					(pHSVImageBuffer[3 * (i * W + j) + 1] > 150))
				{
					pImageBuffer2[3 * (i * W + j) + 0] = lpVHdr->lpData[3 * (i * W + j) + 0];
					pImageBuffer2[3 * (i * W + j) + 1] = lpVHdr->lpData[3 * (i * W + j) + 1];
					pImageBuffer2[3 * (i * W + j) + 2] = lpVHdr->lpData[3 * (i * W + j) + 2];
				}
				else
				{
					pImageBuffer2[3 * (i * W + j) + 0] = (BYTE)0;
					pImageBuffer2[3 * (i * W + j) + 1] = (BYTE)0;
					pImageBuffer2[3 * (i * W + j) + 2] = (BYTE)0;
				}
			}
		}
	}
*/
	if (m_IsGreen)
	{
		if (pImageBuffer3 == NULL)
			pImageBuffer3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_G == NULL)
			Erosion_G = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_G == NULL)
			Dilation_G = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_green_1 == NULL)
			pImageBuffer_green_1 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_green_2 == NULL)
			pImageBuffer_green_2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		for (int i = 0; i < H * W; i++)
		{
			if (((*(pHSVImageBuffer + (i * 3)) <100) && (*(pHSVImageBuffer + (i * 3)) > 70)) &&
				((*(pHSVImageBuffer + (i * 3) + 1) >70)) && ((*(pHSVImageBuffer + (i * 3) + 2) >50)))
			{
				*(pImageBuffer3 + i) = (BYTE)255;
			}
			else *(pImageBuffer3 + i) = (BYTE)0;
			if (count == 0)
			{
				*(pImageBuffer_green_1 + i) = (BYTE)0;
				*(pImageBuffer_green_2 + i) = (BYTE)0;
			}
		}
		
		
		/*int index = 0, xCenter = 0, yCenter = 0, counter = 0;
		for (int i = 0; i < BmInfo_Gray->bmiHeader.biHeight; i++)
		{
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			for (int j = 0; j < BmInfo_Gray->bmiHeader.biWidth; j++)
			{
				if (*(pImageBuffer3 + index + j) == 255)
				{
					xCenter += i;
					yCenter += j;
					counter++;
				}
			}
		}

		xCenter = (int)((float)xCenter / (float)counter);
		yCenter = (int)((float)yCenter / (float)counter);

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 0) =0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 0;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 0;
		}
*/
		m_AllocStructureElementBinary(4);
		m_SetStructureElementBinary(0, 4, 0);
		m_SetStructureElementBinary(1, 0, -1);
		m_SetStructureElementBinary(2, 0, 0);
		m_SetStructureElementBinary(3, 0, 1);
		m_MorphologyBinaryErosion(H, W, pImageBuffer3, Erosion_G);
		m_MorphologyBinaryDilation(H, W, Erosion_G, Dilation_G);
		m_BorderFollow2(H, W, pImageBuffer_green_2, lpVHdr->lpData);
		m_BorderFollow(H, W, Dilation_G, lpVHdr->lpData);

		if (t == 0)
		{
			xCenter = xcenter3;
			yCenter = ycenter3;
		}

		if (s == 0)
		{
			xCenter = (xcenter2 + xcenter3) / 2;
			yCenter = (ycenter2 + ycenter3) / 2;
		}
		if (t != 0 && s != 0)
		{
			xCenter = (xcenter2 + xcenter3) / 2;
			yCenter = (ycenter2 + ycenter3) / 2;
		}

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 0;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 0;
		}
		if (count >= 3)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_green_2 + i) = *(pImageBuffer3 + i) - *(pImageBuffer_green_1 + i);
				if (*(pImageBuffer_green_2 + i) < 0) *(pImageBuffer_green_2 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_green_1 + i) = 0;

			count = 1;
		}

		else
		{
			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_green_1 + i) += *(pImageBuffer3 + i);
				if (*(pImageBuffer_green_1 + i) >= 255) {
					*(pImageBuffer_green_1 + i) = 255;
				}

			}
			count++;
		}

		//////////////////////Į������/////////////////////
		////initial values for the kalman filter    
		//float x_est_last = 0;
		//float P_last = 0;

		//the noise in the system     

		//float Q = 0.022;
		//float R = 0.617;
		//float K;
		//float P;
		//float P_temp;
		//float x_temp_est;
		//float x_est;

		//float z_measured;
		////the 'noisy' value we measured   
		//float z_real = 0.5;
		////the ideal value we wish to measure         
		//srand(0);
		////initialize with a measurement     
		//x_est_last = z_real + 2 * (xCenter / 320 - 0.5)*0.09;
		//float sum_error_kalman = 0;
		//float sum_error_measure = 0;
		//for (int i = 0; i < 30; i++) {
		//	//do a prediction         
		//	x_temp_est = x_est_last;
		//	P_temp = P_last + Q;
		//	//calculate the Kalman gain         
		//	K = P_temp * (1.0 / (P_temp + R));
		//	//measure         
		//	z_measured = z_real + 2 * (xCenter / 320 - 0.5)*0.09;
		//	//the real measurement plus noise        
		//	//correct         
		//	x_est = x_temp_est + K * (z_measured - x_temp_est);
		//	P = (1 - K) * P_temp;
		//	//we have our new system                  
		//	printf("Ideal position: %6.3f \n", z_real);
		//	printf("Mesaured position: %6.3f [diff:%.3f]\n", z_measured, fabs(z_real - z_measured));
		//	printf("Kalman position: %6.3f [diff:%.3f]\n", x_est, fabs(z_real - x_est));
		//	sum_error_kalman += fabs(z_real - x_est);
		//	sum_error_measure += fabs(z_real - z_measured);
		//	//update our last's         
		//	P_last = P;
		//	x_est_last = x_est;

		//}
	}
	
	
	/*
	if (m_IsGreen)
	{
		if (pImageBuffer3 == NULL)
			pImageBuffer3 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth * 3];

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if ((((pHSVImageBuffer[3 * (i * W + j) + 0] > 70)) && ((pHSVImageBuffer[3 * (i * W + j) + 0] < 90))) &&
					(pHSVImageBuffer[3 * (i * W + j) + 1] > 80))
				{
					pImageBuffer3[3 * (i * W + j) + 0] = lpVHdr->lpData[3 * (i * W + j) + 0];
					pImageBuffer3[3 * (i * W + j) + 1] = lpVHdr->lpData[3 * (i * W + j) + 1];
					pImageBuffer3[3 * (i * W + j) + 2] = lpVHdr->lpData[3 * (i * W + j) + 2];
				}
				else
				{
					pImageBuffer3[3 * (i * W + j) + 0] = (BYTE)0;
					pImageBuffer3[3 * (i * W + j) + 1] = (BYTE)0;
					pImageBuffer3[3 * (i * W + j) + 2] = (BYTE)0;
				}
			}
		}
	}
	*/
	if (m_IsYellow)
	{
		if (pImageBuffer4 == NULL)
			pImageBuffer4 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Erosion_Y == NULL)
			Erosion_Y = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (Dilation_Y == NULL)
			Dilation_Y = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_yellow_1 == NULL)
			pImageBuffer_yellow_1 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		if (pImageBuffer_yellow_2 == NULL)
			pImageBuffer_yellow_2 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth];
		for (int i = 0; i < H * W; i++)
		{
			if (((*(pHSVImageBuffer + (i * 3)) <70) && (*(pHSVImageBuffer + (i * 3)) > 20)) && ((*(pHSVImageBuffer + (i * 3) + 1) > 80)))
			{
				*(pImageBuffer4 + i) = (BYTE)255;
			}
			else *(pImageBuffer4 + i) = (BYTE)0;
			if (count == 0)
			{
				*(pImageBuffer_yellow_1 + i) = (BYTE)0;
				*(pImageBuffer_yellow_2 + i) = (BYTE)0;
			}
		}

		/*int index = 0, xCenter = 0, yCenter = 0, counter = 0;
		for (int i = 0; i < BmInfo_Gray->bmiHeader.biHeight; i++)
		{
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			for (int j = 0; j < BmInfo_Gray->bmiHeader.biWidth; j++)
			{
				if (*(pImageBuffer4 + index + j) == 255)
				{
					xCenter += i;
					yCenter += j;
					counter++;
				}
			}
		}

		xCenter = (int)((float)xCenter / (float)counter);
		yCenter = (int)((float)yCenter / (float)counter);

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 255;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 255;
		}*/

		m_AllocStructureElementBinary(4);
		m_SetStructureElementBinary(0, 4, 0);
		m_SetStructureElementBinary(1, 0, -1);
		m_SetStructureElementBinary(2, 0, 0);
		m_SetStructureElementBinary(3, 0, 1);
		m_MorphologyBinaryErosion(H, W, pImageBuffer4, Erosion_Y);
		m_MorphologyBinaryDilation(H, W, Erosion_Y, Dilation_Y);
		m_BorderFollow2(H, W, pImageBuffer_yellow_2, lpVHdr->lpData);
		m_BorderFollow(H, W, Dilation_Y, lpVHdr->lpData);

		if (t == 0)
		{
			xCenter = xcenter3;
			yCenter = ycenter3;
		}

		if (s == 0)
		{
			xCenter = (xcenter2 + xcenter3) / 2;
			yCenter = (ycenter2 + ycenter3) / 2;
		}
		if (t != 0 && s != 0)
		{
			xCenter = (xcenter2 + xcenter3) / 2;
			yCenter = (ycenter2 + ycenter3) / 2;
		}

		for (int i = xCenter - 15; i <= xCenter + 15; i++)
		{
			if (i < 0 || i >= BmInfo_Gray->bmiHeader.biHeight) continue;
			index = i*BmInfo_Gray->bmiHeader.biWidth;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + yCenter) + 2) = 0;
		}

		index = xCenter*BmInfo_Gray->bmiHeader.biWidth;

		for (int j = yCenter - 15; j < yCenter + 15; j++)
		{
			if (j < 0 || j >= BmInfo_Gray->bmiHeader.biWidth)  continue;
			*(lpVHdr->lpData + 3 * (index + j) + 0) = 0;
			*(lpVHdr->lpData + 3 * (index + j) + 1) = 255;
			*(lpVHdr->lpData + 3 * (index + j) + 2) = 0;
		}
		if (count >= 3)
		{
			for (int i = 0; i < H*W; i++) {
				*(pImageBuffer_yellow_2 + i) = *(pImageBuffer4 + i) - *(pImageBuffer_yellow_1 + i);
				if (*(pImageBuffer_yellow_2 + i) < 0) *(pImageBuffer_yellow_2 + i) = 0;
			}

			for (int i = 0; i < H*W; i++)
				*(pImageBuffer_yellow_1 + i) = 0;

			count = 1;
		}

		else
		{
			for (int i = 0; i < H*W; i++)
			{

				*(pImageBuffer_yellow_1 + i) += *(pImageBuffer4 + i);
				if (*(pImageBuffer_yellow_1 + i) >= 255) {
					*(pImageBuffer_yellow_1 + i) = 255;
				}

			}
			count++;
		}
	}
	//if (m_IsYellow)
	//{
	//	if (pImageBuffer4 == NULL)
	//		pImageBuffer4 = (LPBYTE)new BYTE[BmInfo_Gray->bmiHeader.biHeight * BmInfo_Gray->bmiHeader.biWidth * 3];

	//	for (int i = 0; i < H; i++)
	//	{
	//		for (int j = 0; j < W; j++)
	//		{
	//			if ((((pHSVImageBuffer[3 * (i * W + j) + 0] > 35)) && ((pHSVImageBuffer[3 * (i * W + j) + 0] < 46))) &&
	//				(pHSVImageBuffer[3 * (i * W + j) + 1] > 150))
	//			{
	//				pImageBuffer4[3 * (i * W + j) + 0] = lpVHdr->lpData[3 * (i * W + j) + 0];
	//				pImageBuffer4[3 * (i * W + j) + 1] = lpVHdr->lpData[3 * (i * W + j) + 1];
	//				pImageBuffer4[3 * (i * W + j) + 2] = lpVHdr->lpData[3 * (i * W + j) + 2];
	//			}
	//			else
	//			{
	//				pImageBuffer4[3 * (i * W + j) + 0] = (BYTE)0;
	//				pImageBuffer4[3 * (i * W + j) + 1] = (BYTE)0;
	//				pImageBuffer4[3 * (i * W + j) + 2] = (BYTE)0;
	//			}
	//		}
	//	}
	//}
	
	end = clock();
	CMFCDlg *pDlg = (CMFCDlg*)AfxGetMainWnd();
	pDlg->Invalidate(false);

	pDlg->m_Fps.Format(_T("FPS : %f"), 1 / (((double)end - (double)start) / CLOCKS_PER_SEC));
	pDlg->UpdateData(FALSE);
	return (LRESULT)true;
}

void CMFCDlg::OnBnClickedButton1()
{
	if (m_IsRed) m_IsRed = FALSE;
	else m_IsRed = TRUE;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCDlg::OnBnClickedButton2()
{
	if (m_IsBlue) m_IsBlue = FALSE;
	else m_IsBlue = TRUE;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCDlg::OnBnClickedButton3()
{
	if (m_IsGreen) m_IsGreen = FALSE;
	else m_IsGreen = TRUE;
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCDlg::OnBnClickedButton4()
{
	if (m_IsYellow) m_IsYellow = FALSE;
	else m_IsYellow = TRUE;
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
		capDriverDisconnect(m_hWndCap);
		if (pImageBuffer1 != NULL) delete[] pImageBuffer1;
		if (pImageBuffer2 != NULL) delete[] pImageBuffer2;
		if (pImageBuffer3 != NULL) delete[] pImageBuffer3;
		if (pImageBuffer4 != NULL) delete[] pImageBuffer4;
		if (pImageBuffer_red_1 != NULL) delete[] pImageBuffer_red_1;
		if (pImageBuffer_red_2 != NULL) delete[] pImageBuffer_red_2;
		if (Dilation_R != NULL) delete[] Dilation_R;
		if (Erosion_R != NULL) delete[] Erosion_R;
		if (Dilation_G != NULL) delete[] Dilation_G;
		if (Erosion_G != NULL) delete[] Erosion_G;
		if (Dilation_B != NULL) delete[] Dilation_B;
		if (Erosion_B != NULL) delete[] Erosion_B;
		if (Dilation_Y != NULL) delete[] Dilation_Y;
		if (Erosion_Y != NULL) delete[] Erosion_Y;
		m_FreeStructureElementBinary();
		/*if (pImageBuffer_blue_1 != NULL) delete[] pImageBuffer_blue_1;
		if (pImageBuffer_blue_2 != NULL) delete[] pImageBuffer_blue_2;
		if (pImageBuffer_green_1 != NULL) delete[] pImageBuffer_green_1;
		if (pImageBuffer_green_2 != NULL) delete[] pImageBuffer_green_2;
		if (pImageBuffer_yellow_1 != NULL) delete[] pImageBuffer_yellow_1;
		if (pImageBuffer_yellow_2 != NULL) delete[] pImageBuffer_yellow_2;*/

}


void CMFCDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void m_BorderFollow(int height, int width, LPBYTE src, LPBYTE dest)
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
				if ((border_count<150)||(border_count>200)) continue; // �ʹ����� ������ ����̸� �����Ѵ�.  

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




	// ȭ�鿡 ��踦 ����ϱ� ���� m_OutImg�迭�� �̿�����. 
	//memset(dest, 255, height*width*sizeof(char));
	for (k = 0; k<numberBorder; k++)
	{
		
		TRACE("(%d: %d %d, %d)\r\n", k, stBorderInfo[k].n, stBorderInfo[k].dn, (int)(sqrt(2.0)*stBorderInfo[k].dn) + (stBorderInfo[k].n - stBorderInfo[k].dn));

		for (int i = 0; i<stBorderInfo[k].n; i++)
		{
			x = x + stBorderInfo[k].x[i];
			y = y + stBorderInfo[k].y[i];
			counter++;
			//for (int a = 0; a < 3; a++) {
			//for (int b = 0; b < 3; b++) {
			/*dest[3 * (x*(width - 1 + a) + y - 1 + b) + 0] = (BYTE)0;
			dest[3 * (x*(width - 1 + a) + y - 1 + b) + 1] = (BYTE)0;
			dest[3 * (x*(width - 1 + a) + y - 1 + b) + 2 ] = (BYTE)0;*/
			//}
			//}
			/*dest[3 * (x*width + y) + 0] = (BYTE)0;
			dest[3 * (x*width + y) + 1] = (BYTE)0;
			dest[3 * (x*width + y) + 2] = (BYTE)0;*/
		}
		for (k = 0; k < numberBorder; k++) {
			xCenter += (int)((float)x / (float)counter);
			yCenter += (int)((float)y / (float)counter);
		}
		xCenter = xCenter/ numberBorder;
		yCenter = yCenter/ numberBorder;
		xcenter2 = xCenter;
		ycenter2 = yCenter;
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
	}
	if (numberBorder >= 1)
	{
		xcenter2 = xCenter;
		ycenter2 = yCenter;
		s = 0;
	}
	if (numberBorder == 0)
	{
		
		s = 1;
	}
	
	for (k = 0; k<numberBorder; k++) { delete[]stBorderInfo[k].x; delete[]stBorderInfo[k].y; }
	delete[]visited; delete[]xchain; delete[]ychain;
}

void m_BorderFollow2(int height, int width, LPBYTE src, LPBYTE dest)
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
				if ((border_count<50) || (border_count>400)) continue; // �ʹ����� ������ ����̸� �����Ѵ�.  

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
	for (k = 0; k<numberBorder; k++)
	{

		TRACE("(%d: %d %d, %d)\r\n", k, stBorderInfo[k].n, stBorderInfo[k].dn, (int)(sqrt(2.0)*stBorderInfo[k].dn) + (stBorderInfo[k].n - stBorderInfo[k].dn));

		for (int i = 0; i<stBorderInfo[k].n; i++)
		{
			x = x + stBorderInfo[k].x[i];
			y = y + stBorderInfo[k].y[i];
			counter++;
			//for (int a = 0; a < 3; a++) {
			//for (int b = 0; b < 3; b++) {
			/*dest[3 * (x*(width - 1 + a) + y - 1 + b) + 0] = (BYTE)0;
			dest[3 * (x*(width - 1 + a) + y - 1 + b) + 1] = (BYTE)0;
			dest[3 * (x*(width - 1 + a) + y - 1 + b) + 2 ] = (BYTE)0;*/
			//}
			//}
			/*dest[3 * (x*width + y) + 0] = (BYTE)0;
			dest[3 * (x*width + y) + 1] = (BYTE)0;
			dest[3 * (x*width + y) + 2] = (BYTE)0;*/
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
		xcenter3 = xCenter;
		ycenter3 = yCenter;
	}
	if (numberBorder >= 1)
	{
		xcenter3 = xCenter;
		ycenter3 = yCenter;
		t = 0;
	}

	if (numberBorder == 0)
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

void CMFCDlg::OnStnClickedCam1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
