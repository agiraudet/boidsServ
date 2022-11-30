/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:39:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 15:45:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Setting.hpp"
#include <SDL2/SDL.h>
#include <exception>

Scene::Scene(void)
: _scWd(g_set.getSetInt("screen_width")),
_scHg(g_set.getSetInt("screen_height")),
_fullSc(g_set.getSetBool("fullscreen")),
_maxFps(g_set.getSetInt("fps_max")), _win(NULL), _ren(NULL)
{
	std::srand(time(NULL));
	this->_initSdl();
}

Scene::Scene(int scWd, int scHg, bool fullSc)
: _scWd(scWd), _scHg(scHg), _fullSc(g_set.getSetBool("fullscreen")),
_maxFps(g_set.getSetInt("fps_max")), _win(NULL), _ren(NULL)
{
	std::srand(time(NULL));
	this->_initSdl();
}

Scene::Scene(Scene const & src)
{
	*this = src;
}

Scene::~Scene(void)
{
	SDL_DestroyRenderer(this->_ren);
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
}

Scene & Scene::operator=(Scene const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_win = rhs._win;
	this->_ren = rhs._ren;
	return *this;
}

void	Scene::_initSdl(void)
{
	Uint32	flags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::exception();
	if (this->_fullSc)
		flags = SDL_WINDOW_FULLSCREEN;
	this->_win = SDL_CreateWindow("BOIIIIDS", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, this->_scWd, this->_scHg, flags);
	this->_ren = SDL_CreateRenderer(this->_win, -1, 0);
	
	if (!this->_win || ! this->_ren)
	{
		SDL_Quit();
		throw std::exception();
	}
}

void	Scene::_render(Sky *sky) 
{
	SDL_SetRenderDrawColor(this->_ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(this->_ren);
	if (!sky)
		return;
	for (size_t i = 0; i < sky->size(); i++)
		this->_render(sky->getFlock(i));
}

void	Scene::_render(Flock *flock) 
{
	if (!flock)
		return;

	SDL_Color const &	color = flock->getColor();
	SDL_SetRenderDrawColor(this->_ren, color.r, color.g, color.b, 0);
	for (size_t i = 0; i < flock->size(); i++)
		this->_render(flock->getBoid(i));
}

void	Scene::_render(Boid *boid) 
{
	static int	boidHeight = g_set.getSetInt("boid_height");
	static int	boidWidth = g_set.getSetInt("boid_width");

	if (!boid)
		return;
	SDL_Rect		rect;
	Coord const &	boidPos = boid->getPos();
	rect.x = boidPos.getX();
	rect.y = boidPos.getY();
	rect.h = boidHeight;
	rect.w = boidWidth;
	SDL_RenderFillRect(this->_ren, &rect);
}

void	Scene::render(Sky *sky)
{
	this->_render(sky);
	SDL_RenderPresent(this->_ren);
	this->_timer.capFps(this->_maxFps);
}

double	Scene::getAvgFps(void) const
{
	return this->_timer.getAvgFps();
}
