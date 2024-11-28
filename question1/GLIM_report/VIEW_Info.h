#pragma once

// VIEW_Info 폼 보기
#include "GLIM_reportDlg.h"

class VIEW_Info : public CFormView
{
	DECLARE_DYNCREATE(VIEW_Info)
public:
	
	VIEW_Info();
	VIEW_Info(int startX, int startY, double screenWidth, double screenHeight);
	virtual ~VIEW_Info();

	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWINFO };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedButton_Draw();
	afx_msg void OnBnClickedButton_Action();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonApply2();
	afx_msg void OnBnClickedButtonOpen();
	LRESULT OpenCirclePos(WPARAM wParam, LPARAM lParam);
	LRESULT OpenCircleRadius(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
private:
	int m_nStartX, m_nStartY;
	double m_dScreenWidth;
	double m_dScreenHeight;

	// can setting image View size
	int m_nMaxWidth, m_nMaxHeight;

	bool ParseEditCtrl(CString cstr, int& x, int& y);

	CButton m_btnDraw;
	CButton m_btnAction;

	CStatic m_staticGroup;
	CStatic m_staticRange;
	CStatic m_staticStart;
	CEdit m_editStartPos;
	CButton m_btnStartApply;
	CStatic m_staticCurStart;
	CStatic m_staticEnd;
	CButton m_btnEndApply;
	CEdit m_editEndPos;
	CStatic m_staticCurEnd;
	CStatic m_staticRandom;
	CEdit m_editRandom;
	CButton m_btnRandom;



	CStatic m_staticGroupOpen;

	CStatic m_staticFileName;
	CButton m_btnOpen;
	CEdit m_editOpen;
	CStatic m_staticCirclePos;
	CEdit m_editCirclePos;
	CStatic m_staticCircleRadius;
	CEdit m_editCircleRadius;


public:
	afx_msg void OnBnClickedButtonRandom();
};


