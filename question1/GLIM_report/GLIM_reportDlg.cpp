
// GLIM_reportDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIM_report.h"
#include "GLIM_reportDlg.h"
#include "afxdialogex.h"

#include "VIEW_Info.h"   // VIEW_Info 클래스 정의 포함
#include "VIEW_Image.h"  // VIEW_Image 클래스 정의 포함

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGLIMreportDlg* pMainDlg = nullptr;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CGLIMreportDlg 대화 상자



CGLIMreportDlg::CGLIMreportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_REPORT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMreportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIEW_INFO, m_LayoutViewInfo);
	DDX_Control(pDX, IDC_VIEW_Image, m_LayoutViewImage);
}

BEGIN_MESSAGE_MAP(CGLIMreportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CGLIMreportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	pMainDlg = this;

	
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

	// setting monitor resolution
	theApp.m_dWidthRatio = (double)GetSystemMetrics(SM_CXSCREEN) / DevelopScreenWidth;
	theApp.m_dHeightRatio = (double)GetSystemMetrics(SM_CYSCREEN) / DevelopScreenHeight;
	m_dScreenWidth = Size_MainVIEW_Width * theApp.m_dWidthRatio;
	m_dScreenHeight = Size_MainVIEW_Height * theApp.m_dHeightRatio;
	theApp.m_dScreenWidth = m_dScreenWidth;
	theApp.m_dScreenHeight = m_dScreenHeight;
	// setting dialog pos
	SetWindowPos(NULL, 0, 0, m_dScreenWidth, m_dScreenHeight, SWP_NOMOVE);

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// setting View Layout
	const int WINDOW_MARGIN = 10;
	const int HEIGHT_ADJUSTMENT = 60;

	// View [Info] Layout
	m_sViewInfoCoord.dWidth = (theApp.m_dScreenWidth / 4) - WINDOW_MARGIN;
	m_sViewInfoCoord.dHeight = theApp.m_dScreenHeight - HEIGHT_ADJUSTMENT;
	m_sViewInfoCoord.nStartX = WINDOW_MARGIN + 5;
	m_sViewInfoCoord.nStartY = WINDOW_MARGIN + 5;

	m_LayoutViewInfo.SetWindowPos(NULL, m_sViewInfoCoord.nStartX, m_sViewInfoCoord.nStartY,
		m_sViewInfoCoord.dWidth, m_sViewInfoCoord.dHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// View [Image] Layout
	m_sViewImageCoord.dWidth = (theApp.m_dScreenWidth / 4) * 3 - (WINDOW_MARGIN * 5);
	m_sViewImageCoord.dHeight = theApp.m_dScreenHeight - HEIGHT_ADJUSTMENT;
	m_sViewImageCoord.nStartX = m_sViewInfoCoord.dWidth + WINDOW_MARGIN *2;
	m_sViewImageCoord.nStartY = WINDOW_MARGIN + 5;

	m_LayoutViewImage.SetWindowPos(NULL, m_sViewImageCoord.nStartX, m_sViewImageCoord.nStartY,
		m_sViewImageCoord.dWidth, m_sViewImageCoord.dHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	
	SetWindowText(_T("GLIM SW REPORT"));


	if (!ParamCheck()) {
		AfxMessageBox(_T("paramater File Check."));
	}


	AllocForms();

	// for ui initialize
	SetTimer(1, 10, NULL);
	

	return TRUE;
}

void CGLIMreportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGLIMreportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CGLIMreportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGLIMreportDlg::AllocForms() {
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));
	
	CRect rect;
	// info view
	m_LayoutViewInfo.GetWindowRect(&rect);
	m_pViewInfo = new VIEW_Info(m_sViewInfoCoord.nStartX, m_sViewInfoCoord.nStartY,
									m_sViewInfoCoord.dWidth, m_sViewInfoCoord.dHeight);
	m_pViewInfo->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rect, this, IDC_VIEW_INFO, &context);
	m_pViewInfo->OnInitialUpdate();
	m_pViewInfo->ShowWindow(SW_SHOW);

	// image view
	m_LayoutViewImage.GetWindowRect(&rect);
	m_pViewImage = new VIEW_Image(m_sViewImageCoord.nStartX, m_sViewImageCoord.nStartY,
									m_sViewImageCoord.dWidth, m_sViewImageCoord.dHeight);
	m_pViewImage->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rect, this, IDC_VIEW_INFO, &context);
	m_pViewImage->OnInitialUpdate();
	m_pViewImage->ShowWindow(SW_SHOW);
}


BOOL CGLIMreportDlg::DestroyWindow()
{
	if (m_pViewInfo != NULL)
		m_pViewInfo->DestroyWindow();

	if (m_pViewImage != NULL)
		m_pViewImage->DestroyWindow();

	return CDialogEx::DestroyWindow();
}

bool CGLIMreportDlg::ParamCheck() {

	// DIR ./save/
	if(GetFileAttributes(PATH_SAVEBMP) == INVALID_FILE_ATTRIBUTES)
		CreateDirectory(PATH_SAVEBMP, NULL);
	// DIR ./save/draw
	if (GetFileAttributes(PATH_DRAWBMP) == INVALID_FILE_ATTRIBUTES)
		CreateDirectory(PATH_DRAWBMP, NULL);
	// DIR ./save/action
	if (GetFileAttributes(PATH_ACTIONBMP) == INVALID_FILE_ATTRIBUTES)
		CreateDirectory(PATH_ACTIONBMP, NULL);
	// DIR ./save/random
	if (GetFileAttributes(PATH_RANDOMBMP) == INVALID_FILE_ATTRIBUTES)
		CreateDirectory(PATH_RANDOMBMP, NULL);
	// DIR ./log/
	if (GetFileAttributes(PATH_LOG) == INVALID_FILE_ATTRIBUTES)
		CreateDirectory(PATH_LOG, NULL);

	return true;
}

void CGLIMreportDlg::SetCirclePos_Start(int x, int y) {
	m_pViewImage->SetCircleStart({x, y});
}
void CGLIMreportDlg::SetCirclePos_End(int x, int y) {
	m_pViewImage->SetCircleEnd({ x, y});
}

void CGLIMreportDlg::Draw_Circle() {
	int nMaxValue = 101;
	int nRadius = rand() % nMaxValue;

	m_pViewImage->SetCImage();
	m_pViewImage->DrawCircle(nRadius);

	CString cstr;
	cstr.Format(PATH_DRAWBMP + _T("%04d.bmp"), 1);

	CString cstrLog = GetTime() + cstr +_T("draw Success");
	m_pViewInfo->WriteLog(cstrLog);
}

void CGLIMreportDlg::MoveCircle_ImageView() {

	m_pViewImage->SetCImage();
	m_pViewImage->SetCircleMoving(true);

	int cnt = 1;
	while (m_pViewImage->GetCircleMoving()) {
		m_pViewImage->MoveCircle();

		CString cstr;
		cstr.Format(PATH_ACTIONBMP + _T("%04d.bmp"), cnt);	
		cnt++;

		
		m_pViewImage->SaveCImage(cstr);
		CString cstrLog = GetTime() + cstr + _T("Action Success");
		m_pViewInfo->WriteLog(cstrLog);
	}
}

void CGLIMreportDlg::Draw_Random(int count) {
	m_pViewImage->SetCImage();
	GetTime();

	for (int i = 0; i < count; i++) {
		m_pViewImage->DrawRandomCircle();

		CString cstr;
		cstr.Format(PATH_RANDOMBMP + _T("%04d.bmp"), i);

		m_pViewImage->SaveCImage(cstr);

		CString cstrLog = GetTime() + cstr + _T("Raondom Success");
		m_pViewInfo->WriteLog(cstrLog);
		Sleep(100);	//delay
	}
}


void CGLIMreportDlg::OpenBmp(CString cstrPath) {
	m_pViewImage->OpenCImage(cstrPath);

	WPARAM wP = m_pViewImage->GetCircleOpenPos().x;
	LPARAM lP = m_pViewImage->GetCircleOpenPos().y;
	::SendMessage(m_pViewInfo->m_hWnd, WM_OPEN_POS, wP, lP);
	wP = m_pViewImage->GetCircleOpenRadius();
	::SendMessage(m_pViewInfo->m_hWnd, WM_OPEN_RADIUS, wP, NULL);
}

CString CGLIMreportDlg::GetTime() {
	CTime currentTime = CTime::GetCurrentTime();
	CString timeString = currentTime.Format(_T("[%Y-%m-%d %H:%M:%S] "));
	return timeString;
}


void CGLIMreportDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bFirstLoad) {
		m_pViewImage->SetCImage();
		m_bFirstLoad = true;

		KillTimer(1);
	}


	CDialogEx::OnTimer(nIDEvent);
}
