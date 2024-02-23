#include <windows.h>
#include "resource.h"
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");
HICON hIcon;
HCURSOR hCursor1, hCursor2, hCursor3, hCursor4;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // иконка загружается из ресурсов приложения	
	wcl.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR3));	// курсор загружается из ресурсов приложения	
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Ресурсы"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY: //Закрітие окна
		PostQuitMessage(0);
		break;
	case WM_CREATE://При создании окна
	{
		//получаем дескриптор прилоежения
		HINSTANCE hInstance = GetModuleHandle(0);
		//загружаем курсоры из ресурсов приложения
		hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
		hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
		hCursor3 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));
		hCursor4 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR4));
	}
	break;
	case WM_MOUSEMOVE:
	{
		// устанавливаем тот или иной курсор в зависимости от местонахождения указателя мыши
		RECT rect;
		GetClientRect(hWnd, &rect);//возвращает полностью клиентскую область окна(от какого окна,куда записать)
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);







		int width = rect.right / 2;
		int height = rect.bottom / 2;

		if (x < width && y < height)
			SetCursor(hCursor1); //  верхняя левая часть.
		else if (x >= width && y < height)
			SetCursor(hCursor2); //  верхняя правая часть.
		else if (x < width && y >= height)
			SetCursor(hCursor3); //  нижняя левая часть.
		else if (x >= width && y >= height)
			SetCursor(hCursor4); //  нижняя правая часть.
	}



	/*if (x >= rect.right / 4 && x <= rect.right * 3 / 4 &&
		y >= rect.bottom / 4 && y <= rect.bottom * 3 / 4)
		SetCursor(hCursor1);
	else
		SetCursor(hCursor2);
}*/
	break;
	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



