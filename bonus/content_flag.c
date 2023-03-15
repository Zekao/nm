/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:54:13 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/15 19:44:45 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_bonus.h"

static bool is_data_section(char const *section)
{
    return str_starts_with(section, ".dynamic") || str_starts_with(section, ".data") || str_starts_with(section, ".init_array") || str_starts_with(section, ".fini_array") || str_starts_with(section, ".got");
}

static bool is_readonly_section(char const *section)
{
    return str_starts_with(section, ".rodata") || str_starts_with(section, ".note") || str_starts_with(section, ".eh_frame") || str_starts_with(section, ".eh_frame_hdr");
}

static bool is_text_section(char const *section)
{
    return str_starts_with(section, ".text") || str_starts_with(section, ".fini") || str_starts_with(section, ".init");
}

char	content_flag32(Elf32_Sym *symbol, char *section)
{
	if (symbol->st_shndx == SHN_ABS)
    {
        if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
            return ('a');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('A');
    }
    else if (section && str_starts_with(section, ".bss"))
    {
        if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('b');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('B');
    }
    else if (symbol->st_shndx == SHN_COMMON)
    {
        if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('c');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('C');
    }
    else if (section && is_data_section(section))
    {
        if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('d');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('D');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK)
			return ('W');
    }
    else if (section && is_readonly_section(section))
    {
        if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('r');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('R');
    }
    else if (section && is_text_section(section))
    {
        if (ELF32_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('t');
        else if (ELF32_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('T');
    }
    else if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK && ELF32_ST_TYPE(symbol->st_info) == STT_OBJECT)
    {
		return ('v');
    }
    else if (ELF32_ST_BIND(symbol->st_info) == STB_WEAK)
    {
		return ('w');
    }
    else if (symbol->st_shndx == SHN_UNDEF)
    {
		return ('U');
    }
	return ('?');
}

char	content_flag(Elf64_Sym *symbol, char *section)
{
	if (symbol->st_shndx == SHN_ABS)
    {
        if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
            return ('a');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('A');
    }
    else if (section && str_starts_with(section, ".bss"))
    {
        if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('b');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('B');
    }
    else if (symbol->st_shndx == SHN_COMMON)
    {
        if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('c');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('C');
    }
    else if (section && is_data_section(section))
    {
        if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('d');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('D');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK)
			return ('W');
    }
    else if (section && is_readonly_section(section))
    {
        if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('r');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('R');
    }
    else if (section && is_text_section(section))
    {
        if (ELF64_ST_BIND(symbol->st_info) == STB_LOCAL)
			return ('t');
        else if (ELF64_ST_BIND(symbol->st_info) == STB_GLOBAL)
			return ('T');
    }
    else if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK && ELF64_ST_TYPE(symbol->st_info) == STT_OBJECT)
    {
		return ('v');
    }
    else if (ELF64_ST_BIND(symbol->st_info) == STB_WEAK)
    {
		return ('w');
    }
    else if (symbol->st_shndx == SHN_UNDEF)
    {
		return ('U');
    }
	return ('?');
}


