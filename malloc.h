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

/*
 ** Define
 */
# define GETSIZE(page, optional_size) \
((page) == small_type ? small_page_size : \
(page) == medium_type ? medium_page_size : \
(page) == normal_type ? normal_page_size : \
optional_size)

# define GETLABEL(type) ((type) == small_type ?  "Small" : \
(type) == medium_type ? "Medium" : \
(type) == normal_type ? "Normal" : \
"Unique")

# define ALIGNPAGESIZE(x) (((((x) - 1) >> 12) << 12) + 4096)
# define ALIGN4(x)        (((((x) - 1) >> 2) << 2) + 4)
# define ALIGNMETA(x)     (ALIGN4(x + sizeof(t_meta_data)))
# define METADATASIZEOF   sizeof(t_meta_data)
# define METADATAOFFSET   METADATASIZEOF
# define PAGEDATASIZEOF   sizeof(t_page)
# define PAGEDATAOFFSET   PAGEDATASIZEOF
# define PROT_FLAGS       (PROT_EXEC | PROT_READ | PROT_WRITE)
# define MAP_FLAGS        (MAP_ANONYMOUS | MAP_PRIVATE)

void            *malloc(size_t size);
void            *realloc(void *ptr, size_t size);
void            free(void *ptr);
void            show_alloc_mem(void);

typedef struct s_page       t_page;
typedef struct s_meta_data  t_meta_data;

typedef enum    e_page_type
{
    small_type,
    medium_type,
    normal_type,
    unique_type
}               t_page_type;

typedef struct  s_meta_data
{
    size_t      alloc_space;
    t_meta_data *next;
    t_meta_data *prev;
}               t_meta_data;

typedef enum    e_page_size
{
    small_page_size = 4096,
    medium_page_size = 4096 << 1,
    normal_page_size = 4096 << 2
}               t_page_size;

typedef enum    e_alloc_treshold
{
    small_alloc = 1024 - METADATASIZEOF,
    medium_alloc = ((small_alloc + METADATASIZEOF) << 1) - METADATASIZEOF,
    normal_alloc = ((small_alloc + METADATASIZEOF) << 2) - METADATASIZEOF
}               t_alloc_treshold;

typedef struct  s_page
{
    size_t      origin_size;
    size_t      space_left;
    t_page      *next;
    t_page      *prev;
    t_meta_data *meta_data_head;
    void        *raw_data;
}               t_page;

typedef struct  s_ctuple
{
    t_page      *page;
    t_meta_data *md;
}               t_ctuple;

typedef struct  s_page_dispatcher
{
    t_page      *page_heads[4];
    void        *malloc_ptr;
}               t_page_dispatcher;

extern t_page_dispatcher g_pd;
extern pthread_mutex_t   g_malloc_mutex;

#endif
