//////////////////////////////////////////////////////////////////////////////
//File name : dmsg_func.c
//
#include "stdafx.h"
#include <stdio.h>
#include "var_type.h"
#include "elf_header.h"
#include "parser_func.h"
#include "resource.h"

extern HWND Main_hWnd;

void Display_Status(char *str)
{
	char temp_str[MAX_PATH];

	strcpy(temp_str, str);
	strcat(temp_str, "\r\n");
	HWND Str_Status = GetDlgItem(Main_hWnd, IDC_STATUS);
	SendMessage(Str_Status, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)temp_str);
	UpdateWindow(Str_Status);
}

void Nr_Display_Status(char *str)
{
	char temp_str[MAX_PATH];

	strcpy(temp_str, str);
	HWND Str_Status = GetDlgItem(Main_hWnd, IDC_STATUS);
	SendMessage(Str_Status, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)temp_str);
	UpdateWindow(Str_Status);
}

void UIdent_Dmsg(ELF_IDENT *elf_ident)
{
	char buff[MAX_PATH];

	//ELF_IDENT elf_ident;
	Display_Status("\n");
	Display_Status("[ARM ELF Information]");
	Nr_Display_Status("The data encoding of all data in the object file: ");
	switch(elf_ident->EI_CLASS){
		case ELFCLASSNONE:
			Display_Status("Invalid class");
			break;
		case ELFCLASS32:
			Display_Status("32-bit objects");
			break;
		case ELFCLASS64:
			Display_Status("64-bit objects");
			break;
		default:
			break;
	}

	Nr_Display_Status("The ELF header version number: ");
	switch(elf_ident->EI_DATA){
		case ELFDATANONE:
			Display_Status("Invalid data encoding");
			break;
		case ELFDATA2LSB:
			Display_Status("Data encodings ELFDATA2LSB");
			break;
		case ELFDATA2MSB:
			Display_Status("Data encodings ELFDATA2MSB");
			break;
		default:
			break;
	}
	
	sprintf(buff, "ELF header version number: %d", elf_ident->EI_VERSION);
	Display_Status(buff);
	Display_Status("\n");
}

void UHeader_Dmsg(Elf32_Ehdr *elf_hd)
{
	char buff[MAX_PATH];

	Nr_Display_Status("Object File type: ");
	switch(elf_hd->e_type){
		case ET_NONE:
			Display_Status("ET_NONE\n");
			break;
		case ET_REL:
			Display_Status("Re-locatable file\n");
			break;
		case ET_EXEC:
			Display_Status("Executable file\n");
			break;
		case ET_DYN:
			Display_Status("Shared object file\n");
			break;
		case ET_CORE:
			Display_Status("Core file\n");
			break;
		case ET_LOPROC:
			Display_Status("Processor-specific\n");
			break;
		case ET_HIPROC:
			Display_Status("Processor-specific\n");
			break;
		default:
			break;
	}
	Nr_Display_Status("The required architecture: ");
	switch(elf_hd->e_machine){
		case EM_NONE:
			Display_Status("No machine\n");
			break;
		case EM_M32:
			Display_Status("AT&T WE 32100\n");
			break;
		case EM_SPARC:
			Display_Status("SPARC\n");
			break;
		case EM_386:
			Display_Status("Intel Architecture\n");
			break;
		case EM_68K:
			Display_Status("Motorola 68000\n");
			break;
		case EM_88K:
			Display_Status("Motorola 88000\n");
			break;
		case EM_860:
			Display_Status("Intel 80860\n");
			break;
		case EM_MIPS:
			Display_Status("MIPS RS3000 Big-Endian\n");
			break;
		case EM_MIPS_RS4_BE:
			Display_Status("MPIS RS4000 Big-Endian\n");
			break;
		case EM_ARM:
			Display_Status("ARM/Thumb Architecture\n");
			break;
		default:
			Display_Status("...\n");
			break;
	}

	Nr_Display_Status("The object file version: ");
	switch(elf_hd->e_version){
		case EV_NONE:
			Display_Status("Invalid version\n");
			break;
		case EV_CURRENT:
			Display_Status("Current version\n");
			break;
	}

	sprintf(buff,"The virtual address(E_entry): %x\n",elf_hd->e_entry);
	Display_Status(buff);
	sprintf(buff,"The program header table's file offset(E_phoff): 0x%x Bytes\n",elf_hd->e_phoff);
	Display_Status(buff);
	sprintf(buff,"The Section header table's file offset(E_shoff): 0x%x Bytes\n",elf_hd->e_shoff);
	Display_Status(buff);
	sprintf(buff,"Processor-specific flags associated with the file(E_flags): 0x%x\n",elf_hd->e_flags);
	Display_Status(buff);
	sprintf(buff,"The ELF header's size(E_ehsize): 0x%x Bytes\n",elf_hd->e_ehsize);
	Display_Status(buff);
	sprintf(buff,"The size of one entry in the file's program header table(E_phentsize): %d Bytes\n",elf_hd->e_phentsize);
	Display_Status(buff);
	sprintf(buff,"The number of entries in the program header table(E_phnum): %d\n",elf_hd->e_phnum);
	Display_Status(buff);
	sprintf(buff,"A section header's size(E_shentsize): %d Bytes\n",elf_hd->e_shentsize);
	Display_Status(buff);
	sprintf(buff,"The number of entries in the section header table(E_shnum): %d\n",elf_hd->e_shnum);
	Display_Status(buff);
	sprintf(buff,"The section header table index of the entry associated with\n");
	Display_Status(buff);
	sprintf(buff,"The section name string table(E_shstrndx): %d\n",elf_hd->e_shstrndx);
	Display_Status(buff);
	Display_Status("\n");
}

int USec_Type_Index(int index)
{
	int s_type;

	switch(index){
		case SHT_LOPROC:
			s_type = 12;
			break;
		case SHT_HIPROC:
			s_type = 13;
			break;
		case SHT_LOUSER:
			s_type = 14;
			break;
		case SHT_HIUSER:
			s_type = 15;
			break;
		default:
			s_type = index;
	}
	return s_type;
}

int USec_Flag_Index(int index)
{
	int s_flag;

	switch(index){
		case SHF_MASKPROC:
			s_flag = 7;
			break;
		default:
			s_flag = index;
	}
	return s_flag;
}

int UGet_Prog_Type_Name(int index)
{
	int s_flag = 0;

	switch(index){
		case PT_LOPROC:
			s_flag = 13;
			break;
		case PT_HIPROC:
			s_flag = 15;
			break;
		default:
			s_flag = index;
	}
	return s_flag;
}

int UGet_Sym_Bind_Name(int index)
{
	int s_flag = 0;

	switch(index){
		case STB_LOPROC:
			s_flag = 13;
			break;
		case STB_HIPROC:
			s_flag = 15;
			break;
		default:
			s_flag = index;
	}
	return s_flag;
}

//Get Symbol Type Nmae Index.
int UGet_Sym_Type_Name(int index)
{
	int s_flag = 0;

	switch(index){
		case STT_LOPROC:
			s_flag = 7;
			break;
		case STT_HIPROC:
			s_flag = 8;
			break;
		default:
			s_flag = index;
	}
	return s_flag;
}

//Get Special Section Index.
int UGet_Ss_Index_Name(int index)
{
	int s_flag = 0;

	switch(index){
		case SHN_UNDEF:
			s_flag = 0;
			break;
			//	case SHN_LORESERVE:
			//		s_flag = 1;
			//		break;
		case SHN_LOPROC:
			s_flag = 2;
			break;
		case SHN_HIPROC:
			s_flag = 3;
			break;
		case SHN_ABS:
			s_flag = 4;
			break;
		case SHN_COMMON:
			s_flag = 5;
			break;
		case SHN_HIRESERVE:
			s_flag = 6;
			break;
		default:
			s_flag = 7;
			break;
	}
	return s_flag;
}

void USec_Hd_Dmsg(Elf32 *elf)
{
	int nsc, str_size;
	int s_type, s_flag;		//Section Types, etc flags.
	Elf32_Shdr *sh;
	char *str_tbl;
	int lstr_num = 0, tstr_num = 0;
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
	char buff[MAX_PATH];

	str_tbl = elf->sc_str_tbl;
	sprintf(buff, "Section Header - Contains %d entries:\n", elf->hd.e_shnum);
	Display_Status(buff);
	sprintf(buff, " %-20s %-13s %-16s %-16s %-8s %-13s %s\n",
		"Name", "Type", "Addr[0x]", "Offset[0x]", "Size[0x]", "Flags", "Link");
	Display_Status(buff);

	for(nsc = 0; nsc < elf->hd.e_shnum; nsc++){
		sh = elf->sc_hd + nsc;
		s_type = USec_Type_Index(sh->sh_type);
		s_flag = USec_Flag_Index(sh->sh_flags);

		sprintf(buff, " %-20s %-13s %-16x %-16x %-8x %-13s %x\n", 
			str_tbl + sh->sh_name, 
			sh_type_str[s_type],
			sh->sh_addr, 
			sh->sh_offset, 
			sh->sh_size, 
			sh_flags[s_flag],
			sh->sh_link);
		Display_Status(buff);
		if(s_type == SHT_STRTAB){
			str_size = sh->sh_size;
		}
	}
	Display_Status("\n");
}

void UProg_Hd_Dmsg(Elf32 *elf)
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
	char str_buff[MAX_PATH];

	sprintf(str_buff, "Program Header - Contains %d entries\n", elf->hd.e_phnum);
	Display_Status(str_buff);

	sprintf(str_buff, " %7s %8s %8s %8s %8s %8s %5s\n","Type", "Offset", "Vaddr", "Paddr", "Filesz", "Memsz", "Flags");
	Display_Status(str_buff);

	for(nph = 0; nph < elf->hd.e_phnum; nph++){
		ph = elf->prog_hd + nph;
		if(ph->p_flags == PF_MASKPROC)
			flag = 0;
		else
			flag = ph->p_flags;

		sprintf(str_buff, " %7s %8x %8x %8x %8x %8x %5s\n", p_type_str[UGet_Prog_Type_Name(ph->p_type)],
			ph->p_offset,
			ph->p_vaddr,
			ph->p_paddr,
			ph->p_filesz,
			ph->p_memsz,
			p_flag_str[flag]);
		Display_Status(str_buff);
	}
	Display_Status("\n");
}

void UNote_Dmsg(Elf32 *elf)
{
	int nnote;
	Elf32_Shdr *sh;
	Elf32_Note *sn;
	char s_index;
	char str_buff[MAX_PATH];

	s_index = Get_Section_Index(elf, SHT_NOTE);
	sh = elf->sc_hd + s_index;

	sprintf(str_buff, "Note Section - contains %d entries:\n", sh->sh_size/sizeof(Elf32_Note));
	Display_Status(str_buff);
	sprintf(str_buff, " %8s  %8s  %8s  %8s\n","Namesz", "Descsz", "Type", "Name");
	Display_Status(str_buff);
	for(nnote = 0; nnote < sh->sh_size/sizeof(Elf32_Note); nnote++){
		sn = elf->sc_note + nnote;
		sprintf(str_buff, " %8x  %8x  %8x  %8s\n", sn->namesz, sn->descsz, sn->n_type, sn->note_name);
		Display_Status(str_buff);
	}
	Display_Status("\n");
}

void USec_Sym_Dmsg(Elf32 *elf)
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

	char str_buff[MAX_PATH];

	sh = elf->sc_hd + Get_Section_Index(elf, SHT_SYMTAB);

	sym_num = sh->sh_size/ sizeof(Elf32_Sym);
	str_tbl = elf->sym_str_tbl;


	sprintf(str_buff, "Symbol Table[.symtab] - contains %d entries:\n", sym_num);
	Display_Status(str_buff);
	sprintf(str_buff, " %10s %5s %-6s %-7s %-10s %s\n", "Value[0x]", "Size", "BIND", "TYPE", "Ndx", "Name");
	Display_Status(str_buff);
	for(nsym = 0; nsym < sym_num; nsym++){
		sym = elf->sym_hd + nsym;
		sym_bind = UGet_Sym_Bind_Name(ELF32_ST_BIND(sym->st_info));
		sym_type = UGet_Sym_Type_Name(ELF32_ST_TYPE(sym->st_info));
		sym_info = ELF32_ST_INFO(sym_bind, sym_type);
		ss_index = UGet_Ss_Index_Name(sym->st_shndx);
		if(ss_index != 7){
			sprintf(str_buff, " %10x %5d %-6s %-7s %-10s %s\n", sym->st_value, 
				sym->st_size, 
				sym_bind_name[sym_bind],
				sym_type_name[sym_type],
				sym_ndex[ss_index],
				str_tbl + sym->st_name);	
			Display_Status(str_buff);
		}
		else{
			sprintf(str_buff, " %10x %5d %-6s %-7s %-10x %s\n", sym->st_value, 
				sym->st_size, 
				sym_bind_name[sym_bind],
				sym_type_name[sym_type],
				sym->st_shndx,
				str_tbl + sym->st_name);	
			Display_Status(str_buff);
		}
	}
	Display_Status("\n");
}

void UComment_Dmsg(Elf32 *elf)
{
	char str_buff[MAX_PATH];
	sprintf(str_buff, "Version control information: %s\n", elf->sc_comment);
	Display_Status(str_buff);
	Display_Status("\n");
}
