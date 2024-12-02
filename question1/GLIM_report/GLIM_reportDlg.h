#pragma once
//#include "VIEW_Info.h"
//#include "VIEW_Image.h"
class VIEW_Info;
class VIEW_Image;

struct ViewCoord {
	int nStartX, nStartY;
	double dWidth, dHeight;
};

class CGLIMreportDlg : public CDialogEx
{

public:
	CGLIMreportDlg(CWnd* pParent = nullptr);	

	VIEW_Info* m_pViewInfo;
	ViewCoord m_sViewInfoCoord;			// View [info] coordinate
	VIEW_Image* m_pViewImage;
	ViewCoord m_sViewImageCoord;		// View [image] coordinate


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_REPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


	void AllocForms();

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// dlg size
	double m_dScreenWidth;
	double m_dScreenHeight;
	// for ui (OnTimer)
	bool m_bFirstLoad =false;
	bool ParamCheck();
	void WriteLogFile(CString cstr);

public:
	virtual BOOL DestroyWindow();
	
	// Layout  (Picture Control)
	CStatic m_LayoutViewInfo;
	CStatic m_LayoutViewImage;

	// for ImageView
	void SetCirclePos_Start(int x, int y);		//set : start pos
	void SetCirclePos_End(int x, int y);		//set : end pos
	void Draw_Circle();							//draw
	void MoveCircle_ImageView();				//action
	void Draw_Random(int count);

	void OpenBmp(CString cstrPath);
	
	CString GetTime();
	CString GetFNTime();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

extern CGLIMreportDlg* pMainDlg;
