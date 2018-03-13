/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:19:45 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 15:01:28 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void			getItem(int itemNumber, t_game *env)
{
	switch(itemNumber)
	{
		case 1:
		env->jeu.etoiles++;
		if (env->jeu.etoiles >= 100)
		{
			env->jeu.etoiles = 0;
			env->jeu.vies++;
		}
		break;
		case 2:
		if(env->player.life < 3)
			env->player.life++;
		break;
		default:
		break;
	}
}

void			centerScrollingOnPlayer(t_game *env)
{
	env->map.startX = env->player.x - (SCREEN_WIDTH / 2);

	if (env->map.startX < 0)
		env->map.startX = 0;
	else if (env->map.startX + SCREEN_WIDTH >= env->map.maxX)
		env->map.startX = env->map.maxX - SCREEN_WIDTH;
	env->map.startY = env->player.y - (SCREEN_HEIGHT / 2);
	if (env->map.startY < 0)
		env->map.startY = 0;
	else if (env->map.startY + SCREEN_HEIGHT >= env->map.maxY)
		env->map.startY = env->map.maxY - SCREEN_HEIGHT;
}

void			initializePlayer(t_game *env)
{
	changeAnimation(&(env->player), "graphics/walkright.bmp", env);
	env->player.direction = RIGHT;
	env->player.etat = IDLE;
	env->player.etat = WALK;
	if (env->player.checkpointActif == 1)
	{
		env->player.x = env->player.respawnX;
		env->player.y = env->player.respawnY;
	}
	else
	{
		env->player.x = 0;
		env->player.y = 0;
	}
	env->player.w = PLAYER_WIDTH;
	env->player.h = PLAYER_HEIGHT;
	env->player.timerMort = 0;
	env->player.onGround = 0;
	env->jeu.nombreMonstres = 0;
	env->player.life = 3;
	env->player.invicibleTimer = 0;
	env->jeu.nombreFireballs = 0;
	env->jeu.nombrePlateforme = 0;
	loadMap("map/map1.txt", env);
}

void			drawplayer(t_game *env)
{
	SDL_Rect	dest;
	dest.x = env->player.x - env->map.startX;
	dest.y = env->player.y - env->map.startY;
	dest.w = PLAYER_WIDTH;
	dest.h = PLAYER_HEIGHT;

	SDL_Rect	src;
	src.x = env->player.frameNumber * PLAYER_WIDTH;
	src.y = 0;
	src.w = PLAYER_WIDTH;
	src.h = PLAYER_HEIGHT;

	SDL_BlitSurface(env->player.sprite, &src, env->jeu.screen, &dest);
}
