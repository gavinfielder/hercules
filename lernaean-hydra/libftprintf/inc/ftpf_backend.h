/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_backend.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 22:54:50 by gfielder          #+#    #+#             */
/*   Updated: 2019/03/08 22:45:39 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPF_BACKEND_H
# define FTPF_BACKEND_H

# include "libft.h"
# include <stdarg.h>

# define FTPF_SIZEMOD_HH   1
# define FTPF_SIZEMOD_H    2
# define FTPF_SIZEMOD_L    3
# define FTPF_SIZEMOD_LL   4
# define FTPF_SIZEMOD_BIGL 5

# define FTPF_NUM_CHECKFLAGS 28
# define FTPF_CHECKFLAG_INIT 0x0FFFFE7F
# define FTPF_CHECKER_BEGIN 0
# define FTPF_CHECKER_END (FTPF_NUM_CHECKFLAGS - 1)

# define FTPF_NUM_EXPANDERS 13

# define FTPF_UNLIMITED_LEN -1

# define FTPF_ERROR -1

/*
** -----------------------------------------------------------------------------
**                        CHECK_FLAGS
** -----------------------------------------------------------------------------
**  bit        description                  masks      mask description
** -----------------------------------------------------------------------------
**   0   %%  : print a %                    0000.0000  (disallows all)
** -----------------------------------------------------------------------------
**   1   ##$ : choose argument number       FFFF.FFFC  (disallows self & prior)
** -----------------------------------------------------------------------------
**   2   0   : zero padding                 FFFF.FFFC  (disallows prior groups)
**   3   ' ' : space before positive        FFFF.FFFC  (disallows prior groups)
**   4   #   : alternate format display     FFFF.FFFC  (disallows prior groups)
**   5   -   : pad for negative sign        FFFF.FFFC  (disallows prior groups)
**   6   +   : always put a sign            FFFF.FFFC  (disallows prior groups)
** -----------------------------------------------------------------------------
**   7       : UNUSED
**   8       : UNUSED
** -----------------------------------------------------------------------------
**   9   ##  : field width                  FFFF.FF00  (disallows self & prior)
** -----------------------------------------------------------------------------
**   10   .  : precision                    FFFF.FE00  (disallows self & prior)
** -----------------------------------------------------------------------------
**   11  hh  : short short size modifier    FFFF.C000  (prior & same group)
**   12  h   : short size modifer           FFFF.C000  (prior & same group)
**   13  ll  : long long size modifier      FFFF.C000  (prior & same group)
**   14  l   : long size modifier           FFFF.C000  (prior & same group)
**   15  L   : long double size modifier    FFFF.C000  (prior & same group)
** -----------------------------------------------------------------------------
**   16  p   : ptr expansion                0000.0000  (disallows all)
**   17  di  : signed integer expansion     0000.0000  (disallows all)
**   18  b   : binary                       0000.0000  (disallows all)
**   19  u   : unsigned integer expansion   0000.0000  (disallows all)
**   20  x   : hex expansion lower          0000.0000  (disallows all)
**   21  X   : hex expansion upper          0000.0000  (disallows all)
**   22  f   : float expansion              0000.0000  (disallows all)
**   23  s   : string expansion             0000.0000  (disallows all)
**   24  c   : char expansion               0000.0000  (disallows all)
**   25  o   : octal expansion              0000.0000  (disallows all)
**   26  m   : memory expansion             0000.0000  (disallows all)
**   27  {   : extension                    0000.0000  (disallows all)
** -----------------------------------------------------------------------------
**   27 - 31   UNUSED
** -----------------------------------------------------------------------------
*/

typedef long long						t_ftint8;
typedef int								t_ftint4;
typedef short							t_ftint2;
typedef char							t_ftint1;
typedef unsigned long long				t_ftuint8;
typedef unsigned int					t_ftuint4;
typedef unsigned short					t_ftuint2;
typedef unsigned char					t_ftuint1;

typedef struct s_ftpf_master_data		t_ftpf_master_data;
typedef struct s_ftpf_expandler			t_ftpf_expandler;
typedef	int		(*t_ftpf_expander_func)	(t_ftpf_master_data *);
typedef int		(*t_ftpf_checker_func)	(t_ftpf_expandler *);
typedef	t_ftint8	(*t_ftpf_sint_ga)	(t_ftpf_master_data *);

struct									s_ftpf_expandler
{
	const char							*start;
	unsigned int						check_flags;
	unsigned char						handled_len;
	unsigned char						total_specifier_len;
	unsigned char						zpad;
	unsigned char						space;
	unsigned char						altform;
	unsigned char						lfjusty;
	unsigned char						allsign;
	unsigned char						field_width;
	int									precision;
	unsigned char						size_mod;
	short								arg_num;
	t_ftpf_expander_func				expand;
};

struct									s_ftpf_master_data
{
	int									i;
	int									max_len;
	int									len;
	va_list								args;
	t_ftpf_expandler					*ex;
	t_multistringer						*ms;
	short								next_arg_num;
};

/*
** -----------------------------------------------------------------------------
**              Specific expansion helper functions and structures
** -----------------------------------------------------------------------------
*/

long long								ftpf_sint_get_arg_4
											(t_ftpf_master_data *md);
long long								ftpf_sint_get_arg_8
											(t_ftpf_master_data *md);

void									ftpf_handle_padding_sint
											(t_ftpf_master_data *md,
											char **str);

/*
** -----------------------------------------------------------------------------
**                             Primary Functions
** -----------------------------------------------------------------------------
*/

void									ftpf_expandler_init
										(t_ftpf_expandler *ex,
										const char *start);
void									ftpf_read_specifier
										(t_ftpf_expandler *ex);
void									ftpf_get_arg(t_ftpf_expandler *ex);
int										ftpf_master(t_multistringer *ms,
										const char *fmt, int max_len,
										va_list args);
int										ft_vsbprintf(t_stringbuilder *sb,
										const char *fmt, va_list args);
int										ft_vdprintf(int fd, const char *fmt,
										va_list args);
int										ft_vsprintf(char *str, const char *fmt,
										va_list args);
int										ft_vsnprintf(char *str, size_t size,
										const char *fmt, va_list args);
int										number_len(t_ftpf_expandler *ex);

/*
** -----------------------------------------------------------------------------
**                             Checker Functions
** -----------------------------------------------------------------------------
*/

extern const	t_ftpf_checker_func		g_checkfuncs[FTPF_NUM_CHECKFLAGS];

int										ftpf_check_percent
										(t_ftpf_expandler *expandler);
int										ftpf_get_arg_num
										(t_ftpf_expandler *expandler);
int										ftpf_check_zeropad_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_spacepad_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_alternate_form_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_negativepad_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_alwayssign_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_leftjustify_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_fieldwidth_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_precision_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_shortshort_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_short_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_long_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_longlong_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_longdouble_mod
										(t_ftpf_expandler *expandler);
int										ftpf_check_ptr_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_signed_int_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_binary_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_unsigned_int_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_hexlower_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_hexupper_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_float_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_string_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_char_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_octal_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_memory_expansion
										(t_ftpf_expandler *expandler);
int										ftpf_check_extension_expansion
										(t_ftpf_expandler *expandler);

/*
** -----------------------------------------------------------------------------
**                            Expander Functions
** -----------------------------------------------------------------------------
*/

int										ftpf_percent_expander(
											t_ftpf_master_data *md);
int										ftpf_ptr_expander(
											t_ftpf_master_data *md);
int										ftpf_signed_int_expander(
											t_ftpf_master_data *md);
int										ftpf_binary_expander(
											t_ftpf_master_data *md);
int										ftpf_unsigned_int_expander(
											t_ftpf_master_data *md);
int										ftpf_hexlower_expander(
											t_ftpf_master_data *md);
int										ftpf_hexupper_expander(
											t_ftpf_master_data *md);
int										ftpf_float_expander(
											t_ftpf_master_data *md);
int										ftpf_string_expander(
											t_ftpf_master_data *md);
int										ftpf_char_expander(
											t_ftpf_master_data *md);
int										ftpf_octal_expander(
											t_ftpf_master_data *md);
int										ftpf_memory_expander(
											t_ftpf_master_data *md);
int										ftpf_extension_expander(
											t_ftpf_master_data *md);

#endif
