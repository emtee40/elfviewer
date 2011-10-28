#include "stdafx.h"
#include "resource.h"
#include <Commdlg.h>
#include <Shlobj.h>
#include "main_ui.h"

#include "parser_func.h"
#include "elf_header.h"
#include "message_dsp.h"
#include "basic_inf_dsp.h"
#include "dwarf_parser.h"

extern HWND Main_hWnd;
HWND		SP_hWnd;
HINSTANCE	g_hInst_sp;
extern Elf32 elf;
extern DWARF dwarf;
char elf_path[MAX_PATH];

INT_PTR CALLBACK Elf_File_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	
	switch (message)
	{
	case WM_INITDIALOG:
		Init_Elf(&elf);
		Init_Dwarf(&dwarf);
		Item_List(hDlg);
		Init_Item_List(hDlg);
		Parsing_Button(hDlg, FALSE);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch(wParam){
		case ELF_OPEN:
			Open_Elf_File(hDlg);
			return (INT_PTR)TRUE;
		case IDC_REFRESH:{
			char lpstrFile[MAX_PATH] = "";
			HWND folder_dp = GetDlgItem(hDlg, IDC_FILE_PATH);
			if(GetWindowText(folder_dp, lpstrFile, MAX_PATH) != NULL){
				strcpy(elf_path, lpstrFile);
				if(Elf_Header_Parser(lpstrFile, &elf.hd)){
					//indicate basic information for ELF on UI.
					Ident_Display(hDlg, &elf.hd.e_ident);
					Header_Display(hDlg, &elf.hd);
					//indicate message for debugging.
					UIdent_Dmsg(&elf.hd.e_ident);
					UHeader_Dmsg(&elf.hd);
					Parsing_Button(hDlg, TRUE);
				}
			}
			else{
				Display_Status("File is not opened");
				Parsing_Button(hDlg, TRUE);
			}
			return (INT_PTR)TRUE;
		}
		case IDC_PARSING:{
			//InitCommonControls();
			SP_hWnd = CreateDialog(g_hInst_sp, MAKEINTRESOURCE(IDD_SP_FRAME), hDlg, Elf_Parsing_UI);
			return (INT_PTR)TRUE;
		}
		case IDOK:
			return (INT_PTR)TRUE;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		default:
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL Open_Elf_File(HWND hDlg)
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
		HWND folder_dp = GetDlgItem(hDlg, IDC_FILE_PATH);
		SetWindowText(folder_dp, lpstrFile);
		strcpy(elf_path, lpstrFile);
		if(Elf_Header_Parser(lpstrFile, &elf.hd)){
			//indicate basic information for ELF on UI.
			Ident_Display(hDlg, &elf.hd.e_ident);
			Header_Display(hDlg, &elf.hd);
			//indicate message for debugging.
			UIdent_Dmsg(&elf.hd.e_ident);
			UHeader_Dmsg(&elf.hd);
			Parsing_Button(hDlg, TRUE);
		}
		else{
			Display_Status("File is not opened");
			Parsing_Button(hDlg, TRUE);
		}

		return TRUE;
	}

	return FALSE;
}

void Init_Item_List(HWND hDlg)
{
	LVCOLUMN COL;

	//InitCommonControls();

	HWND hItem_List = GetDlgItem(hDlg,IDC_ITEM_LIST);
	
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;

	COL.pszText = "Name";
	COL.iSubItem = 0;
	ListView_InsertColumn(hItem_List,0,&COL);

	COL.cx = 250;
	COL.pszText = "Data";
	COL.iSubItem = 1;
	ListView_InsertColumn(hItem_List,1,&COL);
}

void Item_List(HWND hdlg)
{
	LVITEM LI;
	char *basic_names[17] ={"The object file type", 
						"The required architecture", 
						"The object file version", 
						"Entry", 
						"The program header table's offset", 
						"The Section header table's offset", 
						"Flags",
						"The ELF header's size",
						"The size of one entry in the program header table",
						"The number of entries in the program header table",
						"A section header's size",
						"The number of entries in the section header table",
						"The section header table index of the entry associated with the section name string table",
						"",
						"File's class",
						"Data encoding",
						"The ELF header version number"};

	HWND hItem_List = GetDlgItem(hdlg, IDC_ITEM_LIST);
	
	for(unsigned int i = 0; i < 17; i++){
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = i;
		LI.pszText = (LPSTR)(LPCSTR)basic_names[i];
		ListView_InsertItem(hItem_List, &LI);
	}
}

void Parsing_Button(HWND hButton, BOOL status)
{
	HWND parsing_b = GetDlgItem(hButton, IDC_PARSING);
	EnableWindow(parsing_b, status);
}