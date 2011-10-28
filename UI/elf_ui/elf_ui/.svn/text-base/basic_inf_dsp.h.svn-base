#ifndef BASIC_INF_DSP_H
#define BASIC_INF_DSP_H

#include "stdafx.h"
#include "Commctrl.h"
#include "elf_header.h"
#include "edit_program.h"
#include "dwarf_header.h"

typedef enum{
	NTYPE = 0,
	NMACHINE,
	NVERSION,
	NENTRY,
	NPHOFF,
	NSHOFF,
	NFLAGS,
	NEHSIZE,
	NPHENTSIZE,
	NPHNUM,
	NSHENTSIZE,
	NSHNUM,
	NSHSTRNDX,
	NCLASS = 14,
	NDATA,
	NIVERSION
}ITEM_ELF_IDENT;

typedef enum{
	NSYM_NUM = 0,
	NSYM_VALUE,
	NSYM_SIZE,
	NSYM_BIND,
	NSYM_TYPE,
	NSYM_NDX,
	NSYM_NAME
}ITEM_ELF_SYM;

typedef enum{
	NOTE_NUM = 0,
	NOTE_NAMESZ,
	NOTE_DESCSZ,
	NOTE_TYPE,
	NOTE_NAME
}ITEM_ELF_NOTE;

typedef enum{
	DEBUG_ABBREV_NUM = 0,
	DEBUG_ABBREV_TBL_NUM,
	DEBUG_ABBREV_TAG_NAME,
	DEBUG_ABBREV_CHILDREN,
	DEBUG_ABBREV_ATTR
}DEBUG_ABBREV_ITEM;

typedef enum{
	ATTRIBUTE_NUM = 0,
	ATTRIBUTE_ENCODING,
	ATTRIBUTE_FORM_ENCODING,
	ATTRIBUTE_DATA
}ATTRIBUTE_ITEM;

//DWARF Definition.
typedef enum{
	DEBUG_INFO_NUM = 0,
	DEBUG_INFO_UNIT_LENGTH,
	DEBUG_INFO_VERSION,
	DEBUG_ABBREV_OFFSET,
	DEBUG_INFO_ADDRESS_SIZE,
	DEBUG_INFO_ABBREV_NUM,
	DEBUG_INFO_DATA_DEF
}DEBUG_INFO_ITEM;

typedef enum{
	PUBNAMES_NUM = 0,
	PUBNAMES_UNIT_LENGTH,
	PUBNAMES_VERSION,
	PUBNAMES_DEBUG_INFO_OFFSET,
	PUBNAMES_DEBUG_INFO_LENGTH,
	PUBNAMES_OFFSET,
	PUBNAMES_STRING
}PUBNAMES_ITEM;

#define NAME_ITEM	0
#define DATA_ITEM	1

void Ident_Display(HWND hDlg, ELF_IDENT *elf_ident);
void Header_Display(HWND hDlg, Elf32_Ehdr *elf_hd);

void SC_Item_List(HWND hDlg, Elf32 *elf);
void PG_Item_List(HWND hDlg, Elf32 *elf);
void Select_Section_Item(HWND hDlg, char *path, Elf32 *elf_data);
void Select_Program_Item(HWND hDlg, char *path, Elf32 *elf_data);
void Select_Symbol_Item(HWND hDlg, char *path, Elf32 *elf_data, OPTION_ENV *o_env);
void Select_Dwarf_Item(HWND hDlg);
void Select_Debug_Info_Attr_Item(HWND hDlg);
void Attribute_Data_List(HWND hDlg, DEBUG_INFO *d_info, DWARF *indwarf);
void Debug_Info_List(HWND hDlg, DWARF *indwarf);
void Debug_Pubnames_List(HWND hDlg, DWARF *indwarf);
void Debug_Abbrev_List(HWND hDlg, DWARF *indwarf);
void Attribute_Item_List(HWND hDlg, DWARF *indwarf, unsigned int nitem);
void Insert_Pubnames(HWND lc, NAME_LOOKUP_TABLES *nlt, unsigned int *nitem);
void Sym_List(HWND hDlg, Elf32 *elf);
void Note_List(HWND hDlg, Elf32 *elf);

char* Hexa_to_String(int num);
char* Dec_to_String(int num);
#endif //BASIC_INF_DSP_H