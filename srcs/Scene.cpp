/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:39:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 13:11:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Setting.hpp"
#include "cptl_stl.h"
#include "utils.hpp"
#include <SDL2/SDL.h>
#include <exception>

ctpl::thread_pool	g_thPool;
Setting				g_set;

Scene::Scene(void)
{
	std::srand(time(NULL));
	this->_initValues();
	this->_initThreads();
	this->_initSdl();
}

Scene::Scene(std::string const & confFile)
{
	std::srand(time(NULL));
	g_set.loadFile(confFile);
	this->_initValues();
	this->_initThreads();
	this->_initSdl();
}

Scene::Scene(Scene const & src)
{
	*this = src;
}

Scene::~Scene(void)
{
	if (this->_ren)
		SDL_DestroyRenderer(this->_ren);
	if (this->_win)
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

void	Scene::_initValues(void)
{
	this->_scWd = g_set.getSetInt("screen_width");
	this->_scHg = g_set.getSetInt("screen_height");
	this->_fullSc = g_set.getSetBool("fullscreen");
	this->_maxFps = g_set.getSetInt("fps_max");
	this->_win = NULL;
	this->_ren = NULL;
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

void	Scene::_initThreads(void)
{
	int	nbThread = std::thread::hardware_concurrency();

	if (g_set.getSetBool("force_nb_thread") && g_set.setExist("nb_thread"))
		nbThread = g_set.getSetInt("nb_thread");
	g_thPool.resize(nbThread);
	if (g_set.getSetBool("debug_thread"))
		std::cout << "ThreadPool size: " << nbThread << std::endl;
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

void	Scene::_render(ABoid *boid) 
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

void	Scene::reload(void)
{
	if (this->_ren)
		SDL_DestroyRenderer(this->_ren);
	if (this->_win)
		SDL_DestroyWindow(this->_win);
	SDL_Quit();
	this->_initValues();
	this->_initThreads();
	this->_initSdl();
}

void	Scene::reloadConf(std::string const & confFile)
{
	g_set.loadFile(confFile);
	this->reload();
}

void	Scene::mainLoop(Sky& sky)
{
	SDL_Event	event;
	int			nbCycle = g_set.getSetInt("nb_cycle");

	for (int i = 0; i != nbCycle; i++)
	{
		sky.update();
		this->render(&sky);
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			break;
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_q:
					i = nbCycle - 1;
					break;
				case SDLK_a:
					sky.addFlock(randNb(50, 500));
					break;
				case SDLK_s:
					sky.delFlock(-1);
					break;
			}
		}
	}
	if (g_set.getSetBool("debug_fps_atexit"))
		std::cout << "AvgFps: " << this->getAvgFps() << std::endl;
}
