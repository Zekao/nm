/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:57:08 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/15 19:44:45 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm_bonus.h"

static int is_underscore(char c) {
    return c == '_';
}

static int ft_strcmp_ignore_underscores(const char *s1, const char *s2) {
    if (!s1 || !s2) {
        return 0;
    }
    const char *p1 = s1;
    const char *p2 = s2;
    while (*p1 && *p2) {
        if (is_underscore(*p1)) {
            p1++;
            continue;
        }
        if (is_underscore(*p2)) {
            p2++;
            continue;
        }
        char c1 = (*p1 >= 'A' && *p1 <= 'Z') ? *p1 + 32 : *p1;
        char c2 = (*p2 >= 'A' && *p2 <= 'Z') ? *p2 + 32 : *p2;
        if (c1 != c2) {
            return c1 - c2;
        }
        p1++;
        p2++;
    }
    if (is_underscore(*p1)) {
        return 1;
    }
    if (is_underscore(*p2)) {
        return -1;
    }
    return (*p1 - *p2);
}


#include <string.h>

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
            } else if (cmp_result == 0 && ft_strcmp(content[i]->section, content[j]->section) > 0) {
                // If the sections are equal ignoring underscores, compare them directly
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
        j = i + 1;
        while (content[j]) {
            int cmp_result = ft_strcmp_ignore_underscores(content[i]->section, content[j]->section);
            if (cmp_result > 0) {
                temp = content[i];
                content[i] = content[j];
                content[j] = temp;
            } else if (cmp_result == 0 && ft_strcmp(content[i]->section, content[j]->section) > 0) {
                // If the sections are equal ignoring underscores, compare them directly
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