// VIEW_Info.cpp: 구현 파일
//
#include "pch.h"
#include "GLIM_report.h"
#include "VIEW_Info.h"



// VIEW_Info

IMPLEMENT_DYNCREATE(VIEW_Info, CFormView)

VIEW_Info::VIEW_Info()
	: CFormView(VIEW_INFO)
{
}

VIEW_Info::VIEW_Info(int startX, int startY, double screenWidth, double screenHeight)
	: CFormView(VIEW_INFO)
{
	m_nStartX = startX;
	m_nStartY = startY;
	m_dScreenWidth = screenWidth;
	m_dScreenHeight = screenHeight;
}

VIEW_Info::~VIEW_Info()
{
}

void VIEW_Info::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_DRAW, m_btnDraw);
	DDX_Control(pDX, IDC_BUTTON_ACTION, m_btnAction);

	DDX_Control(pDX, IDC_STATIC_START, m_staticStart);
	DDX_Control(pDX, IDC_EDIT_START, m_editStartPos);
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_btnStartApply);
	DDX_Control(pDX, IDC_STATIC_CURSTART, m_staticCurStart);
	
	DDX_Control(pDX, IDC_STATIC_END, m_staticEnd);
	DDX_Control(pDX, IDC_EDIT_END, m_editEndPos);
	DDX_Control(pDX, IDC_BUTTON_APPLY2, m_btnEndApply);
	DDX_Control(pDX, IDC_STATIC_CUREND, m_staticCurEnd);
	

	DDX_Control(pDX, IDC_STATIC_RANGE, m_staticRange);
	DDX_Control(pDX, IDC_STATIC_Group, m_staticGroup);

	DDX_Control(pDX, IDC_STATIC_RANDOM, m_staticRandom);
	DDX_Control(pDX, IDC_EDIT_RANDOM, m_editRandom);
	DDX_Control(pDX, IDC_BUTTON_RANDOM, m_btnRandom);

	DDX_Control(pDX, IDC_STATIC_GroupOpen, m_staticGroupOpen);

	DDX_Control(pDX, IDC_STATIC_FileName, m_staticFileName);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_btnOpen);
	DDX_Control(pDX, IDC_EDIT_OPEN, m_editOpen);
	
	DDX_Control(pDX, IDC_STATIC_OpenCircle, m_staticCirclePos);
	DDX_Control(pDX, IDC_EDIT_OPENCIRCLE, m_editCirclePos);
	DDX_Control(pDX, IDC_STATIC_OpenRadius, m_staticCircleRadius);
	DDX_Control(pDX, IDC_EDIT_OPENRadius, m_editCircleRadius);
}

BEGIN_MESSAGE_MAP(VIEW_Info, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &VIEW_Info::OnBnClickedButton_Draw)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &VIEW_Info::OnBnClickedButton_Action)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &VIEW_Info::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_APPLY2, &VIEW_Info::OnBnClickedButtonApply2)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &VIEW_Info::OnBnClickedButtonOpen)

	ON_MESSAGE(WM_OPEN_POS, &VIEW_Info::OpenCirclePos)
	ON_MESSAGE(WM_OPEN_RADIUS, &VIEW_Info::OpenCircleRadius)
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &VIEW_Info::OnBnClickedButtonRandom)
END_MESSAGE_MAP()


// VIEW_Info 진단

#ifdef _DEBUG
void VIEW_Info::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void VIEW_Info::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// VIEW_Info 메시지 처리기


BOOL VIEW_Info::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void VIEW_Info::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	double dResolutionRatioX = theApp.m_dWidthRatio;
	double dResolutionRatioY = theApp.m_dWidthRatio;

	//main Dlg Picture Control 가리지 않기위한 가중치
	SetWindowPos(NULL, m_nStartX+1, m_nStartY+1,
		m_dScreenWidth-2, m_dScreenHeight-2, SWP_NOZORDER | SWP_NOACTIVATE);
	

	// ■■■■■■■■■■■■■■ FOR UI pos ■■■■■■■■■■■■■■
	int nCtrlHeightSize = 25;
	int nMarginX = 20 * dResolutionRatioX;

	int nCtrlMarginX = 5 * dResolutionRatioX;
	int nCtrlMarginY = 8 * dResolutionRatioY;

	// [Static] GroupBox
	int nStaticGroupStartX = 5 * dResolutionRatioX;
	int nStaticGroupStartY = 5 * dResolutionRatioY;
	int nStaticGroupWidth = m_dScreenWidth - nStaticGroupStartX *2;
	int nStaticGroupHeight = 270 * dResolutionRatioY;
	m_staticGroup.SetWindowPos(NULL, nStaticGroupStartX, nStaticGroupStartY,
		nStaticGroupWidth, nStaticGroupHeight, SWP_NOZORDER | SWP_NOACTIVATE);


	// [Static] Range
	int nWidth = pMainDlg->m_sViewImageCoord.dWidth -2;
	int nHeight = pMainDlg->m_sViewImageCoord.dHeight - 2;

	m_nMaxWidth = nWidth;
	m_nMaxHeight = nHeight;
	CString cstr;
	cstr.Format(_T("%d"), nWidth);
	CString cstrContent = _T("[ Max Range : (");
	cstrContent += cstr;
	cstrContent += _T(",");
	cstr.Format(_T("%d"), nHeight);
	cstrContent += cstr;
	cstrContent += _T(") ]");
	m_staticRange.SetWindowText(cstrContent);

	int nStaticRangeStartX = nMarginX * dResolutionRatioX;
	int nStaticRangeStartY = 20 * dResolutionRatioY;
	int nStaticRangeWidth = nStaticGroupWidth - 20;
	int nStaticRangeHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticRange.SetWindowPos(NULL, nStaticRangeStartX, nStaticRangeStartY,
		nStaticRangeWidth, nStaticRangeHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [ StartControl : STATIC | EDIT | BUTTON ]
	int n3Width = nStaticGroupWidth - 5;
	// [Static] Start
	int nStaticStartX = nMarginX * dResolutionRatioX;
	int nStaticStartY = nStaticRangeStartY + nStaticRangeHeight + nCtrlMarginY;
	int nStaticStartWidth = n3Width / 3 - nCtrlMarginX;
	int nStaticStartHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticStart.SetWindowPos(NULL, nStaticStartX, nStaticStartY,
		nStaticStartWidth, nStaticStartHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Edit] Start
	int nEditStartX = nStaticStartX + nStaticStartWidth  + nCtrlMarginX;
	int nEditStartY = nStaticRangeStartY + nStaticRangeHeight + nCtrlMarginY;
	int nEditStartWidth = n3Width / 3 - nCtrlMarginX;
	int nEditStartHeight= nCtrlHeightSize * dResolutionRatioY;
	m_editStartPos.SetWindowPos(NULL, nEditStartX, nEditStartY,
		nEditStartWidth, nEditStartHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Button] Start
	int nButtonStartX = nEditStartX + nEditStartWidth + nCtrlMarginX;
	int nButtonStartY = nStaticRangeStartY + nStaticRangeHeight + nCtrlMarginY;
	int nButtonStartWidth = n3Width / 3 - nMarginX * dResolutionRatioX;
	int nButtonStartHeight = nCtrlHeightSize * dResolutionRatioY;
	m_btnStartApply.SetWindowPos(NULL, nButtonStartX, nButtonStartY,
		nButtonStartWidth, nButtonStartHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Static] Current Startpos
	int nStaticCurStartX = nMarginX * dResolutionRatioX;
	int nStaticCurStartY = nButtonStartY + nButtonStartHeight + nCtrlMarginY;
	int nStaticCurStartWidth = nStaticRangeWidth;
	int nStaticCurStartHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticCurStart.SetWindowPos(NULL, nStaticCurStartX, nStaticCurStartY,
		nStaticCurStartWidth, nStaticCurStartHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [ EndControl : STATIC | EDIT | BUTTON ]
	// [Static] End
	int nStaticEndX = nMarginX * dResolutionRatioX;
	int nStaticEndY = nStaticCurStartY + nStaticCurStartHeight + nCtrlMarginY;
	int nStaticEndWidth = n3Width / 3 - nCtrlMarginX;
	int nStaticEndHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticEnd.SetWindowPos(NULL, nStaticEndX, nStaticEndY,
		nStaticEndWidth, nStaticEndHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Edit] End
	int nEditEndX = nStaticEndX + nStaticEndWidth + nCtrlMarginX;
	int nEditEndY = nStaticCurStartY + nStaticCurStartHeight + nCtrlMarginY;
	int nEditEndWidth = n3Width / 3 - nCtrlMarginX;
	int nEditEndHeight = nCtrlHeightSize * dResolutionRatioY;
	m_editEndPos.SetWindowPos(NULL, nEditEndX, nEditEndY,
		nEditEndWidth, nEditEndHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Button] End
	int nButtonEndX = nEditEndX + nEditEndWidth + nCtrlMarginX;
	int nButtonEndY = nStaticCurStartY + nStaticCurStartHeight + nCtrlMarginY;
	int nButtonEndWidth = n3Width / 3 - nMarginX * dResolutionRatioX;
	int nButtonEndHeight = nCtrlHeightSize * dResolutionRatioY;
	m_btnEndApply.SetWindowPos(NULL, nButtonEndX, nButtonEndY,
		nButtonEndWidth, nButtonEndHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Static] Current Endpos
	int nStaticCurEndX = nMarginX * dResolutionRatioX;
	int nStaticCurEndY = nButtonEndY + nButtonEndHeight + nCtrlMarginY;
	int nStaticCurEndWidth = nStaticRangeWidth;
	int nStaticCurEndHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticCurEnd.SetWindowPos(NULL, nStaticCurEndX, nStaticCurEndY,
		nStaticCurEndWidth, nStaticCurEndHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [Button] Draw
	int nButtonMarginY = 4 * dResolutionRatioY;
	int nButtonDrawX = nButtonEndX;
	int nButtonDrawY = nStaticCurEndY + nStaticCurEndHeight + nButtonMarginY;
	int nButtonDrawWidth = nButtonEndWidth;
	int nButtonDrawHeight = nCtrlHeightSize * dResolutionRatioY;
	m_btnDraw.SetWindowPos(NULL, nButtonDrawX, nButtonDrawY,
		nButtonDrawWidth, nButtonDrawHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Button] Action
	int nButtonActionX = nButtonEndX;;
	int nButtonActionY = nButtonDrawY + nButtonDrawHeight + nButtonMarginY;
	int nButtonActionWidth = nButtonEndWidth;
	int nButtonActionHeight = nCtrlHeightSize * dResolutionRatioY;
	m_btnAction.SetWindowPos(NULL, nButtonActionX, nButtonActionY,
		nButtonActionWidth, nButtonActionHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [Static] Random
	int nStaticRandomX = nMarginX * dResolutionRatioX;
	int nStaticRandomY = nButtonActionY + nButtonActionHeight + nCtrlMarginY;
	int nStaticRandomWidth = n3Width / 3 - nCtrlMarginX;
	int nStaticRandomHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticRandom.SetWindowPos(NULL, nStaticRandomX, nStaticRandomY,
		nStaticRandomWidth, nStaticRandomHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Edit] Random
	int nEditRandomX = nStaticEndX + nStaticEndWidth + nCtrlMarginX;
	int nEditRandomY = nButtonActionY + nButtonActionHeight + nCtrlMarginY;
	int nEditRandomWidth = n3Width / 3 - nCtrlMarginX;
	int nEditRandomHeight = nCtrlHeightSize * dResolutionRatioY;
	m_editRandom.SetWindowPos(NULL, nEditRandomX, nEditRandomY,
		nEditRandomWidth, nEditRandomHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Button] Random
	int nButtonRandomX = nEditEndX + nEditEndWidth + nCtrlMarginX;
	int nButtonRandomY = nButtonActionY + nButtonActionHeight + nCtrlMarginY;
	int nButtonRandomWidth = n3Width / 3 - nMarginX * dResolutionRatioX;
	int nButtonRandomHeight = nCtrlHeightSize * dResolutionRatioY;
	m_btnRandom.SetWindowPos(NULL, nButtonRandomX, nButtonRandomY,
		nButtonRandomWidth, nButtonRandomHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	///////////////////////////////////////////////////////////////////////////////
	// [GroupBox] Open
	int nStaticGroupOpenX = 5 * dResolutionRatioX;
	int nStaticGroupOpenY = nStaticRandomY + nButtonActionHeight + nButtonMarginY *6;
	int nStaticGroupOpenWidth = m_dScreenWidth - nStaticGroupStartX * 2;
	int nStaticGroupOpenHeight = 130 * dResolutionRatioY;
	m_staticGroupOpen.SetWindowPos(NULL, nStaticGroupOpenX, nStaticGroupOpenY,
		nStaticGroupOpenWidth, nStaticGroupOpenHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [Static] File 명
	int nStaticFnX = nMarginX * dResolutionRatioX;
	int nStaticFnY = nStaticRandomY + (nButtonActionHeight * 2) + nButtonMarginY * 6;
	int nStaticFnWidth = n3Width / 3 - nCtrlMarginX * 10;
	int nStaticFnHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticFileName.SetWindowPos(NULL, nStaticFnX, nStaticFnY,
		nStaticFnWidth, nStaticFnHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Edit] Open
	int nEditOpenX = nStaticFnX + nStaticFnWidth;
	int nEditOpenY = nStaticRandomY + (nButtonActionHeight * 2) + nButtonMarginY * 6;
	int nEditOpenWidth = (n3Width / 3) * 2 - nCtrlMarginX * 16;
	int nEditOpenHeight = nCtrlHeightSize * dResolutionRatioY;
	m_editOpen.SetWindowPos(NULL, nEditOpenX, nEditOpenY,
		nEditOpenWidth, nEditOpenHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Button] Open
	int nButtonOpenX = nButtonEndX;
	int nButtonOpenY = nStaticRandomY + (nButtonActionHeight*2) + nButtonMarginY * 6;
	int nButtonOpenWidth = nButtonEndWidth;
	int nButtonOpenHeight = nCtrlHeightSize * dResolutionRatioY;
	m_btnOpen.SetWindowPos(NULL, nButtonOpenX, nButtonOpenY,
		nButtonOpenWidth, nButtonOpenHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [Static] CirclePos
	int nStaticCirclePosX = nMarginX * dResolutionRatioX;
	int nStaticCirclePosY = nButtonOpenY + nButtonOpenHeight + nCtrlMarginY;
	int nStaticCirclePosWidth = n3Width / 3 - nCtrlMarginX * 10;
	int nStaticCirclePosHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticCirclePos.SetWindowPos(NULL, nStaticCirclePosX, nStaticCirclePosY,
		nStaticCirclePosWidth, nStaticCirclePosHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Edit] CirclePos
	int nEditCirclePosX = nStaticFnX + nStaticFnWidth;
	int nEditCirclePosY = nButtonOpenY + nButtonOpenHeight + nCtrlMarginY;
	int nEditCirclePosWidth = (n3Width / 3) * 2 - nCtrlMarginX * 16;
	int nEditCirclePosHeight = nCtrlHeightSize * dResolutionRatioY;
	m_editCirclePos.SetWindowPos(NULL, nEditCirclePosX, nEditCirclePosY,
		nEditCirclePosWidth, nEditCirclePosHeight, SWP_NOZORDER | SWP_NOACTIVATE);

	// [Static] Circle Radius
	int nStaticCircleRdX = nMarginX * dResolutionRatioX;
	int nStaticCircleRdY = nEditCirclePosY + nEditCirclePosHeight + nCtrlMarginY;
	int nStaticCircleRdWidth = n3Width / 3 - nCtrlMarginX * 10;
	int nStaticCircleRdHeight = nCtrlHeightSize * dResolutionRatioY;
	m_staticCircleRadius.SetWindowPos(NULL, nStaticCircleRdX, nStaticCircleRdY,
		nStaticCircleRdWidth, nStaticCircleRdHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	// [Edit] Circle Radius
	int nEditCircleRdX = nStaticFnX + nStaticFnWidth;
	int nEditCircleRdY = nEditCirclePosY + nEditCirclePosHeight + nCtrlMarginY;
	int nEditCircleRdWidth = (n3Width / 3) * 2 - nCtrlMarginX * 16;
	int nEditCircleRdHeight = nCtrlHeightSize * dResolutionRatioY;
	m_editCircleRadius.SetWindowPos(NULL, nEditCircleRdX, nEditCircleRdY,
		nEditCircleRdWidth, nEditCircleRdHeight, SWP_NOZORDER | SWP_NOACTIVATE);



}


void VIEW_Info::OnBnClickedButton_Draw()
{
	pMainDlg->Draw_Circle();
	m_editOpen.SetWindowText(_T(""));
	m_editCirclePos.SetWindowText(_T(""));
	m_editCircleRadius.SetWindowText(_T(""));
}


void VIEW_Info::OnBnClickedButton_Action()
{
	pMainDlg->MoveCircle_ImageView();
	m_editOpen.SetWindowText(_T(""));
	m_editCirclePos.SetWindowText(_T(""));
	m_editCircleRadius.SetWindowText(_T(""));
}
void VIEW_Info::OnBnClickedButtonRandom()
{
	CString cstr;
	m_editRandom.GetWindowText(cstr);
	if (cstr.IsEmpty()) {
		AfxMessageBox(_T("생성할 이미지 개수를 입력해주세요."));
		return;
	}
	int cnt = _ttoi(cstr);

	// 예외처리 해주기.
	pMainDlg->Draw_Random(cnt);
	m_editOpen.SetWindowText(_T(""));
	m_editCirclePos.SetWindowText(_T(""));
	m_editCircleRadius.SetWindowText(_T(""));
}


void VIEW_Info::OnBnClickedButtonApply()
{
	CString cstr;
	m_editStartPos.GetWindowText(cstr);

	int nPosX, nPosY;
	if (!ParseEditCtrl(cstr, nPosX, nPosY)) {
		AfxMessageBox(_T("입력 형식 및 최대 범위를 맞춰주세요.\nex) 214,300"));
		return;
	}

	pMainDlg->SetCirclePos_Start(nPosX, nPosY);
	CString cstrX, cstrY;
	cstrX.Format(_T("%d"), nPosX);
	cstrY.Format(_T("%d"), nPosY);

	cstr = _T("Current (x1,y1) : ") + cstrX + _T(",") + cstrY;
	m_staticCurStart.SetWindowText(cstr);

}
void VIEW_Info::OnBnClickedButtonApply2()
{
	CString cstr;
	m_editEndPos.GetWindowText(cstr);
	int nPosX, nPosY;
	
	if (!ParseEditCtrl(cstr, nPosX, nPosY)) {
		AfxMessageBox(_T("입력 형식 및 최대 범위를 맞춰주세요.\nex) 214,300"));
		return;
	}
	
	pMainDlg->SetCirclePos_End(nPosX, nPosY);
	CString cstrX, cstrY;
	cstrX.Format(_T("%d"), nPosX);
	cstrY.Format(_T("%d"), nPosY);

	cstr = _T("Current (x2,y2) : ") + cstrX + _T(",") + cstrY;
	m_staticCurEnd.SetWindowText(cstr);
}

bool VIEW_Info::ParseEditCtrl(CString cstr, int& x, int& y) {
	CString cstrFind = _T(",");
	int nSearch = 0;
	nSearch = cstr.Find(cstrFind);
	
	// delimeter check
	if (nSearch != -1) {
		CString cstrLeft, cstrRight;
		cstrLeft = cstr.Left(nSearch);
		cstrRight = cstr.Right(cstr.GetLength() - (nSearch+1));

		try
		{
			string strLeft = CT2A(cstrLeft);
			string strRight = CT2A(cstrRight);
			
			// image View 최대 사이즈 넘어서면
			if (stoi(strLeft) > m_nMaxWidth || stoi(strRight) > m_nMaxHeight) 
				return false;

			x = std::stoi(strLeft);
			y = std::stoi(strRight);

			return true; // 숫자 변환 성공
		}
		catch (const std::invalid_argument& e)
		{
			return false;
		}
		catch (const std::out_of_range& e)
		{
			return false;
		}
	}
	else return false;


	return true;
}



void VIEW_Info::OnBnClickedButtonOpen()
{
	TCHAR szFilter[] = _T("Image File(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |All Files(*.*)|*.*||");
	
	CFileDialog fDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter);
	
	if (fDlg.DoModal() == IDOK)
	{
		CString filePath = fDlg.GetPathName();

		CString fileName;
		int pos;
		wchar_t cstrFind = '\\';
		pos = filePath.ReverseFind(cstrFind);
		fileName = filePath.Mid(pos+1);

		m_editOpen.SetWindowText(fileName);

		pMainDlg->OpenBmp(filePath);
	}


}

LRESULT VIEW_Info::OpenCirclePos(WPARAM wparam, LPARAM lparam) {
	CString cstr;
	cstr.Format(_T("%d,%d"), wparam, lparam);

	m_editCirclePos.SetWindowText(cstr);
	return 0;
}


LRESULT VIEW_Info::OpenCircleRadius(WPARAM wparam, LPARAM lparam) {
	CString cstr;
	cstr.Format(_T("%d pixel"), wparam);
	m_editCircleRadius.SetWindowText(cstr);
	return 0;
}



