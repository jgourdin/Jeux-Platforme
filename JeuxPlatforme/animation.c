/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:33:54 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/01 00:50:43 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		changeAnimation(t_object *entity, char *name, t_game *env)
{
	if (entity->sprite != NULL)
		SDL_FreeSurface(entity->sprite);
	entity->sprite = loadImage(name, env);
	entity->frameNumber = 0;
	entity->frameTimer = TIME_BETWEEN_2_FRAMES;
}

void		drawAnimatedObject(t_object *entity, t_game *env)
{
	if (entity->frameTimer <= 0)
	{
		entity->frameTimer = TIME_BETWEEN_2_FRAMES;
		entity->frameNumber++;
		if (entity->frameNumber >= entity->sprite->w / entity->w)
			entity->frameNumber = 0;
	}
	else
		entity->frameTimer--;

	SDL_Rect	dest;
	dest.x = entity->x - env->map.startX;
	dest.y = entity->y - env->map.startY;
	dest.w = entity->w;
	dest.h = entity->h;

	SDL_Rect	src;
	src.x = entity->frameNumber * entity->w;
	src.y = 0;
	src.w = entity->w;
	src.h = entity->h;

	SDL_BlitSurface(entity->sprite, &src, env->jeu.screen, &dest);
}
