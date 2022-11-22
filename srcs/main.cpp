/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/22 16:25:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Boid.hpp"
#include "Flock.hpp"
#include "conf.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>

int main(void)
{
	Scene	sc;
	SDL_Event	event;

	Flock	flock(500);
	flock.randomizePos(DFLT_SCWD - BS_WD, DFLT_SCHG - BS_HG);
	flock.randomizeDir(10., 10.);


	for(;;)
	{
		flock.update();
//		std::cout << flock << std::endl;
		sc.render(&flock);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_q)
				break;
		}
	}
	return (0);
}
