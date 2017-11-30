#include <tchar.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

static TCHAR szWindowClass[] = _T("win32app");					/* Name of the application */
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");	/* Text that appears over the title bar */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,			/* Handler to the current instance of the application */
	_In_ HINSTANCE hPrevInstance,		/* Handler to the previous instance of the application */
	_In_ LPSTR lpCmdLine,				/* Command line for the application */
	_In_ int nCmdShow)					/* Controls how the window is to be shown */
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


	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed."),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}

	HWND hwnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd) {
		MessageBox(NULL,
			_T("Call to CreateWindow failed."),
			_T("Wind32 Guided Tour"),
			NULL);
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

}

/* Window Procedure Function:
		Write code inside this function 
		to handle messages that the application 
		receives from Windows when events occur */
LRESULT CALLBACK WndProc(
	_In_ HWND hwnd,						/* Handler to window procedure that recieved the msg */
	_In_ UINT uMsg,						/* The msg */
	_In_ WPARAM wParam,					/* Additional msg info */
	_In_ LPARAM lParam)					/* Additional msg info */
{

	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello World");
	switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}


/*

	https://msdn.microsoft.com/en-us/library/bb384843.aspx
	http://www.cplusplus.com/forum/beginner/3329/
	https://msdn.microsoft.com/en-us/library/windows/desktop/hh298354(v=vs.85).aspx


*/