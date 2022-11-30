/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 12:27:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Sky.hpp"
#include "Boid.hpp"
#include "Flock.hpp"
#include "utils.hpp"
#include "conf.hpp"
#include <SDL2/SDL.h>

ctpl::thread_pool	g_thPool;
Setting				g_set;

int main(void)
{
	Scene				sc;
	SDL_Event			event;
	Sky					sky;

	g_thPool.resize(4);
	g_set.loadFile(".conf");
	if (g_set.getSetBool("print_settings"))
		std::cout << g_set << std::endl;

	sky.addFlock(500, 255, 0, 0);
	sky.addFlock(300, 0, 255, 0);
	sky.addFlock(150);

	//for(int i = 0; i < 1000; i++)
	for(;;)
	{
		sky.update();
		sc.render(sky);
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
	
	if (SHOW_AVGFPSATEND)
		std::cout << "AvgFps: " << sc.getAvgFps() << std::endl;
	return (0);
}
