/////////////////////////////////////////////////////////////////////
//File name : parser_func.c
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "var_type.h"
#include "elf_header.h"
#include "message_dsp.h"
#include "parser_func.h"

int Check_Magic(ELF_IDENT *elf_i)
{
	unsigned int i = 0;

	if((elf_i->EI_MAG0 != ELFMAG0) || (elf_i->EI_MAG1 != ELFMAG1) 
	   || (elf_i->EI_MAG2 != ELFMAG2) || (elf_i->EI_MAG3 != ELFMAG3)){
#ifdef DEBUG_MSG
		if(elf_i->EI_MAG0 != 0x7f){
			Display_Status("error EI_MAG0");
		}
		
		if(elf_i->EI_MAG1 != 'E'){
			Display_Status("error EI_MAG1");
		}
		
		if(elf_i->EI_MAG2 != 'L'){
			Display_Status("error EI_MAG2");
		}
		
		if(elf_i->EI_MAG3 != 'F'){
			Display_Status("error EI_MAG3");
		}
#endif	//DEBUG_MSG
		return FALSE;
	}

	return TRUE;
}

void Init_Elf(Elf32 *elf)
{
	elf->sc_hd = NULL;
	elf->prog_hd = NULL;
	elf->sym_hd = NULL;
	elf->sc_str_tbl = NULL;
	elf->sym_str_tbl = NULL;
	elf->sc_note = NULL;
	elf->temp_data = NULL;
	elf->sc_comment = 0;
}

int Unalloc_Elf(Elf32 *elf)
{
	char sf_flag = TRUE;

	if(elf->sc_str_tbl != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for string table");
#endif	//DEBUG_MSG
		free(elf->sc_str_tbl);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for section string table");
#endif
		sf_flag = FALSE;
	}

	if(elf->sym_hd != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for symbol header");
#endif	//DEBUG_MSG
		free(elf->sym_hd);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for symbol header");
#endif
		sf_flag = FALSE;
	}

	if(elf->sym_str_tbl != NULL){
#ifdef DEBUG_MSG
		printf("Deallocated memory for symbol table\n");
#endif	//DEBUG_MSG
		free(elf->sym_str_tbl);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for symbol string table");
#endif
		sf_flag = FALSE;
	}
	if(elf->sc_comment != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for comment section");
#endif	//DEBUG_MSG
		free(elf->sc_comment);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for comment section");
#endif
		sf_flag = FALSE;
	}
	
	if(elf->sc_note != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for Note section");
#endif	//DEBUG_MSG
		free(elf->sc_note);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for Note section");
#endif
		sf_flag = FALSE;
	}

	if(elf->prog_hd != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for program header");
#endif	//DEBUG_MSG
		free(elf->prog_hd);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for program header");
#endif
		sf_flag = FALSE;
	}

	if(elf->sc_hd != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for section header");
#endif	//DEBUG_MSG
		free(elf->sc_hd);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for section header");
#endif
		sf_flag = FALSE;
	}

	if(elf->temp_data != NULL){
#ifdef DEBUG_MSG
		Display_Status("Deallocated memory for section header");
#endif	//DEBUG_MSG
		free(elf->temp_data);
	}
	else{
#ifdef DEBUG_MSG
		Display_Status("not allocate memory for section header");
#endif
		sf_flag = FALSE;
	}

	return sf_flag;
}

int Elf_Header_Parser(char *file_path, Elf32_Ehdr *elf_header)
{
	FILE *elf_file;
	int fret;

	elf_file = fopen(file_path, "rb");

	if(elf_file == NULL){
		printf("File not opened\n");
		return FALSE;
	}

	fret = fread(elf_header, sizeof(Elf32_Ehdr), 1, elf_file);

	if(!Check_Magic(&(elf_header->e_ident))){
		Display_Status("This file is not ELF File\n");
		fclose(elf_file);
		return FALSE;
	}

	fclose(elf_file);
	
	return TRUE;
}

int Elf_Sec_Parser(char *file_path, Elf32 *elf)
{
	FILE *elf_file;
	Elf32_Shdr *sh;
	int fret, nsec_hd;
	int sh_index = 0;

	elf_file = fopen(file_path, "rb");
	
	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, elf->hd.e_shoff, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	elf->sc_hd = (Elf32_Shdr *)malloc(sizeof(Elf32_Shdr) * elf->hd.e_shnum);

	if(elf->sc_hd== NULL){
#ifdef DEBUG_MSG
		Display_Status("memory did not allocated");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	//read section headers from elf file. 
	for(nsec_hd = 0; nsec_hd < elf->hd.e_shnum; nsec_hd++){
		sh = elf->sc_hd + nsec_hd;
		fret = fread(sh, sizeof(Elf32_Shdr), 1, elf_file);
		if(fret != 1){
			fclose(elf_file);
			return FALSE;
		}	
	}
	fclose(elf_file);

	Get_String_Table(file_path, elf);	//Get string table from elf file.

	Sym_Tbl_Parser(file_path, elf);
	Get_Sym_Table(file_path, elf);

	return TRUE;
}

int Get_Note_Section(char *file_path, Elf32 *elf)
{
	FILE *elf_file;
	char s_index;
	Elf32_Shdr	*sh;
	Elf32_Note	*sn;
	int fret, nns;

	s_index = Get_Section_Index(elf, SHT_NOTE);
	if(s_index == NOTFIND)
		return FALSE;

	sh = elf->sc_hd + s_index;

	elf_file = fopen(file_path, "rb");
	
	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, sh->sh_offset, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	elf->sc_note = (Elf32_Note *)malloc(sizeof(Elf32_Note) * sh->sh_size/sizeof(Elf32_Note));

	if(elf->sc_note == NULL){
#ifdef DEBUG_MSG
		Display_Status("Momory for program did not allocated");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}
	
	//read note section from elf file. 
	for(nns = 0; nns < sh->sh_size/sizeof(Elf32_Note); nns++){
		sn = elf->sc_note + nns;
		fret = fread(sn, sizeof(Elf32_Note), 1, elf_file);
		if(fret != 1){
			fclose(elf_file);
			return FALSE;
		}	
	}
	fclose(elf_file);

	return TRUE;
}

//
// Parsing program Header.
//
int Elf_Prog_Parser(char *file_path, Elf32 *elf)
{
	FILE *elf_file;
	Elf32_Phdr	*prog;
	int fret = 0, nph = 0;

	elf_file = fopen(file_path, "rb");
	
	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, elf->hd.e_phoff, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	elf->prog_hd = (Elf32_Phdr *)malloc(sizeof(Elf32_Phdr) * elf->hd.e_phnum);

	if(elf->prog_hd == NULL){
#ifdef DEBUG_MSG
		Display_Status("Momory for program did not allocated");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}
	
	//read section headers from elf file. 
	for(nph = 0; nph < elf->hd.e_phnum; nph++){
		prog = elf->prog_hd + nph;
		fret = fread(prog, sizeof(Elf32_Phdr), 1, elf_file);
		if(fret != 1){
			fclose(elf_file);
			return FALSE;
		}	
	}
	fclose(elf_file);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
// This function parse symbol information from elf file.				 //
// Parameter															 //
//	file_path: path of elf file.										 //
//	elf: Structure to store elf information.							 //
///////////////////////////////////////////////////////////////////////////
int Sym_Tbl_Parser(char *file_path, Elf32 *elf)
{
	FILE *elf_file;
	int sym_num = 0;
	Elf32_Shdr *sh;
	int sym_index = 0;
	int nsym = 0, fret = 0;
	int nsh = 0;

	nsh = Get_Section_Index(elf, SHT_SYMTAB);
	if(nsh == NOTFIND){
		return FALSE;
	}

	sh = elf->sc_hd + nsh;
	sym_num = sh->sh_size / sizeof(Elf32_Sym);
	elf->sym_hd = (Elf32_Sym *)malloc(sizeof(Elf32_Sym) * sym_num);

	elf_file = fopen(file_path, "rb");

	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, sh->sh_offset, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	fret = fread(elf->sym_hd, sh->sh_size, 1, elf_file);
	if(fret != 1){
#ifdef DEBUG_MSG
		Display_Status("file not read from elf file");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fclose(elf_file);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// Description: This function get string table from elf file.			//
// Parameter:															//
// file_path : path of elf file.										//
// elf : elf structure.													//
//////////////////////////////////////////////////////////////////////////
int Get_String_Table(char *file_path, Elf32 *elf)
{
	FILE *elf_file;
	int fret;
	Elf32_Shdr *sh;

	sh = elf->sc_hd + elf->hd.e_shstrndx;
	
	elf_file = fopen(file_path, "rb");
	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, sh->sh_offset, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	elf->sc_str_tbl = (char *)malloc(sizeof(char) * sh->sh_size);
	if(elf->sc_str_tbl == NULL){
#ifdef DEBUG_MSG
		Display_Status("momory did not allocated");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fret = fread(elf->sc_str_tbl, sh->sh_size, 1, elf_file);
	if(fret != 1){
#ifdef DEBUG_MSG
		Display_Status("file not read from elf file\n");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fclose(elf_file);
	return TRUE;
}

int Get_Sym_Table(char *file_path, Elf32 *elf)
{
	FILE *elf_file;
	int fret;
	Elf32_Shdr *sh;
	int sc_inx;

	sc_inx = Get_Section_Index(elf, SHT_SYMTAB);

	if(sc_inx == NOTFIND)
		return FALSE;

	sh = elf->sc_hd + sc_inx;			//Get symbol section.
	sh = elf->sc_hd + sh->sh_link;		//Get symbol string section using link of symbol section.

	elf_file = fopen(file_path, "rb");
	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened\n");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, sh->sh_offset, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	elf->sym_str_tbl = (char *)malloc(sizeof(char) * sh->sh_size);
	if(elf->sym_str_tbl == NULL){
#ifdef DEBUG_MSG
		Display_Status("momory did not allocated\n");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fret = fread(elf->sym_str_tbl, sh->sh_size, 1, elf_file);
	if(fret != 1){
#ifdef DEBUG_MSG
		Display_Status("file not read from elf file\n");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fclose(elf_file);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// This function return index of section about input parameter "in_sh_type". //
// Parameter:																 //
//	elf: elf file.														     //
//	in_sh_type: section types.											     //
///////////////////////////////////////////////////////////////////////////////
int Get_Section_Index(Elf32 *elf, int in_sh_type)
{
	Elf32_Shdr *sh;
	int nsc = 0;

	for(nsc = 0; nsc < elf->hd.e_shnum; nsc++){
		sh = elf->sc_hd + nsc;
		if(sh->sh_type == in_sh_type)
			return nsc;
	}

	return NOTFIND;
}

//////////////////////////////////////////////////////////////////////////////
//Description: Get data of a section.
//Parameter: 
// -file_path: path of a elf file.
// -elf: elf structure.
// -section_name: name of the selected section.
// -store_var: address to restore data of the section.
//////////////////////////////////////////////////////////////////////////////
int Get_Section_Data(char *file_path, Elf32 *elf, char *section_name, char **store_var, int size)
{
	FILE *elf_file;
	int fret, nsc;
	Elf32_Shdr *sh;
	char *sec_str;
	char temp[20] = {0,};
	char exist_flag = 0;

	sec_str = elf->sc_str_tbl;
	for(nsc = 0; nsc < elf->hd.e_shnum; nsc++){
		sh = elf->sc_hd + nsc;
		strcpy(temp, (sec_str + sh->sh_name));
		if(!strcmp((sec_str + sh->sh_name), section_name)){
			exist_flag = 1;
			break;
		}
	}
	
	if(exist_flag == 0){
		return NOTFIND;
	}

	elf_file = fopen(file_path, "rb");
	if(elf_file == NULL){
#ifdef DEBUG_MSG
		Display_Status("File not opened\n");
#endif	//DEBUG_MSG
		return FALSE;
	}

	fret = fseek(elf_file, sh->sh_offset, SEEK_SET);
	if(fret != 0){
		fclose(elf_file);
		return FALSE;
	}

	if(store_var != NULL){
		free(*store_var);
		*store_var = NULL;
	}
	if(size == NULL)
		elf->temp_size = sh->sh_size;
	else{
		elf->temp_size = size;
	}

	*store_var = (char *)malloc(sizeof(char) * sh->sh_size);
	if(*store_var == NULL){
#ifdef DEBUG_MSG
		Display_Status("momory did not allocated\n");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fret = fread(*store_var, sh->sh_size, 1, elf_file);
	if(fret != 1){
#ifdef DEBUG_MS
		Display_Status("file not read from elf file\n");
#endif	//DEBUG_MSG
		fclose(elf_file);
		return FALSE;
	}

	fclose(elf_file);
	return TRUE;

}

