/*** coff information for 80960.  Origins: Intel corp, natch. */

/* This include file is also used for rudimentary ECOFF support on MIPS
   machines.  Such differences as are needed are #ifdef MIPS.  */

/* NOTE: Tagentries (cf TAGBITS) are not used by the 960 */

/********************** FILE HEADER **********************/

struct external_filehdr {
	char f_magic[2];	/* magic number			*/
	char f_nscns[2];	/* number of sections		*/
	char f_timdat[4];	/* time & date stamp		*/
	char f_symptr[4];	/* file pointer to symtab	*/
	char f_nsyms[4];	/* number of symtab entries	*/
	char f_opthdr[2];	/* sizeof(optional hdr)		*/
	char f_flags[2];	/* flags			*/
};

struct internal_filehdr 
{
  unsigned short	f_magic; /* magic number			*/
  unsigned short	f_nscns; /* number of sections		*/
  long		f_timdat;	 /* time & date stamp		*/
  long		f_symptr;	 /* file pointer to symtab	*/
  long		f_nsyms;	 /* number of symtab entries	*/
  unsigned short	f_opthdr; /* sizeof(optional hdr)		*/
  unsigned short	f_flags;  /* flags			*/
};

/* Bits for f_flags:
*	F_RELFLG	relocation info stripped from file
*	F_EXEC		file is executable (no unresolved external references)
*	F_LNNO		line numbers stripped from file
*	F_LSYMS		local symbols stripped from file
*	F_AR32WR	file has byte ordering of an AR32WR machine (e.g. vax)
*/

#define F_RELFLG	(0x0001)
#define F_EXEC		(0x0002)
#define F_LNNO		(0x0004)
#define F_LSYMS		(0x0008)
#define F_AR32WR	(0x0010)

/*
*	Intel 80960 (I960) processor flags.
*	F_I960TYPE == mask for processor type field. 
*/

#define	F_I960TYPE	(0xf000)
#define	F_I960CORE	(0x1000)
#define	F_I960KB	(0x2000)
#define	F_I960SB	(0x2000)
#define	F_I960MC	(0x3000)
#define	F_I960XA	(0x4000)
#define	F_I960CA	(0x5000)
#define	F_I960KA	(0x6000)
#define	F_I960SA	(0x6000)


/* Mips magics */
#define MIPS_MAGIC_1 0x0180
#define MIPS_MAGIC_2 0x0162
#define MIPS_MAGIC_3 0x0160



#define ECOFFBADMAG(x) (((x).f_magic!=MIPS_MAGIC_1) && \
			((x).f_magic!=MIPS_MAGIC_2) &&\
			((x).f_magic!=MIPS_MAGIC_3))


/** i80960 Magic Numbers
*/

#define I960ROMAGIC	(0x160)	/* read-only text segments */
#define I960RWMAGIC	(0x161)	/* read-write text segments */

#define I960BADMAG(x) (((x).f_magic!=I960ROMAGIC) && ((x).f_magic!=I960RWMAGIC))

#define	FILHDR	struct external_filehdr
#define	FILHSZ	20

/********************** AOUT "OPTIONAL HEADER" **********************/

typedef struct {
	unsigned long	phys_addr;
	unsigned long	bitarray;
} TAGBITS;


/*  These appear to be used only by exec(2).  I don't know who cares
    about them in a cross development environment.  In any case, this
    is my collection after researching the issue for a few hours.
    Apparently, most have these have remained essentially unchanged
    since v7 days, although a few new ones have been added.  xoxorich.
    Could we have a little more teleology please? -- Gumby */

#define BAD0MAGIC   (0401)	/* (?) "lpd (UNIX/RT)" */
#define BAD1MAGIC   (0405)	/* (?) overlay */
#define OMAGIC      (0407)	/* old impure format. data immediately
                                   follows text. both sections are rw. */
#define NMAGIC      (0410)	/* split i&d, read-only text */
#define A_MAGIC3    (0411)	/* (?) "separated I&D" */
#define ZMAGIC      (0413)	/* like NMAGIC, but demand loaded */
#define PAGEMAGIC2  (0414)	/* (?) like ZMAGIC, but address zero
                                   explicitly unmapped. */ /*  */
#define REGMAGIC    (0414)	/* (?) a PAGEMAGIC2 alias? */
#define PAGEMAGIC3  (0415)	/* (?) like ZMAGIC, but address zero mapped. */
#define A_MAGIC5    (0437)	/* (?) "system overlay, separated I&D" */
#define SASMAGIC    (010000)	/* (?) "Single Address Space" */    
#define MASMAGIC    (020000)	/* (?) "Multiple (separate I/D) Addr. Spaces" */

struct internal_aouthdr {
	short		magic;	/* type of file				*/
	short		vstamp;	/* version stamp			*/
	unsigned long	tsize;	/* text size in bytes, padded to FW bdry*/
	unsigned long	dsize;	/* initialized data "  "		*/
	unsigned long	bsize;	/* uninitialized data "   "		*/
#if U3B
	unsigned long	dum1;
	unsigned long	dum2;	/* pad to entry point	*/
#endif
	unsigned long	entry;	/* entry pt.				*/
	unsigned long	text_start;	/* base of text used for this file */
	unsigned long	data_start;	/* base of data used for this
					   file */
#ifndef MIPS
	unsigned long	tagentries;	/* number of tag entries to
					   follow */
#endif

} ;


typedef struct 
{
  char 	magic[2];		/* type of file				*/
  char	vstamp[2];		/* version stamp			*/
  char	tsize[4];		/* text size in bytes, padded to FW bdry*/
  char	dsize[4];		/* initialized data "  "		*/
  char	bsize[4];		/* uninitialized data "   "		*/
  char	entry[4];		/* entry pt.				*/
  char 	text_start[4];		/* base of text used for this file */
  char 	data_start[4];		/* base of data used for this file */
#ifndef MIPS
  char	tagentries[4];		/* number of tag entries to follow */
#endif
}
AOUTHDR;

/* return a pointer to the tag bits array */

#define TAGPTR(aout) ((TAGBITS *) (&(aout.tagentries)+1))

/* compute size of a header */

/*#define AOUTSZ(aout) (sizeof(AOUTHDR)+(aout.tagentries*sizeof(TAGBITS)))*/
#define AOUTSZ (sizeof(AOUTHDR))


/********************** STORAGE CLASSES **********************/

#define C_EFCN		-1	/* physical end of function	*/
#define C_NULL		0
#define C_AUTO		1	/* automatic variable		*/
#define C_EXT		2	/* external symbol		*/
#define C_STAT		3	/* static			*/
#define C_REG		4	/* register variable		*/
#define C_EXTDEF	5	/* external definition		*/
#define C_LABEL		6	/* label			*/
#define C_ULABEL	7	/* undefined label		*/
#define C_MOS		8	/* member of structure		*/
#define C_ARG		9	/* function argument		*/
#define C_STRTAG	10	/* structure tag		*/
#define C_MOU		11	/* member of union		*/
#define C_UNTAG		12	/* union tag			*/
#define C_TPDEF		13	/* type definition		*/
#define C_USTATIC	14	/* undefined static		*/
#define C_ENTAG		15	/* enumeration tag		*/
#define C_MOE		16	/* member of enumeration	*/
#define C_REGPARM	17	/* register parameter		*/
#define C_FIELD		18	/* bit field			*/
/* #define C_REGARG     19 */	/* My guess - but Intel specific*/
#define C_AUTOARG	19	/* auto argument		*/
#define C_LASTENT	20	/* dummy entry (end of block)	*/
#define C_BLOCK		100	/* ".bb" or ".eb"		*/
#define C_FCN		101	/* ".bf" or ".ef"		*/
#define C_EOS		102	/* end of structure		*/
#define C_FILE		103	/* file name			*/
#define C_LINE		104	/* line # reformatted as symbol table entry */
#define C_ALIAS	 	105	/* duplicate tag		*/
#define C_HIDDEN	106	/* ext symbol in dmert public lib */

	/* New storage classes for 80960 */
 
/* C_LEAFPROC is obsolete.  Use C_LEAFEXT or C_LEAFSTAT */
#define C_LEAFPROC	108	/* Leaf procedure, "call" via BAL */

#define C_SCALL		107	/* Procedure reachable via system call */
#define C_LEAFEXT       108	/* External leaf */
#define C_LEAFSTAT      113     /* Static leaf */
#define C_OPTVAR	109	/* Optimized variable		*/
#define C_DEFINE	110	/* Preprocessor #define		*/
#define C_PRAGMA	111	/* Advice to compiler or linker	*/
#define C_SEGMENT	112	/* 80960 segment name		*/

/********************** SECTION HEADER **********************/

struct internal_scnhdr {
	char		s_name[8];	/* section name			*/
	long		s_paddr;	/* physical address, aliased s_nlib */
	long		s_vaddr;	/* virtual address		*/
	long		s_size;		/* section size			*/
	long		s_scnptr;	/* file ptr to raw data for section */
	long		s_relptr;	/* file ptr to relocation	*/
	long		s_lnnoptr;	/* file ptr to line numbers	*/
	unsigned short	s_nreloc;	/* number of relocation entries	*/
	unsigned short	s_nlnno;	/* number of line number entries*/
	long		s_flags;	/* flags			*/
#ifndef MIPS
 /* This field exists in Intel COFF, not in Mips ECOFF. */
	unsigned long	s_align;	/* section alignment		*/
#endif
};

struct external_scnhdr {
	char		s_name[8];	/* section name			*/
	char		s_paddr[4];	/* physical address, aliased s_nlib */
	char		s_vaddr[4];	/* virtual address		*/
	char		s_size[4];	/* section size			*/
	char		s_scnptr[4];	/* file ptr to raw data for section */
	char		s_relptr[4];	/* file ptr to relocation	*/
	char		s_lnnoptr[4];	/* file ptr to line numbers	*/
	char		s_nreloc[2];	/* number of relocation entries	*/
	char		s_nlnno[2];	/* number of line number entries*/
	char		s_flags[4];	/* flags			*/
#ifndef MIPS
 /* This field exists in Intel COFF, not in Mips ECOFF. */
	char 		s_align[4];	/* section alignment		*/
#endif
};

/*
 * names of "special" sections
 */
#define _TEXT	".text"
#define _DATA	".data"
#define _BSS	".bss"

/*
 * s_flags "type"
 */
#define STYP_REG	 (0x0000) /* "regular": allocated, relocated, loaded */
#define STYP_DSECT	 (0x0001) /* "dummy":  relocated only*/
#define STYP_NOLOAD	 (0x0002) /* "noload": allocated, relocated, not loaded */
#define STYP_GROUP	 (0x0004) /* "grouped": formed of input sections */
#define STYP_PAD	 (0x0008) /* "padding": not allocated, not relocated, loaded */
#define STYP_COPY	 (0x0010) /* "copy": for decision function used by field update;  not allocated, not relocated,
				     loaded; reloc & lineno entries processed normally */
#define STYP_TEXT	 (0x0020) /* section contains text only */
#define S_SHRSEG	 (0x0020) /* In 3b Update files (output of ogen), sections which appear in SHARED segments of the Pfile
				     will have the S_SHRSEG flag set by ogen, to inform dufr that updating 1 copy of the proc. will
				     update all process invocations. */
#define STYP_DATA	 (0x0040) /* section contains data only */
#define STYP_BSS	 (0x0080) /* section contains bss only */
#define S_NEWFCN	 (0x0100) /* In a minimal file or an update file, a new function (as compared with a replaced function) */
#define STYP_INFO	 (0x0200) /* comment: not allocated not relocated, not loaded */
#define STYP_OVER	 (0x0400) /* overlay: relocated not allocated or loaded */
#define STYP_LIB	 (0x0800) /* for .lib: same as INFO */
#define STYP_MERGE	 (0x2000) /* merge section -- combines with text, data or bss sections only */
#define STYP_REVERSE_PAD (0x4000) /* section will be padded with no-op instructions wherever padding is necessary and there is a
				     word of contiguous bytes beginning on a word boundary. */

#define	SCNHDR	struct external_scnhdr
#define	SCNHSZ	sizeof(SCNHDR)


/********************** LINE NUMBERS **********************/

/* 1 line number entry for every "breakpointable" source line in a section.
 * Line numbers are grouped on a per function basis; first entry in a function
 * grouping will have l_lnno = 0 and in place of physical address will be the
 * symbol table index of the function name.
 */
struct external_lineno {
	union {
		char l_symndx[4];	/* function name symbol index, iff l_lnno == 0*/
		char l_paddr[4];	/* (physical) address of line number	*/
	} l_addr;
	char l_lnno[2];		/* line number		*/
	char padding[2];	/* force alignment	*/
};

struct internal_lineno {
	union {
		long l_symndx;	/* function name symbol index, iff l_lnno == 0*/
		long l_paddr;	/* (physical) address of line number	*/
	} l_addr;
	unsigned short	l_lnno;	/* line number		*/
};

#define	LINENO	struct external_lineno
#define	LINESZ	8


/********************** SYMBOLS **********************/

#define SYMNMLEN	8	/* # characters in a symbol name	*/
#define FILNMLEN	14	/* # characters in a file name		*/
#define DIMNUM		4	/* # array dimensions in auxiliary entry */

struct external_syment 
{
  union {
    char e_name[SYMNMLEN];
    struct {
      char e_zeroes[4];
      char e_offset[4];
    } e;
  } e;
  char e_value[4];
  char e_scnum[2];
  char e_flags[2];
  char e_type[4];
  char e_sclass[1];
  char e_numaux[1];
  char pad2[2];
};


struct internal_syment {
	union {
		char	_n_name[SYMNMLEN];	/* old COFF version	*/
		struct {
			long	_n_zeroes;	/* new == 0		*/
			long	_n_offset;	/* offset into string table */
		} _n_n;
		char	*_n_nptr[2];	/* allows for overlaying	*/
	} _n;
	long		n_value;	/* value of symbol		*/
	short		n_scnum;	/* section number		*/
	unsigned short	n_flags;	/* copy of flags from filhdr	*/
	unsigned long	n_type;		/* type and derived type	*/
	char		n_sclass;	/* storage class		*/
	char		n_numaux;	/* number of aux. entries	*/
};

/*
 * Relocatable symbols have number of the section in which they are defined,
 * or one of the following:
 */
#define N_UNDEF	((short)0)  /* undefined symbol */
#define N_ABS	((short)-1) /* value of symbol is absolute */
#define N_DEBUG	((short)-2) /* debugging symbol -- value is meaningless */
#define N_TV	((short)-3) /* indicates symbol needs preload transfer vector */
#define P_TV	((short)-4) /* indicates symbol needs postload transfer vector*/

/*
 * Type of a symbol, in low 4 bits of the word
 */
#define T_NULL		0
#define T_VOID		1	/* function argument (only used by compiler) */
#define T_CHAR		2	/* character		*/
#define T_SHORT		3	/* short integer	*/
#define T_INT		4	/* integer		*/
#define T_LONG		5	/* long integer		*/
#define T_FLOAT		6	/* floating point	*/
#define T_DOUBLE	7	/* double word		*/
#define T_STRUCT	8	/* structure 		*/
#define T_UNION		9	/* union 		*/
#define T_ENUM		10	/* enumeration 		*/
#define T_MOE		11	/* member of enumeration*/
#define T_UCHAR		12	/* unsigned character	*/
#define T_USHORT	13	/* unsigned short	*/
#define T_UINT		14	/* unsigned integer	*/
#define T_ULONG		15	/* unsigned long	*/
#define T_LNGDBL	16	/* long double		*/

/*
 * derived types, in n_type
*/
#define DT_NON		(0)	/* no derived type */
#define DT_PTR		(1)	/* pointer */
#define DT_FCN		(2)	/* function */
#define DT_ARY		(3)	/* array */

#define N_BTMASK	(0x1f)
#define N_TMASK		(0x60)
#define N_BTSHFT	(5)
#define N_TSHIFT	(2)
  
#define BTYPE(x)	((x) & N_BTMASK)

#define ISPTR(x)	(((x) & N_TMASK) == (DT_PTR << N_BTSHFT))
#define ISFCN(x)	(((x) & N_TMASK) == (DT_FCN << N_BTSHFT))
#define ISARY(x)	(((x) & N_TMASK) == (DT_ARY << N_BTSHFT))

#define DECREF(x) ((((x)>>N_TSHIFT)&~N_BTMASK)|((x)&N_BTMASK))
union external_auxent {
	struct {
		char x_tagndx[4];	/* str, un, or enum tag indx */
		union {
			struct {
			    char  x_lnno[2]; /* declaration line number */
			    char  x_size[2]; /* str/union/array size */
			} x_lnsz;
			char x_fsize[4];	/* size of function */
		} x_misc;
		union {
			struct {		/* if ISFCN, tag, or .bb */
			    char x_lnnoptr[4];	/* ptr to fcn line # */
			    char x_endndx[4];	/* entry ndx past block end */
			} x_fcn;
			struct {		/* if ISARY, up to 4 dimen. */
			    char x_dimen[DIMNUM][2];
			} x_ary;
		} x_fcnary;
		char x_tvndx[2];		/* tv index */
	} x_sym;

	union {
		char x_fname[FILNMLEN];
		struct {
			char x_zeroes[4];
			char x_offset[4];
		} x_n;
	} x_file;

	struct {
		char x_scnlen[4];			/* section length */
		char x_nreloc[2];	/* # relocation entries */
		char x_nlinno[2];	/* # line numbers */
	} x_scn;

        struct {
		char x_tvfill[4];	/* tv fill value */
		char x_tvlen[2];	/* length of .tv */
		char x_tvran[2][2];	/* tv range */
	} x_tv;		/* info about .tv section (in auxent of symbol .tv)) */

	/******************************************
	 *  I960-specific *2nd* aux. entry formats
	 ******************************************/
	struct {
	  /* This is a very old typo that keeps getting propagated. */
#define x_stdindx x_stindx
		char x_stindx[4];	/* sys. table entry */
	} x_sc;	/* system call entry */

	struct {
		char x_balntry[4]; /* BAL entry point */
	} x_bal; /* BAL-callable function */

        struct {
		char x_timestamp[4];	        /* time stamp */
		char 	x_idstring[20];	        /* producer identity string */
	} x_ident;	                        /* Producer ident info */

};

union 	internal_auxent {
	struct {
		long x_tagndx;	/* str, un, or enum tag indx */
		union {
			struct {
			    unsigned short x_lnno; /* declaration line number */
			    unsigned short x_size; /* str/union/array size */
			} x_lnsz;
			long x_fsize;	/* size of function */
		} x_misc;
		union {
			struct {		/* if ISFCN, tag, or .bb */
			    long x_lnnoptr;	/* ptr to fcn line # */
			    long x_endndx;	/* entry ndx past block end */
			} x_fcn;
			struct {		/* if ISARY, up to 4 dimen. */
			    unsigned short x_dimen[DIMNUM];
			} x_ary;
		} x_fcnary;
		unsigned short x_tvndx;		/* tv index */
	} x_sym;

	union {
		char x_fname[FILNMLEN];
		struct {
			long x_zeroes;
			long x_offset;
		} x_n;
	} x_file;

	struct {
		long x_scnlen;			/* section length */
		unsigned short x_nreloc;	/* # relocation entries */
		unsigned short x_nlinno;	/* # line numbers */
	} x_scn;

        struct {
		long		x_tvfill;	/* tv fill value */
		unsigned short	x_tvlen;	/* length of .tv */
		unsigned short	x_tvran[2];	/* tv range */
	} x_tv;		/* info about .tv section (in auxent of symbol .tv)) */

	/******************************************
	 *  I960-specific *2nd* aux. entry formats
	 ******************************************/
	struct {
/* This is a very old typo that keeps getting propagated. */
#define x_stdindx x_stindx
		long x_stindx;	/* sys. table entry */
	} x_sc;	/* system call entry */

	struct {
		unsigned long x_balntry; /* BAL entry point */
	} x_bal; /* BAL-callable function */

        struct {
		unsigned long	x_timestamp;	        /* time stamp */
		char 	x_idstring[20];	        /* producer identity string */
	} x_ident;	                        /* Producer ident info */


};

#define	SYMENT	struct external_syment
#define	SYMESZ	sizeof(SYMENT)			/* FIXME - calc by hand */
#define	AUXENT	union external_auxent
#define	AUXESZ	sizeof(AUXENT)			/* FIXME - calc by hand */

#	define _ETEXT	"_etext"

/********************** RELOCATION DIRECTIVES **********************/

struct external_reloc {
  char r_vaddr[4];
  char r_symndx[4];
  char r_type[2];
  char pad[2];
};

struct internal_reloc {
	long r_vaddr;		/* Virtual address of reference */
	long r_symndx;		/* Index into symbol table	*/
	unsigned short r_type;	/* Relocation type		*/
};

/* Relevent values for r_type and i960.  Would someone please document them */

#define R_RELLONG	(0x11)	/* Direct 32-bit relocation */
#define R_IPRSHORT	(0x18)
#define R_IPRMED 	(0x19)	/* 24-bit ip-relative relocation */
#define R_IPRLONG	(0x1a)
#define R_OPTCALL	(0x1b)	/* 32-bit optimizable call (leafproc/sysproc) */
#define R_OPTCALLX	(0x1c)	/* 64-bit optimizable call (leafproc/sysproc) */
#define R_GETSEG	(0x1d)
#define R_GETPA		(0x1e)
#define R_TAGWORD	(0x1f)

#define RELOC struct external_reloc
#define RELSZ 12

#define DEFAULT_DATA_SECTION_ALIGNMENT 4
#define DEFAULT_BSS_SECTION_ALIGNMENT 4
#define DEFAULT_TEXT_SECTION_ALIGNMENT 16
/* For new sections we havn't heard of before */
#define DEFAULT_SECTION_ALIGNMENT 4
