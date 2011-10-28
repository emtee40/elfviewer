#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include "var_type.h"

#define EI_NIDENT 16

//ELF Identification.
typedef struct{
	unsigned char EI_MAG0;
	unsigned char EI_MAG1;
	unsigned char EI_MAG2;
	unsigned char EI_MAG3;
	unsigned char EI_CLASS;
	unsigned char EI_DATA;
	unsigned char EI_VERSION;
	unsigned char EI_PADDING[EI_NIDENT - 7];
}ELF_IDENT;

// ELF Header.
typedef struct{
	//unsigned char e_ident[EI_NIDENT];
	ELF_IDENT	e_ident;
	Elf32_Half	e_type;			//The Object file type.
	Elf32_Half	e_machine;		//The required architecture for an individual file.
	Elf32_Word	e_version;		//The object file version.
	Elf32_Addr	e_entry;		//The virtual address.
	Elf32_Off	e_phoff;		//The program header table's file offset.
	Elf32_Off	e_shoff;		//The section header table's file offset.
	Elf32_Word	e_flags;		//Processor-specific flags associated with the file.
	Elf32_Half	e_ehsize;		//The ELF header's size.
	Elf32_Half	e_phentsize;	//The size of one entry in the file's program header table.
	Elf32_Half	e_phnum;		//The number of entries in the program header table.
	Elf32_Half	e_shentsize;	//A section header's size.
	Elf32_Half	e_shnum;		//The number of entries in the section header table.
	Elf32_Half	e_shstrndx;		//The section header table index of the entry associated with 
								//the section name string table.
} Elf32_Ehdr;

//Section Header.
typedef struct{
	Elf32_Word	sh_name;		//The name of the section.
	Elf32_Word	sh_type;		//The section's contents and semantics.
	Elf32_Word	sh_flags;		//1-bit flags that describe miscellaneous attributes.
	Elf32_Addr	sh_addr;		//The memory image of a process.
	Elf32_Off	sh_offset;		//The byte offset from the beginning of the file to the first 
								//byte in the section.
	Elf32_Word	sh_size;		//The section's size.
	Elf32_Word	sh_link;		//A section header table index link.
	Elf32_Word	sh_info;		//Extra information.
	Elf32_Word	sh_addralign;	//address alignment constraints.
	Elf32_Word	sh_entsize;		//A table of fixed-size entries.
} Elf32_Shdr;

typedef struct{
	Elf32_Word		st_name;	//Holds and index into the object file's symbol string table.
	Elf32_Addr		st_value;	//The value of the associated symbol.
	Elf32_Word		st_size;	//Associated sizes.
	unsigned char	st_info;	//The symbol's type and binding attributes.
	unsigned char	st_other;	//
	Elf32_Half		st_shndx;	//The relevant section header table index.
}Elf32_Sym;

//Relocation.
typedef struct{
	Elf32_Addr	r_offset;		//The location at whitch to apply the relocation action.
	Elf32_Word	r_info;			//Both the symbol table index with respect to which relocation must be made,
								//and the type of relocation to apply.
}Elf32_Rel;

typedef struct{
	Elf32_Addr	r_offset;		//The location at whitch to apply the relocation action.
	Elf32_Word	r_info;			//Both the symbol table index with respect to which relocation must be made,
								//and the type of relocation to apply.
	Elf32_Sword r_addend;		//A constant addend used to compute the value to be 
								//stored into the relocatable field.
}Elf32_Rela;

//Program Header.
typedef struct{
	Elf32_Word	p_type;
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;
	Elf32_Word	p_align;
}Elf32_Phdr;

//Note Section
typedef struct{
	Elf32_Word	namesz;
	Elf32_Word	descsz;
	Elf32_Word	n_type;
	char		note_name[8];
}Elf32_Note;


typedef struct{
	Elf32_Ehdr	hd;				//ELF Header.
	Elf32_Shdr	*sc_hd;			//Section Header.
	Elf32_Phdr	*prog_hd;		//Program Header.
	Elf32_Sym	*sym_hd;		//Symbol Table.
	Elf32_Note	*sc_note;		//Section Note.
	char		*sc_str_tbl;	//Section name table.
	char		*sym_str_tbl;	//Symbol name table.
	char		*sc_comment;	//Version control information.
	char		*temp_data;
	unsigned int temp_size;		
}Elf32;

#endif //ELF_HEADER_H
