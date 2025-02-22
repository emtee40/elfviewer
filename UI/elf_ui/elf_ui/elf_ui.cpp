// elf_ui.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <Commctrl.h>
#include <Commdlg.h>
#include <Shlobj.h>
#include "elf_ui.h"
#include "main_ui.h"
#include "elf_header.h"
#include "parser_func.h"
#include "edit_program.h"
#include "dwarf_header.h"
#include "dwarf_parser.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND Main_hWnd;									// Main Window.
HINSTANCE g_hInst;								// current instance.
HWND hState;

Elf32 elf;										//ELF Structure.
DWARF dwarf;									//DWARF Structure.
OPTION_ENV opt_env;								//ELF Viewer option.

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Env_Option(HWND, UINT, WPARAM, LPARAM);
BOOL Open_Edit_Program(HWND hDlg);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ELF_UI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ELF_UI));

	// Main message loop:
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

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ELF_UI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ELF_UI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 500, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			InitCommonControls();
			//hState = CreateStatusWindow(WS_CHILD | WS_VISIBLE, "Status Line", hWnd, 0);
			Main_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_MAIN_FRAME), hWnd, Elf_File_UI);
			Init_Env(&opt_env);
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_TOOL_OPTION:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_OPTION), hWnd, Env_Option);
			break;
		case IDM_EXIT:
			Unalloc_Elf(&elf);
			Unalloc_Dwarf(&dwarf);
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_GETMINMAXINFO:
		LPMINMAXINFO mmi;
		mmi=(LPMINMAXINFO)lParam;
		mmi->ptMinTrackSize.x=1000;
		mmi->ptMinTrackSize.y=500;
		mmi->ptMaxTrackSize.x=1000;
		mmi->ptMaxTrackSize.y=500;
		mmi->ptMaxPosition.x=CW_USEDEFAULT;
		mmi->ptMaxPosition.y=0;
		mmi->ptMaxSize.x=1000;
		mmi->ptMaxSize.y=500;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

INT_PTR CALLBACK Env_Option(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		if(opt_env.edit_cmd != NULL){
			HWND path = GetDlgItem(hDlg, IDC_EDIT_PROGRAM_PATH);
			SetWindowText(path, opt_env.edit_cmd);
		}
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam)){
			case IDOK:
				Save_Env(hDlg, &opt_env);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			case IDC_OPTION_EDIT_BROWSER:
				Open_Edit_Program(hDlg);
				return (INT_PTR)TRUE;
			default:
				break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL Open_Edit_Program(HWND hDlg)
{
	TCHAR lpstrFile[MAX_PATH] = "";
	OPENFILENAME OFN;

	TCHAR szFileTitle[MAX_PATH];
	TCHAR InitDir[MAX_PATH];

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hDlg;
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = MAX_PATH;
	OFN.lpstrFileTitle = szFileTitle;
	OFN.nMaxFileTitle = MAX_PATH;
	OFN.lpstrDefExt = "abc";
	GetWindowsDirectory(InitDir, MAX_PATH);
	OFN.lpstrInitialDir = InitDir;

	if(GetOpenFileName(&OFN) != 0){
		HWND folder_dp = GetDlgItem(hDlg, IDC_EDIT_PROGRAM_PATH);
		SetWindowText(folder_dp, lpstrFile);
		return TRUE;
	}

	return FALSE;

}

