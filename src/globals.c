/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:34:21 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 16:34:22 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"

t_page_dispatcher   g_pd =
{
    .page_heads = {__DARWIN_NULL, __DARWIN_NULL, __DARWIN_NULL, __DARWIN_NULL},
    .malloc_ptr = __DARWIN_NULL
};

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
