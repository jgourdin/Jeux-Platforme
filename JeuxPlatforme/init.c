/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:43:02 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 01:38:59 by jgourdin         ###   ########.fr       */
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
	env->jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH,  SCREEN_HEIGHT, 0,
			SDL_HWPALETTE | SDL_DOUBLEBUF);
	if (env->jeu.screen == NULL)
	{
		printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH,
				SCREEN_HEIGHT, SDL_GetError());
		cleanup(env);
	}
	SDL_WM_SetCaption(title, NULL);
	SDL_ShowCursor(SDL_DISABLE);
	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		cleanup(env);
	}
	env->font = loadFont("font/GenbasB.ttf", 32, env);
}

void	loadGame(t_game *env)
{
	env->map.background = loadImage("graphics/background.bmp", env);
	env->jeu.level = 1;
	changeLevel(env);
	env->map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	env->map.tileSetNumber = 0;
	env->jeu.vies = 3;
	env->jeu.etoiles = 0;
	env->jeu.HUD_vie = loadImage("graphics/life.bmp", env);
	env->jeu.HUD_etoiles = loadImage("graphics/stars.bmp", env);
	env->jeu.Shuriken_image = loadImage("graphics/shuriken.bmp", env);
	loadPlateforme(env);
	env->jeu.onMenu = 1;
	env->jeu.menuType = 1;
}


void	cleanup(t_game *env)
{
	printf("nb = %d\n",env->jeu.nombreMonstres);
	int	i;
	if (env->map.background != NULL)
		SDL_FreeSurface(env->map.background);
	if (env->map.tileSet != NULL)
		SDL_FreeSurface(env->map.tileSet);
	if (env->map.tileSetB != NULL)
		SDL_FreeSurface(env->map.tileSetB);
	if (env->player.sprite != NULL)
		SDL_FreeSurface(env->player.sprite);
	for (i = 0; i < MONSTRES_MAX; i++)
	{
		if (env->monster[i].sprite != NULL)
			SDL_FreeSurface(env->monster[i].sprite);
	}
	if (env->jeu.plateforme != NULL)
		SDL_FreeSurface(env->jeu.plateforme);
	if (env->jeu.HUD_etoiles != NULL)
		SDL_FreeSurface(env->jeu.HUD_etoiles);
	if (env->jeu.HUD_vie != NULL)
		SDL_FreeSurface(env->jeu.HUD_vie);
	if (env->jeu.Shuriken_image != NULL)
		SDL_FreeSurface(env->jeu.Shuriken_image);
	closeFont(env);
	TTF_Quit();
	SDL_Quit();
	exit(1);
}


