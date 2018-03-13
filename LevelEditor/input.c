/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:52:49 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 17:50:06 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	update(t_game *env)
{
	char	file[120];
	env->cursor.x = env->input.mouseX;
	env->cursor.y = env->input.mouseY;
	if (env->input.left == 1)
	{
		env->map.startX -= TILE_SIZE;
		if (env->map.startX < 0)
			env->map.startX = 0;
	}
	else if (env->input.right == 1)
	{
		env->map.startX += TILE_SIZE;
		if (env->map.startX + SCREEN_WIDTH >= env->map.maxX)
			env->map.startX = env->map.maxX - SCREEN_WIDTH;
	}
	if (env->input.up == 1)
	{
		env->map.startY -= TILE_SIZE;
		if (env->map.startY < 0)
			env->map.startY = 0;
	}
	else if (env->input.down == 1)
	{
		env->map.startY += TILE_SIZE;
		if (env->map.startY + SCREEN_HEIGHT >= env->map.maxY)
			env->map.startY = env->map.maxY - SCREEN_HEIGHT;
	}
	if (env->input.levelup == 1)
	{
		env->jeu.level++;
		if (env->jeu.level > LEVEL_MAX)
			env->jeu.level = 1;
		loadGame(env);
		env->input.levelup = 0;
	}
	if (env->input.leveldown == 1)
	{
		env->jeu.level--;
		if (env->jeu.level < 1)
			env->jeu.level = LEVEL_MAX;
		loadGame(env);
		env->input.leveldown = 0;
	}
	if (env->input.add == 1)
	{
		if (env->input.layerDrawn == 1)
			env->map.tile[(env->map.startY + env->cursor.y) / TILE_SIZE]
				[(env->map.startX + env->cursor.x) / TILE_SIZE] = env->cursor.tileID;
		else if (env->input.layerDrawn == 2)
			env->map.tile2[(env->map.startY + env->cursor.y) / TILE_SIZE]
				[(env->map.startX + env->cursor.x) / TILE_SIZE] = env->cursor.tileID;
	}
	else if (env->input.remove == 1)
	{
		if (env->input.layerDrawn == 1)
		{
			env->map.tile[(env->map.startY + env->cursor.y) / TILE_SIZE]
				[(env->map.startX + env->cursor.x) / TILE_SIZE] = BLANK_TILE;
		}
		else if (env->input.layerDrawn == 2)
		{
			env->map.tile2[(env->map.startY + env->cursor.y) / TILE_SIZE]
				[(env->map.startX + env->cursor.x) / TILE_SIZE] = env->cursor.tileID;
		}
		env->cursor.tileID = 0;
	}
	if (env->input.previous == 1)
	{
		env->cursor.tileID--;
		if (env->cursor.tileID < 0)
			env->cursor.tileID = MAX_TILES;
		else if (env->cursor.tileID > MAX_TILES)
			env->cursor.tileID = 0;
		env->input.previous = 0;
	}
	if (env->input.next == 1)
	{
		env->cursor.tileID++;
		if (env->cursor.tileID < 0)
			env->cursor.tileID = MAX_TILES;
		else if (env->cursor.tileID > MAX_TILES)
			env->cursor.tileID = 0;
		env->input.next = 0;
	}
	if (env->input.copy == 1)
	{
		if (env->input.layerDrawn == 1)
			env->cursor.tileID = env->map.tile[(env->map.startY + env->cursor.y) /
				TILE_SIZE][(env->map.startX + env->cursor.x) / TILE_SIZE];
		else if (env->input.layerDrawn == 2)
				env->map.tile2[(env->map.startY + env->cursor.y) / TILE_SIZE]
			[(env->map.startX + env->cursor.x) / TILE_SIZE] = env->cursor.tileID;
		env->input.copy = 0;
	}
	if (env->input.reinit == 1)
	{
		sprintf(file, "map/map%d.txt", env->jeu.level);
		reinitMap(file, env);
		loadMap(file, env);
		env->input.reinit = 0;
	}
	if (env->input.save == 1)
	{
		sprintf(file, "map/map%d.txt", env->jeu.level);
		saveMap(file,env);
		loadMap(file, env);
		env->input.save = 0;
	}
	if (env->input.load == 1)
	{
		sprintf(file, "map/map%d.txt", env->jeu.level);
		loadMap(file, env);
		env->input.load = 0;
	}
	if (env->input.changeLayer == 1)
	{
		env->input.layerDrawn++;
		if (env->input.layerDrawn > 3)
			env->input.layerDrawn = 1;
		env->input.changeLayer = 0;
	}
	if (env->input.left == 1 || env->input.right == 1 || env->input.up == 1 || env->input.down == 1)
		SDL_Delay(30);
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
			if (EVENT_KEY == SDLK_ESCAPE)
				cleanup(env);
			if (EVENT_KEY == SDLK_DELETE)
				env->input.reinit = 1;
			if (EVENT_KEY == SDLK_s)
				env->input.save = 1;
			if (EVENT_KEY == SDLK_l)
				env->input.load = 1;
			if (EVENT_KEY == SDLK_LEFT)
				env->input.left = 1;
			else if (EVENT_KEY == SDLK_RIGHT)
				env->input.right = 1;
			if (EVENT_KEY == SDLK_UP)
				env->input.up = 1;
			if (EVENT_KEY == SDLK_DOWN)
				env->input.down = 1;
			if (EVENT_KEY == SDLK_F1)
				env->input.levelup = 1;
			else if (EVENT_KEY == SDLK_F2)
				env->input.leveldown = 1;
			if (EVENT_KEY == SDLK_w)
				env->input.next = 1;
			else if (EVENT_KEY == SDLK_q)
				env->input.previous = 1;
			if (EVENT_KEY == SDLK_F3)
				env->input.changeLayer = 1;
		}
		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
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
				default:
					break;
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (EVENT_BUTTON == SDL_BUTTON_LEFT)
				env->input.add = 1;
			else if (EVENT_BUTTON == SDL_BUTTON_MIDDLE)
				env->input.remove = 1;
			else if (EVENT_BUTTON == SDL_BUTTON_RIGHT)
				env->input.copy = 1;
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (EVENT_BUTTON == SDL_BUTTON_LEFT)
				env->input.add = 0;
			if (EVENT_BUTTON == SDL_BUTTON_RIGHT)
				env->input.remove = 0;
		}
	}
	SDL_GetMouseState(&(env->input.mouseX), &(env->input.mouseY));
	env->input.mouseX /= TILE_SIZE;
	env->input.mouseY /= TILE_SIZE;
	env->input.mouseX *= TILE_SIZE;
	env->input.mouseY *= TILE_SIZE;
}
