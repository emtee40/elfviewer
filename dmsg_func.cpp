//////////////////////////////////////////////////////////////////////////////
//File name : dmsg_func.c
//
#include "stdafx.h"
#include <stdio.h>
#include "var_type.h"
#include "elf_header.h"
#include "parser_func.h"

void Ident_Dmsg(ELF_IDENT *elf_ident)
{
	//ELF_IDENT elf_ident;
	printf("\n");
	printf("[ARM ELF Information]\n");
	printf("The data encoding of all data in the object file: ");
	switch(elf_ident->EI_CLASS){
		case ELFCLASSNONE:
			printf("Invalid class\n");
			break;
		case ELFCLASS32:
			printf("32-bit objects\n");
			break;
		case ELFCLASS64:
			printf("64-bit objects\n");
			break;
		default:
			break;
	}

	printf("The ELF header version number: ");
	switch(elf_ident->EI_DATA){
		case ELFDATANONE:
			printf("Invalid data encoding\n");
			break;
		case ELFDATA2LSB:
			printf("Data encodings ELFDATA2LSB\n");
			break;
		case ELFDATA2MSB:
			printf("Data encodings ELFDATA2MSB\n");
			break;
		default:
			break;
	}

	printf("ELF header version number: %d\n", elf_ident->EI_VERSION);
	printf("\n");
}

void Header_Dmsg(Elf32_Ehdr *elf_hd)
{
	printf("Object File type: ");
	switch(elf_hd->e_type){
		case ET_NONE:
			printf("ET_NONE\n");
			break;
		case ET_REL:
			printf("Re-locatable file\n");
			break;
		case ET_EXEC:
			printf("Executable file\n");
			break;
		case ET_DYN:
			printf("Shared object file\n");
			break;
		case ET_CORE:
			printf("Core file\n");
			break;
		case ET_LOPROC:
			printf("Processor-specific\n");
			break;
		case ET_HIPROC:
			printf("Processor-specific\n");
			break;
		default:
			break;
	}
	printf("The required architecture: ");
	switch(elf_hd->e_machine){
		case EM_NONE:
			printf("No machine\n");
			break;
		case EM_M32:
			printf("AT&T WE 32100\n");
			break;
		case EM_SPARC:
			printf("SPARC\n");
			break;
		case EM_386:
			printf("Intel Architecture\n");
			break;
		case EM_68K:
			printf("Motorola 68000\n");
			break;
		case EM_88K:
			printf("Motorola 88000\n");
			break;
		case EM_860:
			printf("Intel 80860\n");
			break;
		case EM_MIPS:
			printf("MIPS RS3000 Big-Endian\n");
			break;
		case EM_MIPS_RS4_BE:
			printf("MPIS RS4000 Big-Endian\n");
			break;
		case EM_ARM:
			printf("ARM/Thumb Architecture\n");
			break;
		default:
			printf("...\n");
			break;
	}

	printf("The object file version: ");
	switch(elf_hd->e_version){
		case EV_NONE:
			printf("Invalid version\n");
			break;
		case EV_CURRENT:
			printf("Current version\n");
			break;
	}

	printf("The virtual address(E_entry): %x\n",elf_hd->e_entry);
	printf("The program header table's file offset(E_phoff): 0x%x Bytes\n",elf_hd->e_phoff);
	printf("The Section header table's file offset(E_shoff): 0x%x Bytes\n",elf_hd->e_shoff);
	printf("Processor-specific flags associated with the file(E_flags): 0x%x\n",elf_hd->e_flags);
	printf("The ELF header's size(E_ehsize): 0x%x Bytes\n",elf_hd->e_ehsize);
	printf("The size of one entry in the file's program header table(E_phentsize): %d Bytes\n",elf_hd->e_phentsize);
	printf("The number of entries in the program header table(E_phnum): %d\n",elf_hd->e_phnum);
	printf("A section header's size(E_shentsize): %d Bytes\n",elf_hd->e_shentsize);
	printf("The number of entries in the section header table(E_shnum): %d\n",elf_hd->e_shnum);
	printf("The section header table index of the entry associated with\n");
	printf("The section name string table(E_shstrndx): %d\n",elf_hd->e_shstrndx);
	printf("\n");
}

int Sec_Type_Index(int index)
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

int Sec_Flag_Index(int index)
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

int Get_Prog_Type_Name(int index)
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

int Get_Sym_Bind_Name(int index)
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
int Get_Sym_Type_Name(int index)
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
int Get_Ss_Index_Name(int index)
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

void Sec_Hd_Dmsg(Elf32 *elf)
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

	str_tbl = elf->sc_str_tbl;
	printf("Section Header - Contains %d entries:\n", elf->hd.e_shnum);
	printf(" %-20s %-13s %-16s %-16s %-8s %-13s %s\n",
			"Name", "Type", "Addr[0x]", "Offset[0x]", "Size[0x]", "Flags", "Link");

	for(nsc = 0; nsc < elf->hd.e_shnum; nsc++){
		sh = elf->sc_hd + nsc;
		s_type = Sec_Type_Index(sh->sh_type);
		s_flag = Sec_Flag_Index(sh->sh_flags);

		printf(" %-20s %-13s %-16x %-16x %-8x %-13s %x\n", 
				str_tbl + sh->sh_name, 
				sh_type_str[s_type],
				sh->sh_addr, 
				sh->sh_offset, 
				sh->sh_size, 
				sh_flags[s_flag],
				sh->sh_link);
		if(s_type == SHT_STRTAB){
			str_size = sh->sh_size;
		}
	}
	printf("\n");
}

void Prog_Hd_Dmsg(Elf32 *elf)
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

	printf("Program Header - Contains %d entries\n", elf->hd.e_phnum);
	printf(" %7s %8s %8s %8s %8s %8s %5s\n","Type", "Offset", "Vaddr", "Paddr", "Filesz", "Memsz", "Flags");
	for(nph = 0; nph < elf->hd.e_phnum; nph++){
		ph = elf->prog_hd + nph;
		if(ph->p_flags == PF_MASKPROC)
			flag = 0;
		else
			flag = ph->p_flags;

		printf(" %7s %8x %8x %8x %8x %8x %5s\n", p_type_str[Get_Prog_Type_Name(ph->p_type)],
				ph->p_offset,
				ph->p_vaddr,
				ph->p_paddr,
				ph->p_filesz,
				ph->p_memsz,
				p_flag_str[flag]);
	}
	printf("\n");
}

void Note_Dmsg(Elf32 *elf)
{
	int nnote;
	Elf32_Shdr *sh;
	Elf32_Note *sn;
	char s_index;

	s_index = Get_Section_Index(elf, SHT_NOTE);
	sh = elf->sc_hd + s_index;

	printf("Note Section - contains %d entries:\n", sh->sh_size/sizeof(Elf32_Note));
	printf(" %8s  %8s  %8s  %8s\n","Namesz", "Descsz", "Type", "Name");
	for(nnote = 0; nnote < sh->sh_size/sizeof(Elf32_Note); nnote++){
		sn = elf->sc_note + nnote;
		printf(" %8x  %8x  %8x  %8s\n", sn->namesz, sn->descsz, sn->n_type, sn->note_name);
	}
	printf("\n");
}

void Sec_Sym_Dmsg(Elf32 *elf)
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

	sh = elf->sc_hd + Get_Section_Index(elf, SHT_SYMTAB);

	sym_num = sh->sh_size/ sizeof(Elf32_Sym);
	str_tbl = elf->sym_str_tbl;


	printf("Symbol Table[.symtab] - contains %d entries:\n", sym_num);
	printf(" %10s %5s %-6s %-7s %-10s %s\n", "Value[0x]", "Size", "BIND", "TYPE", "Ndx", "Name");
	for(nsym = 0; nsym < sym_num; nsym++){
		sym = elf->sym_hd + nsym;
		sym_bind = Get_Sym_Bind_Name(ELF32_ST_BIND(sym->st_info));
		sym_type = Get_Sym_Type_Name(ELF32_ST_TYPE(sym->st_info));
		sym_info = ELF32_ST_INFO(sym_bind, sym_type);
		ss_index = Get_Ss_Index_Name(sym->st_shndx);
		if(ss_index != 7){
			printf(" %10x %5d %-6s %-7s %-10s %s\n", sym->st_value, 
					sym->st_size, 
					sym_bind_name[sym_bind],
					sym_type_name[sym_type],
					sym_ndex[ss_index],
					str_tbl + sym->st_name);	
		}
		else{
			printf(" %10x %5d %-6s %-7s %-10x %s\n", sym->st_value, 
					sym->st_size, 
					sym_bind_name[sym_bind],
					sym_type_name[sym_type],
					sym->st_shndx,
					str_tbl + sym->st_name);	

		}
	}
	printf("\n");
}

void Comment_Dmsg(Elf32 *elf)
{
	printf("Version control information: %s\n", elf->sc_comment);
	printf("\n");
}

