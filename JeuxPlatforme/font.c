/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:01:54 by jgourdin          #+#    #+#             */
/*   Updated: 2017/11/30 23:50:28 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

TTF_Font	*loadFont(char *name, int size, t_game *env)
{
	TTF_Font	*font = TTF_OpenFont(name, size);
	if (font == NULL)
	{
		printf("Failed to open Font %s : %s\n", name, TTF_GetError());
		cleanup(env);
	}
	return (font);
}

void		closeFont(t_game *env)
{
	if (env->font != NULL)
		TTF_CloseFont(env->font);
}

void		drawString(char *text, int x, int y, t_game *env)
{
	SDL_Rect	dest;
	SDL_Surface	*surface;
	SDL_Color	foregroundColor;

	foregroundColor.r = 0;
	foregroundColor.g = 0;
	foregroundColor.b = 0;

	surface = TTF_RenderUTF8_Blended(env->font, text, foregroundColor);
	if (surface == NULL)
	{
		printf("Couldn't create String %s : %s\n", text, SDL_GetError());
		cleanup(env);
	}
	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_BlitSurface(surface, NULL, env->jeu.screen, &dest);
	SDL_FreeSurface(surface);
}

