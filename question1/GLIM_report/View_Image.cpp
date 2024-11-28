// View_Image.cpp: 구현 파일
//

#include "pch.h"
#include "GLIM_report.h"
#include "VIEW_Image.h"


// View_Image

IMPLEMENT_DYNCREATE(VIEW_Image, CFormView)

VIEW_Image::VIEW_Image()
	: CFormView(VIEW_IMAGE)
{

}
VIEW_Image::VIEW_Image(int startX, int startY, double screenWidth, double screenHeight)
	: CFormView(VIEW_IMAGE)
{
	m_nStartX = startX;
	m_nStartY = startY;

	m_dScreenWidth = screenWidth;
	m_dScreenHeight = screenHeight;
}

VIEW_Image ::~VIEW_Image()
{
}

void VIEW_Image::SetCImage()
{
	int nWidth = m_dScreenWidth;
	int nHeight = m_dScreenHeight;
	int nBpp = 8;

	if (m_image != NULL)
		m_image.Destroy();

	m_image.Create(nWidth, -nHeight, nBpp);	// height check

	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	// pitch 는 - (bmp 이므로)

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	
	// memset 시 nHeight가 음수이기 때문에 마지막 픽셀 행 값이 0임.
	//memset(fm, COLOR_BACKGROUND, nWidth * nHeight);
	SetBackground(fm, nWidth, nHeight, nPitch);


	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void VIEW_Image::SetCircleStart(pos pos1) {
	m_nCirclePos1.x = pos1.x;
	m_nCirclePos1.y = pos1.y;
}
void VIEW_Image::SetCircleEnd(pos pos2) {
	m_nCirclePos2.x = pos2.x;
	m_nCirclePos2.y = pos2.y;
}


void VIEW_Image::OpenCImage(CString filePath) {
	if (m_image != NULL)
		m_image.Destroy();

	// for ui
	m_image.Load(filePath);

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	// Image Open exception 
	// open bmp Size가 dlg 보다 크면
	if (nWidth > m_dScreenWidth && nHeight > m_dScreenHeight) {
		AfxMessageBox(_T(" up scale 필요"));
		return;
	} else if (nWidth < m_dScreenWidth && nHeight < m_dScreenHeight) {
		AfxMessageBox(_T("down scale 필요"));
		return;
	}

	// Find Circle pos
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int minX = 987654321, maxX = -1;
	int minY = 987654321, maxY = -1;

	for (int y = 0; y < nHeight; y++) {
		for (int x = 0; x < nWidth; x++) {
			int offset = x + (nPitch* y);
			if ((int)fm[offset] == COLOR_BACKGROUND) continue;

			minX = min(x, minX);	maxX = max(x, maxX);
			minY = min(y, minY);	maxY = max(y, maxY);
		}
	}

	m_nCircleOpenPos.x = (minX + maxX) / 2;
	m_nCircleOpenPos.y = (maxY + minY) / 2;
	m_nCircleOpenRadius = (maxX - minX) /2;

	// 원의 중심을 기준으로 대각선으로 X 표시하기
	for (int i = -m_nCircleOpenRadius; i <= m_nCircleOpenRadius; i++) {
		int x1 = m_nCircleOpenPos.x + i;
		int y1 = m_nCircleOpenPos.y + i;

		if((int)fm[x1 + y1 * nPitch] == COLOR_CIRCLE)
			fm[x1 + y1 *nPitch] = COLOR_CROSS; 

		int x2 = m_nCircleOpenPos.x - i;
		int y2 = m_nCircleOpenPos.y + i;
		if ((int)fm[x2 + y2 * nPitch] == COLOR_CIRCLE)
			fm[x2 + y2 * nPitch] = COLOR_CROSS; 
	}

	


	UpdateDisplay();
}

void VIEW_Image::SaveCImage(CString filePath) {
	m_image.Save(filePath);

}
void VIEW_Image::SetBackground(unsigned char*& img, int width, int height, int pitch) {
	for (int y = 0; y < abs(height); y++) {
		for (int x = 0; x < width; x++) {
			int offset = x + (pitch * y);
			img[offset] = COLOR_BACKGROUND;
		}
	}
}
void VIEW_Image::CircleInImage(int centerX, int centerY, int radius) {
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 배경 설정
	SetBackground(fm, nWidth, nHeight, nPitch);

	for (int y = -radius; y < radius; y++) {
		for (int x = -radius; x < radius; x++) {
			// 원 내부 점인지 체크
			if ((x * x) + (y * y) <= radius * radius) {
				int drawX = centerX + x;
				int drawY = centerY + y;

				// 예외 처리: 좌표가 유효한지 확인
				if (drawX >= 0 && drawX < nWidth && drawY >= 0 && drawY < nHeight) {
					fm[drawY * nPitch + drawX] = COLOR_CIRCLE;
				}
			}
		}
	}
}

void VIEW_Image::DrawCircle(int radius) {
	int nRadius = radius;
	CircleInImage(m_nCirclePos1.x, m_nCirclePos1.y, nRadius);

	UpdateDisplay();
}
void VIEW_Image::DrawRandomCircle() {
	int nMaxValue = 300;
	int nRadius = rand() % nMaxValue;

	int nMaxX = rand() % (int)m_dScreenWidth;
	int nMaxY = rand() % (int)m_dScreenHeight;

	CircleInImage(nMaxX, nMaxY, nRadius);
	UpdateDisplay();
}

void VIEW_Image::MoveCircle() {
	// static Init Flag
	static bool bInitialized = false;
	static int nSttX1, nSttY1, nSttX2, nSttY2;

	if (!bInitialized) {
		// movePos
		nSttX1 = m_nCirclePos1.x;
		nSttY1 = m_nCirclePos1.y;
		// end
		nSttX2 = m_nCirclePos2.x;
		nSttY2 = m_nCirclePos2.y;

		bInitialized = true;
	}

	int nRadius = 30;
	// DrawCircleInImage 함수 호출
	CircleInImage(nSttX1, nSttY1, nRadius);

	int moveWeight = 1;
	// 원 이동
	if (nSttX1 < nSttX2)
		nSttX1+= moveWeight;
	else if (nSttX1 > nSttX2)
		nSttX1-= moveWeight;

	if (nSttY1 < nSttY2)
		nSttY1+= moveWeight;
	else if (nSttY1 > nSttY2)
		nSttY1-= moveWeight;

	// 이동 완료 
	if (nSttX1 == nSttX2 && nSttY1 == nSttY2) {
		m_bIsMoving = false;
		bInitialized = false;
	}
	UpdateDisplay();
}


void VIEW_Image::UpdateDisplay() {
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}




void VIEW_Image::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(VIEW_Image, CFormView)
END_MESSAGE_MAP()


// View_Image 진단

#ifdef _DEBUG
void VIEW_Image::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void VIEW_Image::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// View_Image 메시지 처리기


BOOL VIEW_Image::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void VIEW_Image::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	//main Dlg Picture Control 가리지 않기위한 가중치
	SetWindowPos(NULL, m_nStartX+1, m_nStartY+1,
		m_dScreenWidth-2, m_dScreenHeight-2 , SWP_NOZORDER | SWP_NOACTIVATE);


}
