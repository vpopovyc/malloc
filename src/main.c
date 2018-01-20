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
//#include <unistd.h>
//#include <stdio.h>
#include <sys/resource.h>
//#include <stdlib.h>
#include <sys/mman.h>

int main(void)
{
//    struct rlimit as_rlimit;
//    struct rlimit data_rlimit;
//
//    getrlimit(RLIMIT_AS, &as_rlimit);
//    getrlimit(RLIMIT_DATA, &data_rlimit);
//    printf("soft limit AS, hard limit AS: %llu, %llu\n", as_rlimit.rlim_cur, as_rlimit.rlim_max);
//    printf("soft limit Data, hard limit Data: %llu, %llu\n", data_rlimit.rlim_cur, data_rlimit.rlim_max);
//    printf("pagesize(): %d\n", getpagesize());
    (void)malloc(26);
    (void)malloc(45);
    return (0);
//    void *page = mmap(0, getpagesize(), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
//    printf("page idx: %#lx\n", (size_t)(page));
//    void *page_2 = mmap(0, getpagesize(), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
//    printf("page_2 idx: %#lx\n", (size_t)page_2);
//    munmap(page, getpagesize());
//    munmap(page_2, getpagesize());
}
