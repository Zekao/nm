/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:55:18 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/15 19:47:23 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_bonus.h"

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int    ft_putstr_error(char *str)
{
    write(2, str, ft_strlen(str));
    return (1);
}

int check_elf(Elf64_Ehdr *header)
{
    if (header->e_ident[EI_MAG0] != ELFMAG0 ||
        header->e_ident[EI_MAG1] != ELFMAG1 ||
        header->e_ident[EI_MAG2] != ELFMAG2 ||
        header->e_ident[EI_MAG3] != ELFMAG3)
        return (-1);
    return (0);
}

void putnbr_hex(size_t n)
{
	char *hex = "0123456789abcdef";
	if (n > 15)
		putnbr_hex(n / 16);
	write(1, &hex[n % 16], 1);
}

int str_starts_with(char const *haystack, char const *needle)
{
    while (*needle && *haystack && *haystack == *needle)
    {
        ++haystack;
        ++needle;
    }
    return *needle == '\0';
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

size_t symbol_len32(Elf32_Addr value)
{
	size_t len = 0;
	while (value > 0)
	{
		value /= 16;
		len++;
	}
	return len;
}

size_t symbol_len64(Elf64_Addr value)
{
	size_t len = 0;
	while (value > 0)
	{
		value /= 16;
		len++;
	}
	return len;
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
