/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:35:14 by emaugale          #+#    #+#             */
/*   Updated: 2023/02/13 22:20:06 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <elf.h>

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

int    ft_putstr_error(char *str)
{
    write(2, str, ft_strlen(str));
    return (1);
}

int check_elf(Elf64_Ehdr *header)
{
    if (header->e_ident[EI_MAG0] != ELFMAG0 ||
        header->e_ident[EI_MAG1] != ELFMAG1 ||
        header->e_ident[EI_MAG2] != ELFMAG2 ||
        header->e_ident[EI_MAG3] != ELFMAG3)
        return (-1);
    return (0);
}

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
    i = 0;
    while (i < header->e_shnum)
    {
        content[i] = strtab_content + section[i].sh_name;
        i++;
    }
    return (content);
}

int main(int argc, char **argv)
{
    char    *line;
    int     fd;
    int     ret;
    Elf64_Ehdr *header;
    char **content;

    if (argc != 2)
        return (ft_putstr_error("Usage: ./a.out [file_name]"));
    fd = open(argv[1], O_RDONLY | S_IRUSR | S_IWUSR);
    if (fd == -1)
        return (ft_putstr_error("Error: cannot read file\n"));

   struct stat sb;
    if (fstat(fd, &sb) == -1) {
         perror("fstat");
         exit(EXIT_FAILURE);
    }
    printf("File size: %lld bytes\n", sb.st_size);

    header = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
     
    if (header == MAP_FAILED)
        return (ft_putstr_error("Error: cannot map file\n"));


    if (check_elf(header) == -1)
        return (ft_putstr_error("Error: not an ELF file\n"));

    if (header->e_ident[EI_CLASS] == ELFCLASS32)
        content = parse_elf32(header);
    else if (header->e_ident[EI_CLASS] == ELFCLASS64)
        printf("Class: ELF64\n");

    



    if (munmap(header, sb.st_size) == -1)
        return (ft_putstr_error("Error: cannot unmap file\n"));
    close(fd);
}