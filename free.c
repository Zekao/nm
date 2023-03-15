/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:31:08 by emaugale          #+#    #+#             */
/*   Updated: 2023/03/15 18:53:51 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/nm.h"
void    free_struct(t_content_32 **content)
{
    int i;

    i = -1;
    while (content[++i])
        free(content[i]);
    free(content);
}

void    free_struct64(t_content_64 **content)
{
    int i;

    i = -1;
    while (content[++i])
        free(content[i]);
    free(content);
}