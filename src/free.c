/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:48 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:19:50 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include "page.h"

t_meta_data   *traverse_page(t_page *page, void *ptr)
{
    t_meta_data *md_iter;

    md_iter = page->meta_data_head;
    while (md_iter)
    {
        if ((void*)md_iter + METADATAOFFSET == ptr)
            return (md_iter);
        if (md_iter->next)
            md_iter = md_iter->next;
        else
            break ;
    }
    return (__DARWIN_NULL);
}

t_ctuple      find_pointer(void *ptr)
{
    int i;
    t_meta_data *ptrs_meta_data;
    t_page      *page_iter;

    i = 0;
    while (i < 4) // Num of heads
    {
        page_iter = g_pd.page_heads[i];
        while (page_iter)
        {
            ptrs_meta_data = traverse_page(page_iter, ptr);
            if (ptrs_meta_data != __DARWIN_NULL)
                return ((t_ctuple){g_pd.page_heads[i], ptrs_meta_data});
            if (page_iter->next)
                page_iter = page_iter->next;
            else
                break ;
        }
        ++i;
    }
    return ((t_ctuple){__DARWIN_NULL, __DARWIN_NULL});
}

void    free_page(t_page *page)
{
    int i;
    t_page *prev_page;
    t_page *next_page;

    i = 0;
    prev_page = page->prev;
    next_page = page->next;
    if (prev_page)
    {
        prev_page->next = next_page;
    }
    else
    {
        // Look for main pointer and substitute it
        while (i < 4)
        {
            if (g_pd.page_heads[i] == page)
            {
                g_pd.page_heads[i] = next_page;
            }
            ++i;
        }
    }
    if (next_page)
    {
        next_page->prev = prev_page;
    }
    munmap(page, page->origin_size + sizeof(t_page));
}

void    free_block_in_page(t_page *page, t_meta_data *md)
{
    t_meta_data *prev_md;
    t_meta_data *next_md;
    
    prev_md = md->prev;
    next_md = md->next;
    if (prev_md)
    {
        prev_md->next = next_md;
    }
    else
    {
        // next_md – can be null here
        page->meta_data_head = next_md;
    }
    if (next_md)
    {
        next_md->prev = prev_md;
    }
    page->space_left += md->alloc_space;
}

void    free(void *ptr)
{
    t_ctuple search_result;
    
    pthread_mutex_lock(&g_malloc_mutex);
    if (ptr == __DARWIN_NULL)
    {
        pthread_mutex_lock(&g_malloc_mutex);
        return ;
    }
    search_result = find_pointer(ptr);
    if (search_result.page && search_result.md)
    {
        free_block_in_page(search_result.page, search_result.md);
        if (search_result.page->origin_size == search_result.page->space_left)
        {
            free_page(search_result.page);
        }
    }
    pthread_mutex_lock(&g_malloc_mutex);
}
