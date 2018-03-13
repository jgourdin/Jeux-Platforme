/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:42:41 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 17:50:08 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		saveMap(char *name, t_game *env)
{
	int		x;
	int		y;
	FILE	*fp;

	fp = fopen(name, "wb");

	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);
		cleanup(env);
	}
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for(x = 0; x < MAX_MAP_X; x++)
		{
			fprintf(fp,"%d ", env->map.tile[y][x]);
		}
		fprintf(fp, "\n");
	}
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			fprintf(fp, "%d ", env->map.tile2[y][x]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void		reinitMap(char *name, t_game *env)
{
	int		x;
	int		y;
	FILE	*fp;

	fp = fopen(name, "wb+");
	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);
		cleanup(env);
	}
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
			fprintf(fp, "0 ");
		fprintf(fp, "\n");
	}
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
			fprintf(fp, "0 ");
		fprintf(fp, "\n");
	}
	fclose(fp);
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
		for (x = 0; x < MAX_MAP_X; x++)
			fscanf(fp, "%d", &(env->map.tile2[y][x]));
	}
	env->map.maxX = MAX_MAP_X * TILE_SIZE;
	env->map.maxY = MAX_MAP_Y * TILE_SIZE;
	env->map.startX = 0;
	env->map.startY = 0;
	fclose(fp);
}

void		drawMap(t_game *env)
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
	
	if (env->input.layerDrawn == 1 || env->input.layerDrawn == 3)
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = env->map.startX / TILE_SIZE;
			for (x = x1; x < x2; x += TILE_SIZE)
			{
				a = env->map.tile[mapY][mapX];
				ysource = a / 10 * TILE_SIZE;
				xsource = a % 10 * TILE_SIZE;
				drawTile(env, x, y, xsource, ysource);
				mapX++;
			}
			mapY++;
		}
	}
	mapX = env->map.startX / TILE_SIZE;
	mapY = env->map.startY / TILE_SIZE;
	if (env->input.layerDrawn == 2 || env->input.layerDrawn == 3)
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = env->map.startX / TILE_SIZE;
			for (x = x1; x < x2; x += TILE_SIZE)
			{
				a = env->map.tile2[mapY][mapX];
				ysource = a / 10 * TILE_SIZE;
				xsource = a % 10 * TILE_SIZE;
				drawTile(env, x, y, xsource, ysource);
				mapX++;
			}
			mapY++;
		}
	}
	ysource = env->cursor.tileID / 10 * TILE_SIZE;
	xsource = env->cursor.tileID % 10 * TILE_SIZE;
	drawTile(env, env->cursor.x, env->cursor.y, xsource, ysource);
}
