/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_construct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:23:10 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/22 20:23:23 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/texture_helper.h"

t_texture	*texture_construct()
{
	t_texture *this;

	// stbi_set_flip_vertically_on_load(1);
	if(!(this = (t_texture *)malloc(sizeof(t_texture))))
		return(NULL);
	this->error = 0;
	this->gl_target = -1;
	this->load = &load;
	this->bind = &bind;
	this->set_params = &set_params;
	this->exec = &exec;
	this->destroy = &tex_destroy;
	return (this);
}
