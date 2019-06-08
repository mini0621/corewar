/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:18:49 by mnishimo          #+#    #+#             */
/*   Updated: 2019/03/28 16:17:06 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libftprintf.h"
# include <stdint.h>

typedef enum		e_lm
{
	none = 0,
	h,
	hh,
	l,
	ll,
	L,
	j
}					t_lm;

typedef struct		s_flags
{
	char			sharp;
	char			min_0;
	char			plus_sp;
}					t_flags;

typedef struct		s_printops
{
	t_flags			flag;
	size_t			width;
	size_t			precision;
	t_lm			lmod;
	char			cnvrtsp;
}					t_printops;

typedef char		*(*t_prcs_fp)(va_list *, t_printops *, size_t *);

typedef struct		s_funcs
{
	char			cnvrt_specifier;
	t_prcs_fp		function;
}					t_funcs;

typedef struct		s_double
{
	int				sign;
	uint16_t		expo;
	uint64_t		frac;
}					t_double;

int					ft_printf(const char *fmt, ...);
int					ft_sprintf(char *str, const char *fmt, ...);
int					ft_snprintf(char *str, size_t size, const char *fmt, ...);
int					ft_dprintf(int fd, const char *fmt, ...);
int					ft_asprintf(char **ret, const char *fmt, ...);
void				printoutput(char *output, size_t len);
int					asprinterror(char **ret);
void				snprintoutput(char *str, char *output, size_t len,
		size_t size);
void				dprintoutput(int fd, char *output, size_t len);
char				*join_chars(char **output, char *fmt, size_t *len);
char				*join_cnvrt(char **output, char **start,
		va_list *ap, size_t *len);

char				*convert(va_list *ap, char **start, size_t *l);
t_prcs_fp			getprcsf(t_printops *opt);
char				*prcs_percent(t_printops *opt, size_t *l);

int					is_cnvrtsp(char c);
t_printops			*initoption(void);
t_printops			*readops(char **start, va_list *ap);
t_printops			*adjust_ops(t_printops *opt, char *i, int ret,
		char **start);
void				storeops(char *i, t_printops *opt, va_list *ap);

char				*prcs_e(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_x(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_o(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_u(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_d(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_p(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_s(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_c(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_f(va_list *ap, t_printops *opt, size_t *l);
char				*prcs_ld(va_list *ap, t_printops *opt, int *sign);
char				*prcs_db(va_list *ap, t_printops *opt, int *sign);
char				*sp_double(int sign, uint64_t frac);

long long			ft_llpower(long long base, long long power);
char				*ft_lltoa(long long n);
unsigned long long	ft_lluporwer(unsigned long long base,
		unsigned long long power);
char				*ft_llutoa(unsigned long long n, unsigned int base,
		unsigned long long max);

long double			ft_neg_power(int power);
char				get_n_dig(long double n);
long double			round_ld(long double n, int precision);
char				*ft_ldtolltoa(long double n, int precision);

void				carry_frac(unsigned long long *frac10);
void				add_frac(unsigned long long *a, unsigned long long **b);
void				mult_frac(unsigned long long *frac, int a, int times);
int					div_frac(unsigned long long *a, int times);
int					shift_frac_right(unsigned long long *a);
int					shift_frac_left(unsigned long long *a);
unsigned long long	get_mincarry(unsigned long long *a,
		unsigned long long carry);

char				*fractoa(unsigned long long *frac, int e);
unsigned long long	*init_frac(uint64_t frac);
char				*get_frac10(t_double *n, int frac_bits, int subnormal);
int					get10th_expo(uint16_t expo);
int					add_zeros(char **s, int point);
char				*ft_ldtoa(t_double *n, size_t precision, int e);
t_double			*get_ldouble(long double n);
int					round_s(char **s, int point, size_t precision);
int					skip_zeros(char *s);
char				*sub_integer(char **s, int point, int precision);

char				*ft_dbtoa(t_double *n, size_t precision, int e);
t_double			*get_double(double n);

char				*normalize(char **s, int expo, size_t precision,
		int iszero);
char				*prcs_eld(va_list *ap, t_printops *opt, int *sign);
char				*prcs_edb(va_list *ap, t_printops *opt, int *sign);
char				*round_e(char **s, size_t precision, int iszero);
char				*prcs_flags(t_printops *opt, char **s, int sign);
char				*prcs_cflags(t_printops *opt, char **s, size_t *l);
char				*prcs_sharp(char sp, char **s);
char				*prcs_plus(char	sp, char **s, char c);
char				*prcs_zero(char sp, char **s, size_t w, t_flags *flags);
char				*prcs_min(char **s, size_t w, char min);

char				*prcs_precision(char **s, size_t precision, int sign);
char				*prcs_precision_s(char **s, size_t precision);
char				*prcs_precision_end(char **s, size_t precision);
#endif
