#include <windows.h>
#include "Active.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	char lpszClassName[] = "Window";
	char lpszTitle[] = "Snake";
	
	wndclass.style = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, NULL);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = lpszClassName;
	
	if (!RegisterClass(&wndclass))
	{
		MessageBeep(0);
		
		return false;
	}

	int nWidth = GetDeviceCaps(GetDC(0), HORZRES);
	int nHeight = GetDeviceCaps(GetDC(0), VERTRES);
	
	hwnd = CreateWindow(
		lpszClassName,
		lpszTitle,
		WS_OVERLAPPED | WS_SYSMENU,
		(nWidth -  nWindowWidth) / 2,
		(nHeight -  nWindowHeight) / 2,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	

	ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);
		
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	return Msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		{
			CureentMode = Ready;

			RECT re;

			GetClientRect(hwnd, &re);

			HDC hdc = GetDC(hwnd);

			hmemdc = CreateCompatibleDC (hdc) ;

			hbitmap = CreateCompatibleBitmap(hdc, re.right - re.left, re.bottom - re.top);

			SelectObject(hmemdc, hbitmap);

			GetObject(hbitmap, sizeof(BITMAP), (LPVOID)&bm);

			ReleaseDC(hwnd, hdc);


			return 0;
		}

	case WM_DESTROY:
		{
			KillTimer(hwnd, 1);
			DeleteObject (hbitmap);
			DeleteObject(hmemdc);
			PostQuitMessage(0);
			return 0;
		}
		
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
            HDC hdc;
            hdc = BeginPaint(hwnd, &ps);
		
			Show(hwnd);
            EndPaint(hwnd, &ps);
			return 0;
		}

	case WM_KEYDOWN:
		{
			KeyDown(hwnd, wParam, lParam);
			
			return 0;
		}

	case WM_TIMER:
		{
			Time(hwnd);
			
			return 0;
		}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}


