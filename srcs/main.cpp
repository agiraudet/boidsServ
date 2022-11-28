/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/28 15:40:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Sky.hpp"
#include "Boid.hpp"
#include "Flock.hpp"
#include "conf.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>

ctpl::thread_pool	g_thPool;

int main(void)
{
	Scene				sc;
	SDL_Event			event;
	Sky					sky;

	g_thPool.resize(4);

	sky.addFlock(500, 255, 0, 0);
	sky.addFlock(300, 0, 255, 0);

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
		}
	}
	
	if (SHOW_AVGFPSATEND)
		std::cout << "AvgFps: " << sc.getAvgFps() << std::endl;
	return (0);
}
