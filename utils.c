/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:55:18 by emaugale          #+#    #+#             */
/*   Updated: 2023/02/13 23:33:19 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/nm.h"

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