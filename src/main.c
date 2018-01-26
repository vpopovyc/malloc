/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:22 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:19:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../malloc.h"
#include <sys/resource.h>
#include <sys/mman.h>

int main(void)
{
    {
        void *ptr;
        
        ptr = malloc(67);
        (void)malloc(4096 << 1);
//        free(ptr);
        ptr = malloc(4096 << 2);
        show_alloc_mem();
    }
    (void)malloc(4);
    void *ptr;
    ptr = malloc(8);
    (void)malloc(4);
    free(ptr);
    ptr = malloc(4);
    ptr = realloc(ptr, 8);
    (void)malloc(4);

    return (0);
}
