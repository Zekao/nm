#include "include/nm.h"

void print_content_64(Elf64_Ehdr *header)
{
    char **content;

    content = parse_elf64(header);
	(void)content;
    return ;
}

void print_content_32(Elf32_Ehdr *header)
{
    char **content;
    content = parse_elf32(header);
	(void)content;
    return;
}