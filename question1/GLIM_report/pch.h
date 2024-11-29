// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WM_OPEN_POS WM_USER +101
#define WM_OPEN_RADIUS WM_USER +102

// 여기에 미리 컴파일하려는 헤더 추가
using namespace std;

#include "framework.h"
#include <iostream>
#include <string>

const CString PATH_SAVEBMP = _T("./BMP/");
const CString PATH_DRAWBMP = PATH_SAVEBMP + _T("DRAW/");
const CString PATH_ACTIONBMP = PATH_SAVEBMP + _T("ACTION/");
const CString PATH_RANDOMBMP = PATH_SAVEBMP + _T("RANDOM/");
const CString PATH_LOG = _T("./LOG/");
const CString FILE_LOG = PATH_LOG + _T("OperatingLog.txt");


const int DevelopScreenWidth = 2560;
const int DevelopScreenHeight = 1440;

const int Size_MainVIEW_Width = 1600;
const int Size_MainVIEW_Height = 1000;


#endif //PCH_H
