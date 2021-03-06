#pragma once

#include <memory>

// CtestMFCDlg dialog
class CtestMFCDlg : public CDialogEx
{
// Construction
public:
	CtestMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	__forceinline void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg
	__inline void OnTimer(UINT_PTR uTime);
	__forceinline BOOL OnEraseBkgnd(CDC* pDC);
	void OnPaint();
	afx_msg __forceinline HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
