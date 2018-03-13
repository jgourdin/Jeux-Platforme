/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:16:09 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 13:34:19 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int			checkFall(t_game *env, int i)
{
	int		x;
	int		y;

	if (env->monster[i].direction == LEFT)
	{
		x = (int)(env->monster[i].x + env->monster[i].dirX) / TILE_SIZE;
		y = (int)(env->monster[i].y + env->monster[i].h - 1) / TILE_SIZE;
		if (y < 0)
			y = 1;
		if (y > MAX_MAP_Y)
			y = MAX_MAP_Y;
		if (x < 0)
			x = 1;
		if (x > MAX_MAP_X)
			x = MAX_MAP_X;
		if (env->map.tile[y + 1][x] < BLANK_TILE)
			return (1);
		else
			return (0);
	}
	else
	{
		x = (int)(env->monster[i].x + env->monster[i].dirX) / TILE_SIZE;
		y = (int)(env->monster[i].y + env->monster[i].h - 1) / TILE_SIZE;
		if (y < 0)
			y = 1;
		if (y >= MAX_MAP_Y)
			y = MAX_MAP_Y - 1;
		if (x <= 0)
			x = 1;
		if (x >= MAX_MAP_X)
			x = MAX_MAP_X - 1;
		if (env->map.tile[y + 1][x] < BLANK_TILE)
			return (1);
		else
			return (0);
	}
}

void		updateMonsters(t_game *env)
{
	int		a;
	int		i;
	for (i = 0; i < env->jeu.nombreMonstres; i++)
	{
		if(env->monster[i].timerMort == 0)
		{
			env->monster[i].dirX = 0;
			env->monster[i].dirY += GRAVITY_SPEED;
			if (env->monster[i].dirY >= MAX_FALL_SPEED)
				env->monster[i].dirY = MAX_FALL_SPEED;
			if (env->monster[i].x == env->monster[i].saveX ||
					checkFall(env, i) == 1)
			{
				if (env->monster[i].direction == LEFT)
				{
					env->monster[i].direction = RIGHT;
					changeAnimation(&(env->monster[i]), "graphics/monster1right.bmp", env);
				}
				else
				{
					env->monster[i].direction = LEFT;
					changeAnimation(&(env->monster[i]), "graphics/monster1.bmp", env);
				}
			}
			if (env->monster[i].direction == LEFT)
				env->monster[i].dirX -= 2;
			else
				env->monster[i].dirX += 2;
			env->monster[i].saveX = env->monster[i].x;
			monsterCollisionToMap(&(env->monster[i]), env);
			if (collide(&(env->monster[i]),&(env->player), env) == 1)
			{
				if (env->player.life > 1)
				{
					if (env->player.invicibleTimer == 0)
					{
						env->player.life--;
						env->player.invicibleTimer = 60;
						env->monster[i].timerMort = 1;
						env->player.dirY = -JUMP_HEIGHT;
					}
				}
				else
					env->player.timerMort = 1;
			}
			else if (collide(&(env->monster[i]),&(env->player), env) == 2)
				env->monster[i].timerMort = 1;
			for (a = 0; a < env->jeu.nombreFireballs; a++)
			{
				if (collide(&(env->monster[i]), &(env->shuriken[a]), env))
				{
					env->monster[i].timerMort = 1;
					env->shuriken[a] = env->shuriken[env->jeu.nombreFireballs - 1];
					env->jeu.nombreFireballs--;
				}
			}
		}
		if (env->monster[i].timerMort > 0)
		{
			env->monster[i].timerMort--;
			if (env->monster[i].timerMort == 0)
			{
				if (env->monster[i].sprite != NULL)
				{
					SDL_FreeSurface(env->monster[i].sprite);
					env->monster[i].sprite = NULL;
				}
				env->monster[i] = env->monster[env->jeu.nombreMonstres - 1];
				env->jeu.nombreMonstres--;
			}
		}
	}
	env->monster[env->jeu.nombreMonstres].sprite = NULL;
}

int			collide(t_object *entity, t_object *entity2, t_game *env)
{
	if ((entity2->x >= entity->x +
			entity->w) || (entity2->x + entity2->w
			<= entity->x) || (entity2->y >=
			entity->y + entity->h) ||
			(entity2->y + entity2->h <= entity->y))
				return(0);
	else if (entity2->y + entity2->h <= entity->y + 10)
	{
		entity2->dirY = -JUMP_HEIGHT;
		return (2);
	}
	else
		return 1;
}

void		initializeMonster(int x, int y, t_game *env)
{
	if (env->jeu.nombreMonstres < MONSTRES_MAX)
	{
		env->monster[env->jeu.nombreMonstres].sprite =
			loadImage("graphics/monster1.bmp", env);
		env->monster[env->jeu.nombreMonstres].direction = LEFT;
		env->monster[env->jeu.nombreMonstres].frameNumber = 0;
		env->monster[env->jeu.nombreMonstres].frameTimer =
			TIME_BETWEEN_2_FRAMES;
		env->monster[env->jeu.nombreMonstres].x = x;
		env->monster[env->jeu.nombreMonstres].y = y;
		env->monster[env->jeu.nombreMonstres].w = TILE_SIZE;
		env->monster[env->jeu.nombreMonstres].h = TILE_SIZE;
		env->monster[env->jeu.nombreMonstres].timerMort = 0;
		env->monster[env->jeu.nombreMonstres].onGround = 0;
		env->jeu.nombreMonstres++;
	}
}
