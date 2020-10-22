/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:22:45 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/22 20:25:41 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_texture	*load_texture(char *path, t_shader *shader)
{
	t_texture *tex;

	if (path
	&& (tex = texture_construct())
	&& tex->load(tex, path)->
	bind(tex, GL_TEXTURE_2D, 0)->set_params(tex,
	(t_tex_params){WRAP_R, WRAP_R, 0, FILTER_N, FILTER_N})->exec(tex))
	{
		shader->set_int(shader, "texSampler", tex->bind_id);
		return (tex);
	}
	return (NULL);
}
