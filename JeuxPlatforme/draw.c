/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:04:56 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 01:28:50 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		drawHud(t_game *env)
{
	char	text[200];
	int		i;

	for (i = 0; i < env->player.life; i++)
	{
		int ysource = TILE_POWER_UP_FIN / 10 * TILE_SIZE;
		int xsource = TILE_POWER_UP_FIN % 10 * TILE_SIZE;
		drawTile(env->map.tileSet, 60 + i * 32, 20, xsource, ysource, env);
	}
	drawImage(env->jeu.HUD_vie, 480, 410, env);
	sprintf(text, "%d", env->jeu.vies);
	drawString(text, 560, 420, env);
	drawImage(env->jeu.HUD_etoiles, 60, 60, env);
	sprintf(text, "%d", env->jeu.etoiles);
	drawString(text, 100, 57, env);
}

void		drawImageEtoile(t_game *env , int x, int y)
{
	SDL_Rect	dest;

	dest.x = x;
	dest.y = y;
	dest.w = env->jeu.HUD_etoiles->w;
	dest.h = env->jeu.HUD_etoiles->h;

	SDL_BlitSurface(env->jeu.HUD_etoiles, NULL, env->jeu.screen, &dest);
}

void		drawImageVie(t_game *env , int x, int y)
{
	SDL_Rect	dest;

	dest.x = x;
	dest.y = y;
	dest.w = env->jeu.HUD_vie->w;
	dest.h = env->jeu.HUD_vie->h;

	SDL_BlitSurface(env->jeu.HUD_vie, NULL, env->jeu.screen, &dest);
}

void		drawTile(SDL_Surface *tile , int destx, int desty, int srcx, int srcy, t_game *env)
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
	SDL_BlitSurface(tile, &src, env->jeu.screen, &dest);
}

void		drawImage(SDL_Surface *surface , int x, int y, t_game *env)
{
	SDL_Rect	dest;

	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, env->jeu.screen, &dest);
}

void		draw(t_game *env)
{
	int	i;
	drawImage(env->map.background, 0, 0, env);
	drawMap(1, env);
	drawAnimatedObject(&(env->player), env);
	for (i = 0; i < env->jeu.nombreMonstres; i++)
		drawAnimatedObject(&(env->monster[i]),env);
	drawPlateforme(env);
	drawFireballs(env);
	drawMap(2, env);
	drawHud(env);
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
