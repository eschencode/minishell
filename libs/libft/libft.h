/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:06:47 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/24 17:58:57 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

int				ft_atoi(const char *str);

void			*ft_memset(void *b, int c, size_t len);

void			ft_bzero(void *s, size_t n);

void			*ft_calloc(size_t nmemb, size_t size);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

char			*ft_itoa(int n);

void			*ft_memccpy(void *dst, const void *src, int c, size_t n);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t n);

void			*ft_memmove(void *dst, const void *src, size_t len);

void			ft_putchar_fd(char c, int fd);

void			ft_striteri(char *s, void (*f)(unsigned int, char *));

void			ft_putendl_fd(char *s, int fd);

void			ft_putnbr_fd(int n, int fd);

void			ft_putstr_fd(char *s, int fd);

char			**ft_split(char const *s, char c);

char			*ft_strchr(const char *s, int c);

char			*ft_strdup(const char *s1);

char			*ft_strjoin(char const *s1, char const *s2);

size_t			ft_strlcat(char *dst, const char *src, size_t size);

size_t			ft_strlcpy(char *dst, const char *src, size_t size);

size_t			ft_strlen(const char *s);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);

char			*ft_strrchr(const char *s, int c);

char			*ft_strtrim(char const *s1, char const *set);

char			*ft_substr(char const *s, unsigned int start, size_t len);

int				ft_tolower(int c);

int				ft_toupper(int c);

size_t			ft_strcat(char *dest, const char *src);

char			*get_next_line(int fd);
char			*ft_new_left_str(char *left_str);
char			*ft_get_ret_str(char *left_str);
char			*read2left_str(int fd, char *left_str);
char			*gnlft_strchr(char *s, int c);
char			*gnlft_strjoin(char *s1, char *s2);
size_t			gnlft_strlen( char *str);
int				ft_printf(const char *str, ...);
int				ft_print_char(int c);
int				ft_print_str(char *str);
int				ft_print_percent(void);
int				ft_print_nbr(int nbr);
int				ft_formats(va_list args, const char format);
int				ft_hex_len(unsigned int num);
int				ft_print_hex(unsigned int num, char format);
void			ft_put_hex(unsigned int num, const char format);
int				ft_print_ptr(unsigned long long ptr);
int				ft_count_len(unsigned int nbr);
char			*ft_unsigned_itoa(int len, unsigned int nbr);
int				ft_print_unsigned_int(unsigned int nbr);
void			ft_put_ptr(unsigned long long num);
int				ft_ptr_len(unsigned long long ptr);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_strcpy(char *dst, const char *src);

#endif
