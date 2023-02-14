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
void print_content_32(Elf32_Ehdr *header);
void print_content_64(Elf64_Ehdr *header);