/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:52:49 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 13:21:49 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	updatePlayer(t_game *env)
{
	if (env->player.timerMort == 0)
	{
		env->player.dirX = 0;
		env->player.dirY += GRAVITY_SPEED;
		if (env->player.dirY >= MAX_FALL_SPEED)
			env->player.dirY = MAX_FALL_SPEED;
		if (env->input.left == 1)
		{
			env->player.dirX -= PLAYER_SPEED;
			env->player.direction = LEFT;
			if (env->player.etat != WALK_LEFT && env->player.onGround == 1)
			{
				env->player.etat = WALK_LEFT;
				changeAnimation(&(env->player), "graphics/walkleft.bmp", env);
			}
		}
		else if (env->input.right == 1)
		{
			env->player.dirX += PLAYER_SPEED;
			env->player.direction = RIGHT;
			if (env->player.etat != WALK_RIGHT && env->player.onGround == 1)
			{
				env->player.etat = WALK_RIGHT;
				changeAnimation(&(env->player), "graphics/walkright.bmp", env);
			}
		}
		else if (env->input.right == 0 && env->input.left == 0 &&
				env->player.onGround == 1)
		{
			if (env->player.etat != IDLE)
			{
				env->player.etat = IDLE;
				if (env->player.direction == LEFT)
					changeAnimation(&(env->player), "graphics/IdleLeft.bmp", env);
				else
					changeAnimation(&(env->player), "graphics/IdleRight.bmp", env);
			}
		}
		if (env->input.jump == 1)
		{
			if (env->player.onGround == 1)
			{
				env->player.dirY =- JUMP_HEIGHT;
				env->player.onGround = 0;
				env->player.jump = 1;
			}
			else if (env->player.jump == 1)
			{
				env->player.dirY =-JUMP_HEIGHT;
				env->player.jump = 0;
			}
			env->input.jump = 0;
		}
		if (env->input.enter == 1)
		{
			env->jeu.onMenu = 1;
			env->jeu.menuType = 0;
			env->input.enter = 0;
		}
		if (env->input.attack == 1)
		{
			createFireBall(env);
			env->input.attack = 0;
		}
		if (env->player.onGround == 1)
			env->player.jump = 1;
		if (env->player.onGround == 0)
		{
			if (env->player.direction == RIGHT && env->player.etat != JUMP_RIGHT)
			{
				env->player.etat = JUMP_RIGHT;
				changeAnimation(&(env->player), "graphics/JumpRight.bmp", env);
			}
			else if(env->player.direction == LEFT && env->player.etat !=
					JUMP_LEFT)
			{
				env->player.etat = JUMP_LEFT;
				changeAnimation(&(env->player), "graphics/JumpRight.bmp", env);
			}
		}
		mapCollision(&(env->player), env);
		centerScrollingOnPlayer(env);
	}
	if (env->player.timerMort > 0)
	{
		env->player.timerMort--;
		if (env->player.timerMort == 0)
		{
			if (env->player.invicibleTimer > 0)
				env->player.invicibleTimer--;
			else
			{
				env->jeu.vies--;
				if (env->jeu.vies < 0)
				{
					env->jeu.onMenu = 1;
					env->jeu.menuType = 1;
				}
				initializePlayer(env);
				changeLevel(env);
			}
		}
	}
}


void	getInput(t_game *env)
{
	SDL_Event	event;
	static int	i = 0;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			cleanup(env);
		if (event.type == SDL_KEYDOWN)
		{
			if (EVENT_KEY == SDLK_DELETE)
				env->input.erase = 1;
			if (EVENT_KEY == SDLK_c)
				env->input.jump = 1;
			if (EVENT_KEY == SDLK_v)
				env->input.attack = 1;
			if (EVENT_KEY == SDLK_LEFT)
				env->input.left = 1;
			else if (EVENT_KEY == SDLK_RIGHT)
				env->input.right = 1;
			if (EVENT_KEY == SDLK_UP)
				env->input.up = 1;
			else if (EVENT_KEY == SDLK_DOWN)
				env->input.down = 1;
			if (EVENT_KEY == SDLK_RETURN)
				env->input.enter = 1;
			if (EVENT_KEY == SDLK_ESCAPE)
				cleanup(env);
		}
		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_DELETE:
					env->input.erase = 0;
					break;
				case SDLK_c:
					env->input.jump = 0;
					break;
				case SDLK_v:
					env->input.attack = 0;
					break;
				case SDLK_LEFT:
					env->input.left = 0;
					break;
				case SDLK_RIGHT:
					env->input.right = 0;
					break;
				case SDLK_UP:
					env->input.up = 0;
					break;
				case SDLK_DOWN:
					env->input.down = 0;
					break;
				case SDLK_RETURN:
					env->input.enter = 0;
					break;
				default:
					break;
				}
			}
	}
}
