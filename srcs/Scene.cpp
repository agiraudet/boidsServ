/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:39:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/22 11:12:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "conf.hpp"
#include <SDL2/SDL.h>
#include <exception>

Scene::Scene(void)
: _scWd(DFLT_SCWD), _scHg(DFLT_SCHG), _fullSc(false), _maxFps(DFLT_MAXFPS), _win(NULL), _ren(NULL)
{
	this->_initSdl();
}

Scene::Scene(int scWd, int scHg, bool fullSc)
: _scWd(scWd), _scHg(scHg), _fullSc(fullSc), _maxFps(DFLT_MAXFPS), _win(NULL), _ren(NULL)
{
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
	Uint32	flags;

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

void	Scene::_renderSingleBoid(Boid const & boid)
{
	SDL_Rect		rect;
	Coord const &	boidPos = boid.getPos();

	rect.x = boidPos.getX();
	rect.y = boidPos.getY();
	rect.h = BS_HG;
	rect.w = BS_WD;
	SDL_SetRenderDrawColor(this->_ren, BC_R, BC_G, BC_B, 0x00);
	SDL_RenderFillRect(this->_ren, &rect);
}

void	Scene::render(Flock *flock)
{
	SDL_SetRenderDrawColor(this->_ren, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(this->_ren);

	if (flock)
	{
		for (size_t i = 0; i < flock->size(); i++)
		{
			this->_renderSingleBoid(flock->getBoid(i));
		}
	}

	SDL_RenderPresent(this->_ren);
	this->_timer.capFps(this->_maxFps);
}
