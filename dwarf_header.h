#ifndef DWARF_HEADER_H
#define DWARF_HEADER_H

#include "var_type.h"
#pragma pack(1)

#define ZERO_OFFSET	4
#define OFFSET		4
#define ITSELF_SIZE	4

//.debug_pubnames structure
typedef struct{
	unsigned int	offset;
	char			*pubname;
}PUBNAME_PAIR;

typedef struct{
	initial_length	unit_length;
	uhalf			version;
	section_offset	debug_info_offset;
	section_length	debug_info_lenght;
}NAME_LOOKUP_TABLES_HD;

typedef struct{
	NAME_LOOKUP_TABLES_HD	nlt_hd;
	PUBNAME_PAIR			*pubname_pair;
	unsigned int			pubname_num;
}NAME_LOOKUP_TABLES;

//.debug_abbrev structure
typedef struct{
	ubyte	abbrev_table_num;
	ubyte	tag_encoding;
	ubyte	child_encoding;
}DEBUG_ABBREV_HD;

typedef struct{
	ubyte	attribute_encoding;
	ubyte	attribute_form;
}DEBUG_ABBREV_ATTRIBUTE;

typedef struct{
	DEBUG_ABBREV_HD debug_abbrev_hd;
	DEBUG_ABBREV_ATTRIBUTE *debug_abbrev_attribute;
	unsigned int attribute_num;
}DEBUG_ABBREV;

//.debug_info structure
typedef struct{
	initial_length	unit_length;
	uhalf			version;
	section_offset	debug_abbrev_offset;
	ubyte			address_size;
}DEBUG_INFO_HD;

typedef struct{
	void *data[255];
	DEBUG_ABBREV *data_struct;
}DEBUG_INFO_DATA;

typedef struct{
	ubyte	abbrev_table_num;
	unsigned char	*info_data;
	DEBUG_INFO_DATA debug_info_data;
}DEBUG_INFO_ENTRY;

typedef struct{
	DEBUG_INFO_HD		debug_info_hd;		//debug_info header.
	DEBUG_INFO_ENTRY	debug_info_entry;
}DEBUG_INFO;

typedef struct{
	DEBUG_INFO			*debug_info;	
	NAME_LOOKUP_TABLES	*debug_pubnames;
	DEBUG_ABBREV		*debug_abbrev;
	unsigned int		debug_abbrev_num;
	unsigned int		debug_info_num;
	unsigned int		debug_pubnames_num;
}DWARF;

#endif	//DWARF_HEADER_H
