#ifndef DMSG_FUNC_H
#define DMSG_FUNC_H

void Ident_Dmsg(ELF_IDENT *elf_ident);
void Header_Dmsg(Elf32_Ehdr *elf_hd);
int Sec_Type_Index(int index);
int Get_Prog_Type_Name(int index);
int Sec_Flag_Index(int index);
int Get_Sym_Bind_Name(int index);
int Get_Sym_Type_Name(int index);
int Get_Ss_Index_Name(int index);
void Sec_Hd_Dmsg(Elf32 *elf);
void Prog_Hd_Dmsg(Elf32 *elf);
void Sec_Sym_Dmsg(Elf32 *elf);
void Comment_Dmsg(Elf32 *elf);
#endif	//DMSG_FUNC_H
