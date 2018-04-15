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

#include <malloc.h>
#include <page.h>
#include <stddef.h>
#include <libft.h>

_Bool	check_if_new_block_can_fit(t_page *page, t_meta_data *md, size_t size)
{
	ptrdiff_t	prev_block;
	ptrdiff_t	next_block;
	ptrdiff_t	space_between;

	prev_block = (ptrdiff_t)md + md->alloc_space;
	next_block = (ptrdiff_t)md->next;
	if (!next_block)
		next_block = (ptrdiff_t)page->raw_data + page->origin_size;
	space_between = next_block - prev_block;
	if ((size_t)space_between >= size)
		return (1);
	else
		return (0);
}

void	create_new_block(t_page *page, size_t size)
{
	t_meta_data	*md_iter;

	md_iter = page->meta_data_head;
	if (!md_iter)
		insert_new_block_in_fresh_page(page, size);
	else
	{
		if (md_iter != page->raw_data)
		{
			if (try_insert_at_begin(page, size))
				return ;
		}
		while (md_iter)
		{
			if (check_if_new_block_can_fit(page, md_iter, size))
				return (insert_new_block_in_used_page(page, md_iter, size));
			else
			{
				if (md_iter->next)
					md_iter = md_iter->next;
				else
					break ;
			}
		}
	}
}

void	find_best_fit(t_page_type page_type, size_t size)
{
	t_page	*page_iter;

	page_iter = g_pd.page_heads[page_type];
	while (page_iter)
	{
		if (page_iter->space_left > size)
		{
			create_new_block(page_iter, size);
			break ;
		}
		if (page_iter->next)
			page_iter = page_iter->next;
		else
		{
			page_iter->next = new_page(size, page_iter);
			page_iter = page_iter->next;
		}
	}
}

void	process_page(t_page_type page_type, size_t size)
{
	if (!g_pd.page_heads[page_type])
	{
		g_pd.page_heads[page_type] = new_page(get_size(page_type, size),
												__DARWIN_NULL);
		if (!g_pd.page_heads[page_type])
			return ;
	}
	find_best_fit(page_type, size);
}

void	*malloc(size_t size)
{
	void	*thread_local_ptr;

	pthread_mutex_lock(&g_malloc_mutex);
	if (size == 0)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		return (__DARWIN_NULL);
	}
	if (size < (size_t)-32)
		size = ALIGNMETA(size);
	if (size < small_alloc)
		process_page(small_type, size);
	else if (size < medium_alloc)
		process_page(medium_type, size);
	else if (size < normal_alloc)
		process_page(normal_type, size);
	else
		process_page(unique_type, size);
	thread_local_ptr = g_pd.malloc_ptr;
	pthread_mutex_unlock(&g_malloc_mutex);
	return (thread_local_ptr);
}
