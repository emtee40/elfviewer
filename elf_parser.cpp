////////////////////////////////////////////////////////////////////////////
//File name : elf_parser.c
//created by : soontae

#include <stdio.h>
#include "parser_func.h"

int main(int argc, char *argv[])
{
	Elf32 elf;
	char *path = argv[2];
	char *msg_para = argv[1];

	if(argc == 3){
		//Parse ELF header.
		Elf_Header_Parser(path, &elf.hd);
		//32bit format.
		if(elf.hd.e_ident.EI_CLASS == ELFCLASS32){
			if(elf.hd.e_ident.EI_DATA == ELFDATA2LSB){
				Init_Elf(&elf);
				Elf_Sec_Parser(path, &elf);		//Parsing section header.
				Elf_Prog_Parser(path, &elf);		//Parsing program header.
				Get_Note_Section(path, &elf);
				Get_Section_Data(path, &elf, ".comment", &elf.sc_comment);
				if(!strcmp(msg_para, "-a")){
					Ident_Dmsg(&(elf.hd.e_ident));
					Header_Dmsg(&elf.hd);
					Sec_Hd_Dmsg(&elf);
					Prog_Hd_Dmsg(&elf);
					Sec_Sym_Dmsg(&elf);
					Note_Dmsg(&elf);
					Comment_Dmsg(&elf);
				}

				if(!Unalloc_Elf(&elf)){
					printf("Failed memory free\n");
				}
			}
		}
	}

	return 0;
}
