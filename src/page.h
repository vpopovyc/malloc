/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 14:19:38 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/20 14:19:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAGE_H
# define __PAGE_H

# include <malloc.h>

t_page		*new_page(size_t size, t_page *prev_page);
_Bool		try_insert_at_begin(t_page *page, size_t size);
void		insert_new_block_in_fresh_page(t_page *page, size_t size);
void		insert_new_block_in_used_page(t_page *page,
						t_meta_data *md, size_t size);
_Bool		check_if_new_block_can_fit(t_page *page,
						t_meta_data *md, size_t size);
t_ctuple	find_pointer(void *ptr);
size_t		get_size(t_page_type type, size_t optional_size);

#endif
