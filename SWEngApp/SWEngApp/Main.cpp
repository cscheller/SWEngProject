#include <tchar.h>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <wchar.h>
#include <math.h>


HWND BoxForMonth, BoxForDay, BoxForYear;
wchar_t monthArray[2], dayArray[2], yearArray[4];

static TCHAR szWindowClass[] = _T("win32app");					/* Name of the application */
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");	/* Text that appears over the title bar */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int firstPartOfYear(long year);
int secondPartOfYear(long year, long month);
int shiftedMonth(long month);
int calculate(long month, long day, long year);
void printFindings(HWND hwnd, int number);

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
		//		WS_OVERLAPPEDWINDOW,
		WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		750, 750,
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


LRESULT CALLBACK WndProc(_In_ HWND hwnd, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam) {

	int dayOfWeek;
	long monthValue, dayValue, yearValue;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello World");
	switch (msg) {
	case WM_CREATE:
		BoxForMonth = CreateWindow(
			L"Edit",
			NULL,
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			10, 50,
			150, 20,
			hwnd,
			NULL,
			NULL,
			NULL);

		BoxForDay = CreateWindow(
			L"Edit",
			NULL,
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			10, 80,
			150, 20,
			hwnd,
			NULL,
			NULL,
			NULL);

		BoxForYear = CreateWindow(
			L"Edit",
			NULL,
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			10, 110,
			150, 20,
			hwnd,
			NULL,
			NULL,
			NULL);

		CreateWindow(
			L"Button",
			L"Find Day of the Week",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			250, 250,
			200, 35,
			hwnd,
			(HMENU) 1,
			NULL,
			NULL);
		
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		
		case 1:

			GetWindowText(BoxForMonth, &monthArray[0], 3);
			GetWindowText(BoxForDay, &dayArray[0], 3);
			GetWindowText(BoxForYear, &yearArray[0], 5);

			monthValue = wcstol(monthArray, 0, 3);
			dayValue = wcstol(dayArray, 0, 3);
			yearValue = wcstol(yearArray, 0, 5);

			dayOfWeek = calculate(monthValue, dayValue, yearValue);
			if (dayOfWeek < 0) {
				dayOfWeek += 7;
			}

			printFindings(hwnd, dayOfWeek);

			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}


int firstPartOfYear(long year) {
	return (int)((year - (year % 100)) / 100);
}

int secondPartOfYear(long year, long month) {
	if (month < 3)
		return (int)((year % 100) - 1);
	else
		return (int)(year % 100);
}

int shiftedMonth(long month) {
	if (month > 2)
		return (int)(month - 2);
	else if (month == 1)
		return 11;
	else if (month == 2) {
		return 12;
	}
}


int calculate(long month, long day, long year) {
	int sum = (day + (int)floor((2.6*shiftedMonth(month)) - 0.2) + secondPartOfYear(year, month) + 
		(int)floor(secondPartOfYear(year, month)/4) + (int)floor(firstPartOfYear(year)/4) - (2*firstPartOfYear(year))) % 7;
	return sum;
}


void printFindings(HWND hwnd, int number) {
	switch (number) {
	case 0:
		MessageBox(hwnd, L"Your birthday fell on a Sunday.", L"Results", MB_OK);
		break;
	case 1:
		MessageBox(hwnd, L"Your birthday fell on a Monday.", L"Results", MB_OK);
		break;
	case 2:
		MessageBox(hwnd, L"Your birthday fell on a Tuesday.", L"Results", MB_OK);
		break;
	case 3:
		MessageBox(hwnd, L"Your birthday fell on a Wednesday.", L"Results", MB_OK);
		break;
	case 4:
		MessageBox(hwnd, L"Your birthday fell on a Thursday.", L"Results", MB_OK);
		break;
	case 5:
		MessageBox(hwnd, L"Your birthday fell on a Friday.", L"Results", MB_OK);
		break;
	case 6:
		MessageBox(hwnd, L"Your birthday fell on a Saturday.", L"Results", MB_OK);
		break;
	}
}