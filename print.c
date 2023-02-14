#include "include/nm.h"

void print_content_64(Elf64_Ehdr *header)
{
    char **content;
    int i;

    content = parse_elf64(header);
    return ;
    i = -1;
    while (content[++i] && content[i + 1] != NULL)
        printf("%p %s \n", content[i], content[i]);
}

void print_content_32(Elf32_Ehdr *header)
{
    char **content;
    int i;

    content = parse_elf32(header);
    i = -1;
    while (content[++i])
        printf("%p %s \n", content[i], content[i]);
}