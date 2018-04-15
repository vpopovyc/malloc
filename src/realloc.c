/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:20:03 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:20:06 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <page.h>
#include <stddef.h>

_Bool	check_alloc_gap(t_page *page, t_meta_data *md, size_t new_size)
{
	ptrdiff_t	prev_block;
	ptrdiff_t	next_block;
	ptrdiff_t	space_between;

	prev_block = (ptrdiff_t)md + md->alloc_space;
	next_block = (ptrdiff_t)md->next;
	if (!next_block)
		next_block = (ptrdiff_t)page->raw_data + page->origin_size;
	space_between = next_block - prev_block;
	if (md->alloc_space + space_between >= new_size)
		return (1);
	else
		return (0);
}

void	extend_allocation(t_page *page, t_meta_data *md, size_t new_size)
{
	page->space_left += md->alloc_space;
	md->alloc_space = new_size;
	page->space_left -= md->alloc_space;
	g_pd.malloc_ptr = (void*)md + METADATAOFFSET;
}

void	make_fresh_allocation(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (new_ptr)
		memmove(new_ptr, old_ptr, old_size);
	free(old_ptr);
	g_pd.malloc_ptr = new_ptr;
}

void	*realloc(void *ptr, size_t size)
{
	void		*thread_local_ptr;
	t_ctuple	search_result;

	if (ptr == __DARWIN_NULL || size == 0)
		return (__DARWIN_NULL);
	pthread_mutex_lock(&g_malloc_mutex);
	size = ALIGNMETA(size);
	search_result = find_pointer(ptr);
	if (search_result.page && search_result.md)
	{
		if (check_alloc_gap(search_result.page, search_result.md, size))
			extend_allocation(search_result.page, search_result.md, size);
		else
			make_fresh_allocation(ptr, search_result.md->alloc_space, size);
	}
	else
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (__DARWIN_NULL);
	}
	thread_local_ptr = g_pd.malloc_ptr;
	pthread_mutex_unlock(&g_malloc_mutex);
	return (thread_local_ptr);
}
