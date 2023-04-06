/**
 * @file trlMain.cpp
 * @author Chentian
 * @date 2009.12.08
 * @brief TRL Emulate For PC - Trl Main
 */
#include "..\EmuShell\trlEmuShell.h"

#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include "..\resource.h"

#define MAX_LOADSTRING 100

/** @name Global Variable */
//@{
HINSTANCE	g_hInst;
TCHAR		g_szTitle[MAX_LOADSTRING];
TCHAR		g_szWindowClass[MAX_LOADSTRING];
DWORD		g_dwThreadID;
HWND		g_hWnd;
BOOL		g_bStart;
//@}

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
static DWORD WINAPI OnRender(LPVOID pParam);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, g_szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TRL, g_szWindowClass, MAX_LOADSTRING);
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRL));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TRL);
	wcex.lpszClassName	= g_szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_TRL));
	RegisterClassEx(&wcex);

	g_hInst = hInstance;
	g_hWnd = CreateWindow(g_szWindowClass, g_szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 16, 16, NULL, NULL, hInstance, NULL);

	if (!g_hWnd)
		return FALSE;
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRL));

	// Start Render Thread
	CloseHandle(CreateThread(NULL, 0, OnRender, NULL, 0, &g_dwThreadID));

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		}
		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		EndPaint(hWnd, &ps);
//		break;
	case WM_DESTROY:
		g_bStart = FALSE;
		do{
			if(g_dwThreadID==0)
				break;
			Sleep(1);
		}while(1);
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		trlEmuShellInput(wParam, 1);
		break;
	case WM_KEYUP:
		trlEmuShellInput(wParam, 0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

DWORD WINAPI OnRender(LPVOID pParam)
{
	g_bStart = TRUE;
	g_eTrlEmuShellState = eTrlEmuShellStateInitShell;
	while(g_bStart)
	{
		trlTimeFPS_Start();
		trlEmuShellMain();
		trlTimeFPS_End();
	};

	trlEmuShellExit();
	g_dwThreadID = 0;
	return 0;
}
