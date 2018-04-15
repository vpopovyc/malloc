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

#include "malloc.h"

int main(void)
{
    {
        void *ptr;
        
        ptr = malloc(67);
        (void)malloc(4096 << 1);
//        free(ptr);
        ptr = malloc(4096 << 2);
    }
    // (void)malloc(-1);
    void *ptr;
    ptr = malloc(-1);
    // (void)malloc(4);
    show_alloc_mem();
    free(ptr);
    show_alloc_mem();
    // ptr = malloc(4);
    // ptr = realloc(ptr, 8);
    // (void)malloc(4);
    // show_alloc_mem();

    return (0);
}
