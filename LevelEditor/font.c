/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:55:21 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 02:18:00 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

TTF_Font	*loadFont(char *name, int size, t_game *env)
{
	TTF_Font	*font = TTF_OpenFont(name, size);
	if (font == NULL)
	{
		printf("failed to open Font %s : %s\n", name, TTF_GetError());
		cleanup(env);
	}
	return (font);
}

void		closeFont(TTF_Font *font, t_game *env)
{
	if (font != NULL)
		TTF_CloseFont(font);
}

void		drawString(char *text, int x, int y, TTF_Font *font, t_game *env)
{
	SDL_Rect	dest;
	SDL_Surface	*surface;
	SDL_Color	foregroundColor;

	foregroundColor.r = 0;
	foregroundColor.g = 0;
	foregroundColor.b = 0;

	surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);
	if (surface == NULL)
	{
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());
		return;
	}
	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;
	SDL_BlitSurface(surface, NULL, env->jeu.screen, &dest);
	SDL_FreeSurface(surface);
}
