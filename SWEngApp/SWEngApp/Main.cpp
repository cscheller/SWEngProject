#include <tchar.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,			/* Handler to the current instance of the application */
	_In_ HINSTANCE hPrevInstance,		/* Handler to the previous instance of the application */
	_In_ LPSTR lpCmdLine,				/* Command line for the application */
	_In_ int nCmdLine)					/* Controls how the window is to be shown */
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
{}


//	https://msdn.microsoft.com/en-us/library/bb384843.aspx