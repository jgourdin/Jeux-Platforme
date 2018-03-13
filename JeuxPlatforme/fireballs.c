/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireballs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:55:57 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 13:23:32 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	createFireBall(t_game *env)
{
	if (env->jeu.nombreFireballs < FIREBALLS_MAX)
	{
		env->shuriken[env->jeu.nombreFireballs].w = env->jeu.Shuriken_image->w;
		env->shuriken[env->jeu.nombreFireballs].h = env->jeu.Shuriken_image->h;
		if (env->player.direction == RIGHT)
		{
			env->shuriken[env->jeu.nombreFireballs].x = env->player.x + 15;
			env->shuriken[env->jeu.nombreFireballs].y = env->player.y + 35;
			env->shuriken[env->jeu.nombreFireballs].direction = 1;
		}
		else
		{
			env->shuriken[env->jeu.nombreFireballs].x = env->player.x - 15;
			env->shuriken[env->jeu.nombreFireballs].y = env->player.y + 35;
			env->shuriken[env->jeu.nombreFireballs].direction = 0;
		}
		env->jeu.nombreFireballs++;
	}
}

void	doFireballs(t_game *env)
{
	int		i;

	for (i = 0; i < env->jeu.nombreFireballs; i++)
	{
		if (env->shuriken[i].direction == 1)
			env->shuriken[i].x += 10;
		else
			env->shuriken[i].x -= 10;
		if (env->shuriken[i].x < env->map.startX ||
				env->shuriken[i].x > env->map.startX + SCREEN_WIDTH)
		{
			env->shuriken[i] = env->shuriken[env->jeu.nombreFireballs - 1];
			env->jeu.nombreFireballs--;
		}
	}
}

void	drawFireballs(t_game *env)
{
	int		i;
	for (i = 0; i< env->jeu.nombreFireballs; i++)
		drawImage(env->jeu.Shuriken_image, env->shuriken[i].x - env->map.startX,
				env->shuriken[i].y - env->map.startY, env);
}
