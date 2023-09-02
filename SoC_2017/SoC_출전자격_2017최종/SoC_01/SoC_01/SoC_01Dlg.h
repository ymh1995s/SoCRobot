
// SoC_01Dlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "vfw.h"
#include "imgpro.h"
#pragma comment(lib, "Vfw32.lib")


// CSoC_01Dlg ��ȭ ����
class CSoC_01Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSoC_01Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SOC_01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CStatic m_cam1;
	CStatic m_cam2;
	HWND m_hWndCap;
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	void OnDestroy();
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonRed();
	afx_msg void OnBnClickedButtonGreen();
	afx_msg void OnBnClickedButtonBlue();
	afx_msg void OnBnClickedButtonYellow();
	CStatic m_cam3;
	CStatic m_cam4;
	CStatic m_cam5;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeMaxCbEdit();
	afx_msg void OnEnChangeMinCbEdit();
	afx_msg void OnEnChangeMaxCrEdit();
	afx_msg void OnEnChangeMinCrEdit();
	CEdit m_Max_Value;
	CEdit m_Min_Value;

	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	CEdit m_min_value;
	CEdit m_max_value;
	CString m_Fps;
};

LRESULT CALLBACK capCallbackOnFrame(HWND hWnd, LPVIDEOHDR lpVHdr);
void m_BorderFollow(int height, int width, LPBYTE src, LPBYTE dest, CString Color);
void m_BorderFollow2(int height, int width, LPBYTE src, LPBYTE dest, CString Color);
void m_BorderFollow3(int height, int width, LPBYTE src, LPBYTE dest);

