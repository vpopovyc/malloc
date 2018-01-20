/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:38 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:19:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

t_page   *new_page(t_page_type page_type)
{
    void    *raw_mem;
    size_t  page_size;
    t_page  new_page;

    if (page_type == small_type)
        page_size = small_page_size;
    else if (page_type == medium_type)
        page_size = medium_page_size;
    else
        page_size = normal_page_size;
    raw_mem = mmap(0, page_size + sizeof(t_page), PROT_FLAGS, MAP_FLAGS, -1, 0);
    memset(&new_page, 0, sizeof(t_page));
    new_page.origin_size = page_size;
    new_page.space_left = page_size;
    new_page.raw_data = raw_mem + sizeof(t_page);
    memcpy(raw_mem, &new_page, sizeof(t_page));
    return (raw_mem);
}

_Bool    check_if_new_block_can_fit(t_page *page, t_meta_data *md, size_t size)
{
    ptrdiff_t   prev_block;
    ptrdiff_t   next_block;
    ptrdiff_t   space_between;
    uint8_t     *offset_ptr;

    offset_ptr = (uint8_t*)md + md->alloc_space;
    prev_block = (ptrdiff_t)offset_ptr;
    next_block = (ptrdiff_t)md->next;
    if (!next_block)
        next_block = (ptrdiff_t)page->raw_data + page->origin_size;
    space_between = next_block - prev_block;
    if (space_between >= size)
        return (1);
    else
        return (0);
}

void    insert_new_block_in_used_page(t_page *page, t_meta_data *md, size_t size)
{
    t_meta_data new_md;
    uint8_t     *offset_ptr;
    
    memset(&new_md, 0, sizeof(t_meta_data));
    new_md.alloc_space = size;
    offset_ptr = (uint8_t*)md + md->alloc_space;
    memcpy(offset_ptr, &new_md, sizeof(t_meta_data));
    md->next = (t_meta_data*)offset_ptr;
    page->space_left -= new_md.alloc_space;
    g_pd.malloc_ptr = offset_ptr + METADATAOFFSET;
}

void    insert_new_block_in_fresh_page(t_page *page, size_t size)
{
    t_meta_data md;
    uint8_t     *offset_ptr;

    memset(&md, 0, sizeof(md));
    md.alloc_space = size;
    memcpy(page->raw_data, &md, sizeof(t_meta_data));
    page->meta_data_head = (t_meta_data*)(page->raw_data);
    offset_ptr = (uint8_t*)page->meta_data_head;
    page->space_left -= md.alloc_space;
    g_pd.malloc_ptr = offset_ptr + METADATAOFFSET;
}

void    create_new_block(t_page *page, size_t size)
{
    t_meta_data *meta_data_iter;

    meta_data_iter = page->meta_data_head;
    if (!meta_data_iter)
    {
        insert_new_block_in_fresh_page(page, size);
    }
    else
    {
        while (meta_data_iter)
        {
            if (check_if_new_block_can_fit(page, meta_data_iter, size))
            {
                insert_new_block_in_used_page(page, meta_data_iter, size);
                break ;
            }
            else
            {
                if (meta_data_iter->next)
                    meta_data_iter = meta_data_iter->next;
                else
                    break ;
            }
        }
    }
}

void    find_best_fit(t_page_type page_type, size_t size)
{
    t_page  *page_iter;

    page_iter = g_pd.page_heads[page_type];
    while (page_iter)
    {
        if (page_iter->space_left > size)
        {
            create_new_block(page_iter, size);
        }
        if (page_iter->next)
            page_iter = page_iter->next;
        else
            break ;
    }
    // Create new page if not found
}

void    process_page(t_page_type page_type, size_t size)
{
    if (!g_pd.page_heads[page_type])
    {
        g_pd.page_heads[page_type] = new_page(page_type);
        if (!g_pd.page_heads[page_type])
        {
            // Bad alloc
            return ;
        }
    }
    find_best_fit(page_type, size);
}

void    *malloc(size_t size)
{
    size = ALIGNMETA(size);
    if (size == 0)
    {
        return (__DARWIN_NULL);
    }
    if (size < small_page_size)
    {
        process_page(small_type, size);
    }
    else if (size < medium_page_size)
    {
        process_page(medium_type, size);
    }
    else if (size < normal_page_size)
    {
        process_page(normal_type, size);
    }
    else
    {
        // unique allocations here
    }
    return (g_pd.malloc_ptr);
}
