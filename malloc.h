 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:08:19 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 16:08:20 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_H
# define __MALLOC_H

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include <pthread.h>

void					*malloc(size_t size) __attribute__ ((visibility ("default")));
void					*realloc(void *ptr, size_t size) __attribute__ ((visibility ("default")));
void					free(void *ptr) __attribute__ ((visibility ("default")));
void					show_alloc_mem(void) __attribute__ ((visibility ("default")));

typedef struct			s_meta_data
{
	size_t				alloc_space;
	struct s_meta_data	*next;
	struct s_meta_data	*prev;
}						t_meta_data;

typedef enum			e_page_type
{
	small_type,
	medium_type,
	normal_type,
	unique_type
}						t_page_type;

typedef enum			e_page_size
{
	small_page_size = 4096 << 2,
	medium_page_size = 4096 << 8,
	normal_page_size = 4096 << 12
}						t_page_size;

typedef struct			s_page
{
	size_t				origin_size;
	size_t				space_left;
	struct s_page		*next;
	struct s_page		*prev;
	struct s_meta_data	*meta_data_head;
	void				*raw_data;
}						t_page;

typedef struct			s_ctuple
{
	struct s_page		*page;
	struct s_meta_data	*md;
}						t_ctuple;

# define ALIGNPAGESIZE(x)	(((((x) - 1) >> 12) << 12) + 4096)
# define ALIGN4(x)	(((((x) - 1) >> 2) << 2) + 4)
# define ALIGNMETA(x)	(ALIGN4(x + sizeof(struct s_meta_data)))
# define METADATASIZEOF	sizeof(struct s_meta_data)
# define METADATAOFFSET	METADATASIZEOF
# define PAGEDATASIZEOF	sizeof(struct s_page)
# define PAGEDATAOFFSET	PAGEDATASIZEOF
# define PROT_FLAGS	(PROT_EXEC | PROT_READ | PROT_WRITE)
# define MAP_FLAGS	(MAP_ANONYMOUS | MAP_PRIVATE)

typedef enum			e_alloc_treshold
{
	small_alloc = small_page_size / 100 - METADATASIZEOF,
	medium_alloc = medium_page_size / 100 - METADATASIZEOF,
	normal_alloc = normal_page_size / 100 - METADATASIZEOF
}						t_alloc_treshold;

typedef struct			s_page_dispatcher
{
	t_page				*page_heads[4];
	void				*malloc_ptr;
}						t_page_dispatcher;

extern t_page_dispatcher g_pd;
extern pthread_mutex_t g_malloc_mutex;

#endif
