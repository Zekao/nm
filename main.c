/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:35:14 by emaugale          #+#    #+#             */
/*   Updated: 2023/02/14 01:39:53 by emaugale         ###   ########.fr       */
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

char **parse_elf64(Elf64_Ehdr *header)
{
    
    // Elf64_Shdr *section;
    // section = (void *)header + header->e_shoff;
    // Elf64_Shdr *symtab = NULL;
    // Elf64_Shdr *strtab = NULL;
    // int i;

    // for (i = 0; i < header->e_shnum; i++) {
    //     if (section[i].sh_type == SHT_SYMTAB)
    //         symtab = &section[i];
    //     else if (section[i].sh_type == SHT_STRTAB)
    //         strtab = &section[i];
    // }

    // if (!symtab || !strtab)
    //     return (NULL);
    // Elf64_Sym *symbol;
    // char *strtab_content;
    // int j;

    // strtab_content = (void *)header + strtab->sh_offset;
    // symbol = (void *)header + symtab->sh_offset;

    // for (j = 0; j < symtab->sh_size / sizeof(Elf64_Sym); j++) {
    //     if (ELF64_ST_TYPE(symbol[j].st_info) == STT_FUNC ||
    //         ELF64_ST_TYPE(symbol[j].st_info) == STT_OBJECT)
    //         printf("%016lx %c %s\n", symbol[j].st_value,
    //             ELF64_ST_TYPE(symbol[j].st_info) == STT_FUNC ? 'T' : 'D',
    //             strtab_content + symbol[j].st_name);
    // }






    /*
        --- ELF64 ---

        e_shoff: offset to section header table
        e_shnum: number of section headers
        e_shstrndx: index of section name string table
        sh_name: offset to section name
        sh_offset: offset to section data
        
    */
    Elf64_Shdr *section;
    Elf64_Shdr *strtab;
    Elf64_Sym *symbol;
    char *strtab_content;
    char **content;
    int i;

    section = (void *)header + header->e_shoff;
    strtab = &section[header->e_shstrndx];
    strtab_content = (void *)header + strtab->sh_offset;
    content = malloc(sizeof(char *) * header->e_shnum);
    i = -1;

    symbol = (void *)header + strtab->sh_offset;
    while (++i < header->e_shnum) {
            content[i] = strtab_content + section[i].sh_name;
            printf("%016lx %c %s %s\n", symbol[i].st_value,
                ELF64_ST_TYPE(symbol[i].st_info) == STT_FUNC ? 'T' : 'D',
                strtab_content, content[i]);
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    int                fd;
    Elf64_Ehdr    *header;
    struct stat        sb;

    if (argc != 2)
        return (ft_putstr_error("Usage: ./a.out [file_name]"));
    fd = open(argv[1], O_RDONLY | S_IRUSR | S_IWUSR);
    if (fd == -1)
        return (ft_putstr_error("Error: cannot read file\n"));

    if (fstat(fd, &sb) == -1) {
         perror("fstat");
         exit(EXIT_FAILURE);
    }
    
    printf("File size: %ld bytes\n", sb.st_size);

    header = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
     
    if (header == MAP_FAILED)
        return (ft_putstr_error("Error: cannot map file\n"));

    if (check_elf(header) == -1)
        return (ft_putstr_error("Error: not an ELF file\n"));

    if (header->e_ident[EI_CLASS] == ELFCLASS32)
        print_content_32(header);
    else if (header->e_ident[EI_CLASS] == ELFCLASS64)
        print_content_64(header);

    if (munmap(header, sb.st_size) == -1)
        return (ft_putstr_error("Error: cannot unmap file\n"));
    close(fd);
}