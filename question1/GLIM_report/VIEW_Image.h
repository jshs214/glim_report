#pragma once

#define COLOR_BACKGROUND 124
#define COLOR_CIRCLE 255
#define COLOR_CROSS 0
struct pos {
	int x;
	int y;
};

// View_Image 폼 보기

class VIEW_Image : public CFormView
{
	DECLARE_DYNCREATE(VIEW_Image)
public:
	VIEW_Image();
	VIEW_Image(int startX, int startY, double screenWidth, double screenHeight);
	virtual ~VIEW_Image();
	
	void UpdateDisplay();
	// memset 대체
	void SetBackground(unsigned char*& img, int width, int height, int pitch);
	// make CImage buffer
	void SetCImage();
	// Circle parameter
	void SetCircleStart(pos pos1);
	void SetCircleEnd(pos pos2);
	
	// for Draw Circle In Cimage
	void CircleInImage(int centerX, int centerY, int radius);

	// for Draw
	void DrawCircle(int radius);
	// for Action
	void SetCircleMoving(bool b) { m_bIsMoving = b; }
	bool GetCircleMoving() { return m_bIsMoving; }
	void MoveCircle();
	// for Random
	void DrawRandomCircle();

	// utility
	void OpenCImage(CString cstrPath);
	void SaveCImage(CString filePath);

	
	pos GetCircleOpenPos() { return m_nCircleOpenPos; }
	int GetCircleOpenRadius() { return m_nCircleOpenRadius;}

private:
	// for FormView size
	int m_nStartX, m_nStartY;
	double m_dScreenWidth;
	double m_dScreenHeight;

	// for background image
	CImage m_image;

	// circle size
	int m_nCircleWidth, m_nCircleHeight;

	// x, y
	pos m_nCirclePos1 = { 0,0 };	// start
	pos m_nCirclePos2 = { 100,100 };	// end
	pos m_nCircleOpenPos;			// Open Circle의 중심좌표
	int m_nCircleOpenRadius;

	bool m_bIsMoving;


protected:
	
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = VIEW_IMAGE };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
};


