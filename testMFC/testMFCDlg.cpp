
// testMFCDlg.cpp : implementation file
//

#include "pch.h"

#include "framework.h"
#include "testMFC.h"
#include "testMFCDlg.h"
#include "afxdialogex.h"
#include "Apple.h"
#include "Snake.h"
#include "ModeDispatcher.h"
#include "constants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

std::unique_ptr<ModeDispatcher> dispatcher_;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestMFCDlg dialog

CtestMFCDlg::CtestMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CtestMFCDlg message handlers

BOOL CtestMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	dispatcher_ = make_unique<ModeDispatcher>(this);

	SetTimer(1, 150, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CtestMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework



__forceinline void CtestMFCDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	dispatcher_->currentMode->OnKeyDown(dispatcher_.get(), nChar);
}

void CtestMFCDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize.x = static_cast<LONG>(816);
	lpMMI->ptMinTrackSize.y = static_cast<LONG>(539);

	lpMMI->ptMaxTrackSize.x = static_cast<LONG>(816);
	lpMMI->ptMaxTrackSize.y = static_cast<LONG>(539);
}

__inline void CtestMFCDlg::OnTimer(UINT_PTR uTime)
{
	if ((uTime == 1 && dispatcher_->GetMode() != Modes::GAME) || (uTime == 2 && dispatcher_->GetMode() == Modes::GAME))
		RedrawWindow();
}

__forceinline BOOL CtestMFCDlg::OnEraseBkgnd(CDC* pDC)
{
	return static_cast<BOOL>(true);
}

void CtestMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		CDC* dc = GetDC();

		CDC dc_mem;
		dc_mem.CreateCompatibleDC(dc);

		CRect rectWindow;
		GetClientRect(&rectWindow);

		CRgn rgn;
		rgn.CreateRectRgn(0, 0, rectWindow.Width(), rectWindow.Height());
		dc->SelectClipRgn(&rgn);

		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(dc, rectWindow.Width(), rectWindow.Height());
		CBitmap* pOldBit = dc_mem.SelectObject(&bitmap);

		/*---------------------------------------------------------------------------------*/

		dispatcher_->currentMode->Draw(dispatcher_.get(), &dc_mem);

		/*---------------------------------------------------------------------------------*/

		dc_mem.SetStretchBltMode(HALFTONE);
		dc->BitBlt(0, 0, rectWindow.Width(), rectWindow.Height(), &dc_mem, 0, 0, SRCCOPY);


		dc->SelectClipRgn(nullptr);
		dc_mem.DeleteDC();
		bitmap.DeleteObject();
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
__forceinline HCURSOR CtestMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}