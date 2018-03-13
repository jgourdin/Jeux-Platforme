/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plateforme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 14:27:49 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 06:52:09 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		loadPlateforme(t_game *env)
{
	env->jeu.plateforme = loadImage("graphics/plateforme.bmp", env);
	if (env->jeu.plateforme == NULL)
	{
		printf("Impossible de charger l'image de la plateforme\n");
		cleanup(env);
	}
}

void		initPlateforme(int x, int y, int type, t_game *env)
{
	env->jeu.nombrePlateforme++;
	if (env->jeu.nombrePlateforme > PLATEFORME_MAX)
	{
		printf("Trop de platforme initialisees !\n");
		cleanup(env);
	}
	env->plateforme[env->jeu.nombrePlateforme].x =
		env->plateforme[env->jeu.nombrePlateforme].beginX = x;
	env->plateforme[env->jeu.nombrePlateforme].y =
		env->plateforme[env->jeu.nombrePlateforme].beginY = y;
	env->plateforme[env->jeu.nombrePlateforme].w = env->jeu.plateforme->w;
	env->plateforme[env->jeu.nombrePlateforme].h = env->jeu.plateforme->h;
	env->plateforme[env->jeu.nombrePlateforme].type = type;
	if (env->plateforme[env->jeu.nombrePlateforme].type == 2)
		env->plateforme[env->jeu.nombrePlateforme].direction = UP;
	else
		env->plateforme[env->jeu.nombrePlateforme].direction = RIGHT;
}

void		doPlateforme(t_game *env)
{
	int		i;

	for (i = 1; i < env->jeu.nombrePlateforme; i++)
	{
		if (env->plateforme[i].type == 2)
		{
			if (env->plateforme[i].direction == UP)
			{
				env->plateforme[i].y -= PLATEFORM_SPEED;
				if (env->plateforme[i].player_dessus == 1)
					env->player.y -= PLATEFORM_SPEED;
			}
			else
			{
				env->plateforme[i].y += PLATEFORM_SPEED;
				if (env->plateforme[i].player_dessus == 1)
					env->player.y += PLATEFORM_SPEED;
			}
			if (env->plateforme[i].y > env->plateforme[i].beginY + 5 * TILE_SIZE)
				env->plateforme[i].direction = UP;
			if (env->plateforme[i].y < env->plateforme[i].beginY)
				env->plateforme[i].direction = DOWN;
		}
		else
		{
			if (env->plateforme[i].direction == RIGHT)
			{
				env->plateforme[i].x += PLATEFORM_SPEED;
				if (env->plateforme[i].player_dessus == 1)
					env->player.y += PLATEFORM_SPEED;
			}
			else
			{
				env->plateforme[i].x -= PLATEFORM_SPEED;
				if (env->plateforme[i].player_dessus == 1)
					env->player.y -= PLATEFORM_SPEED;
			}
			if (env->plateforme[i].x > env->plateforme[i].beginX + 5 * TILE_SIZE)
				env->plateforme[i].direction = LEFT;
			if (env->plateforme[i].x < env->plateforme[i].beginX)
				env->plateforme[i].direction = RIGHT;
		}
	}
}

void		drawPlateforme(t_game *env)
{
	int		i;
	for (i = 1; i <= env->jeu.nombrePlateforme; i++)
		drawImage(env->jeu.plateforme, env->plateforme[i].x - env->map.startX,
				env->plateforme[i].y - env->map.startY, env);
}

