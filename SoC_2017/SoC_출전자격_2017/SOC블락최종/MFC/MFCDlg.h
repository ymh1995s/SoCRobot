
// MFCDlg.h : 헤더 파일
//

#pragma once

#include "afxwin.h"
#include "vfw.h"
#include "imgpro.h"
#pragma comment(lib, "Vfw32.lib")

// CMFCDlg 대화 상자
class CMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CStatic m_Cam1;
	CStatic m_Blue;
	CStatic m_Green;
	CStatic m_Yellow;
	CStatic m_Red;
	HWND m_hWndCap;
	CStatic m_subtract;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();	
	afx_msg void OnEnChangeEdit1();
	CString m_Fps;
	afx_msg void OnStnClickedCam1();
};
void m_BorderFollow2(int height, int width, LPBYTE src, LPBYTE dest);
void m_BorderFollow(int height, int width, LPBYTE src, LPBYTE dest);
void m_BorderFollow3(int height, int width, LPBYTE src, LPBYTE dest);
LRESULT CALLBACK capCallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr);