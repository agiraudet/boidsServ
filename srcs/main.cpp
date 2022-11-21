/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/21 14:23:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Boid.hpp"
#include "Flock.hpp"
#include <SDL2/SDL.h>

int main(void)
{
	Flock	flock(10);

	std::cout << flock << std::endl;
	return (0);
}
/*
int main(void)
{
	Scene	sc;
	SDL_Event	event;

	Flock	flock(1);

	std::cout << flock << std::endl;

	for(;;)
	{
		sc.render();
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
*/
