/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 19:50:30 by gfielder          #+#    #+#             */
/*   Updated: 2019/05/17 15:31:03 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

# ifndef ABS
#  define ABS(x) ((x) < 0 ? (-(x)) : (x))
# endif

# define MY_INT_MIN -2147483648

/*
** ------------------------------ Memory functions -----------------------------
*/

void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
							size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memalloc(size_t size);
void					*ft_memdelr(void **ap);
void					*ft_memdup(void *src, size_t len);

/*
** ----------------------------- String informators ----------------------------
*/

size_t					ft_strlen(const char *str);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *str, const char *to_find);
char					*ft_strnstr(const char *str, const char *to_find,
							size_t max_len);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
int						ft_strchr_idx(const char *s, int c);
int						ft_strchr_idx_any(const char *s, const char *any);

/*
** -------------------- String constructors and destructors --------------------
*/

char					*ft_strnew(size_t size);
char					*ft_strsub(char const *s,
							unsigned int start, size_t len);
char					*ft_strdup(const char *str);
char					*ft_strdup_to(const char *str, char c);
char					*ft_strdup_to_any(const char *str, const char *delim);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
void					ft_strdel(char **as);
char					*ft_strjoin(char const *s1, char const *s2);
void					ft_strjoin_inplace(char **s1, char const *s2);
void					ft_strjoin_inplace_rev(const char *s1, char **s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, const char *delim);
char					**ft_strsplit_grouping(char const *s, const char *delim,
							char *groupers);
void					ft_destroy_nullterm_ptrarray(void ***arr);
int						ft_strrepl(char **str, unsigned int start, size_t len,
							const char *with);
char					*ft_getfield(const char *str, int fieldno,
							const char *delims);

/*
** ------------------------------- String modifiers ----------------------------
*/

char					*ft_strcat(char *dest, const char *src);
char					*ft_strncat(char *dest, const char *src, size_t nb);
unsigned int			ft_strlcat(char *dest, const char *src, size_t size);
void					ft_strclr(char *s);
void					ft_strinsert_nchr(char **str, char c, int index, int n);
void					ft_strwrite_nchar(char *str, char c, int n);

/*
** --------------------------- String-integer conversion -----------------------
*/

int						ft_atoi(const char *str);
unsigned long			ft_atoul(const char *str);
char					*ft_itoa(int value);
char					*ft_litoa(long long value);
char					*ft_luitoa(unsigned long long value);
char					*ft_itoa_base(int value, int base);
char					*ft_luitoa_base_upper(unsigned long long value,
							int base);
char					*ft_luitoa_base_lower(unsigned long long value,
							int base);

/*
** ----------------------------- Printing functions  ---------------------------
*/

void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putnbr(int nb);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putnbr_fd(int nb, int fd);
void					ft_printhexbyte(const void *loc);
void					ft_print_hex(unsigned int n);
void					ft_print_hex_padded(unsigned int n, unsigned int width);
void					ft_putchar_np(char c, char c_if_nonprintable);
void					ft_putstr_np(const char *str, char c_if_nonprintable);
void					ft_putnchar_np_hex(const char *str, size_t n);

/*
** ---------------------------- Hashed Array Tables ----------------------------
*/

typedef struct			s_hatlf
{
	void				*data;
	int					start_index;
	struct s_hatlf		*next;
	struct s_hatlf		*prev;
}						t_hatlf;

typedef struct			s_hat
{
	size_t				leaf_capacity;
	size_t				atom_size;
	t_hatlf				*head;
	t_hatlf				*tail;
}						t_hat;

# define FT_HAT_PRINTMODE_HEX 0
# define FT_HAT_PRINTMODE_ASC 1

t_hat					*ft_hatnew(size_t leaf_capacity, size_t atom_size);
void					ft_hatset(t_hat *hat, int index, void *data);
void					*ft_hataccess(t_hat *hat, int index);
void					ft_hatdel(t_hat **hat);
void					*ft_hat_toarr(t_hat *hat, int index, size_t count);
int						ft_hatreindex(t_hat *hat, int head_index);
void					ft_hatprint(t_hat *hat, int data_display_format);
/*
** ------- HAT Utility --------
*/
void					ft_hatinslf(t_hat *hat, t_hatlf *lf);
void					ft_hatdellf(t_hat *hat, t_hatlf **lf);
void					ft_hatdeltolf(t_hat *hat, t_hatlf *lf);
int						ft_hat_get_start_index(t_hat *hat, int index);
int						ft_hat_get_end_index(t_hat *hat, int index);
t_hatlf					*ft_hatlfnew(size_t leaf_capacity, size_t atom_size,
							int start_index);

/*
** ------------------------------- Stringbuilder -------------------------------
*/

# define FT_STRINGBUILDER_LEAFSIZE 32

typedef struct			s_stringbuilder
{
	char				type;
	size_t				len;
	t_hat				*hat;
}						t_stringbuilder;

t_stringbuilder			*ft_sbnew(void);
void					ft_sbdel(t_stringbuilder **sb);
char					*ft_sbtostr(t_stringbuilder *sb);
void					ft_sbwrite(t_stringbuilder *sb, const char *str);
void					ft_sbwriten(t_stringbuilder *sb, const char *str,
							size_t n);
void					ft_sbclear(t_stringbuilder *sb);
void					ft_sbwrite_nullterm(t_stringbuilder *sb);

/*
** ------------------------------- Stringwriter --------------------------------
*/

typedef struct			s_stringwriter
{
	char				type;
	size_t				len;
	char				*buff;
	size_t				capacity;
}						t_stringwriter;

t_stringwriter			*ft_swnew(char *buff_location, size_t capacity);
void					ft_swdel(t_stringwriter **sw);
void					ft_swwrite(t_stringwriter *sw, const char *str);
void					ft_swwriten(t_stringwriter *sw,
							const char *str, size_t n);
void					ft_swclear(t_stringwriter *sw);
void					ft_swwrite_nullterm(t_stringwriter *sw);

/*
** Buffwriter is a variant of stringwriter that does not null terminate
*/

t_stringwriter			*ft_bwnew(char *buff_location, size_t capacity);
void					ft_bwwrite(t_stringwriter *sw, const char *str);
void					ft_bwwriten(t_stringwriter *sw,
							const char *str, size_t n);
void					ft_bwwrite_nullterm(t_stringwriter *sw);
/*
** The below functions are wrappers for the corresponding sw functions. They
** are only provided for interface completeness.
*/
void					ft_bwdel(t_stringwriter **sw);
void					ft_bwclear(t_stringwriter *sw);

/*
** ------------------------------- Fildeswriter --------------------------------
*/

typedef struct			s_fdwriter
{
	char				type;
	size_t				len;
	int					fd;
}						t_fdwriter;

t_fdwriter				*ft_fdwnew(int fd);
void					ft_fdwdel(t_fdwriter **fdw);
void					ft_fdwwrite(t_fdwriter *fdw, const char *str);
void					ft_fdwwriten(t_fdwriter *fdw,
							const char *str, size_t n);
void					ft_fdwclear(t_fdwriter *fdw);
void					ft_fdwwrite_nullterm(t_fdwriter *fdw);

/*
** ------------------------------ Multistringer --------------------------------
**    Emulated polymorphism for various string writing functionality
*/

typedef union			u_multistringer
{
	t_stringbuilder		sb;
	t_stringwriter		sw;
	t_fdwriter			fdw;
}						t_multistringer;

void					ft_msdel(t_multistringer **ms);
void					ft_mswrite(t_multistringer *ms, const char *str);
void					ft_mswriten(t_multistringer *ms, const char *str,
						size_t n);
void					ft_msclear(t_multistringer *ms);
void					ft_msputnchar(t_multistringer *ms, char c, int n);
void					ft_ms_put_ul(t_multistringer *ms, unsigned long nb);
void					ft_mswrite_nullterm(t_multistringer *ms);

/*
** ------------------------------ Get Next Line --------------------------------
*/

# define GNL_BUFF_SIZE 1
# define MIN_LEAF_SIZE 128

# define GNL_EOF 0
# define GNL_OK 1
# define GNL_ERROR -1

# define FDH_GET 0
# define FDH_RMV 1

# define MALLOC_GUARD(x) if (!(x)) return (GNL_ERROR)
# define MALLOC_GUARDN(x) if (!(x)) return (NULL)

typedef struct			s_fdh_initializer
{
	char				nums[28];
	int					bytes;
	int					fd;
	t_hat				*hat;
	char				*check;
	int					found;
	int					total_bytes;

	struct s_fdhandler	*next;
}						t_fdh_initializer;

typedef struct			s_fdhandler
{
	int					index;
	int					line_start;
	int					bytes_to_eof;
	struct s_fdhandler	*prev;
	int					bytes;
	int					fd;
	t_hat				*hat;
	char				*check;
	int					found;
	int					total_bytes;

	struct s_fdhandler	*next;
}						t_fdhandler;

typedef union			u_fdhandler
{
	t_fdh_initializer	i;
	t_fdhandler			a;
}						t_fdhandler_u;

int						ft_get_next_line(const int fd, char **line);

/*
** -------------------------------- Dictionary ---------------------------------
*/

/*
** ------- autosize settings --------
*/
# define FTDICT_AUTO_STR -1

typedef struct			s_dict_ent
{
	char				*key;
	void				*value;
	size_t				val_size;
	struct s_dict_ent	*left;
	struct s_dict_ent	*right;
	struct s_dict_ent	*parent;
}						t_dict_ent;

typedef struct			s_dict
{
	struct s_dict_ent	*head;
	int					autosize;
}						t_dict;

/*
** -------- API ---------
*/
t_dict					*ft_dict_new(int autosize);
int						ft_dict_set(t_dict *dict, char *key, void *value,
							size_t size);
int						ft_dict_unset(t_dict *dict, char *key);
int						ft_dict_del(t_dict **dict);
int						ft_dict_count_entries(t_dict *dict);
t_dict					*ft_dict_copy(t_dict *dict);

/*
** ---- Conversions -----
*/
int						ft_dict_set_parse(t_dict *dict, char *cmd);
char					**ft_dict_to_ntarr(t_dict *dict);
t_dict					*ft_ntarr_to_dict(char **arr);

/*
** ------- Debug --------
*/
int						ft_dict_print_entry(t_dict_ent *ent, int extended);
int						ft_dict_print_tree(t_dict_ent *ent,
							int extended, int depth);
int						ft_dict_print(t_dict *dict);

/*
** ------ Utility -------
*/
t_dict_ent				*ft_dictent_new(char *key, void *value,
							size_t val_size);
int						ft_dict_add(t_dict *dict, t_dict_ent *ent);
void					*ft_dict_get_byref(t_dict *dict, char *key);
t_dict_ent				*ft_dict_getentry_byref(t_dict *dict, char *key);
int						ft_dictent_del(t_dict_ent **ent);
int						ft_dict_remove_entry(t_dict *dict, t_dict_ent *ent);

/*
** -------------------------------- Args Array ---------------------------------
*/

typedef struct			s_argsarr
{
	char				**argv;
	int					argc;
}						t_argsarr;

t_argsarr				*ft_strsplit_args(char const *s, const char *delim,
							char *groupers);
t_argsarr				*ft_argsarr_del(t_argsarr **args);

/*
** ---------------------------------- Queue ------------------------------------
*/

/*
** ------- autosize settings --------
*/
# define FTQ_AUTO_STR -1

typedef struct			s_queue_ent
{
	void				*data;
	size_t				data_size;
	struct s_queue_ent	*next;
}						t_queue_ent;

typedef struct			s_queue
{
	struct s_queue_ent	*head;
	struct s_queue_ent	*tail;
	size_t				len;
	int					autosize;
}						t_queue;

/*
** -------- API ---------
*/
t_queue					*ft_queue_new(int autosize);
int						ft_enqueue(t_queue *q, void *data, size_t data_size);
void					*ft_dequeue(t_queue *q, size_t *data_size);
void					*ft_queue_peek(t_queue *q, size_t *data_size);
t_queue					*ft_queue_del(t_queue **q, int free_data_ptrs);
void					ft_queue_flush(t_queue *q, int free_data_ptrs);

/*
** ------- Debug --------
*/
int						ft_queue_print(t_queue *q);

/*
** ------ Utility -------
*/

/*
** -------------------------------- Options ------------------------------------
*/

# define FTOPT_MAX_OPTIONS 63

typedef struct			s_clopt
{
	char				selected[FTOPT_MAX_OPTIONS + 1];
	int					num_sel;
	char				*program_name;
	t_argsarr			args;
}						t_clopt;

t_clopt					ft_optget(int argc, char **argv);
int						ft_issel(t_clopt *opt, char c);

#endif
