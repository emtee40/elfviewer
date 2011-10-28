#ifndef VAR_TYPE_H
#define VAR_TYPE_H

typedef unsigned int	Elf32_Addr;
typedef unsigned short	Elf32_Half;
typedef unsigned int	Elf32_Off;	
typedef int				Elf32_Sword;	
typedef int				Elf32_Word;

//DWARF 
typedef unsigned int	initial_length;
typedef unsigned short	uhalf;
typedef unsigned int	section_offset;
typedef unsigned int	section_length;
typedef unsigned char	ubyte;
//
#define TRUE	1
#define FALSE	0
#define NOTFIND	-1
#define NOTEXIST -1

#define ELFMAG0	0x7f
#define ELFMAG1	'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFCLASSNONE	0
#define ELFCLASS32		1
#define ELFCLASS64		2

#define ELFDATANONE		0
#define ELFDATA2LSB		1
#define ELFDATA2MSB		2

#define ELFDATA2LSB32	1
#define ELFDATA2LSB64	2
#define ELFDATA2MSB32	3
#define ELFDATA2MSB64	4

#define EV_NONE			0
#define EV_CURRENT		1

//Special Section Indexes.
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC		0xff00
#define SHN_HIPROC		0xff1f
#define SHN_ABS			0xfff1
#define SHN_COMMON		0xfff2
#define SHN_HIRESERVE	0xffff

//Defined program header flags.
#define PF_X		1
#define PF_W		2
#define	PF_R		4
#define PF_MASKPROC	0xf0000000

typedef enum{
	ET_NONE = 0, 
	ET_REL, 
	ET_EXEC, 
	ET_DYN, 
	ET_CORE, 
	ET_LOPROC, 
	ET_HIPROC
}E_TYPE;

typedef enum{
	EM_NONE = 0,
	EM_M32,
	EM_SPARC,
	EM_386,
	EM_68K,
	EM_88K,
	EM_860,
	EM_MIPS,
	EM_MIPS_RS4_BE = 10,
	EM_ARM = 40
}E_MACHINE;

typedef enum{
	SHT_NULL = 0,
	SHT_PROGBITS,
	SHT_SYMTAB,
	SHT_STRTAB,
	SHT_RELA,
	SHT_HASH,
	SHT_DYNAMIC,
	SHT_NOTE,
	SHT_NOBITS,
	SHT_REL,
	SHT_SHLIB,
	SHT_DYNSYM,
	SHT_LOPROC = 0x70000000,
	SHT_HIPROC = 0x7fffffff,
	SHT_LOUSER = 0x80000000,
	SHT_HIUSER = 0xffffffff
}SH_TYPE;

typedef enum{
	PT_NULL = 0,
	PT_LOAD,
	PT_DYNAMIC,
	PT_INTERP,
	PT_NOTE,
	PT_SHLIB,
	PT_PHDR,
	PT_LOPROC = 0x70000000,
	PT_HIPROC = 0x7fffffff
}PT_TYPE;

typedef enum{
	SHF_WRITE = 1,
	SHF_ALLOC,
	SHF_EXECINSTR = 4,
	SHF_MASKPROC = 0xf0000000
}SH_FLAGS;

typedef enum{
	STB_LOCAL = 0,
	STB_GLOBAL,
	STB_WEAK,
	STB_LOPROC = 13,
	STB_HIPROC = 15
}SYM_BIND;

typedef enum{
	STT_NOTYPE = 0,
	STT_OBJECT,
	STT_FUNC,
	STT_SECTION,
	STT_FILE,
	STT_LOPROC = 13,
	STT_HIPROC = 15
}SYM_TYPE;


#endif //VAR_TYPE_H
