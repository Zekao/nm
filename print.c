#include "include/nm.h"

void print_content_64(Elf64_Ehdr *header)
{
    char **content;
    int i;

    content = parse_elf64(header);
    (void)content;
    (void)i;
    return ;
}

void print_content_32(Elf32_Ehdr *header)
{
    char **content;
    int i;

    content = parse_elf32(header);
    return;
    i = -1;
    while (content[++i])
        printf("%p %s \n", content[i], content[i]);
}

void	print_symbol_line(Elf64_Sym *symbol, char *strtab_content, char *section)
{
	char symbol_type = content_flag(symbol, section);

	if (symbol_type == 'a')
		return ;
	if (symbol_type != 'U' || symbol_type != 'w')
		printf("%016lx %c %s\n", symbol->st_value, symbol_type, strtab_content + symbol->st_name);
	else
		printf("%-17c %c %s\n", 0, symbol_type, strtab_content + symbol->st_name);
}

void	print_symbol_line32(Elf32_Sym *symbol, char *strtab_content, char *section)
{
	char symbol_type = content_flag32(symbol, section);

	if (symbol_type == 'a')
		return ;
	if (symbol_type != 'U' && symbol_type != 'w')
		printf("%08x %c %s\n", symbol->st_value, symbol_type, strtab_content + symbol->st_name);
	else
		printf("%-9c %c %s\n", 0, symbol_type, strtab_content + symbol->st_name);
}