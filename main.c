/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:35:14 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/11 03:04:18 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/nm.h"

char **parse_elf32(Elf32_Ehdr *header)
{
	/*
		--- ELF32 ---

		e_shoff: offset to section header table
		e_shnum: number of section headers
		e_shstrndx: index of section name string table
		sh_name: offset to section name
		sh_offset: offset to section data
		
	*/
	Elf32_Shdr *section;
	Elf32_Shdr *strtab;
	char *strtab_content;
	char **content;
	int i;

	section = (void *)header + header->e_shoff;
	strtab = &section[header->e_shstrndx];
	strtab_content = (void *)header + strtab->sh_offset;
	content = malloc(sizeof(char *) * header->e_shnum);
	i = -1;
	while (++i < header->e_shnum)
		content[i] = strtab_content + section[i].sh_name;
	return (content);
}

char	content_flag(Elf64_Sym *symbol)
{
	if (ELF64_ST_TYPE(symbol->st_info) == STT_FUNC)
		return ('T');
	else if (ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
		return ('D');
	else if (ELF64_ST_TYPE(symbol->st_info) == STT_NOTYPE)
		return ('U');
	else if (ELF64_ST_TYPE(symbol->st_info) == STT_FILE)
		return ('F');
	else if (ELF64_ST_TYPE(symbol->st_info) == STT_COMMON)
		return ('C');
	else if (ELF64_ST_TYPE(symbol->st_info) == STT_TLS)
		return ('T');
	else if (ELF64_ST_TYPE(symbol->st_info) == STT_GNU_IFUNC)
		return ('I');
	return ('?');
}

// void	print_symbol_line(Elf64_Sym *symbol, char *strtab_content)
// {
// 	char symbol_type = content_flag(symbol);

// 	if (symbol_type == '?')
// 		return ;
// 	else if (symbol_type != 'U')
// 		printf("%016lx %c %s\n", symbol->st_value, symbol_type, strtab_content + symbol->st_name);

// 	else
// 		printf("%-17c %c %s\n", 0, symbol_type, strtab_content + symbol->st_name);
// }

	/*								Macros Used							*/
	//-----------------------------------------------------------------//

		// SHT_SYMTAB: symbol table
		// SHT_STRTAB: string table
		// STT_FUNC: function
		// STT_OBJECT: variable
		// STT_NOTYPE: undefined symbols (like external functions)
		// ELF64_ST_TYPE: get the type of a symbol according to the macros defined in elf.h

	//-----------------------------------------------------------------//
	/*												      			  */

char **parse_elf64(Elf64_Ehdr *header)
{

	Elf64_Shdr 		*section;
	Elf64_Shdr 		*symtab;
	Elf64_Sym 		*symbol;
	char 			*strtab_content;
	size_t 			j;
	size_t			i;



	section = (void *)header + header->e_shoff;
	strtab_content = (void *)header + section[header->e_shstrndx].sh_offset;
	for (i = 0; i < header->e_shnum; i++) {
		if (section[i].sh_type == SHT_SYMTAB)
			symtab = &section[i];
	}

	if (!symtab || !strtab_content)
		return (NULL);

	symbol = (void *)header + symtab->sh_offset;
	char *symbol_name_table = (char *)header + section[symtab->sh_link].sh_offset;

	for (j = 1; j < symtab->sh_size / sizeof(Elf64_Sym); j++)
		print_symbol_line(&symbol[j], symbol_name_table);
	return (NULL);
}

int main(int argc, char **argv)
{
	int                fd;
	Elf64_Ehdr    *header;
	struct stat        sb;

	/* 									Open macros used								*/
	//---------------------------------------------------------------------------------//

	// O_RDONLY: open for reading only
	// S_IRUSR: read permission, owner
	// S_IWUSR: write permission, owner

	//---------------------------------------------------------------------------------//
	/* 																				  */
	
	if (argc <= 1)
		fd = open("a.out", O_RDONLY | S_IRUSR | S_IWUSR);
	else
		fd = open(argv[1], O_RDONLY | S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (perror(""), 1);

	if (fstat(fd, &sb) == -1)
		return (perror("fstat"), 1);
	
	printf("File size: %ld bytes\n", sb.st_size);

	header = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	 
	if (header == MAP_FAILED)
		return (ft_putstr_error("Error: cannot map file\n"));

	if (check_elf(header) == -1)
		return (ft_putstr_error("Error: not an ELF file\n"));

	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		print_content_32((Elf32_Ehdr *)header);
	else if (header->e_ident[EI_CLASS] == ELFCLASS64)
		print_content_64(header);

	if (munmap(header, sb.st_size) == -1)
		return (ft_putstr_error("Error: cannot unmap file\n"));
	close(fd);
}