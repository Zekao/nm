/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:55:15 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/15 20:03:31 by emaugale         ###   ########.fr       */
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
#include <stdbool.h>
#include <elf.h>

/**************************************************************/
/*                        Structs                             */
/**************************************************************/

typedef struct s_content_32
{
    char *name;
    char *section;
    char type;
    Elf32_Sym symbol;
    unsigned long offset;
} t_content_32;

typedef struct s_content_64
{
    char *name;
    char *section;
    char type;
    Elf64_Sym symbol;
    unsigned long offset;
} t_content_64;



/**************************************************************/
/*                      Sorting my struct                     */
/**************************************************************/

t_content_32        **sort_t_content_32(t_content_32 **content);
t_content_64        **sort_t_content_64(t_content_64 **content);

/**************************************************************/
/*                        Utils functions                     */
/**************************************************************/

char	            *ft_strdup(char *str);
size_t              ft_strlen(char *str);
int                 ft_putstr_error(char *str);
void                free_struct(t_content_32 **content);
void                free_struct64(t_content_64 **content);
void                putnbr_hex(size_t n);
void                ft_putstr(char *str);
int                 ft_strcmp(char *s1, char *s2);
size_t              symbol_len32(Elf32_Addr value);
size_t              symbol_len64(Elf64_Addr value);

/**************************************************************/
/*                        Print functions                     */
/**************************************************************/

void                print_content_32(Elf32_Ehdr *header, char *bonus_flag);
void                print_content_64(Elf64_Ehdr *header, char *bonus_flag);

char	            content_flag(Elf64_Sym *symbol, char *section);
char	            content_flag32(Elf32_Sym *symbol, char *section);

/**************************************************************/
/*                       Parsing functions                    */
/**************************************************************/

char                **parse_elf32(Elf32_Ehdr *header, char *bonus_flag);
char                **parse_elf64(Elf64_Ehdr *header, char *bonus_flag);
int                 check_elf(Elf64_Ehdr *header);
int                 str_starts_with(char const *haystack, char const *needle);
