/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:38 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:19:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "page.h"

void	insert_new_block_in_used_page(t_page *page,
										t_meta_data *md, size_t size)
{
	t_meta_data	new_md;
	uint8_t		*offset_ptr;

	memset(&new_md, 0, sizeof(t_meta_data));
	new_md.alloc_space = size;
	new_md.prev = md;
	new_md.next = md->next;
	offset_ptr = (uint8_t*)md + md->alloc_space;
	memmove(offset_ptr, &new_md, sizeof(t_meta_data));
	if (md->next)
		md->next->prev = (t_meta_data*)offset_ptr;
	md->next = (t_meta_data*)offset_ptr;
	page->space_left -= new_md.alloc_space;
	g_pd.malloc_ptr = offset_ptr + METADATAOFFSET;
}

void	insert_new_block_in_fresh_page(t_page *page, size_t size)
{
	t_meta_data	md;
	uint8_t		*offset_ptr;

	memset(&md, 0, sizeof(md));
	md.alloc_space = size;
	memmove(page->raw_data, &md, sizeof(t_meta_data));
	page->meta_data_head = (t_meta_data*)(page->raw_data);
	offset_ptr = (uint8_t*)page->meta_data_head;
	page->space_left -= md.alloc_space;
	g_pd.malloc_ptr = offset_ptr + METADATAOFFSET;
}

_Bool	try_insert_at_begin(t_page *page, size_t size)
{
	t_meta_data	*new_md;

	new_md = page->raw_data;
	new_md->alloc_space = 0;
	new_md->prev = __DARWIN_NULL;
	new_md->next = page->meta_data_head;
	if (check_if_new_block_can_fit(page, new_md, size))
	{
		new_md->alloc_space = size;
		page->meta_data_head->prev = new_md;
		page->meta_data_head = new_md;
		g_pd.malloc_ptr = (void*)new_md + METADATAOFFSET;
		return (1);
	}
	return (0);
}

t_page	*new_page(size_t size, t_page *prev_page)
{
	void	*raw_mem;
	t_page	new_page;
	size_t	page_size;

	page_size = ALIGNPAGESIZE(size);
	raw_mem = mmap(0, page_size, PROT_FLAGS, MAP_FLAGS, -1, 0);
	if (raw_mem == MAP_FAILED)
		return (g_pd.malloc_ptr = __DARWIN_NULL);
	memset(&new_page, 0, sizeof(t_page));
	new_page.origin_size = page_size - sizeof(t_page);
	new_page.space_left = page_size - sizeof(t_page);
	new_page.raw_data = raw_mem + sizeof(t_page);
	new_page.prev = prev_page;
	memmove(raw_mem, &new_page, sizeof(t_page));
	if (prev_page)
		prev_page->next = (t_page*)raw_mem;
	return (raw_mem);
}
