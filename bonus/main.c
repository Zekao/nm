/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:35:14 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/17 14:33:05 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_bonus.h"

static void print_32(t_content_32 **content, char *bonus_flag)
{
	if (ft_strcmp(bonus_flag, "-p") != 0)
		content = sort_t_content_32(content);
	if (ft_strcmp(bonus_flag, "-r") == 0)
		content = reverse_t_content_32(content);
	for (size_t i = 0; content[i]; i++)
	{
		if ((content[i]->type != 'a' || !ft_strcmp(bonus_flag, "-a")) && content[i]->type != '?' && ft_strlen(content[i]->section) > 0) {
			if ((content[i]->symbol.st_value >= 1 && content[i]->type != 'U') || (content[i]->symbol.st_shndx != SHN_UNDEF)) {
				for (size_t j = 0; j + symbol_len32(content[i]->symbol.st_value) < 8; j++)
					write(1, "0", 1);
				if (symbol_len32(content[i]->symbol.st_value) > 1)
					putnbr_hex(content[i]->symbol.st_value);
				write(1, " ", 1);
			}
			else {
				write(1, "         ", 9);
			}
			write(1, &content[i]->type, 1);
			write(1, " ", 1);
			ft_putstr(content[i]->section);
			write(1, "\n", 1);
		}
	}
}

static void print_64(t_content_64 **content, char *bonus_flag)
{
	if (ft_strcmp(bonus_flag, "-p") != 0)
		content = sort_t_content_64(content);
	if (ft_strcmp(bonus_flag, "-r") == 0)
		content = reverse_t_content_64(content);
	for (size_t i = 0; content[i]; i++)
	{
		if ((content[i]->type != 'a' || !ft_strcmp(bonus_flag, "-a")) && content[i]->type != '?' && ft_strlen(content[i]->section) > 0) {
			if ((content[i]->symbol.st_value >= 1 && content[i]->type != 'U') || (content[i]->symbol.st_shndx != SHN_UNDEF)) {
				for (size_t j = 0; j + symbol_len64(content[i]->symbol.st_value) < 16; j++)
					write(1, "0", 1);
				if (symbol_len64(content[i]->symbol.st_value) > 1)
					putnbr_hex(content[i]->symbol.st_value);
				write(1, " ", 1);
			}
			else {
				write(1, "                 ", 17);
			}
			write(1, &content[i]->type, 1);
			write(1, " ", 1);
			ft_putstr(content[i]->section);
			write(1, "\n", 1);
		}
	}
}

char **parse_elf32(Elf32_Ehdr *header, char *bonus_flag)
{
	/*
		--- ELF32 ---

		e_shoff: offset to section header table
		e_shnum: number of section headers
		e_shstrndx: index of section name string table
		sh_name: offset to section name
		sh_offset: offset to section data
		
	*/
	Elf32_Shdr 		*section;
	Elf32_Shdr 		*symtab;
	Elf32_Sym 		*symbols;
	char 			*strtab_content;
	char 			*section_name;
	size_t 			j;
	size_t			i;
	t_content_32		**content;



	section = (void *)header + header->e_shoff;
	strtab_content = (void *)header + section[header->e_shstrndx].sh_offset;
	for (i = 0; i < header->e_shnum; i++) {
		if (section[i].sh_type == SHT_SYMTAB)
			symtab = &section[i];
	}

	if (!symtab || !strtab_content)
		return (NULL);

	symbols = (void *)header + symtab->sh_offset;
	char *symbol_name_table = (char *)header + section[symtab->sh_link].sh_offset;

	content = ft_calloc(sizeof(t_content_32 *) , (symtab->sh_size / sizeof(Elf32_Sym)));
	if (!content)
		return (NULL);
	for (j = 1; j < symtab->sh_size / sizeof(Elf32_Sym); j++)
	{
		if (symbols[j].st_shndx != 0 && symbols[j].st_shndx < header->e_shnum)
		{
			section_name = strtab_content + section[symbols[j].st_shndx].sh_name;
		}
		else
			section_name = NULL;
		content[j - 1] = malloc(sizeof(t_content_32));
		if (!content[j - 1])
			return (free_struct(content), NULL);
		content[j - 1]->type = content_flag32(&symbols[j], section_name);
		if (ft_strcmp(bonus_flag, "-g") == 0)
		{
			if (content[j - 1]->type >= 'a' && content[j - 1]->type <= 'z' && content[j - 1]->type != 'w')
				content[j - 1]->type = 'a';
		}
		content[j - 1]->symbol = symbols[j];
		content[j - 1]->section = symbol_name_table + symbols[j].st_name;
	}
	print_32(content, bonus_flag);
	free_struct(content);
	return (NULL);
}

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

char **parse_elf64(Elf64_Ehdr *header, char *bonus_flag)
{

	Elf64_Shdr 		*section;
	Elf64_Shdr 		*symtab;
	Elf64_Sym 		*symbols;
	char 			*strtab_content;
	size_t 			j;
	size_t			i;
	char 			*section_name;
	t_content_64	**content;



	section = (void *)header + header->e_shoff;
	strtab_content = (void *)header + section[header->e_shstrndx].sh_offset;
	for (i = 0; i < header->e_shnum; i++) {
		if (section[i].sh_type == SHT_SYMTAB)
			symtab = &section[i];
	}

	if (!symtab || !strtab_content)
		return (NULL);

	symbols = (void *)header + symtab->sh_offset;
	char *symbol_name_table = (char *)header + section[symtab->sh_link].sh_offset;

	content = ft_calloc(sizeof(t_content_64 *) , (symtab->sh_size / sizeof(Elf64_Sym)));
	if (!content)
		return (NULL);
	for (j = 1; j < symtab->sh_size / sizeof(Elf64_Sym); j++)
	{
		if (symbols[j].st_shndx != 0 && symbols[j].st_shndx < header->e_shnum)
		{
			section_name = strtab_content + section[symbols[j].st_shndx].sh_name;
		}
		else
			section_name = NULL;
		content[j - 1] = malloc(sizeof(t_content_64));
		if (!content[j - 1])
			return (free_struct64(content), NULL);
		content[j - 1]->type = content_flag(&symbols[j], section_name);
		if (ft_strcmp(bonus_flag, "-g") == 0)
		{
			if (content[j - 1]->type >= 'a' && content[j - 1]->type <= 'z' && content[j - 1]->type != 'w')
				content[j - 1]->type = 'a';
		}
		content[j - 1]->symbol = symbols[j];
		content[j - 1]->section = symbol_name_table + symbols[j].st_name;
	}
	print_64(content, bonus_flag);
	return (free_struct64(content), NULL);
}

int main(int argc, char **argv)
{
	int                fd;
	Elf64_Ehdr    *header;
	struct stat        sb;
	char			*option;
	/* 									Open macros used								*/
	//---------------------------------------------------------------------------------//

	// O_RDONLY: open for reading only
	// S_IRUSR: read permission, owner
	// S_IWUSR: write permission, owner

	//---------------------------------------------------------------------------------//
	/* 																				  */
	
	if (argc > 3 || argc == 1)
		return (ft_putstr_error("Error: you must provide 2 or 3 parameters\n"));
	if (argc == 2) {
		fd = open("a.out", O_RDONLY | S_IRUSR | S_IWUSR);
		option = ft_strdup(argv[1]);
		if (!option)
			return (close(fd), ft_putstr_error("Error: cannot allocate memory\n"));
	}
	else {
		fd = open(argv[2], O_RDONLY | S_IRUSR | S_IWUSR);
		option = ft_strdup(argv[1]);
		if (!option)
			return (close(fd), ft_putstr_error("Error: cannot allocate memory\n"));

	}
	if (ft_strcmp(option, "-g") != 0 && ft_strcmp(option, "-s") != 0 && ft_strcmp(option, "-u") != 0 && ft_strcmp(option, "-p") != 0 && ft_strcmp(option, "-r") != 0 && ft_strcmp(option, "-a") != 0)
		return (free(option), close(fd), ft_putstr_error("Error: invalid option\n"));
	if (fd == -1)
		return (free(option), ft_putstr_error("Error: cannot open file\n"));

	if (fstat(fd, &sb) == -1)
		return (free(option), ft_putstr_error("Error: cannot stat file\n"));
	
	header = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	 
	if (header == MAP_FAILED)
		return (free(option), ft_putstr_error("Error: cannot map file\n"));

	if (check_elf(header) == -1)
		return (free(option), ft_putstr_error("Error: not an ELF file\n"));

	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		print_content_32((Elf32_Ehdr *)header, option);
	else if (header->e_ident[EI_CLASS] == ELFCLASS64)
		print_content_64(header, option);

	if (munmap(header, sb.st_size) == -1)
		return (free(option), ft_putstr_error("Error: cannot unmap file\n"));
	close(fd);
	free(option);
}