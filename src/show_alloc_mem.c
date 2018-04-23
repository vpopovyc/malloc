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

#include <malloc.h>
#include <page.h>
#include <libft.h>

size_t				get_size(t_page_type type, size_t optional_size)
{
	size_t size;

	if (type == small_type)
		size = small_page_size;
	else if (type == medium_type)
		size = medium_page_size;
	else if (type == normal_type)
		size = normal_page_size;
	else
		size = optional_size;
	return (size);
}

static void			print_type(t_page *page, t_page_type page_type)
{
	if (page_type == small_type)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		ft_printf("Small zone: %#.5x\n", (size_t)page);
		pthread_mutex_lock(&g_malloc_mutex);
	}
	else if (page_type == medium_type)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		ft_printf("Medium zone: %#.5x\n", (size_t)page);
		pthread_mutex_lock(&g_malloc_mutex);
	}
	else if (page_type == normal_type)
	{
		pthread_mutex_unlock(&g_malloc_mutex);
		ft_printf("Normal zone: %#.5x\n", (size_t)page);
		pthread_mutex_lock(&g_malloc_mutex);
	}
}

void				show_page_content(t_page *page, t_page_type page_type)
{
	t_meta_data	*md_iter;

	if (page && (md_iter = page->meta_data_head))
	{
		print_type(page, page_type);
		while (md_iter)
		{
			pthread_mutex_unlock(&g_malloc_mutex);
			ft_printf("\t%#.5x – %#.5x : %lu\n",
								(int)md_iter,
								(int)((void*)md_iter + METADATAOFFSET),
								(int)md_iter->alloc_space - METADATASIZEOF);
			pthread_mutex_lock(&g_malloc_mutex);
			if (md_iter->next)
				md_iter = md_iter->next;
			else
				break ;
		}
	}
}

void				show_alloc_mem(void)
{
	int		page_type;
	t_page	*page_iter;

	page_type = small_type;
	pthread_mutex_lock(&g_malloc_mutex);
	while (page_type < 4)
	{
		page_iter = g_pd.page_heads[page_type];
		if (page_type == unique_type && page_iter)
		{
			pthread_mutex_unlock(&g_malloc_mutex);
			ft_printf("Unique zone: %#.5x\n", (int)page_iter);
			pthread_mutex_lock(&g_malloc_mutex);
		}
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
