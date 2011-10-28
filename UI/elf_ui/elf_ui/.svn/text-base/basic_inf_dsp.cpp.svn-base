#include "stdafx.h"
#include <CommCtrl.h>
#include <stdio.h>
#include <Shlobj.h>
#include "resource.h"
#include "basic_inf_dsp.h"
#include "elf_header.h"
#include "parser_func.h"
#include "message_dsp.h"
#include "sp_ui.h"
#include "dwarf_attr.h"

extern HWND SYM_hWnd;
extern HWND bSYM_hWnd;
extern HWND DWARF_hWnd;
extern HINSTANCE g_hInst;

void Ident_Display(HWND hDlg, ELF_IDENT *elf_ident)
{
	HWND hItem_List = GetDlgItem(hDlg,IDC_ITEM_LIST);

	//ELF_IDENT elf_ident;
	switch(elf_ident->EI_CLASS){
		case ELFCLASSNONE:
			ListView_SetItemText(hItem_List, NCLASS, DATA_ITEM, "Invalid class");
			break;
		case ELFCLASS32:
			ListView_SetItemText(hItem_List, NCLASS, DATA_ITEM, "32-bit objects");
			break;
		case ELFCLASS64:
			ListView_SetItemText(hItem_List, NCLASS, DATA_ITEM, "64-bit objects");
			break;
		default:
			break;
	}

	switch(elf_ident->EI_DATA){
		case ELFDATANONE:
			ListView_SetItemText(hItem_List, NDATA, DATA_ITEM, "Invalid data encoding");
			break;
		case ELFDATA2LSB:
			ListView_SetItemText(hItem_List, NDATA, DATA_ITEM, "ELFDATA2LSB");
			break;
		case ELFDATA2MSB:
			ListView_SetItemText(hItem_List, NDATA, DATA_ITEM, "ELFDATA2MSB");
			break;
		default:
			break;
	}

	ListView_SetItemText(hItem_List, NIVERSION, DATA_ITEM, Dec_to_String(elf_ident->EI_VERSION));
	
}

void Header_Display(HWND hDlg, Elf32_Ehdr *elf_hd)
{
	HWND hItem_List = GetDlgItem(hDlg,IDC_ITEM_LIST);

	switch(elf_hd->e_type){
		case ET_NONE:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "ET_NONE");
			break;
		case ET_REL:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "Re-locatable file");
			break;
		case ET_EXEC:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "Executable file");
			break;
		case ET_DYN:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "Shared object file");
			break;
		case ET_CORE:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "Core file");
			break;
		case ET_LOPROC:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "Processor-specific");
			break;
		case ET_HIPROC:
			ListView_SetItemText(hItem_List, NTYPE, DATA_ITEM, "Processor-specific");
			break;
		default:
			break;
	}
	
	switch(elf_hd->e_machine){
		case EM_NONE:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "No machine\n");
			break;
		case EM_M32:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "AT&T WE 32100");
			break;
		case EM_SPARC:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "SPARC");
			break;
		case EM_386:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "Intel Architecture");
			break;
		case EM_68K:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "Motorola 68000");
			break;
		case EM_88K:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "Motorola 88000");
			break;
		case EM_860:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "Intel 80860");
			break;
		case EM_MIPS:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "MIPS RS3000 Big-Endian");
			break;
		case EM_MIPS_RS4_BE:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "MPIS RS4000 Big-Endian");
			break;
		case EM_ARM:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "ARM/Thumb Architecture");
			break;
		default:
			ListView_SetItemText(hItem_List, NMACHINE, DATA_ITEM, "...");
			break;
	}

	switch(elf_hd->e_version){
		case EV_NONE:
			ListView_SetItemText(hItem_List, NVERSION, DATA_ITEM, "Invalid version");
			break;
		case EV_CURRENT:
			ListView_SetItemText(hItem_List, NVERSION, DATA_ITEM, "Current version");
			break;
	}
	
	char temp[MAX_PATH];
	sprintf(temp, "0x%x",elf_hd->e_entry);
	ListView_SetItemText(hItem_List, NENTRY, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_phoff);
	ListView_SetItemText(hItem_List, NPHOFF, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_shoff);
	ListView_SetItemText(hItem_List, NSHOFF, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_flags);
	ListView_SetItemText(hItem_List, NFLAGS, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_ehsize);
	ListView_SetItemText(hItem_List, NEHSIZE, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_phentsize);
	ListView_SetItemText(hItem_List, NPHENTSIZE, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_phnum);
	ListView_SetItemText(hItem_List, NPHNUM, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_shentsize);
	ListView_SetItemText(hItem_List, NSHENTSIZE, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_shnum);
	ListView_SetItemText(hItem_List, NSHNUM, DATA_ITEM, temp);

	sprintf(temp, "0x%x",elf_hd->e_shstrndx);
	ListView_SetItemText(hItem_List, NSHSTRNDX, DATA_ITEM, temp);
}

void SC_Item_List(HWND hDlg, Elf32 *elf)
{
	Elf32_Shdr *sh;
	int s_type, s_flag;		//Section Types, etc flags.
	char *str_tbl;
	char *sh_type_str[16] = {"SHT_NULL", 
		"SHT_PROGBITS",
		"SHT_SYMTAB",
		"SHT_STRTAB",
		"SHT_RELA",
		"SHT_HASH",
		"SHT_DYNAMIC",
		"SHT_NOTE",
		"SHT_NOBITS",
		"SHT_REL",
		"SHT_SHLIB",
		"SHT_DYNSYM",
		"SHT_LOPROC",
		"SHT_HIPROC",
		"SHT_LOUSER",
		"SHT_HIUSER"};

	char *sh_flags[8] = {"NULL",
		"SHF_WRITE",
		"SHF_ALLOC",
		"SHF_WA",
		"SHF_EXECINSTR",
		"SHF_WE",
		"SHF_AE",
		"SHF_MASKPROC"};

	HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_LIST);

	str_tbl = elf->sc_str_tbl;
	for(unsigned int nsc = 0; nsc < elf->hd.e_shnum; nsc++){
		sh = elf->sc_hd + nsc;
		s_type = USec_Type_Index(sh->sh_type);
		s_flag = USec_Flag_Index(sh->sh_flags);

		ListView_SetItemText(hItem_List, nsc, SC_NAME, str_tbl+sh->sh_name);
		ListView_SetItemText(hItem_List, nsc, SC_TYPE, sh_type_str[s_type]);
		ListView_SetItemText(hItem_List, nsc, SC_ADDR, Hexa_to_String(sh->sh_addr));
		ListView_SetItemText(hItem_List, nsc, SC_OFFSET, Hexa_to_String(sh->sh_offset));
		ListView_SetItemText(hItem_List, nsc, SC_HSIZE, Hexa_to_String(sh->sh_size));
		ListView_SetItemText(hItem_List, nsc, SC_FLAGS, sh_flags[s_flag]);
		ListView_SetItemText(hItem_List, nsc, SC_LINK, Hexa_to_String(sh->sh_link));
	}
}

void PG_Item_List(HWND hDlg, Elf32 *elf)
{
	int nph = 0;
	Elf32_Phdr	*ph;
	char *p_type_str[9] = {"NULL",
		"LOAD",
		"DYNAMIC",
		"INTERP",
		"NOTE",
		"SHLIB",
		"PHDR",
		"LOPRPC",
		"HIPROC"};
	char *p_flag_str[8] = {"NULL", "X", "W", "XW", "R", "XR", "WR", "XWR"};
	unsigned int flag = 0;

	HWND hItem_List = GetDlgItem(hDlg, IDC_PROGRAM_LIST);

	for(nph = 0; nph < elf->hd.e_phnum; nph++){
		ph = elf->prog_hd + nph;
		if(ph->p_flags == PF_MASKPROC)
			flag = 0;
		else
			flag = ph->p_flags;

		ListView_SetItemText(hItem_List, nph, PG_TYPE, p_type_str[UGet_Prog_Type_Name(ph->p_type)]);
		ListView_SetItemText(hItem_List, nph, PG_OFFSET, Hexa_to_String(ph->p_offset));
		ListView_SetItemText(hItem_List, nph, PG_VADDR, Hexa_to_String(ph->p_vaddr));
		ListView_SetItemText(hItem_List, nph, PG_PADDR, Hexa_to_String(ph->p_paddr));
		ListView_SetItemText(hItem_List, nph, PG_FILESZ, Hexa_to_String(ph->p_filesz));
		ListView_SetItemText(hItem_List, nph, PG_MEMSZ, Hexa_to_String(ph->p_memsz));
		ListView_SetItemText(hItem_List, nph, PG_FLAGS, p_flag_str[flag]);

	}
}

void Sym_List(HWND hDlg, Elf32 *elf)
{
	int nsym = 0;
	int sym_num = 0;
	Elf32_Shdr *sh;
	Elf32_Sym  *sym;
	char *str_tbl;
	int sym_bind = 0, sym_type = 0, sym_info = 0, ss_index = 0;
	char *sym_bind_name[5] = {"LOCAL",
		"GLOBAL",
		"WEAK",
		"LOPROC",
		"HIPROC"};

	char *sym_type_name[7] = {"NOTYPE",
		"OBJECT",
		"FUNC",
		"SECTION",
		"FILE",
		"LOPROC",
		"HIPROC"};

	char *sym_ndex[7] = {"UNDEF",
		"LORESERVE",
		"LOPROC",
		"HIPROC",
		"ABS",
		"COMMON",
		"HIRESERVE"};

	HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_ITEM_LIST);

	sh = elf->sc_hd + Get_Section_Index(elf, SHT_SYMTAB);

	sym_num = sh->sh_size/ sizeof(Elf32_Sym);
	str_tbl = elf->sym_str_tbl;

	for(nsym = 0; nsym < sym_num; nsym++){
		sym = elf->sym_hd + nsym;
		sym_bind = UGet_Sym_Bind_Name(ELF32_ST_BIND(sym->st_info));
		sym_type = UGet_Sym_Type_Name(ELF32_ST_TYPE(sym->st_info));
		sym_info = ELF32_ST_INFO(sym_bind, sym_type);
		ss_index = UGet_Ss_Index_Name(sym->st_shndx);
		if(ss_index != 7){
			ListView_SetItemText(hItem_List, nsym, NSYM_VALUE, Hexa_to_String(sym->st_value));
			ListView_SetItemText(hItem_List, nsym, NSYM_SIZE, Hexa_to_String(sym->st_size));
			ListView_SetItemText(hItem_List, nsym, NSYM_BIND, sym_bind_name[sym_bind]);
			ListView_SetItemText(hItem_List, nsym, NSYM_TYPE, sym_type_name[sym_type]);
			ListView_SetItemText(hItem_List, nsym, NSYM_NDX, sym_ndex[ss_index]);
			ListView_SetItemText(hItem_List, nsym, NSYM_NAME, str_tbl + sym->st_name);
		}
		else{
			ListView_SetItemText(hItem_List, nsym, NSYM_VALUE, Hexa_to_String(sym->st_value));
			ListView_SetItemText(hItem_List, nsym, NSYM_SIZE, Hexa_to_String(sym->st_size));
			ListView_SetItemText(hItem_List, nsym, NSYM_BIND, sym_bind_name[sym_bind]);
			ListView_SetItemText(hItem_List, nsym, NSYM_TYPE, sym_type_name[sym_type]);
			ListView_SetItemText(hItem_List, nsym, NSYM_NDX, Hexa_to_String(sym->st_shndx));
			ListView_SetItemText(hItem_List, nsym, NSYM_NAME, str_tbl + sym->st_name);
		}
	}
}

void Note_List(HWND hDlg, Elf32 *elf)
{
	int nnote;
	Elf32_Shdr *sh;
	Elf32_Note *sn;
	char s_index;
	int note_num = 0;

	HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_ITEM_LIST);

	s_index = Get_Section_Index(elf, SHT_NOTE);
	sh = elf->sc_hd + s_index;
	note_num = sh->sh_size/sizeof(Elf32_Note);

	for(nnote = 0; nnote < note_num; nnote++){
		sn = elf->sc_note + nnote;
		ListView_SetItemText(hItem_List, nnote, NOTE_NAMESZ, Hexa_to_String(sn->namesz));
		ListView_SetItemText(hItem_List, nnote, NOTE_DESCSZ, Hexa_to_String(sn->descsz));
		ListView_SetItemText(hItem_List, nnote, NOTE_TYPE, Hexa_to_String(sn->n_type));
		ListView_SetItemText(hItem_List, nnote, NOTE_NAME, sn->note_name);		
	}
}

void Debug_Abbrev_List(HWND hDlg, DWARF *indwarf)
{
	unsigned int dabbn;
	unsigned int note_num = 0;
	unsigned int nitem = 0;
	LVITEM LI;
	DEBUG_ABBREV *dabb;
	char temp_str[MAX_PATH];
	char *child_name[2] = {"DW_CHILDREN_no",
						   "DW_CHILDREN_yes"};
	char *tag_names[0x39] = {"Unknown",								
							 "DW_TAG_array_type",					//0x01
							 "DW_TAG_class_type",					//0x02
							 "DW_TAG_entry_point",					//0x03
							 "DW_TAG_enumeration_type",				//0x04
							 "DW_TAG_formal_parameter",				//0x05
							 "Unknown",								
							 "Unknown",								
							 "DW_TAG_imported_declaration",			//0x08
							 "Unknown",								
							 "DW_TAG_label",						//0x0a
							 "DW_TAG_lexical_block",				//0x0b
							 "Unknown",								
							 "DW_TAG_member",						//0x0d
							 "Unknown",								
							 "DW_TAG_pointer_type",					//0x0f
							 "DW_TAG_reference_type",				//0x10
							 "DW_TAG_compile_unit",					//0x11
							 "DW_TAG_string_type",					//0x12
							 "DW_TAG_structue_type",				//0x13
							 "Unknown",
							 "DW_TAG_subroutine_type",				//0x15
							 "DW_TAG_typedef",						//0x16
							 "DW_TAG_union_type",					//0x17
							 "DW_TAG_unspecified_parameters",		//0x18
							 "DW_TAG_variant",						//0x19
							 "DW_TAG_common_block",					//0x1a
							 "DW_TAG_common_inclusion",				//0x1b
							 "DW_TAG_inheritance",					//0x1c
						 	 "DW_TAG_inlined_subroutine",			//0x1d
							 "DW_TAG_module",						//0x1e
							 "DW_TAG_ptr_to_member_type",			//0x1f
							 "DW_TAG_set_type",						//0x20
							 "DW_TAG_subrange_type",				//0x21
							 "DW_TAG_with_stmt",					//0x22
							 "DW_TAG_access_declaration",			//0x23
							 "DW_TAG_base_type",					//0x24
							 "DW_TAG_catch_block",					//0x25
							 "DW_TAG_const_type",					//0x26
							 "DW_TAG_constant",						//0x27
							 "DW_TAG_enumerator",					//0x28
							 "DW_TAG_file_type",					//0x29
							 "DW_TAG_friend",						//0x2a
							 "DW_TAG_namelist",						//0x2b
							 "DW_TAG_namelist_item",				//0x2c
							 "DW_TAG_packed_type",					//0x2d
							 "DW_TAG_subprogram",					//0x2e
							 "DW_TAG_template_type_param",			//0x2f
							 "DW_TAG_template_value_param",			//0x30
							 "DW_TAG_thrown_type",					//0x31
							 "DW_TAG_try_block",					//0x32
							 "DW_TAG_variant_part",					//0x33
							 "DW_TAG_variable",						//0x34
							 "DW_TAG_volatile_type",				//0x35
							 "DW_TAG_lo_user",						//0x4080
							 "DW_TAG_hi_user"						//0xffff
							 };

	HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_ITEM_LIST);

	for(dabbn = 0; dabbn < indwarf->debug_abbrev_num; dabbn++){
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = dabbn;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(dabbn);
		ListView_InsertItem(hItem_List, &LI);

		dabb = indwarf->debug_abbrev + dabbn;
		ListView_SetItemText(hItem_List, dabbn, DEBUG_ABBREV_TBL_NUM, Hexa_to_String(dabb->debug_abbrev_hd.abbrev_table_num));
		
		if(dabb->debug_abbrev_hd.tag_encoding == 0x4080){
			sprintf(temp_str,"%s(0x%x)", tag_names[0x36], dabb->debug_abbrev_hd.tag_encoding);
		}
		else if(dabb->debug_abbrev_hd.tag_encoding == 0xffff){
			sprintf(temp_str,"%s(0x%x)", tag_names[0x37], dabb->debug_abbrev_hd.tag_encoding);
		}
		else
			sprintf(temp_str,"%s(0x%x)", tag_names[dabb->debug_abbrev_hd.tag_encoding], dabb->debug_abbrev_hd.tag_encoding);
		ListView_SetItemText(hItem_List, dabbn, DEBUG_ABBREV_TAG_NAME, temp_str);
		//ListView_SetItemText(hItem_List, dabbn, DEBUG_ABBREV_TAG_NAME, Hexa_to_String(dabb->debug_abbrev_hd.tag_encoding));
		ListView_SetItemText(hItem_List, dabbn, DEBUG_ABBREV_CHILDREN, child_name[dabb->debug_abbrev_hd.child_encoding]);

		if(dabb->attribute_num != 0){
			ListView_SetItemText(hItem_List, dabbn, DEBUG_ABBREV_ATTR, "CLICK");
		}
	}
}

void Attribute_Item_List(HWND hDlg, DWARF *indwarf, unsigned int nitem)
{
	DEBUG_ABBREV *dbg_abb;
	DEBUG_ABBREV_ATTRIBUTE *dbg_abb_att;
	unsigned int attn = 0;
	HWND hItem_List = GetDlgItem(hDlg, IDC_DWARF_ITEM_LIST);
	LVITEM LI;
	char temp_str[MAX_PATH];
	char *att_enc_name[0x50] = {"Unknown", 
		"DW_AT_sibling", "DW_AT_location", "DW_AT_name", "Unknown", 
		"Unknown", "Unknown", "Unknown", "Unknown", 
		"DW_AT_ordering", "DW_AT_byte_size", "DW_AT_bit_offset", "DW_AT_bit_size", 
		"Unknown", "Unknown", "Unknown", "DW_AT_stmt_list", 
		"DW_AT_low_pc", "DW_AT_high_pc", "DW_AT_language", "Unknown", 
		"DW_AT_discr", "DW_AT_discr_value", "DW_AT_visibility", "DW_AT_import", 
		"DW_AT_string_length", "DW_AT_common_reference", "DW_AT_comp_dir", "DW_AT_const_value",
		"DW_AT_containing_type", "DW_AT_default_value",	"Unknown", "DW_AT_inline", 
		"DW_AT_is_optional", "DW_AT_lower_bound", "Unknown", "Unknown", 
		"DW_AT_producer", "Unknown", "DW_AT_prototyped", "Unknown", 
		"Unknown", "DW_AT_return_addr", "Unknown", "DW_AT_start_scope", 
		"Unknown", "DW_AT_stride_size", "DW_AT_upper_bound", "Unknown",
		"DW_AT_abstract_origin", "DW_AT_accessibility", "DW_AT_address_class", "DW_AT_artificial", 
		"DW_AT_base_types",	"DW_AT_calling_convention", "DW_AT_count", "DW_AT_data_member_location",
		"DW_AT_decl_column", "DW_AT_decl_file", "DW_AT_decl_line", "DW_AT_declaration",
		"DW_AT_discr_list",	"DW_AT_encoding", "DW_AT_external", "DW_AT_frame_base",
		"DW_AT_friend", "DW_AT_identifier_case", "DW_AT_macro_info", "DW_AT_namelist_item", 
		"DW_AT_priority", "DW_AT_segment", "DW_AT_specification", "DW_AT_static_link",
		"DW_AT_type", "DW_AT_use_location", "DW_AT_variable_parameter", "DW_AT_virtuality",
		"DW_AT_vtable_elem_location", "DW_AT_lo_user", "DW_AT_hi_user"
	};

	char *att_form_name[0x17] = { "Unknown",
		"DW_FORM_addr", "Unknown", "DW_FORM_block2", "DW_FORM_block4", 
		"DW_FORM_data2", "DW_FORM_data4", "DW_FORM_data8", "DW_FORM_string", 
		"DW_FORM_block", "DW_FORM_block1", "DW_FORM_data1", "DW_FORM_flag", 
		"DW_FORM_sdata", "DW_FORM_strp", "DW_FORM_udata", "DW_FORM_ref_addr", 
		"DW_FORM_ref1", "DW_FORM_ref2", "DW_FORM_ref4", "DW_FORM_ref8", 
		"DW_FORM_ref_udata", "DW_FORM_indirect"
	};
	sprintf(temp_str, "Abbreviation Tables:(0x%x)",nitem);
	SetWindowText(hDlg, temp_str);
	for(attn = 0; attn < indwarf->debug_abbrev_num; attn++){
		dbg_abb = indwarf->debug_abbrev + attn;
		if(dbg_abb->debug_abbrev_hd.abbrev_table_num == nitem){
			break;
		}
	}
	//dbg_abb = indwarf->debug_abbrev + nitem;

	for(attn = 0; attn < dbg_abb->attribute_num; attn++){
		dbg_abb_att = dbg_abb->debug_abbrev_attribute + attn;
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = attn;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(attn);
		ListView_InsertItem(hItem_List, &LI);
		
		sprintf(temp_str,"%s(0x%x)",att_enc_name[dbg_abb_att->attribute_encoding],dbg_abb_att->attribute_encoding);
		ListView_SetItemText(hItem_List, attn, ATTRIBUTE_ENCODING, temp_str);
		sprintf(temp_str,"%s(0x%x)",att_form_name[dbg_abb_att->attribute_form],dbg_abb_att->attribute_form);
		ListView_SetItemText(hItem_List, attn, ATTRIBUTE_FORM_ENCODING, temp_str);

		//ListView_SetItemText(hItem_List, attn, ATTRIBUTE_ENCODING, Hexa_to_String(dbg_abb_att->attribute_encoding));
		//ListView_SetItemText(hItem_List, attn, ATTRIBUTE_FORM_ENCODING, Hexa_to_String(dbg_abb_att->attribute_form));
	}
}

void Attribute_Data_List(HWND hDlg, DEBUG_INFO *d_info, DWARF *indwarf)
{
	DEBUG_ABBREV *dbg_abb;
	DEBUG_ABBREV_ATTRIBUTE *dbg_abb_att;
	unsigned int attn = 0, str_p = 0;
	HWND hItem_List = GetDlgItem(hDlg, IDC_DWARF_ITEM_LIST);
	char temp_str[MAX_PATH];
	unsigned char *data;
	unsigned char constant_data[4];
	
	for(attn = 0; attn < indwarf->debug_abbrev_num; attn++){
		dbg_abb = indwarf->debug_abbrev + attn;
		if(dbg_abb->debug_abbrev_hd.abbrev_table_num == d_info->debug_info_entry.abbrev_table_num){
			break;
		}
	}
	
	for(attn = 0; attn < dbg_abb->attribute_num; attn++){
		dbg_abb_att = dbg_abb->debug_abbrev_attribute + attn;
		memset(constant_data,0,sizeof(unsigned char) * 4);
		switch(dbg_abb_att->attribute_form){
			case DW_FORM_addr:
				break;
			case DW_FORM_block2:
				break;
			case DW_FORM_block4:
				break;
			case DW_FORM_data2:
				break;
			case DW_FORM_data4:
				memcpy(constant_data, d_info->debug_info_entry.info_data + str_p, sizeof(unsigned char) * 4);
				str_p += 4;
				break;
			case DW_FORM_data8:
				memcpy(constant_data, d_info->debug_info_entry.info_data + str_p, sizeof(unsigned char) * 8);
				str_p += 8;
				break;
			case DW_FORM_strp:
			case DW_FORM_string:
				strcpy(temp_str, (char *)(d_info->debug_info_entry.info_data + str_p));
				str_p += strlen((char *)(d_info->debug_info_entry.info_data + str_p));
				str_p++;
				ListView_SetItemText(hItem_List, attn, ATTRIBUTE_DATA, temp_str);
				break;
			case DW_FORM_block:
				break;
			case DW_FORM_block1:
				memcpy(constant_data, d_info->debug_info_entry.info_data + str_p, sizeof(unsigned char));
				str_p++;
				break;
			case DW_FORM_data1:
				memcpy(constant_data, d_info->debug_info_entry.info_data + str_p, sizeof(unsigned char));
				str_p++;				
				break;
			case DW_FORM_flag:
				memcpy(constant_data, d_info->debug_info_entry.info_data + str_p, sizeof(unsigned char));
				str_p++;
				break;
			case DW_FORM_sdata:
				break;
			case DW_FORM_udata:
				break;
			case DW_FORM_ref_addr:
				break;
			case DW_FORM_ref1:
				break;
			case DW_FORM_ref2:
				break;
			case DW_FORM_ref4:
				break;
			case DW_FORM_ref8:
				break;
			case DW_FORM_ref_udata:
				break;
			case DW_FORM_indirect:
				break;
			default:
				break;
		}
		if((dbg_abb_att->attribute_form != DW_FORM_strp) && (dbg_abb_att->attribute_form != DW_FORM_string)){
			unsigned int temp_data = *((unsigned int *)constant_data);
			ListView_SetItemText(hItem_List, attn, ATTRIBUTE_DATA, Hexa_to_String(temp_data));
		}
	}
}

void Debug_Info_List(HWND hDlg, DWARF *indwarf)
{
	unsigned int difn;
	unsigned int note_num = 0;
	unsigned int nitem = 0;
	LVITEM LI;
	DEBUG_INFO *dif;

	HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_ITEM_LIST);

	for(difn = 0; difn < indwarf->debug_info_num; difn++){
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = difn;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(difn);
		ListView_InsertItem(hItem_List, &LI);

		dif = indwarf->debug_info + difn;
		ListView_SetItemText(hItem_List, difn, DEBUG_INFO_UNIT_LENGTH, Hexa_to_String(dif->debug_info_hd.unit_length));
		ListView_SetItemText(hItem_List, difn, DEBUG_INFO_VERSION, Hexa_to_String(dif->debug_info_hd.version));
		ListView_SetItemText(hItem_List, difn, DEBUG_ABBREV_OFFSET, Hexa_to_String(dif->debug_info_hd.debug_abbrev_offset));
		ListView_SetItemText(hItem_List, difn, DEBUG_INFO_ADDRESS_SIZE, Hexa_to_String(dif->debug_info_hd.address_size));
		ListView_SetItemText(hItem_List, difn, DEBUG_INFO_ABBREV_NUM, Hexa_to_String(dif->debug_info_entry.abbrev_table_num));
		ListView_SetItemText(hItem_List, difn, DEBUG_INFO_DATA_DEF, "Click");
	}
}

void Debug_Pubnames_List(HWND hDlg, DWARF *indwarf)
{
	unsigned int pubn;
	unsigned int note_num = 0;
	unsigned int nitem = 0;
	NAME_LOOKUP_TABLES *nlt;	
	LVITEM LI;

	HWND hItem_List = GetDlgItem(hDlg, IDC_SECTION_ITEM_LIST);

	for(pubn = 0; pubn < indwarf->debug_pubnames_num; pubn++){
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = nitem;
		LI.pszText = (LPSTR)(LPCSTR)Dec_to_String(pubn);
		ListView_InsertItem(hItem_List, &LI);

		nlt = indwarf->debug_pubnames + pubn;
		ListView_SetItemText(hItem_List, nitem, PUBNAMES_UNIT_LENGTH, Hexa_to_String(nlt->nlt_hd.unit_length));
		ListView_SetItemText(hItem_List, nitem, PUBNAMES_VERSION, Hexa_to_String(nlt->nlt_hd.version));
		ListView_SetItemText(hItem_List, nitem, PUBNAMES_DEBUG_INFO_OFFSET, Hexa_to_String(nlt->nlt_hd.debug_info_offset));
		ListView_SetItemText(hItem_List, nitem, PUBNAMES_DEBUG_INFO_LENGTH, Hexa_to_String(nlt->nlt_hd.debug_info_lenght));		
		ListView_SetItemText(hItem_List, nitem, PUBNAMES_OFFSET, Hexa_to_String(nlt->pubname_pair->offset));		
		ListView_SetItemText(hItem_List, nitem, PUBNAMES_STRING, nlt->pubname_pair->pubname);
		Insert_Pubnames(hItem_List, nlt, &nitem);
		nitem++;
	}
}

/*********************************************************************************/
//Description:
// This function select a section and then the contained data of each sections 
// is represented on a dialog window.
//Parameter:
// - hDlg: Parent windows.
// - path: path of  elf file.
// - elf_data: elf structure.
/*********************************************************************************/
void Select_Section_Item(HWND hDlg, char *path, Elf32 *elf_data)
{
	int idx = 0;
	char sel_item_str[MAX_PATH];

	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_LIST);

	idx = ListView_GetNextItem(hItem_List,-1,LVNI_ALL|LVNI_SELECTED);
	if(idx > 0){
		ListView_GetItemText(hItem_List, idx, SC_NAME, sel_item_str, MAX_PATH);
		if(!strcmp(sel_item_str, ".comment")){
			Get_Section_Data(path, elf_data, ".comment", &(elf_data->sc_comment), NULL);
			MessageBox(hDlg, elf_data->sc_comment, ".comment", MB_OK);
			UComment_Dmsg(elf_data);
		}
		else if(!strcmp(sel_item_str, ".symtab")){
			SYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SECTION_ITEM_FRAME), hDlg, Sym_Parsing_UI);
			SetWindowText(SYM_hWnd, ".symtab");
			SendMessage(SYM_hWnd, WM_COMMAND, SYM_SYMTAB, 0);
		}
		else if(!strcmp(sel_item_str, ".note")){
			SYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SECTION_ITEM_FRAME), hDlg, Sym_Parsing_UI);
			SetWindowText(SYM_hWnd, ".note");
			SendMessage(SYM_hWnd, WM_COMMAND, SYM_NOTE, 0);
		}
		else{
			Get_Section_Data(path, elf_data, sel_item_str, &(elf_data->temp_data), NULL);	
			if(!strcmp(sel_item_str, ".debug_pubnames")){
				SYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SECTION_ITEM_FRAME), hDlg, Sym_Parsing_UI);
				SetWindowText(SYM_hWnd, ".debug_pubnames");
				SendMessage(SYM_hWnd, WM_COMMAND, SYM_DEBUG_PUBNAMES, 0);
			}
			else if(!strcmp(sel_item_str, ".debug_info")){
				SYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SECTION_ITEM_FRAME), hDlg, Sym_Parsing_UI);
				SetWindowText(SYM_hWnd, ".debug_info");
				SendMessage(SYM_hWnd, WM_COMMAND, SYM_DEBUG_INFO, 0);
			}
			else if(!strcmp(sel_item_str, ".debug_abbrev")){
				SYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SECTION_ITEM_FRAME), hDlg, Sym_Parsing_UI);
				SetWindowText(SYM_hWnd, ".debug_abbrev");
				SendMessage(SYM_hWnd, WM_COMMAND, SYM_DEBUG_ABBREV, 0);
			}
			else{
				bSYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_BINARY_VIEW), hDlg, Binary_View_UI);
				SetWindowText(bSYM_hWnd, sel_item_str);
				SendMessage(bSYM_hWnd, WM_COMMAND, SYM_BINARY, 0);
			}
		}
	}
}

void Select_Program_Item(HWND hDlg, char *path, Elf32 *elf_data)
{
	int idx = 0;
	char sel_item_str[MAX_PATH];

	HWND hItem_List = GetDlgItem(hDlg,IDC_PROGRAM_LIST);

	idx = ListView_GetNextItem(hItem_List,-1,LVNI_ALL|LVNI_SELECTED);
	if(idx > 0){
		ListView_GetItemText(hItem_List, idx, PG_TYPE, sel_item_str, MAX_PATH);
		/*if(!strcmp(sel_item_str, ".comment")){
		}
		else{
			SYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_SECTION_ITEM_FRAME), hDlg, Sym_Parsing_UI);
			if(!strcmp(sel_item_str, ".symtab")){
				SendMessage(SYM_hWnd, WM_COMMAND, SYM_SYMTAB, 0);
			}
			else if(!strcmp(sel_item_str, ".note")){
				SendMessage(SYM_hWnd, WM_COMMAND, SYM_NOTE, 0);
			}
		}*/
	}
}

/***************************************************************************************/
//Description:
// This function represent the data of a symbol. 
//Parameter:
// hDlg: Parent window.
// path: path of elf.
// elf_data: elf structure.
// o_env: structure for program environment.
/***************************************************************************************/
void Select_Symbol_Item(HWND hDlg, char *path, Elf32 *elf_data, OPTION_ENV *o_env)
{
	int idx = 0;
	char sel_item_str[MAX_PATH];
	char sel_ndx[MAX_PATH];
	char *sec_str;
	char temp_str[MAX_PATH];
	int nsym = 0, ndx_num = 0;
	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);
	Elf32_Sym *sym;
	Elf32_Shdr *sh;
	

	idx = ListView_GetNextItem(hItem_List,-1,LVNI_ALL|LVNI_SELECTED);
	if(idx > 0){
		ListView_GetItemText(hItem_List, idx, NSYM_TYPE, sel_item_str, MAX_PATH);
		if(!strcmp(sel_item_str, "FILE")){
			char file_path[MAX_PATH];
			char cmd_str[MAX_PATH];
			ListView_GetItemText(hItem_List, idx, NSYM_NAME, file_path, MAX_PATH);
			
			sprintf(cmd_str,"%s %s", o_env->edit_cmd, file_path);
			WinExec(cmd_str, SW_SHOW);
		}
		else{
			ListView_GetItemText(hItem_List, idx, NSYM_NUM, sel_ndx, MAX_PATH);
			nsym = atoi(sel_ndx);
			sym = elf_data->sym_hd + nsym;		//get a symbol.
			ndx_num = sym->st_shndx;			//get section index of a symbol.
			if((ndx_num != 0) && (ndx_num <= elf_data->hd.e_shnum)){
				sec_str = elf_data->sc_str_tbl;	//get section string table.
				sh = elf_data->sc_hd + ndx_num;	//get a section.
				strcpy(temp_str, (sec_str + sh->sh_name));	//get name of the section.
				bSYM_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_BINARY_VIEW), hDlg, Binary_View_UI);
				//Get_Section_Data(path, elf_data, temp_str, &(elf_data->temp_data), sym->st_size);	
				Get_Section_Data(path, elf_data, temp_str, &(elf_data->temp_data), NULL);	
				ListView_GetItemText(hItem_List, idx, NSYM_NAME, sel_item_str, MAX_PATH);
				SetWindowText(bSYM_hWnd, sel_item_str);
				SendMessage(bSYM_hWnd, WM_COMMAND, SYM_BINARY, 0);
			}
		}
	}
}

void Select_Dwarf_Item(HWND hDlg)
{
	int idx = 0;
	char sel_ndx[MAX_PATH];
	unsigned int nitem = 0;
	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	idx = ListView_GetNextItem(hItem_List,-1,LVNI_ALL|LVNI_SELECTED);
	ListView_GetItemText(hItem_List, idx, DEBUG_ABBREV_NUM, sel_ndx, MAX_PATH);
	nitem = atoi(sel_ndx);
	DWARF_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DWARF_ITEM), hDlg, Dwarf_Item_View_UI);
	//SetWindowText(bSYM_hWnd, sel_item_str);
	SendMessage(DWARF_hWnd, WM_COMMAND, DWARF_ABBREV, nitem);
}

void Select_Debug_Info_Attr_Item(HWND hDlg)
{
	int idx = 0;
	char sel_ndx[MAX_PATH];
	unsigned int nitem = 0;
	HWND hItem_List = GetDlgItem(hDlg,IDC_SECTION_ITEM_LIST);

	idx = ListView_GetNextItem(hItem_List,-1,LVNI_ALL|LVNI_SELECTED);
	ListView_GetItemText(hItem_List, idx, DEBUG_INFO_NUM, sel_ndx, MAX_PATH);
	nitem = atoi(sel_ndx);
	DWARF_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DWARF_ITEM), hDlg, Dwarf_Item_View_UI);
	//SetWindowText(bSYM_hWnd, sel_item_str);
	SendMessage(DWARF_hWnd, WM_COMMAND, DEBUG_INFO_ATTR,nitem);
}

void Insert_Pubnames(HWND lc, NAME_LOOKUP_TABLES *nlt, unsigned int *nitem)
{
	LVITEM LI;
	unsigned int str_n = 0;
	PUBNAME_PAIR *pub_pair = 0;
	unsigned int pubn_num = *nitem;

	for(str_n = 1; str_n < nlt->pubname_num;str_n++){
		pub_pair = nlt->pubname_pair + str_n;
		pubn_num++;
		LI.mask = LVIF_TEXT;
		LI.state = 0;
		LI.stateMask = 0;
		LI.iSubItem = 0;
		LI.iItem = pubn_num;
		LI.pszText = "";
		ListView_InsertItem(lc, &LI);
		
		//ListView_SetItemText(lc, pubn_num, PUBNAMES_UNIT_LENGTH, Hexa_to_String(nlt->nlt_hd.unit_length));
		//ListView_SetItemText(lc, pubn_num, PUBNAMES_VERSION, Hexa_to_String(nlt->nlt_hd.version));
		//ListView_SetItemText(lc, pubn_num, PUBNAMES_DEBUG_INFO_OFFSET, Hexa_to_String(nlt->nlt_hd.debug_info_offset));
		//ListView_SetItemText(lc, pubn_num, PUBNAMES_DEBUG_INFO_LENGTH, Hexa_to_String(nlt->nlt_hd.debug_info_lenght));
		ListView_SetItemText(lc, pubn_num, PUBNAMES_OFFSET, Hexa_to_String(pub_pair->offset));
		ListView_SetItemText(lc, pubn_num, PUBNAMES_STRING, pub_pair->pubname);			
	}
	*nitem = pubn_num;
}

char* Hexa_to_String(int num)
{
	static char str_buff[MAX_PATH];
	if(num != 0)
		sprintf(str_buff,"0x%x",num);
	else
		sprintf(str_buff,"%x",num);
	return str_buff;
}

char* Dec_to_String(int num)
{
	static char str_buff[MAX_PATH];
	sprintf(str_buff,"%d",num);
	return str_buff;
}
