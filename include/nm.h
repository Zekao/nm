/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:55:15 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/13 03:06:02 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once        

#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <elf.h>

size_t  ft_strlen(char *str);
int     ft_putstr_error(char *str);
char    **parse_elf32(Elf32_Ehdr *header);
char    **parse_elf64(Elf64_Ehdr *header);
int     check_elf(Elf64_Ehdr *header);
void	print_symbol_line32(Elf32_Sym *symbol, char *strtab_content, char *section);
void    print_content_32(Elf32_Ehdr *header);
void    print_content_64(Elf64_Ehdr *header);
void	print_symbol_line(Elf64_Sym *symbol, char *strtab_content, char *section);
char	content_flag(Elf64_Sym *symbol, char *section);
char	content_flag32(Elf32_Sym *symbol, char *section);


typedef struct s_content
{
    char *name;
    char type;
    unsigned long offset;
} t_content;