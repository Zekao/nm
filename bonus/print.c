#include "../include/nm_bonus.h"

void print_content_64(Elf64_Ehdr *header, char *bonus_flag)
{
    char **content;

    content = parse_elf64(header, bonus_flag);
	(void)content;
    return ;
}

void print_content_32(Elf32_Ehdr *header, char *bonus_flag)
{
    char **content;
    content = parse_elf32(header, bonus_flag);
	(void)content;
    return;
}