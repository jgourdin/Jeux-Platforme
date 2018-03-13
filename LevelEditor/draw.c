/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:04:56 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 18:08:01 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		drawTile(t_game *env, int destx, int desty, int srcx, int srcy)
{
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;
	SDL_BlitSurface(env->map.tileSet, &src, env->jeu.screen, &dest);
}

void		drawImage(t_game *env, int x, int y)
{
	SDL_Rect	dest;

	dest.x = x;
	dest.y = y;
	dest.w = env->map.background->w;
	dest.h = env->map.background->h;

	SDL_BlitSurface(env->map.background, NULL, env->jeu.screen, &dest);
}

void		draw(t_game *env)
{
	char	text[200];
	drawImage(env, 0, 0);
	drawMap(env);
	if (env->input.layerDrawn == 3)
		sprintf(text, "Layer 1 + 2");
	else
		sprintf(text, "Layer %d", env->input.layerDrawn);
	drawString(text, 475, 10, env->font, env);
	SDL_Flip(env->jeu.screen);

	SDL_Delay(1);
}

SDL_Surface		*loadImage(char *name, t_game *env)
{
	SDL_Surface *temp = SDL_LoadBMP(name);
	SDL_Surface *image;

	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		return NULL;
	}
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY | SDL_RLEACCEL),
		SDL_MapRGB(temp->format, TRANS_R, TRANS_G, TRANS_B));

	image = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);
		return NULL;
	}
	return (image);
}

void			delay(unsigned int frameLimit)
{
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
		return;
	if (frameLimit > ticks + 16)
		SDL_Delay(16);
	else
		SDL_Delay(frameLimit - ticks);
}
