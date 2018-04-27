/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:41:53 by lperret           #+#    #+#             */
/*   Updated: 2018/04/27 12:08:39 by lperret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdarg.h>
# include <wchar.h>

# define BUFF_SIZE 6
# define RESET  "\x1B[0m"
# define BLA  	"\x1B[30m"
# define RED  	"\x1B[31m"
# define GRE  	"\x1B[32m"
# define YEL 	 "\x1B[33m"
# define BLU  	"\x1B[34m"
# define PIN  	"\x1B[35m"
# define TUR  	"\x1B[36m"
# define WHI  	"\x1B[37m"
# define WHI_B  "\x1B[47m"

typedef struct		s_fd
{
	int				fd;
	char			*save;
	struct s_fd		*next;
}					t_fd;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_print
{
	int				hashtag;
	int				zero;
	int				minus;
	int				plus;
	int				space;
	int				width;
	int				precision;
	int				type;
	int				neg;
	int				len;
	int				next;
	intmax_t		putf;
	int				boolutf;
	char			char_conv;
}					t_print;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void(*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putcolor(char const *s, char const *color);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_putgrid(char **grid);
void				print_memory(const void *addr, size_t size);
int					get_next_line(const int fd, char **line);

int					ft_printf(const char *format, ...);

char				*ft_conv_cutf(wchar_t utf, t_print *elem);
char				*ft_conv_sutf(va_list ap, t_print *elem);

char				*ft_conv_c(char *str, t_print *elem, va_list ap);
char				*ft_conv_s(char *str, t_print *elem, va_list ap);
char				*ft_conv_d(char *str, t_print *elem, va_list ap);
char				*ft_conv_u(char *str, t_print *elem, va_list ap);
char				*ft_conv_o(char *str, t_print *elem, va_list ap);
char				*ft_conv_x(char *str, t_print *elem, va_list ap);
char				*ft_conv_b(char *str, t_print *elem, va_list ap);
char				*ft_conv_p(char *str, t_print *elem, va_list ap);
char				*ft_conv_percent(char *str, t_print *elem, va_list ap);

char				*ft_parse_flags(char *cpy, t_print *elem);
char				*ft_parse_width(char *cpy, t_print *elem);
char				*ft_parse_precision(char *cpy, t_print *elem);
char				*ft_parse_type(char *cpy, t_print *elem);
int					ft_parse_conversion(char c, t_print *elem);

char				*ft_set_alpha(t_print *elem, size_t len);
intmax_t			ft_multicast(va_list ap, t_print *elem);
void				ft_set_digit(char *ptr, char *str, t_print *elem);
char				*ft_root(char *format, va_list ap, t_print *elem);
int					ft_printf(const char *format, ...);

void				ft_get_plus_d(char *ptr, char *ptr_ptr, t_print *elem);
void				ft_get_hash_o(char *ptr, char *ptr_ptr, t_print *elem);
void				ft_get_hash_x(char *ptr, char *ptr_ptr, t_print *elem);
void				ft_get_ox(char *ptr, t_print *elem);

char				*ft_wild_format(char *cpy, t_print *elem);
char				*ft_cutter(char *format, t_print *elem);
char				*ft_freezer(char *str);

char				*ft_uchatoa_base(unsigned char nb, int base);
char				*ft_ushotoa_base(unsigned short int nb, int base);
char				*ft_utoa_base(unsigned int nb, int base);
char				*ft_ulotoa_base(unsigned long long int nb, int base);
char				*ft_slotoa_base(long long int nb, int base, t_print *elem);

char				*ft_join_memory_free_all_bis(char *s1, char *s2,
		size_t size, t_print *elem);
char				*ft_join_memory_free_all(char *s1, char *s2, t_print *elem);
char				*ft_join_memory_free_some(char *s1, char *s2,
		t_print *elem);
char				*ft_join_and_free_all(char *s1, char *s2);
char				*ft_strndcpy(char *dst, char *src);

#endif
