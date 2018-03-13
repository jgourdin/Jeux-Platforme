/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:25:33 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 01:27:41 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		main(int argc, char **argv)
{
	unsigned int	frameLimit = SDL_GetTicks() + 16;
	int				go;
	int				i;
	t_game			*env;

	env = (t_game *)ft_memalloc(sizeof(t_game));
	init("Aron", env);
	initializePlayer(env);
	loadGame(env);
	go = 1;
	env->jeu.menuType = 1;
	while (go == 1)
	{
		getInput(env);
		if (env->jeu.onMenu == 0)
		{
			updatePlayer(env);
			doFireballs(env);
			updateMonsters(env);
			doPlateforme(env);
		}
		else
		{
			if (env->jeu.menuType == 1)
				updateStartMenu(env);
			else if(env->jeu.menuType == 0)
				updatePauseMenu(env);
		}
		if (env->jeu.onMenu == 0)
			draw(env);
		else
		{
			if (env->jeu.menuType == 1)
			{
				drawImage(env->map.background, 0, 0, env);
				drawStartMenu(env);
				SDL_Flip(env->jeu.screen);
				SDL_Delay(1);
			}
			else if (env->jeu.menuType == 0)
			{
				drawImage(env->map.background, 0, 0, env);
				drawMap(1, env);
				drawAnimatedObject(&(env->player), env);
				for(i = 0; i< env->jeu.nombreMonstres; i++)
					drawAnimatedObject(&(env->monster[i]), env);
				drawFireballs(env);
				drawMap(2, env);
				drawPlateforme(env);
				drawHud(env);
				drawPauseMenu(env);
				SDL_Flip(env->jeu.screen);
				SDL_Delay(1);
			}
		}
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}
	cleanup(env);
	return (0);
}
