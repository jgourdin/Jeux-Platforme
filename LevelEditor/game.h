/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:17:13 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 00:33:05 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "./libft/libft.h"
# include "sdl/1.2.15/include/SDL/SDL.h"
# include "sdl_image/1.2.12_7/include/SDL/SDL_image.h"
# include "sdl_ttf/2.0.11_1/include/SDL/SDL_ttf.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255
#define MAX_MAP_X 400
#define MAX_MAP_Y 300
#define EVENT_KEY event.key.keysym.sym
#define EVENT_BUTTON event.button.button
#define TILE_SIZE 32
#define BLANK_TILE 0
#define MAX_TILES 17
#define LEVEL_MAX 2

typedef struct	s_cursor
{
	int			x;
	int			y;
	int			tileID;
}				t_cursor;

typedef struct	s_input
{
	int			left;
	int			right;
	int			up;
	int			down;
	int			add;
	int			remove;
	int			previous;
	int			next;
	int			load;
	int			save;
	int			copy;
	int			reinit;
	int			mouseX;
	int			mouseY;
	int			leveldown;
	int			levelup;
	int			layerDrawn;
	int			changeLayer;
}				t_input;

typedef struct	s_gestion
{
	SDL_Surface *screen;
	int			level;
}				t_gestion;

typedef struct	s_map
{
	SDL_Surface	*background;
	SDL_Surface	*tileSet;
	int			startX;
	int			startY;
	int			maxX;
	int			maxY;
	int			tile[MAX_MAP_Y][MAX_MAP_X];
	int			tile2[MAX_MAP_Y][MAX_MAP_X];
}				t_map;

typedef struct	s_game
{
	t_gestion	jeu;
	t_input		input;
	t_map		map;
	t_cursor	cursor;
	TTF_Font	*font;
}				t_game;
TTF_Font		*loadFont(char *name, int size, t_game *env);
void			closeFont(TTF_Font *font, t_game *env);
void			drawString(char *text, int x, int y, TTF_Font *font, t_game *env);
void			update(t_game *env);
void			loadGame(t_game *env);
void			init(char *, t_game *env);
void			cleanup(t_game *env);
void			getInput(t_game *env);
void			draw(t_game *env);
void			drawImage(t_game *env, int x, int y);
void			delay(unsigned int frameLimit);
void			drawMap(t_game *env);
void			loadMap(char *name, t_game *env);
void			saveMap(char *name, t_game *env);
void			reinitMap(char *name, t_game *env);
void			drawTile(t_game *env, int destx, int desty, int srcx, int srcy);
SDL_Surface		*loadImage(char *name, t_game *env);
#endif
