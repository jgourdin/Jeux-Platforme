/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:25:33 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 17:33:52 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		main(int argc, char **argv)
{
	unsigned int	frameLimit = SDL_GetTicks() + 16;
	int				go;
	t_game			*env;

	env = (t_game *)ft_memalloc(sizeof(t_game));
	init("Level Editor", env);
	env->input.layerDrawn = 3;
	loadGame(env);
	go = 1;

	while (go == 1)
	{
		getInput(env);
		update(env);
		draw(env);
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}
	cleanup(env);
	return (0);
}
