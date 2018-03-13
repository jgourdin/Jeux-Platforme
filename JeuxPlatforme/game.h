/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:17:13 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 01:41:02 by jgourdin         ###   ########.fr       */
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

//#define PRINTF_MAP_PAUSE

#define BLANK_TILE 10
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 10
#define JUMP_HEIGHT 13
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 80
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255
#define MAX_MAP_X 400
#define MAX_MAP_Y 300
#define EVENT_KEY event.key.keysym.sym
#define TILE_SIZE 32
#define TIME_BETWEEN_2_FRAMES 8
#define PLAYER_SPEED 4
#define WALK 1
#define JUMP 3
#define RIGHT 1
#define LEFT 2
#define WALK_RIGHT 1
#define WALK_LEFT 2
#define IDLE 3
#define JUMP_RIGHT 4
#define JUMP_LEFT 5
#define MONSTRES_MAX 50
#define LEVEL_MAX 2
#define TILE_RESSORT 12
#define TILE_CHECKPOINT 9
#define TILE_MONSTRE 17
#define TILE_POWER_UP_DEBUT 7
#define TILE_POWER_UP_FIN 8
#define TILE_PLATEFORME_DEBUT 15
#define TILE_PLATFORME_FIN 16
#define FIREBALLS_MAX 3
#define PLATEFORME_MAX 50
#define PLATEFORME_TILES_DEBUT 15
#define PLATEFORME_TILES_FIN 16
#define PLATEFORM_SPEED 2
#define UP 3
#define DOWN 4

typedef struct	s_object
{
	SDL_Surface	*sprite;
	int			invicibleTimer;
	int			x;
	int			y;
	int			h;
	int			w;
	int			life;
	int			frameNumber;
	int			frameTimer;
	int			etat;
	int			direction;
	int			onGround;
	int			timerMort;
	int			jump;
	int			saveX;
	int			saveY;
	float		dirX;
	float		dirY;
	int			respawnY;
	int			checkpointActif;
	int			respawnX;
	int			beginX;
	int			beginY;
	int			type;
	int			player_dessus;
}				t_object;

typedef struct	s_input
{
	int			left;
	int			right;
	int			up;
	int			down;
	int			jump;
	int			attack;
	int			enter;
	int			erase;
	int			pause;
}				t_input;

typedef struct	s_gestion
{
	SDL_Surface	*plateforme;
	SDL_Surface	*screen;
	SDL_Surface	*HUD_vie;
	SDL_Surface	*HUD_etoiles;
	SDL_Surface	*Shuriken_image;
	int			vies;
	int			etoiles;
	int			level;
	int			onMenu;
	int			menuType;
	int			choice;
	int			nombreFireballs;
	int			nombreMonstres;
	int			nombrePlateforme;

}				t_gestion;

typedef struct	s_map
{
	SDL_Surface	*background;
	SDL_Surface	*tileSet;
	SDL_Surface	*tileSetB;
	int			startX;
	int			startY;
	int			maxX;
	int			maxY;
	int			mapTimer;
	int			tileSetNumber;
	int			tile[MAX_MAP_Y][MAX_MAP_X];
	int			tile2[MAX_MAP_Y][MAX_MAP_X];
}				t_map;

typedef struct	s_game
{
	t_object	plateforme[50];
	t_object	shuriken[10];
	t_object	player;
	t_gestion	jeu;
	t_input		input;
	t_map		map;
	t_object	monster[MONSTRES_MAX];
	TTF_Font	*font;
}				t_game;

void			printMap(t_game *env);
void			drawPlateforme(t_game *env);
void			doPlateforme(t_game *env);
void			loadPlateforme(t_game *env);
void			initPlateforme(int x, int y, int type, t_game *env);
void			drawFireballs(t_game *env);
void			doFireballs(t_game *env);
void			createFireBall(t_game *env);
void			updatePauseMenu(t_game *env);
void			drawPauseMenu(t_game *env);
void			updateStartMenu(t_game *env);
void			drawStartMenu(t_game *env);
void			monsterCollisionToMap(t_object *entity, t_game *env);
void			changeLevel(t_game *env);
void			changeAnimation(t_object *entity, char *name, t_game *env);
void			closeFont(t_game *env);
TTF_Font		*loadFont(char *, int, t_game *env);
void			drawString(char *text, int x, int y, t_game *env);
void			drawHud(t_game *env);
void			drawImageEtoile(t_game *env, int x, int y);
void			drawImageVie(t_game *env, int x, int y);
int				checkFall(t_game *env, int i);
int				collide(t_object *entity, t_object *entity2, t_game *env);
void			updateMonsters(t_game *env);
void			mapCollisionMonster(t_game *env);
void			drawanimatedmonster(t_game *env);
void			initializeMonster(int x, int y, t_game *env);
void			mapCollision(t_object *entity, t_game *env);
void			centerScrollingOnPlayer(t_game *env);
void			drawAnimatedObject(t_object *entity, t_game *env);
void			initializePlayer(t_game *env);
void			drawplayer(t_game *env);
void			updatePlayer(t_game *env);
void			loadGame(t_game *env);
void			init(char *, t_game *env);
void			cleanup(t_game *env);
void			getInput(t_game *env);
void			draw(t_game *env);
void			drawImage(SDL_Surface *surface, int x, int y, t_game *env);
void			delay(unsigned int frameLimit);
void			drawMap(int layer, t_game *env);
void			loadMap(char *name, t_game *env);
void			drawTile(SDL_Surface *tile , int destx, int desty, int srcx, int srcy, t_game *env);
void			getItem(int itemNumber, t_game *env);
SDL_Surface		*loadImage(char *name, t_game *env);
#endif
