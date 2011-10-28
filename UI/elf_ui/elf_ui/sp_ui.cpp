#include "stdafx.h"
#include <Commdlg.h>
#include <Shlobj.h>
#include <stdio.h>
#include "resource.h"
#include "sp_ui.h"
#include "elf_header.h"
#include "parser_func.h"
#include "basic_inf_dsp.h"
#include "message_dsp.h"
#include "edit_program.h"
#include "dwarf_header.h"
#include "dwarf_parser.h"

extern Elf32 elf;
extern DWARF dwarf;						//DWARF Structure.
extern OPTION_ENV opt_env;
extern char elf_path[MAX_PATH];
HWND SYM_hWnd;
HWND bSYM_hWnd;
HWND DWARF_hWnd;

INT_PTR CALLBACK Elf_Parsing_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:{
		InitCommonControls();
		Elf_Sec_Parser(elf_path, &elf);
		Elf_Prog_Parser(elf_path, &elf);
		Init_SC_Item_List(hDlg, &elf);
		Init_PG_Item_List(hDlg, &elf);

		SC_Item_List(hDlg, &elf);
		PG_Item_List(hDlg, &elf);

		USec_Hd_Dmsg(&elf);
		UProg_Hd_Dmsg(&elf);
		return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		switch(wParam){
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		default:
			break;
		}
		break;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		LPNMITEMACTIVATE nia;
		hdr=(LPNMHDR)lParam;
		nlv=(LPNMLISTVIEW)lParam;
		HWND hsItem_List = GetDlgItem(hDlg, IDC_SECTION_LIST);
		HWND hpItem_List = GetDlgItem(hDlg, IDC_PROGRAM_LIST);

		switch(hdr->code){
			case NM_DBLCLK:
				nia=(LPNMITEMACTIVATE)lParam;
				if(hdr->hwndFrom == hsItem_List){
					Select_Section_Item(hDlg, elf_path, &elf);
				}
				else if(hdr->hwndFrom == hpItem_List){
					Select_Program_Item(hDlg, elf_path, &elf);
				}
				return (INT_PTR)TRUE;
			default:
				break;
		}
	
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Sym_Parsing_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:{
		InitCommonControls();
		return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		switch(wParam){
			case IDCANCEL:
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			case SYM_SYMTAB:
				Init_SYM_Item_List(hDlg, &elf);
				Sym_List(hDlg, &elf);
				return (INT_PTR)TRUE;
			case SYM_NOTE:
				Init_Note_List(hDlg, &elf);
				Get_Note_Section(elf_path, &elf);
				Note_List(hDlg, &elf);
				return (INT_PTR)TRUE;
			case SYM_DEBUG_PUBNAMES:
				Dwarf_Pubnames((unsigned char *)elf.temp_data, elf.temp_size, &dwarf);
				Init_Debug_Pubnames_List(hDlg);
				Debug_Pubnames_List(hDlg, &dwarf);
				return (INT_PTR)TRUE;
			case SYM_DEBUG_INFO:
				Init_Debug_Info_List(hDlg);
				Dwarf_Info((unsigned char *)elf.temp_data, elf.temp_size, &dwarf);
				Debug_Info_List(hDlg, &dwarf);
				return (INT_PTR)TRUE;
			case SYM_DEBUG_ABBREV:
				Init_Debug_Abbrev_List(hDlg);
				Dwarf_Abbrev((unsigned char *)elf.temp_data, elf.temp_size, &dwarf);
				Debug_Abbrev_List(hDlg, &dwarf);
				return (INT_PTR)TRUE;
			default:
				break;
			}
		break;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		LPNMITEMACTIVATE nia;
		hdr=(LPNMHDR)lParam;
		nlv=(LPNMLISTVIEW)lParam;

		HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_ITEM_LIST);
		switch(hdr->code){
		case NM_DBLCLK:
			nia=(LPNMITEMACTIVATE)lParam;
			if(hdr->hwndFrom == hItem_List){
				char win_text[MAX_PATH];
				GetWindowText(hDlg, win_text, MAX_PATH);
				if(strstr(win_text,".debug") == NULL){
					Select_Symbol_Item(hDlg, elf_path, &elf, &opt_env);
				}
				else if(strstr(win_text,".debug_abbrev") != NULL){
					Select_Dwarf_Item(hDlg);
				}
				else if(strstr(win_text,".debug_info") != NULL){
					Get_Section_Data(elf_path, &elf, ".debug_abbrev", &(elf.temp_data), NULL);
					Select_Debug_Info_Attr_Item(hDlg);
				}
			}
			return (INT_PTR)TRUE;
		default:
			break;
		}	
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Binary_View_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:{
		InitCommonControls();
		return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		switch(wParam){
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case SYM_BINARY:
			Binary_View(hDlg, elf.temp_data, elf.temp_size);
			return (INT_PTR)TRUE;
		/*case SYM_SYMTAB:
			Init_SYM_Item_List(hDlg, &elf);
			Sym_List(hDlg, &elf);
			return (INT_PTR)TRUE;
		case SYM_NOTE:
			Init_Note_List(hDlg, &elf);
			Get_Note_Section(elf_path, &elf);
			Note_List(hDlg, &elf);
			return (INT_PTR)TRUE;*/
		default:
			break;
			}
		break;
	default:
		break;
	}	
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Dwarf_Item_View_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:{
		InitCommonControls();
		return (INT_PTR)TRUE;
					   }
	case WM_COMMAND:
		switch(wParam){
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case DWARF_ABBREV:
			Init_Abbrev_Attr_List(hDlg);
			Attribute_Item_List(hDlg, &dwarf, LOWORD(lParam));
			return (INT_PTR)TRUE;
		case DEBUG_INFO_ATTR:
			Init_Debug_Info_Attr_List(hDlg);
			DEBUG_INFO *d_info;
			d_info = dwarf.debug_info + LOWORD(lParam);
			Dwarf_Abbrev((unsigned char *)(elf.temp_data + d_info->debug_info_hd.debug_abbrev_offset), 
				elf.temp_size - d_info->debug_info_hd.debug_abbrev_offset, &dwarf);
			Attribute_Item_List(hDlg, &dwarf, d_info->debug_info_entry.abbrev_table_num);
			Attribute_Data_List(hDlg, d_info, &dwarf);
			return (INT_PTR)TRUE;
		default:
			break;
			}
		break;
	default:
		break;
	}	
	return (INT_PTR)FALSE;
}

void Init_SC_Item_List(HWND hDlg, Elf32 *elf)
{
	LVCOLUMN COL;
	LVITEM LI;
	
	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = "Num";
	COL.iSubItem = SC_NUM;
	ListView_InsertColumn(hItem_List,SC_NUM,&COL);
	
	COL.cx = 150;
	COL.pszText = "Name";
	COL.iSubItem = SC_NAME;
	ListView_InsertColumn(hItem_List,SC_NAME,&COL);

	COL.cx = 120;
	COL.pszText = "Type";
	COL.iSubItem = SC_TYPE;
	ListView_InsertColumn(hItem_List,SC_TYPE,&COL);

	COL.cx = 120;
	COL.pszText = "Addr";
	COL.iSubItem = SC_ADDR;
	ListView_InsertColumn(hItem_List,SC_ADDR,&COL);

	COL.cx = 120;
	COL.pszText = "Offset";
	COL.iSubItem = SC_OFFSET;
	ListView_InsertColumn(hItem_List,SC_OFFSET,&COL);

	COL.cx = 120;
	COL.pszText = "Size";
	COL.iSubItem = SC_HSIZE;
	ListView_InsertColumn(hItem_List,SC_HSIZE,&COL);

	COL.cx = 120;
	COL.pszText = "Flags";
	COL.iSubItem = SC_FLAGS;
	ListView_InsertColumn(hItem_List,SC_FLAGS,&COL);

	COL.cx = 120;
	COL.pszText = "Link";
	COL.iSubItem = SC_LINK;
	ListView_InsertColumn(hItem_List,SC_LINK,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);
	
	for(unsigned int nsc = 0; nsc < elf->hd.e_shnum; nsc++){		
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = nsc;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(nsc);
		ListView_InsertItem(hItem_List, &LI);
	}
}

void Init_PG_Item_List(HWND hDlg, Elf32 *elf)
{
	LVCOLUMN COL;
	LVITEM LI;

	HWND hItem_List = GetDlgItem(hDlg,IDC_PROGRAM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = "Num";
	COL.iSubItem = PG_NUM;
	ListView_InsertColumn(hItem_List,PG_NUM,&COL);
	
	COL.cx = 120;
	COL.pszText = "Type";
	COL.iSubItem = PG_TYPE;
	ListView_InsertColumn(hItem_List,PG_TYPE,&COL);

	COL.cx = 120;
	COL.pszText = "Offset";
	COL.iSubItem = PG_OFFSET;
	ListView_InsertColumn(hItem_List,PG_OFFSET,&COL);

	COL.cx = 120;
	COL.pszText = "Vaddr";
	COL.iSubItem = PG_VADDR;
	ListView_InsertColumn(hItem_List,PG_VADDR,&COL);

	COL.cx = 120;
	COL.pszText = "Paddr";
	COL.iSubItem = PG_PADDR;
	ListView_InsertColumn(hItem_List,PG_PADDR,&COL);

	COL.cx = 120;
	COL.pszText = "Filesz";
	COL.iSubItem = PG_FILESZ;
	ListView_InsertColumn(hItem_List,PG_FILESZ,&COL);

	COL.cx = 120;
	COL.pszText = "Memsz";
	COL.iSubItem = PG_MEMSZ;
	ListView_InsertColumn(hItem_List,PG_MEMSZ,&COL);

	COL.cx = 100;
	COL.pszText = "Flags";
	COL.iSubItem = PG_FLAGS;
	ListView_InsertColumn(hItem_List,PG_FLAGS,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);

	for(unsigned int nsc = 0; nsc < elf->hd.e_phnum; nsc++){	
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = nsc;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(nsc);

		ListView_InsertItem(hItem_List, &LI);
	}
}

void Init_SYM_Item_List(HWND hDlg, Elf32 *elf)
{
	LVCOLUMN COL;
	LVITEM LI;
	unsigned int sym_num = 0;
	Elf32_Shdr *sh;

	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = "Num";
	COL.iSubItem = NSYM_NUM;
	ListView_InsertColumn(hItem_List,NSYM_NUM,&COL);

	COL.cx = 100;
	if((elf->hd.e_type == ET_EXEC) || (elf->hd.e_type == ET_DYN))
		COL.pszText = "Vaddr";
	else
		COL.pszText = "Value";
	COL.iSubItem = NSYM_VALUE;
	ListView_InsertColumn(hItem_List,NSYM_VALUE,&COL);

	COL.cx = 100;
	COL.pszText = "Size";
	COL.iSubItem = NSYM_SIZE;
	ListView_InsertColumn(hItem_List,NSYM_SIZE,&COL);

	COL.cx = 100;
	COL.pszText = "Bind";
	COL.iSubItem = NSYM_BIND;
	ListView_InsertColumn(hItem_List,NSYM_BIND,&COL);

	COL.cx = 100;
	COL.pszText = "Type";
	COL.iSubItem = NSYM_TYPE;
	ListView_InsertColumn(hItem_List,NSYM_TYPE,&COL);

	COL.cx = 100;
	COL.pszText = "Ndx";
	COL.iSubItem = NSYM_NDX;
	ListView_InsertColumn(hItem_List,NSYM_NDX,&COL);

	COL.cx = 300;
	COL.pszText = "Name";
	COL.iSubItem = NSYM_NAME;
	ListView_InsertColumn(hItem_List,NSYM_NAME,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);

	sh = elf->sc_hd + Get_Section_Index(elf, SHT_SYMTAB);
	sym_num = sh->sh_size/ sizeof(Elf32_Sym);

	for(unsigned int nsc = 0; nsc < sym_num; nsc++){		
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = NSYM_NUM;
		LI.iItem = nsc;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(nsc);
		ListView_InsertItem(hItem_List, &LI);
	}
}

void Init_Note_List(HWND hDlg, Elf32 *elf)
{
	LVCOLUMN COL;
	LVITEM LI;
	Elf32_Shdr *sh;
	char s_index;
	unsigned int note_num = 0;

	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = "Num";
	COL.iSubItem = NOTE_NUM;
	ListView_InsertColumn(hItem_List,NOTE_NUM,&COL);

	COL.cx = 100;
	COL.pszText = "Namesz";
	COL.iSubItem = NOTE_NAMESZ;
	ListView_InsertColumn(hItem_List,NOTE_NAMESZ,&COL);

	COL.cx = 100;
	COL.pszText = "Descsz";
	COL.iSubItem = NOTE_DESCSZ;
	ListView_InsertColumn(hItem_List,NOTE_DESCSZ,&COL);

	COL.cx = 100;
	COL.pszText = "Type";
	COL.iSubItem = NOTE_TYPE;
	ListView_InsertColumn(hItem_List,NOTE_TYPE,&COL);

	COL.cx = 100;
	COL.pszText = "Name";
	COL.iSubItem = NOTE_NAME;
	ListView_InsertColumn(hItem_List,NOTE_NAME,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);

	s_index = Get_Section_Index(elf, SHT_NOTE);
	sh = elf->sc_hd + s_index;
	note_num = sh->sh_size/sizeof(Elf32_Note);

	for(unsigned int nsc = 0; nsc < note_num; nsc++){		
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = NOTE_NUM;
		LI.iItem = nsc;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(nsc);
		ListView_InsertItem(hItem_List, &LI);
	}
}

void Init_Debug_Abbrev_List(HWND hDlg)
{
	LVCOLUMN COL;
	unsigned int sym_num = 0;

	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 70;
	COL.pszText = "Num";
	COL.iSubItem = DEBUG_ABBREV_NUM;
	ListView_InsertColumn(hItem_List,DEBUG_ABBREV_NUM,&COL);

	COL.cx = 70;
	COL.pszText = "Table No.";
	COL.iSubItem = DEBUG_ABBREV_TBL_NUM;
	ListView_InsertColumn(hItem_List,DEBUG_ABBREV_TBL_NUM,&COL);

	COL.cx = 200;
	COL.pszText = "Tag encodings";
	COL.iSubItem = DEBUG_ABBREV_TAG_NAME;
	ListView_InsertColumn(hItem_List,DEBUG_ABBREV_TAG_NAME,&COL);

	COL.cx = 150;
	COL.pszText = "Child encodings";
	COL.iSubItem = DEBUG_ABBREV_CHILDREN;
	ListView_InsertColumn(hItem_List,DEBUG_ABBREV_CHILDREN,&COL);

	COL.cx = 150;
	COL.pszText = "Attribute";
	COL.iSubItem = DEBUG_ABBREV_ATTR;
	ListView_InsertColumn(hItem_List,DEBUG_ABBREV_ATTR, &COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);
}

void Init_Abbrev_Attr_List(HWND hDlg)
{
	LVCOLUMN COL;
	unsigned int sym_num = 0;

	HWND hItem_List = GetDlgItem(hDlg,IDC_DWARF_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 70;
	COL.pszText = "No.";
	COL.iSubItem = ATTRIBUTE_NUM;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_NUM,&COL);

	COL.cx = 200;
	COL.pszText = "Attribute encodings";
	COL.iSubItem = ATTRIBUTE_ENCODING;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_ENCODING,&COL);

	COL.cx = 150;
	COL.pszText = "Attribute form";
	COL.iSubItem = ATTRIBUTE_FORM_ENCODING;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_FORM_ENCODING,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);
}

void Init_Debug_Info_Attr_List(HWND hDlg)
{
	LVCOLUMN COL;
	unsigned int sym_num = 0;

	HWND hItem_List = GetDlgItem(hDlg,IDC_DWARF_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 70;
	COL.pszText = "No.";
	COL.iSubItem = ATTRIBUTE_NUM;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_NUM,&COL);

	COL.cx = 200;
	COL.pszText = "Attribute encodings";
	COL.iSubItem = ATTRIBUTE_ENCODING;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_ENCODING,&COL);

	COL.cx = 150;
	COL.pszText = "Attribute form";
	COL.iSubItem = ATTRIBUTE_FORM_ENCODING;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_FORM_ENCODING,&COL);

	COL.cx = 200;
	COL.pszText = "Attribute data";
	COL.iSubItem = ATTRIBUTE_DATA;
	ListView_InsertColumn(hItem_List,ATTRIBUTE_DATA,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);
}

void Init_Debug_Info_List(HWND hDlg)
{
	LVCOLUMN COL;
	unsigned int sym_num = 0;

	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = "Num";
	COL.iSubItem = DEBUG_INFO_NUM;
	ListView_InsertColumn(hItem_List,DEBUG_INFO_NUM,&COL);

	COL.cx = 90;
	COL.pszText = "Unit_lenght";
	COL.iSubItem = DEBUG_INFO_UNIT_LENGTH;
	ListView_InsertColumn(hItem_List,DEBUG_INFO_UNIT_LENGTH,&COL);

	COL.cx = 70;
	COL.pszText = "Version";
	COL.iSubItem = DEBUG_INFO_VERSION;
	ListView_InsertColumn(hItem_List,DEBUG_INFO_VERSION,&COL);

	COL.cx = 130;
	COL.pszText = "Debug_abbrev_offset";
	COL.iSubItem = DEBUG_ABBREV_OFFSET;
	ListView_InsertColumn(hItem_List,DEBUG_ABBREV_OFFSET,&COL);

	COL.cx = 130;
	COL.pszText = "Address_size";
	COL.iSubItem = DEBUG_INFO_ADDRESS_SIZE;
	ListView_InsertColumn(hItem_List,DEBUG_INFO_ADDRESS_SIZE,&COL);

	COL.cx = 100;
	COL.pszText = "Abbrev table num";
	COL.iSubItem = DEBUG_INFO_ABBREV_NUM;
	ListView_InsertColumn(hItem_List,DEBUG_INFO_ABBREV_NUM,&COL);

	COL.cx = 300;
	COL.pszText = "Debug_Info_Data";
	COL.iSubItem = DEBUG_INFO_DATA_DEF;
	ListView_InsertColumn(hItem_List,DEBUG_INFO_DATA_DEF,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);
}

void Init_Debug_Pubnames_List(HWND hDlg)
{
	LVCOLUMN COL;
	unsigned int sym_num = 0;

	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;

	COL.cx = 50;
	COL.pszText = "Num";
	COL.iSubItem = PUBNAMES_NUM;
	ListView_InsertColumn(hItem_List,PUBNAMES_NUM,&COL);

	COL.cx = 90;
	COL.pszText = "Unit_lenght";
	COL.iSubItem = PUBNAMES_UNIT_LENGTH;
	ListView_InsertColumn(hItem_List,PUBNAMES_UNIT_LENGTH,&COL);

	COL.cx = 70;
	COL.pszText = "Version";
	COL.iSubItem = PUBNAMES_VERSION;
	ListView_InsertColumn(hItem_List,PUBNAMES_VERSION,&COL);

	COL.cx = 130;
	COL.pszText = "Debug_info_offset";
	COL.iSubItem = PUBNAMES_DEBUG_INFO_OFFSET;
	ListView_InsertColumn(hItem_List,PUBNAMES_DEBUG_INFO_OFFSET,&COL);

	COL.cx = 130;
	COL.pszText = "Debug_info_length";
	COL.iSubItem = PUBNAMES_DEBUG_INFO_LENGTH;
	ListView_InsertColumn(hItem_List,PUBNAMES_DEBUG_INFO_LENGTH,&COL);

	COL.cx = 100;
	COL.pszText = "Offset";
	COL.iSubItem = PUBNAMES_OFFSET;
	ListView_InsertColumn(hItem_List,PUBNAMES_OFFSET,&COL);

	COL.cx = 300;
	COL.pszText = "String";
	COL.iSubItem = PUBNAMES_STRING;
	ListView_InsertColumn(hItem_List,PUBNAMES_STRING,&COL);

	ListView_SetExtendedListViewStyle(hItem_List, LVS_EX_FULLROWSELECT);
}
