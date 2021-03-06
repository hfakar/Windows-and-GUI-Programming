// GT_HelloWorldWin32.cpp  
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c  

#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  

// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");
 
// Global variables  
int space = 10;
int fontNumber = 0;
// The string that appears in the application's title bar. 
static TCHAR szTitle[] = _T("Project 1");
LPCTSTR  fonts[] = { "Times New Roman", "Arial", "Tahoma", "Droid Sans", "Georgia", "Verdana", "Comic Sans MS" };
HINSTANCE hInst;
HFONT hFont;
int r = 0;
int g = 0 ;
int b = 0 ;

int writeText(HDC hdc, int X, int Y, char *szMessage, int fontnumber, int r, int g, int b) {
	hFont = CreateFont(18, 14 , 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, TEXT(fonts[fontnumber]));		
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(r % 255, g % 255, b % 255));
	TextOut(hdc, X, Y, szMessage, strlen(szMessage));
	return 0;
}
// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application does not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}
	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello");

	switch (message)
	{
	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, FALSE);
		hdc = BeginPaint(hWnd, &ps);		
		space += 20;
		writeText(hdc, 5, space, greeting, fontNumber % 7, r, g, b); //I took the mod of fontnumber because I have 7 fonts in fonts Array
		r = r + 30;
		g = g + 60;
		b = b + 10;
		fontNumber = fontNumber + 1;
		EndPaint(hWnd, &ps);
		break;
	case WM_PAINT:
		//InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
		hdc = BeginPaint(hWnd, &ps);
		
		TextOut(hdc, 5, 5, "Hello from Huseyin", _tcslen("Hello from Huseyin"));
		// End application-specific layout section.  

		EndPaint(hWnd, &ps);
		DeleteObject(SelectObject(hdc, hFont));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}