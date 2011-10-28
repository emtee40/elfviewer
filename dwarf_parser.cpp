#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "dwarf_header.h"
#include "dwarf_parser.h"
#include "dwarf_attr.h"

void Init_Dwarf(DWARF *indwarf)
{
	indwarf->debug_pubnames = NULL;
	indwarf->debug_pubnames_num = 0;
	indwarf->debug_abbrev = NULL;
	indwarf->debug_abbrev_num = 0;
	indwarf->debug_info = NULL;
	indwarf->debug_info_num = 0;
}

void Unalloc_Dwarf(DWARF *indwarf)
{
	unsigned int pubn = 0, pair_n = 0, att_n = 0, dinf_n = 0;
	NAME_LOOKUP_TABLES *nlt;
	PUBNAME_PAIR *str;
	DEBUG_ABBREV *dabb;
	DEBUG_INFO *dinf;

	if(indwarf->debug_pubnames != NULL){
		for(pubn = 0; pubn < indwarf->debug_pubnames_num; pubn++){
			nlt = indwarf->debug_pubnames + pubn;
			for(pair_n = 0; pair_n < nlt->pubname_num; pair_n++){
				str = nlt->pubname_pair + pair_n;
				free(str->pubname);
			}
			free(nlt);
		}
		free(indwarf->debug_pubnames);
		indwarf->debug_pubnames = NULL;
		indwarf->debug_pubnames_num = 0;
	}

	if(indwarf->debug_abbrev != NULL){
		for(att_n = 0; att_n < indwarf->debug_abbrev_num; att_n++){
			dabb = indwarf->debug_abbrev + att_n;
			if(dabb->debug_abbrev_attribute != NULL)
				free(dabb->debug_abbrev_attribute);
		}
		free(indwarf->debug_abbrev);
		indwarf->debug_abbrev =  NULL;
		indwarf->debug_abbrev_num = 0;
	}

	if(indwarf->debug_info != NULL){
		for(dinf_n = 0; dinf_n < indwarf->debug_info_num; dinf_n++){
			dinf = indwarf->debug_info + dinf_n;
			if(dinf->debug_info_entry.info_data != NULL)
				free(dinf->debug_info_entry.info_data);
		}
		free(indwarf->debug_info);
		indwarf->debug_info = NULL;
		indwarf->debug_info_num = 0;
	}
}

void Dwarf_Abbrev(unsigned char *bdata, unsigned int size, DWARF *indwarf)
{
	unsigned int tbl_num = 0, abbrev_tbl = 0;
	unsigned short zero_data = 0;
	unsigned int pos = 0, cpos =0, attr_size = 0, attr_n = 0;
	unsigned char *pos_zero = 0;
	DEBUG_ABBREV *abbrev;
	DEBUG_ABBREV_ATTRIBUTE *daa;
	DEBUG_ABBREV_HD dah;
	unsigned char temp[3];
	unsigned char zero_padding = 0;
	unsigned short end_flag = 0;

	do{
		zero_padding = *(bdata + pos);
		if((pos > 0) && (zero_padding == 0)){
			do{
				pos++;
				zero_padding = *(bdata + pos);
			}while((pos < size) && (zero_padding == 0));
		}
		memcpy(&dah, bdata + pos, sizeof(DEBUG_ABBREV_HD));
		pos += sizeof(DEBUG_ABBREV_HD);
		cpos = Find_End_Flag(bdata + pos, size - pos);
		if(cpos == NOTEXIST){
			//abbrev_tbl++;
			break;
		}
		pos += (cpos + 2);
		abbrev_tbl++;

		if((size - pos) < sizeof(DEBUG_ABBREV_HD))
			break;
	}while(pos < size);

	indwarf->debug_abbrev_num = abbrev_tbl;
	indwarf->debug_abbrev = (DEBUG_ABBREV *)malloc(sizeof(DEBUG_ABBREV) * abbrev_tbl);
	pos = 0;

	for(tbl_num = 0; tbl_num < abbrev_tbl; tbl_num++){
		zero_padding = *(bdata + pos);
		if((pos > 0) && (zero_padding == 0)){
			do{
				pos++;
				zero_padding = *(bdata + pos);
			}while((pos < size) && (zero_padding == 0));
		}

		abbrev = indwarf->debug_abbrev + tbl_num;
		memcpy(&(abbrev->debug_abbrev_hd), bdata + pos, sizeof(DEBUG_ABBREV_HD));
		pos += sizeof(DEBUG_ABBREV_HD);

		attr_size = Find_End_Flag(bdata + pos, size - pos);
		if(attr_size != 0){
			abbrev->debug_abbrev_attribute = (DEBUG_ABBREV_ATTRIBUTE *)malloc(sizeof(DEBUG_ABBREV_ATTRIBUTE) * attr_size/2);
			abbrev->attribute_num = attr_size/2;
		
			for(attr_n = 0; attr_n < attr_size/2; attr_n++){
				daa = abbrev->debug_abbrev_attribute + attr_n;
				memcpy(daa, bdata + pos, sizeof(DEBUG_ABBREV_ATTRIBUTE));
				pos += sizeof(DEBUG_ABBREV_ATTRIBUTE) ;
			}
		}
		pos += 2;
	}
}

void Dwarf_Info(unsigned char *bdata, unsigned int size, DWARF *indwarf)
{
	unsigned int unit_length = 0, data_size = 0;
	unsigned char temp[4];
	unsigned int info_num = 0, entry_num = 0;
	DEBUG_INFO *dinfo;
	DEBUG_INFO_HD *dinfo_hd;
	
	do{
		memcpy(temp, bdata + unit_length, sizeof(unsigned char) * 4);
		unit_length += *((unsigned int *)temp) + 4;
		info_num++;
	}while(unit_length < size);

	indwarf->debug_info_num = info_num;
	indwarf->debug_info = (DEBUG_INFO *)malloc(sizeof(DEBUG_INFO) * info_num);

	unit_length = 0;

	for(entry_num = 0; entry_num <  info_num; entry_num++){
		dinfo = indwarf->debug_info + entry_num;
		dinfo_hd = &(dinfo->debug_info_hd);
		memcpy(dinfo_hd, bdata + unit_length, sizeof(DEBUG_INFO_HD));
		unit_length += sizeof(DEBUG_INFO_HD);
		dinfo->debug_info_entry.abbrev_table_num = *(bdata + unit_length);
		unit_length++;		//increasing as size of abbrev_table_num
		data_size = dinfo_hd->unit_length - sizeof(DEBUG_INFO_HD) - 1;
		dinfo->debug_info_entry.info_data = (unsigned char *)malloc(sizeof(unsigned char) * data_size);
		memcpy(dinfo->debug_info_entry.info_data, bdata + unit_length, sizeof(unsigned char) * data_size);
		//unit_length += (dinfo_hd->unit_length + ITSELF_SIZE);
		unit_length += data_size;
		unit_length += ITSELF_SIZE;
	}
}

void Dwarf_Pubnames(unsigned char *bdata, unsigned int size, DWARF *indwarf)
{
	unsigned int pnum = 0;
	unsigned int unit_length = 0;
	unsigned char temp[4];
	unsigned char check_data = 0;
	unsigned int table_num = 0, sn = 0, str_n = 0;
	NAME_LOOKUP_TABLES *nlt;
	NAME_LOOKUP_TABLES_HD *nlt_hd;
	char *temp_name;

	do{
		memcpy(temp, bdata + unit_length, sizeof(unsigned char) * 4);
		unit_length += *((unsigned int *)temp) + 4;
		table_num++;
	}while(unit_length < size);
	
	indwarf->debug_pubnames_num = table_num;
	indwarf->debug_pubnames = (NAME_LOOKUP_TABLES *)malloc(sizeof(NAME_LOOKUP_TABLES) * table_num);
	
	unit_length = 0;

	for(pnum = 0; pnum < table_num; pnum++){
		nlt = indwarf->debug_pubnames + pnum;
		nlt_hd = &(nlt->nlt_hd);
		memcpy(nlt_hd, bdata + unit_length, sizeof(NAME_LOOKUP_TABLES_HD));
		unit_length += sizeof(NAME_LOOKUP_TABLES_HD);
		temp_name = (char *)malloc(sizeof(char) * (nlt_hd->unit_length - sizeof(NAME_LOOKUP_TABLES_HD)));
		memcpy(temp_name, bdata + unit_length, nlt_hd->unit_length - sizeof(NAME_LOOKUP_TABLES_HD));
		
		str_n = Get_Pubnames_Str(nlt, temp_name, nlt_hd->unit_length - sizeof(NAME_LOOKUP_TABLES_HD));
		unit_length += (nlt_hd->unit_length - sizeof(NAME_LOOKUP_TABLES_HD) + ITSELF_SIZE);
		free(temp_name);
	}
}

int Assign_Debug_Info_Data(DEBUG_INFO_ENTRY *dinfo_entry, DEBUG_ABBREV *d_abbr)
{
	unsigned int att_n = 0;
	DEBUG_ABBREV_ATTRIBUTE *d_abbr_att;
	
	dinfo_entry->debug_info_data.data_struct = d_abbr;

	for(att_n = 0; att_n < d_abbr->attribute_num; att_n++){
		d_abbr_att = d_abbr->debug_abbrev_attribute + att_n;
		switch(d_abbr_att->attribute_form){
			
		}
	}

	return TRUE;
}

int Get_Pubnames_Str(NAME_LOOKUP_TABLES *nlt, char *str, unsigned int size)
{
	char *null_add;
	unsigned int sn = 0;
	unsigned int null_pos = 0;
	int str_n = 0;
	PUBNAME_PAIR *tmp_pubname;

	do{
		null_pos += OFFSET;
		null_add = strchr(str + null_pos, NULL);
		null_pos += null_add - str;
		str_n++;
	}while(null_pos < size);

	nlt->pubname_num = str_n;
	nlt->pubname_pair = (PUBNAME_PAIR *)malloc(sizeof(PUBNAME_PAIR) * str_n);

	null_pos = 0;

	for(sn = 0; sn < str_n; sn++){
		tmp_pubname = nlt->pubname_pair + sn;		
		memcpy(&(tmp_pubname->offset), (unsigned int *)(str + null_pos), sizeof(unsigned int));
		null_pos += OFFSET;	//increase as size as offset.
		tmp_pubname->pubname = (char *)malloc(sizeof(char) * (strlen(str + null_pos) + 1));
		strcpy(tmp_pubname->pubname, str + null_pos);
		null_pos += (strlen(str + null_pos) + 1);		
	}

	return str_n;
}

int Find_End_Flag(unsigned char *data, unsigned int max_size)
{
	unsigned int npos = 0;
	unsigned short zero_data = 0;
	unsigned char temp[2];

	for(npos = 0; npos < max_size; npos++){
		memcpy(temp, data + npos, sizeof(unsigned char) * 2);
		zero_data = *((unsigned short *)temp);

		if(zero_data == 0){
			return npos;
		}
	}

	return NOTEXIST;
}