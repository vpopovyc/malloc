/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:20:39 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:20:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include "page.h"

void show_page_content(t_page *page, t_page_type page_type)
{
    t_meta_data *md_iter;

    printf("%s zone: %#.5x\n", GETLABEL(page_type), (int)page);
    if (page && (md_iter = page->meta_data_head))
    {
        while (md_iter)
        {
            printf("\t%#.5x – %#.5x : %lu\n",
                                (int)md_iter,
                                (int)((void*)md_iter + METADATAOFFSET),
                                (int)md_iter->alloc_space - METADATASIZEOF);
            if (md_iter->next)
                md_iter = md_iter->next;
            else
                break ;
        }
    }
    else
    {
        printf("\tno allocations\n");
    }
}

void show_alloc_mem(void)
{
    int     page_type;
    t_page  *page_iter;

    pthread_mutex_lock(&g_malloc_mutex);
    page_type = small_type;
    while (page_type < 4)
    {
        page_iter = g_pd.page_heads[page_type];
        while (page_iter)
        {
            show_page_content(page_iter, page_type);
            if (page_iter->next)
                page_iter = page_iter->next;
            else
                break ;
        }
        page_type++;
    }
    pthread_mutex_unlock(&g_malloc_mutex);
}
