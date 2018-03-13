/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:42:41 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/05 01:38:46 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		changeLevel(t_game *env)
{
	char	file[200];
	sprintf(file,"map/map%d.txt", env->jeu.level);
	loadMap(file, env);
	if (env->map.tileSet != NULL)
		SDL_FreeSurface(env->map.tileSet);
	if (env->map.tileSetB != NULL)
		SDL_FreeSurface(env->map.tileSetB);
	sprintf(file, "graphics/tileset%d.bmp", env->jeu.level);
	env->map.tileSet = loadImage(file, env);
	sprintf(file, "graphics/tileset%dB.bmp", env->jeu.level);
	env->map.tileSetB = loadImage(file, env);
}

void		monsterCollisionToMap(t_object *entity, t_game *env)
{
	int		i;
	int		x1;
	int		x2;
	int		y1;
	int		y2;

	entity->onGround = 0;
	if (entity->h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->h;
	for(;;)
	{
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;
		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirX > 0)
			{
				if (env->map.tile[y1][x2] > BLANK_TILE || env->map.tile[y2][x2] >
				BLANK_TILE)
				{
					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;
				}
			}
			else if (entity->dirX < 0)
			{
				if (env->map.tile[y2][x1] > BLANK_TILE || env->map.tile[y2][x1]
					> BLANK_TILE)
				{
					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
				}
			}
		}
		if (i == entity->h)
			break;
		i += TILE_SIZE;
		if (i > entity->h)
			i = entity->h;
	}
	if (entity->w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->w;
	for(;;)
	{
		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;
		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i - 1) / TILE_SIZE;
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirY > 0)
			{
				if (env->map.tile[y2][x1] > BLANK_TILE || env->map.tile[y2][x2] >
				BLANK_TILE)
				{
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
					entity->onGround = 1;
				}
			}
			else if (entity->dirY < 0)
			{
				if (env->map.tile[y1][x1] > BLANK_TILE || env->map.tile[y1][x2]
					> BLANK_TILE)
				{
					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
				}
			}
		}
		if (i == entity->w)
			break;
		i += TILE_SIZE;
		if (i > entity->w)
			i = entity->w;
	}
	entity->x += entity->dirX;
	entity->y += entity->dirY;
	if(entity->x < 0)
		entity->x = 0;
	else if (entity->x + entity->w >= env->map.maxX)
		entity->x = env->map.maxX - entity->w - 1;
	if (entity->y > env->map.maxY)
		entity->timerMort = 60;
}


void		mapCollision(t_object *entity, t_game *env)
{
	int		i;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		j;

	entity->onGround = 0;
	if (entity->h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->h;
	for(;;)
	{
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;
		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirX > 0)
			{
				if (env->map.tile[y1][x2] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y1][x2] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y1][x2] = 0;
				}
				else if (env->map.tile[y2][x2] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y2][x2] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y2][x2] = 0;
				}
				if (env->map.tile[y1][x2] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y1][x2] += 1;
				}
				else if (env->map.tile[y2][x2] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y2][x2] += 1;
				}
				if (env->map.tile[y1][x2] > BLANK_TILE || env->map.tile[y2][x2] >
				BLANK_TILE)
				{
					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;
				}
			}
			else if (entity->dirX < 0)
			{
				if (env->map.tile[y1][x1] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y1][x1] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y1][x1] = 0;
				}
				else if (env->map.tile[y2][x1] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y2][x1] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y2][x1] = 0;
				}
				if (env->map.tile[y1][x1] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y1][x1] += 1;
				}
				else if (env->map.tile[y2][x1] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y2][x1] += 1;
				}
				if (env->map.tile[y2][x1] > BLANK_TILE || env->map.tile[y2][x1]
					> BLANK_TILE)
				{
					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
				}
			}
		}
		if (i == entity->h)
			break;
		i += TILE_SIZE;
		if (i > entity->h)
			i = entity->h;
	}
	if (entity->w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->w;
	for(;;)
	{
		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;
		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i - 1) / TILE_SIZE;
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirY > 0)
			{
				if (env->map.tile[y2][x1] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y2][x1] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y2][x1] = 0;
				}
				else if (env->map.tile[y2][x2] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y2][x2] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y2][x2] = 0;
				}
				if (env->map.tile[y1][x1] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y1][x1] += 1;
				}
				else if (env->map.tile[y2][x2] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y2][x2] += 1;
				}
				if((env->map.tile[y2][x1] == TILE_RESSORT) ||
						(env->map.tile[y2][x2] == TILE_RESSORT))
				{
					entity->dirY = -20;
					entity->onGround = 1;
				}
				else if (env->map.tile[y2][x1] > BLANK_TILE || env->map.tile[y2][x2] >
				BLANK_TILE)
				{
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
					entity->onGround = 1;
				}
				if (env->jeu.nombrePlateforme > 0)
				{
					for (j = 1; j <= env->jeu.nombrePlateforme; j++)
					{
						if (entity->x + entity->w >= env->plateforme[j].x
							&& entity->x <= env->plateforme[j].x + env->plateforme[j].w
							&& entity->y + entity->h >= env->plateforme[j].y
							&& entity->y + entity->h < env->plateforme[j].y + 32)
						{
							entity->y = env->plateforme[j].y - entity->h;
							entity->dirY = 0;
							entity->onGround = 1;
							env->plateforme[j].player_dessus = 1;
						}
						else
							env->plateforme[j].player_dessus = 0;
					}
				}
			}
			else if (entity->dirY < 0)
			{
				if (env->map.tile[y1][x1] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y1][x1] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y1][x1] = 0;
				}
				else if (env->map.tile[y1][x2] >= TILE_POWER_UP_DEBUT &&
						env->map.tile[y1][x2] <= TILE_POWER_UP_FIN)
				{
					getItem(env->map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1, env);
					env->map.tile[y1][x2] = 0;
				}
				if (env->map.tile[y1][x1] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y1][x1] += 1;
				}
				else if (env->map.tile[y1][x2] == TILE_CHECKPOINT)
				{
					entity->checkpointActif = 1;
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;
					env->map.tile[y1][x2] += 1;
				}
				if (env->map.tile[y1][x1] > BLANK_TILE || env->map.tile[y1][x2]
					> BLANK_TILE)
				{
					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
				}
			}
		}
		if (i == entity->w)
			break;
		i += TILE_SIZE;
		if (i > entity->w)
			i = entity->w;
	}
	entity->x += entity->dirX;
	entity->y += entity->dirY;
	if(entity->x < 0)
		entity->x = 0;
	else if (entity->x + entity->w >= env->map.maxX)
	{
		env->jeu.level++;
		if (env->jeu.level > LEVEL_MAX)
		{
			env->jeu.level = LEVEL_MAX;
			entity->x = env->map.maxX - entity->w - 1;
		}
		else
		{
			entity->checkpointActif = 0;
			changeLevel(env);
			initializePlayer(env);
		}
	}
	if (entity->y > env->map.maxY)
		entity->timerMort = 60;
}

void		loadMap(char *name, t_game *env)
{
	int		x;
	int		y;
	FILE	*fp;

	fp = fopen(name, "rb");
	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);
		cleanup(env);
	}
	env->map.maxX = 0;
	env->map.maxY = 0;
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			fscanf(fp, "%d", &(env->map.tile[y][x]));
			if (env->map.tile[y][x] > 0)
			{
				if (x > env->map.maxX)
					env->map.maxX = x;
				if (y > env->map.maxY)
					env->map.maxY = y;
			}
		}
	}
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for(x = 0; x < MAX_MAP_X; x++)
		{
			fscanf(fp, "%d", &(env->map.tile2[y][x]));
		}
	}
	env->map.maxX = (env->map.maxX + 1) * TILE_SIZE;
	env->map.maxY = (env->map.maxY + 1) * TILE_SIZE;
	env->map.startX = 0;
	env->map.startY = 0;
	fclose(fp);
}

void		drawMap(int layer, t_game *env)
{
	int		x;
	int		y;
	int		mapX;
	int		x1;
	int		x2;
	int		mapY;
	int		y1;
	int		y2;
	int		xsource;
	int		ysource;
	int		a;

	mapX = env->map.startX / TILE_SIZE;
	x1 = (env->map.startX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
	mapY = env->map.startY / TILE_SIZE;
	y1 = (env->map.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
	if (env->map.mapTimer <= 0)
	{
		if (env->map.tileSetNumber == 0)
		{
			env->map.tileSetNumber = 1;
			env->map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}
		else
		{
			env->map.tileSetNumber = 0;
			env->map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}
	}
	else
		env->map.mapTimer--;
	if (layer == 1)
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = env->map.startX / TILE_SIZE;
			for (x = x1; x < x2; x += TILE_SIZE)
			{
				if (env->map.tile[mapY][mapX] != 0)
				{
					if (env->map.tile[mapY][mapX] == TILE_MONSTRE)
					{
						initializeMonster(mapX * TILE_SIZE, mapY * TILE_SIZE, env);
						env->map.tile[mapY][mapX] = 0;
					}
					else if (env->map.tile[mapY][mapX] >= TILE_PLATEFORME_DEBUT
							&& env->map.tile[mapY][mapX] <= TILE_PLATFORME_FIN)
					{
						initPlateforme(mapX * TILE_SIZE, mapY * TILE_SIZE,
							env->map.tile[mapY][mapX] - TILE_PLATEFORME_DEBUT + 1, env);
						env->map.tile[mapY][mapX] = 0;
					}
				}
				a = env->map.tile[mapY][mapX];
				ysource = a / 10 * TILE_SIZE;
				xsource = a % 10 * TILE_SIZE;
				if (env->map.tileSetNumber == 0)
					drawTile(env->map.tileSet, x, y, xsource, ysource, env);
				else
					drawTile(env->map.tileSetB, x, y, xsource, ysource, env);
				mapX++;
			}
			mapY++;
		}
	}
	else
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = env->map.startX / TILE_SIZE;
			for (x = x1; x < x2; x += TILE_SIZE)
			{
				if (env->map.tile2[mapY][mapX] != 0)
				{
					if (env->map.tile2[mapY][mapX] == TILE_MONSTRE)
					{
						initializeMonster(mapX * TILE_SIZE, mapY * TILE_SIZE, env);
						env->map.tile2[mapY][mapX] = 0;
					}
					else if (env->map.tile2[mapY][mapX] >= TILE_PLATEFORME_DEBUT
							&& env->map.tile2[mapY][mapX] <= TILE_PLATFORME_FIN)
					{
						initPlateforme(mapX * TILE_SIZE, mapY * TILE_SIZE,
							env->map.tile2[mapY][mapX] - TILE_PLATEFORME_DEBUT + 1, env);
						env->map.tile2[mapY][mapX] = 0;
					}
				}
				a = env->map.tile2[mapY][mapX];
				ysource = a / 10 * TILE_SIZE;
				xsource = a % 10 * TILE_SIZE;
				if (env->map.tileSetNumber == 0)
					drawTile(env->map.tileSet, x, y, xsource, ysource, env);
				else
					drawTile(env->map.tileSetB, x, y, xsource, ysource, env);
				mapX++;
			}
			mapY++;
		}
	}
}
