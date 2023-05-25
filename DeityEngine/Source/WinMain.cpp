#include <windows.h>
#include "../resource.h"

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

WCHAR	WindowClass[MAX_NAME_STRING];
WCHAR	WindowTitle[MAX_NAME_STRING];

INT		WindowWidth;
INT		WindowHeight;

HICON	hIcon;

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	wcscpy_s(WindowClass, TEXT("WindowClass"));
	wcscpy_s(WindowTitle, TEXT("Deity's Game Engine"));
	WindowWidth = 1366;
	WindowHeight = 768;
	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = WindowClass;
	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindowW(
		WindowClass,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WindowWidth,
		WindowHeight,
		nullptr,
		nullptr,
		HInstance(),
		nullptr
	);

	if (!hWnd)
	{
		MessageBox(0, L"Could't create the window!", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}