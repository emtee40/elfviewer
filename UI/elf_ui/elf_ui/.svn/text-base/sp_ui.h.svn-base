#ifndef SP_UI_H
#define SP_UI_H

#include "stdafx.h"
#include "elf_header.h"
#include "dwarf_header.h"

typedef enum{
	SC_NUM = 0,
	SC_NAME,
	SC_TYPE,
	SC_ADDR,
	SC_OFFSET,
	SC_HSIZE,
	SC_FLAGS,
	SC_LINK
}SC_ITEM;

typedef enum{
	PG_NUM = 0,
	PG_TYPE,
	PG_OFFSET,
	PG_VADDR,
	PG_PADDR,
	PG_FILESZ,
	PG_MEMSZ,
	PG_FLAGS
}PG_ITEM;

typedef enum{
	SYM_SYMTAB = 0x10,
	SYM_NOTE,
	SYM_DEBUG_PUBNAMES,
	SYM_DEBUG_INFO,
	SYM_DEBUG_ABBREV,
	SYM_BINARY,
	DWARF_ABBREV,
	DEBUG_INFO_ATTR
}SYM_ITEM;

INT_PTR CALLBACK Elf_Parsing_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Sym_Parsing_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Binary_View_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Dwarf_Item_View_UI(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void Init_SC_Item_List(HWND hDlg, Elf32 *elf);
void Init_PG_Item_List(HWND hDlg, Elf32 *elf);
void Init_SYM_Item_List(HWND hDlg, Elf32 *elf);
void Init_Note_List(HWND hDlg, Elf32 *elf);
void Init_Debug_Abbrev_List(HWND hDlg);
void Init_Abbrev_Attr_List(HWND hDlg);
void Init_Debug_Info_Attr_List(HWND hDlg);
void Init_Debug_Info_List(HWND hDlg);
void Init_Debug_Pubnames_List(HWND hDlg);

#endif	//SP_UI_H