/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:57:08 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/15 04:06:41 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/nm.h"

static int is_underscore(char c) {
    return c == '_';
}

static int ft_strcmp_ignore_underscores(const char *s1, const char *s2) {
    if (!s1 || !s2) {
        return 0;
    }
    while (is_underscore(*s1) && *(s1 + 1) != '\0') {
        s1++;
    }
    while (is_underscore(*s2) && *(s2 + 1) != '\0') {
        s2++;
    }
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    if (is_underscore(*s1)) {
        return 1;
    }
    if (is_underscore(*s2)) {
        return -1;
    }
    return 0;
}

t_content_32 **sort_t_content_32(t_content_32 **content) {
    int i, j;
    t_content_32 *temp;

    i = 0;
    while (content[i]) {
        j = i + 1;
        while (content[j]) {
            int cmp_result = ft_strcmp_ignore_underscores(content[i]->section, content[j]->section);
            if (cmp_result > 0) {
                temp = content[i];
                content[i] = content[j];
                content[j] = temp;
            }
            j++;
        }
        i++;
    }
    return content;
}

t_content_64 **sort_t_content_64(t_content_64 **content) {
    int i, j;
    t_content_64 *temp;

    i = 0;
    while (content[i]) {
	    printf("rip\n");
        j = i + 1;
        while (content[j]) {
	        printf("rip\n");
            int cmp_result = ft_strcmp_ignore_underscores(content[i]->section, content[j]->section);
            if (cmp_result > 0) {
                temp = content[i];
                content[i] = content[j];
                content[j] = temp;
            }
            j++;
        }
        i++;
    }
    return content;
}