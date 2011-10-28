#ifndef	PARSER_FUNC_H
#define PARSER_FUNC_H

#include "elf_header.h"

#define ELF32_ST_BIND(i)	(i >> 4)
#define ELF32_ST_TYPE(i)	(i & 0xf)
#define ELF32_ST_INFO(b,t)  ((b << 4) + (t & 0xf))

int Check_Magic(ELF_IDENT *elf_i);
void Init_Elf(Elf32 *elf);
int Unalloc_Elf(Elf32 *elf);
int Elf_Header_Parser(char *file_path, Elf32_Ehdr *elf_header);
int Elf_Sec_Parser(char *file_path, Elf32 *elf);
int Get_Note_Section(char *file_path, Elf32 *elf);
int Elf_Prog_Parser(char *file_path, Elf32 *elf);
int Sym_Tbl_Parser(char *file_path, Elf32 *elf);
int Get_String_Table(char *file_path, Elf32 *elf);
int Get_Sym_Table(char *file_path, Elf32 *elf);
int Get_Section_Index(Elf32 *elf, int in_sh_type);
int Get_Section_Data(char *file_path, Elf32 *elf, char *section_name, char **store_var, int size);
#endif //PARSER_FUNC_H
