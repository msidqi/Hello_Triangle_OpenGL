/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:53:12 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/11 20:44:09 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/texture_helper.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

t_texture	*load(t_texture *this, char *texture_path)
{
	if (!(this->data = stbi_load(
		texture_path, &this->w, &this->h, &this->channels, 0)))
	{
		this->error = 1;
		printf("ERROR::STBI::COULD_NOT_LOAD_IMAGE : %s\n", texture_path);
	}
	return (this);
}

/*
** texture_number starts from 0: is used to load multiple textures on GPU
** gl_tex_target GL_TEXTURE_2D GL_TEXTURE_3D etc..
*/

t_texture	*bind(t_texture *this, int gl_tex_target, int texture_unit)
{
	this->bind_id = GL_TEXTURE0 + texture_unit;
	glGenTextures(1, &this->bind_id);
	glActiveTexture(this->bind_id);
	glBindTexture(gl_tex_target, this->bind_id);
	this->gl_target = gl_tex_target;
	return (this);
}

/*
** set how openGL wraps textures on S axis (x)
** glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_S, opts.wrap_s);
**
** texture filterng option for when using small texture on bigger obj
** glTexParameteri(this->gl_target, GL_TEXTURE_MIN_FILTER, opts.filter_min);
*/

t_texture	*set_params(t_texture *this, t_tex_params opts)
{
	if (this->gl_target == -1)
	{
		this->error = 1;
		printf("ERROR::TEXTURE::NO_BIND_TARGET\n");
	}
	else
	{
		if (opts.wrap_s)
			glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_S, opts.wrap_s);
		if (opts.wrap_t)
			glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_T, opts.wrap_t);
		if (opts.wrap_r)
			glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_R, opts.wrap_r);
		if (opts.filter_min)
			glTexParameteri(this->gl_target, GL_TEXTURE_MIN_FILTER,
															opts.filter_min);
		if (opts.filter_mag)
			glTexParameteri(this->gl_target, GL_TEXTURE_MAG_FILTER,
															opts.filter_mag);
	}
	return (this);
}

/*
** generates texture on currently bound texture obj
** glTexImage2D(this->gl_target, 0, ..., this->data);
**
** - generates multiple versions of textures to be applied
** depending on distance
** - saves us form calling glTexImage2D(GL_TEXTURE_2D, 0, ...)
** for different levels(0)
** glGenerateMipmap(this->gl_target);
*/

int			exec(t_texture *this)
{
	if (this->error == 1 || !this->data)
	{
		printf("ERROR::TEXTURE::EXEC\n");
		return (0);
	}
	printf("this->channels %d\n", this->channels);
	glTexImage2D(this->gl_target, 0, GL_RGB, this->w, this->h, 0,
	this->channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, this->data);
	glGenerateMipmap(this->gl_target);
	stbi_image_free(this->data);
	this->data = NULL;
	return (1);
}

void		tex_destroy(t_texture **this)
{
	if (*this == NULL)
		return ;
	if ((*this)->data)
		free((*this)->data);
	free(*this);
	*this = NULL;
}
