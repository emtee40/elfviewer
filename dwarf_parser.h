#ifndef DWARF_PARSER_H
#define DWARF_PARSER_H

#include "dwarf_header.h"

void Init_Dwarf(DWARF *indwarf);
void Unalloc_Dwarf(DWARF *indwarf);
void Dwarf_Abbrev(unsigned char *bdata, unsigned int size, DWARF *indwarf);
void Dwarf_Info(unsigned char *bdata, unsigned int size, DWARF *indwarf);
void Dwarf_Pubnames(unsigned char *bdata, unsigned int size,  DWARF *indwarf);
int Get_Pubnames_Str(NAME_LOOKUP_TABLES *nlt, char *str, unsigned int size);
int Assign_Debug_Info_Data(DEBUG_INFO_ENTRY *dinfo_entry, DEBUG_ABBREV *d_abbr);
int Find_End_Flag(unsigned char *data, unsigned int max_size);
#endif //DWARF_PARSER_H
