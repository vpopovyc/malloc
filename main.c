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

void *thread_entry(void *ptr)
{
    (void)ptr;
    for (int i = 0; i < 21; ++i)
    {
        printf("Allocating and freeing in %d\n", (int)pthread_self());
        free(malloc(i + 1));
    }
    pthread_exit(0);
}

int main(void)
{
/*
    {
        printf("~ Small size page test [%d bytes] ~\n", 42);
        void *ptr = malloc(42);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Medium size page test [%d] ~\n", medium_alloc - 256);
        void *ptr = malloc(medium_alloc - 256);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Normal size page test [%d] ~\n", normal_alloc - 256);
        void *ptr = malloc(normal_alloc - 256);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Unique size page test [%d] ~\n", 4096 << 4);
        void *ptr = malloc(4096 << 4);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Small One by One ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(42 + i);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Medium One by One ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(medium_alloc - 256 + i);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Normal One by One ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(normal_alloc - 256 + i);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Unique One by One ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc((4096 << 4) + i);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Small 4 allocs with free of first alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(42 + i);
        show_alloc_mem();
        free(ptr[0]);
        show_alloc_mem();
        for (int i = 1; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Medium 4 allocs with free of first alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(medium_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[0]);
        show_alloc_mem();
        for (int i = 1; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Normal 4 allocs with free of first alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(normal_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[0]);
        show_alloc_mem();
        for (int i = 1; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Unique 4 allocs with free of first alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc((4096 << 4) + i);
        show_alloc_mem();
        free(ptr[0]);
        show_alloc_mem();
        for (int i = 1; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Small 4 allocs with free of last alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(42 + i);
        show_alloc_mem();
        free(ptr[0]);
        show_alloc_mem();
        for (int i = 0; i < 3; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Medium 4 allocs with free of last alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(medium_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[3]);
        show_alloc_mem();
        for (int i = 0; i < 3; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Normal 4 allocs with free of last alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(normal_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[3]);
        show_alloc_mem();
        for (int i = 0; i < 3; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Unique 4 allocs with free of last alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc((4096 << 4) + i);
        show_alloc_mem();
        free(ptr[3]);
        show_alloc_mem();
        for (int i = 0; i < 3; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Small 4 allocs with free of second alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(42 + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        free(ptr[0]);
        for (int i = 2; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Medium 4 allocs with free of second alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(medium_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        free(ptr[0]);
        for (int i = 2; i < 4; ++i)
            free(ptr[i]);

    }
    {
        printf("\n~ Normal 4 allocs with free of second alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(normal_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        free(ptr[0]);
        for (int i = 2; i < 4; ++i)
            free(ptr[i]);

    }
    {
        printf("\n~ Unique 4 allocs with free of second alloc ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc((4096 << 4) + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        free(ptr[0]);
        for (int i = 2; i < 4; ++i)
            free(ptr[i]);

    }
    {
        printf("\n~ Small 4 allocs with free of second alloc and new alloc with same size ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(42 + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        ptr[1] = malloc(42 + 1);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Medium 4 allocs with free of second alloc and new alloc with same size ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(medium_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        ptr[1] = malloc(medium_alloc - 256 + 1);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Normal 4 allocs with free of second alloc and new alloc with same size ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc(normal_alloc - 256 + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        ptr[1] = malloc(normal_alloc - 256 + 1);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ Unique 4 allocs with free of second alloc and new alloc with same size ~\n");
        void *ptr[4];
        for (int i = 0; i < 4; ++i)
            ptr[i] = malloc((4096 << 4) + i);
        show_alloc_mem();
        free(ptr[1]);
        show_alloc_mem();
        ptr[1] = malloc((4096 << 4) + 1);
        show_alloc_mem();
        for (int i = 0; i < 4; ++i)
            free(ptr[i]);
    }
    {
        printf("\n~ -1 test ~\n");
        void *ptr = malloc(-1);
        if (ptr == NULL)
            printf("Could not allocate that much of memory: %zu\n", (size_t)-1);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Small realloc test ~\n");
        void *ptr = malloc(42);
        show_alloc_mem();
        realloc(ptr, 84);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Medium realloc test ~\n");
        void *ptr = malloc(medium_alloc / 2);
        show_alloc_mem();
        realloc(ptr, medium_alloc - 256);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Normal realloc test ~\n");
        void *ptr = malloc(normal_alloc / 2);
        show_alloc_mem();
        realloc(ptr, normal_alloc - 256);
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n~ Unique realloc test ~\n");
        void *ptr = malloc((4096 << 4));
        show_alloc_mem();
        realloc(ptr, ((4096 << 4) + 2048));
        show_alloc_mem();
        free(ptr);
    }
    {
        printf("\n Test for thread safety \n");
        pthread_t       thread[2];
        pthread_attr_t  thread_atrr;

        pthread_attr_init(&thread_atrr);
        pthread_create(&thread[0], &thread_atrr, thread_entry, NULL);
        pthread_create(&thread[1], &thread_atrr, thread_entry, NULL);
        for (int i = 0; i < 2; ++i)
            pthread_join(thread[0], NULL);
        show_alloc_mem();
    }
*/
    return (0);
}
