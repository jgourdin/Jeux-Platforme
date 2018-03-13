/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 14:54:40 by jgourdin          #+#    #+#             */
/*   Updated: 2017/12/04 14:14:27 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void		updateStartMenu(t_game *env)
{
	if (env->input.down == 1)
	{
		if (env->jeu.choice == 0)
			env->jeu.choice++;
		env->input.down = 0;
	}
	if (env->input.up == 1)
	{
		if (env->jeu.choice == 1)
			env->jeu.choice--;
		env->input.up = 0;
	}
	if (env->input.enter)
	{
		if (env->jeu.choice == 0)
		{
			env->player.checkpointActif = 0;
			env->jeu.level = 1;
			initializePlayer(env);
			changeLevel(env);
			env->jeu.vies = 3;
			env->jeu.etoiles = 0;
			env->jeu.onMenu = 0;
		}
		else if (env->jeu.choice == 1)
			cleanup(env);
		env->input.enter = 0;
	}
}

void		drawStartMenu(t_game *env)
{
	char text[200];
	sprintf(text, "MY FIRST GAME MODAFUCKA");
	drawString(text, 110, 50, env);
	if (env->jeu.choice != 0)
	{
		sprintf(text, "START");
		drawString(text, 273, 200, env);
	}
	if (env->jeu.choice != 1)
	{
		sprintf(text, "QUIT");
		drawString(text, 273, 280, env);
	}
	if (env->jeu.choice == 0)
	{
		sprintf(text, "> START");
		drawString(text, 250, 200, env);
	}
	else if(env->jeu.choice == 1)
	{
		sprintf(text, "> QUIT");
		drawString(text, 250, 280, env);
	}
	sprintf(text, "Drunken Wizard corp, 2017");
	drawString(text, 120, 420, env);
}

void		updatePauseMenu(t_game *env)
{
	if (env->input.enter)
	{
		env->jeu.onMenu = 0;
		env->input.enter = 0;
	}
}

void		drawPauseMenu(t_game *env)
{
	char text[200];

	sprintf(text, "** PAUSE **");
	drawString(text, 240, 240, env);
}
