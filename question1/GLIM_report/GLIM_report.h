
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.



class CGLIMreportApp : public CWinApp
{
public:
	CGLIMreportApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	// mainDlg size
	double m_dScreenWidth;
	double m_dScreenHeight;
	// resolution Ratio
	double m_dWidthRatio;
	double m_dHeightRatio;

	DECLARE_MESSAGE_MAP()
};

extern CGLIMreportApp theApp;
