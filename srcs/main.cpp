/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 15:59:17 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Sky.hpp"
#include "Boid.hpp"
#include "Flock.hpp"
#include "utils.hpp"
#include "Setting.hpp"
#include <SDL2/SDL.h>

ctpl::thread_pool	g_thPool;
Setting				g_set;

void	init(void)
{
	g_set.loadFile(".conf");
	if (g_set.getSetBool("print_settings"))
		std::cout << g_set << std::endl;
	int	nbThread;
	if (g_set.getSetBool("force_nb_thread"))
		nbThread = g_set.getSetInt("nb_thread");
	else
		nbThread = std::thread::hardware_concurrency();
	g_thPool.resize(nbThread);
	if (g_set.getSetBool("debug_thread"))
		std::cout << "ThreadPool resized: " << nbThread << std::endl;
}

int main(void)
{
	init();

	Scene				sc;
	SDL_Event			event;
	Sky					sky;

	sky.addFlock(500, 255, 0, 0);
	sky.addFlock(300, 0, 255, 0);
	sky.addFlock(150);

	int	nbCycle = g_set.getSetInt("nb_cycle");
	for(int i = 0; i != nbCycle; i++)
	{
		sky.update();
		sc.render(&sky);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_q)
				break;
			else if (event.key.keysym.sym == SDLK_a)
				sky.addFlock(randNb(50, 500));
			else if (event.key.keysym.sym == SDLK_s)
				sky.delFlock(-1);
		}
	}
	
	if (g_set.getSetBool("debug_fps_atexit"))
		std::cout << "AvgFps: " << sc.getAvgFps() << std::endl;
	return (0);
}
