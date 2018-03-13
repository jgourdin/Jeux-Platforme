/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:43:02 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 18:05:32 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	init(char *title, t_game *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not Initialize SDL: %s\n",
				SDL_GetError());
		cleanup(env);
	}
	if (TTF_Init() < 0)
	{
		printf("Couldn't Initialize SDL TTF: %s\n", SDL_GetError());
		cleanup(env);
	}
	env->font = loadFont("font/GenBasB.ttf", 32, env);
	env->jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH,  SCREEN_HEIGHT, 0,
			SDL_HWPALETTE | SDL_DOUBLEBUF);
	if (env->jeu.screen == NULL)
	{
		printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH,
				SCREEN_HEIGHT, SDL_GetError());
		cleanup(env);
	}
	SDL_WM_SetCaption(title, NULL);
	env->jeu.level = 1;
}

void	loadGame(t_game *env)
{
	char	file[120];
	if (env->map.background == NULL)
		env->map.background = loadImage("graphics/background.bmp", env);
	if (env->map.background == NULL)
	{
		printf("Unable to load background\n");
		cleanup(env);
	}
	if (env->map.tileSet == NULL)
		SDL_FreeSurface(env->map.tileSet);
	sprintf(file, "graphics/tileset%d.bmp", env->jeu.level);
	env->map.tileSet = loadImage(file, env);
	if (env->map.tileSet == NULL)
	{
		printf("Unable to load tileset : %d", env->jeu.level);
		cleanup(env);
	}
	sprintf(file, "map/map%d.txt", env->jeu.level);
	loadMap(file, env);
}


void	cleanup(t_game *env)
{
	if (env->map.background != NULL)
		SDL_FreeSurface(env->map.background);
	if (env->map.tileSet != NULL)
		SDL_FreeSurface(env->map.tileSet);
	closeFont(env->font, env);
	TTF_Quit();
	SDL_Quit();
	exit(1);
}
