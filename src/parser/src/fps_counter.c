/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:37:23 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/12 21:37:29 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h" 

void	ft_fps_print()
{
	static double	last_time = 0;
	static size_t	frames_count = 0;
	double			current_time;

	if (!last_time)
		last_time = glfwGetTime();
	current_time = glfwGetTime();
	frames_count++;
	if (current_time - last_time > 1.0)
	{
		printf("%f ms/frame(%zu fps)\n", 1000.0/(double)frames_count, frames_count);
		frames_count = 0;
		last_time += 1.0;
	}
}
