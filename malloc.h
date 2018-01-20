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

void            *malloc(size_t size);

typedef struct s_page       t_page;
typedef struct s_meta_data  t_meta_data;

typedef enum    e_page_type
{
    small_type,
    medium_type,
    normal_type,
    unique_type
}               t_page_type;

typedef enum    e_page_size
{
    small_page_size = 1024,
    medium_page_size = 2048,
    normal_page_size = 4096
}               t_page_size;

typedef struct  s_meta_data
{
    size_t      alloc_space;
    t_meta_data *next;
    uint8_t     is_free;
}               t_meta_data ;

typedef struct  s_page
{
    size_t      origin_size;
    size_t      space_left;
    t_page      *next;
    t_page      *prev;
    t_meta_data *meta_data_head;
    void        *raw_data;
}               t_page;

typedef struct  s_page_dispatcher
{
    t_page      *page_heads[4];
    void        *malloc_ptr;
}               t_page_dispatcher;

extern t_page_dispatcher g_pd;

/*
** Define
*/

# define ALIGN8(x) (((((x) - 1) >> 5) << 5) + 32)
# define ALIGNMETA(x) (ALIGN8(x + sizeof(t_meta_data)))

# define METADATASIZEOF   sizeof(t_meta_data)
# define METADATAOFFSET   METADATASIZEOF
# define PAGEDATASIZEOF   sizeof(t_page)
# define PAGEDATAOFFSET   PAGEDATASIZEOF
# define PROT_FLAGS       (PROT_EXEC | PROT_READ | PROT_WRITE)
# define MAP_FLAGS        (MAP_ANONYMOUS | MAP_PRIVATE)

#endif
