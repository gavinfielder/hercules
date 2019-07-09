/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:36:42 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/30 01:23:24 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <dirent.h>
# include <stdint.h>

# define FTLS_NAME_SIZE 1024
# define FTLS_USER_SIZE 32
# define FTLS_GROUP_SIZE 32
# define FTLS_LINK_SIZE 1023
# define FTLS_XATTR_SIZE 1023
# define FTLS_WINSIZE_PAD 20

typedef struct						s_file
{
	struct s_file					*left;
	struct s_file					*right;
	struct s_file					*parent;
	char							name[FTLS_NAME_SIZE + 1];
	char							user[FTLS_USER_SIZE + 1];
	char							group[FTLS_GROUP_SIZE + 1];
	char							*link;
	char							*xattr;
	ssize_t							xattr_len;
	char							*path;
	acl_t							acl;
	struct stat						*s;
}									t_file;

/*
** From man 2 stat:
**
** struct stat { / when _DARWIN_FEATURE_64_BIT_INODE is defined /
**     dev_t           st_dev;           / ID of device containing file /
**     mode_t          st_mode;          / Mode of file (see below) /
**     nlink_t         st_nlink;         / Number of hard links /
**     ino_t           st_ino;           / File serial number /
**     uid_t           st_uid;           / User ID of the file /
**     gid_t           st_gid;           / Group ID of the file /
**     dev_t           st_rdev;          / Device ID /
**     struct timespec st_atimespec;     / time of last access /
**     struct timespec st_mtimespec;     / time of last data modification /
**     struct timespec st_ctimespec;     / time of last status change /
**     struct timespec st_birthtimespec; / time of file creation(birth) /
**     off_t           st_size;          / file size, in bytes /
**     blkcnt_t        st_blocks;        / blocks allocated for file /
**     blksize_t       st_blksize;       / optimal blocksize for I/O /
**     uint32_t        st_flags;         / user defined flags for file /
**     uint32_t        st_gen;           / file generation number /
**     int32_t         st_lspare;        / RESERVED: DO NOT USE! /
**     int64_t         st_qspare[2];     / RESERVED: DO NOT USE! /
** };
*/

/*
** -----------------------------------------------------------------------------
**    Function Types and Other Forward Declarations
** -----------------------------------------------------------------------------
*/
struct s_ls_options;
typedef struct s_ls_options	t_ls_options;
typedef void	(*t_ftls_static_initfunc)	(t_file *, t_ls_options *);
typedef void	(*t_ftls_note_entry)	(t_file *, uint16_t);
typedef void	(*t_ftls_fprnt)	(t_file *, t_ls_options *);
typedef void	(*t_ftls_outlo)	(t_file *);
typedef long	t_ftls_itsalong;
typedef t_ftls_itsalong	(*t_ftls_fcmp)	(t_file *, t_file *);

/*
** -----------------------------------------------------------------------------
**    Library API
** -----------------------------------------------------------------------------
*/
t_file								*ft_list_directory_repl(t_file *head,
										const char *path, char *ftls_options);
t_file								*ft_list_directory(const char *path,
										char *ftls_options);
t_file								*ft_match_file(t_file *head,
										const char *prefix);
t_file								*ft_match_file_loop(t_file *head,
										const char *prefix, t_file *f);
t_file								*ft_get_file(const char *path,
										char *ftls_options);
t_file								*ft_match_file_exact(t_file *head,
										const char *filename);

/*
** -----------------------------------------------------------------------------
**    Sorting
** -----------------------------------------------------------------------------
*/
long								ftls_byname(t_file *a, t_file *b);
long								ftls_nosort(t_file *a, t_file *b);
long								ftls_bytime(t_file *a, t_file *b);
long								ftls_bytime_a(t_file *a, t_file *b);
long								ftls_bytime_c(t_file *a, t_file *b);
long								ftls_bytime_m(t_file *a, t_file *b);
long								ftls_bytime_bigu(t_file *a, t_file *b);
long								ftls_bysize(t_file *a, t_file *b);

/*
** -----------------------------------------------------------------------------
**    Tree Operations
** -----------------------------------------------------------------------------
*/
t_file								*ftls_new_node(void);
t_file								*ftls_del_node(t_file **f);
t_file								*ftls_del_tree(t_file **head);
t_file								*ftls_ins_node(t_file **head,
										t_file *toadd, t_ftls_fcmp cmp,
										char sort_dir);
t_file								*ft_get_successor(t_file *f);
t_file								*ft_get_predecessor(t_file *f);
void								ftls_set_parent_pointers(t_file *head);

/*
** -----------------------------------------------------------------------------
**    Options Management
** -----------------------------------------------------------------------------
*/
typedef struct						s_ftls_display_mode
{
	t_ftls_fprnt					display;
	t_ftls_static_initfunc			display_init;
	t_ftls_static_initfunc			display_deinit;
	t_ftls_note_entry				note_entry;
}									t_ftls_display_mode;

struct								s_ls_options
{
	char							a;
	char							l;
	char							big_r;
	char							lxattr;
	char							sort_dir;
	char							time_sel;
	char							d;
	char							lacl;
	char							big_g;
	char							g;
	char							p;
	char							n;
	char							big_t;
	t_ftls_display_mode				display_mode;
	t_ftls_fcmp						sort;
};

t_ls_options						*ftls_get_options(t_ls_options *options,
										char *opt_str);
void								ftls_out_l_set_outl_options
										(t_ls_options *options);

/*
** -----------------------------------------------------------------------------
**    File Operations
** -----------------------------------------------------------------------------
*/
t_file								*ftls_new_file(const char *path,
										const char *filename,
										t_ls_options *options);
t_file								*ftls_list_directory(const char *path,
										t_ls_options *options);

/*
** -----------------------------------------------------------------------------
**    Output
** -----------------------------------------------------------------------------
*/
extern const t_ftls_display_mode	g_ftls_display_h;
extern const t_ftls_display_mode	g_ftls_display_v;
extern const t_ftls_display_mode	g_ftls_display_c;
extern const t_ftls_display_mode	g_ftls_display_l;

void								ftls_out_main(t_file *head,
										t_ls_options *options);

void								ftls_out_v(t_file *f,
										t_ls_options *options);
void								ftls_out_l(t_file *f,
										t_ls_options *options);
void								ftls_out_h(t_file *f,
										t_ls_options *options);
void								ftls_out_h_color(t_file *f,
										t_ls_options *options);
void								ftls_out_c(t_file *f,
										t_ls_options *options);

void								ftls_out_color(t_file *f);

void								ftls_outh_new_entry(void);
void								ftls_note_entry(t_file *f, uint16_t len);
void								ftls_end_column_output(t_file *f,
										t_ls_options *options);
void								ftls_begin_column_output(t_file *f,
										t_ls_options *options);

void								ftls_cleanup_csv(t_file *f,
										t_ls_options *options);

void								ftls_outl_print_mode(t_file *f);
void								ftls_outl_print_totalblocks(t_file *f,
										t_ls_options *options);

void								ftls_out_l_n0g0(t_file *f);
void								ftls_out_l_n1g0(t_file *f);
void								ftls_out_l_n0g1(t_file *f);
void								ftls_out_l_n1g1(t_file *f);

/*
** -----------------------------------------------------------------------------
**    Terminal Control
** -----------------------------------------------------------------------------
*/
uint16_t							tty_get_window_width(void);
void								tty_begin_column(int col);
void								tty_next_row(void);
void								tty_end_columns(void);
uint16_t							tty_note_length(uint16_t len);

/*
** -----------------------------------------------------------------------------
**    Miscellaneous
** -----------------------------------------------------------------------------
*/
void								ftls_noop(t_file *f, t_ls_options *options);
long								ftls_count_blocks(t_file *f);
struct timespec						*ftls_get_selected_timespec(t_file *f,
										t_ls_options *options);
char								*ft_prepend_path(char const *dir,
										char const *filename);
char								*ft_basename(char const *path);

/*
** -----------------------------------------------------------------------------
**    Stuff we need because norm makes us write bad code
** -----------------------------------------------------------------------------
*/
typedef struct						s_ftls_ldhelper
{
	t_file							*head;
	DIR								*dp;
	struct dirent					*ent;
	char							*path;
	t_file							*f;
	const char						*dir;
	t_ls_options					*options;
}									t_ftls_ldhelper;

t_file								*ftls_fileop_abort_close(t_file *f,
										t_ftls_ldhelper *h);

#endif
