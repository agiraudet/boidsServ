/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:17:06 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 15:47:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Timer.hpp"
#include "Setting.hpp"
#include <iostream>
#include <time.h>
#include <SDL2/SDL.h>

Timer::Timer(void)
: _initTime(SDL_GetTicks()), _relativeTime(0), _frames(0), _avgFps(0)
{
}

Timer::Timer(Timer const & src)
{
	*this = src;
}

Timer::~Timer(void)
{
}

Timer & Timer::operator=(Timer const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_initTime = rhs._initTime;
	this->_relativeTime = rhs._relativeTime;
	this->_frames = rhs._frames;
	this->_avgFps = rhs._avgFps;
	return *this;
}

void	Timer::_update(void)
{
	this->_relativeTime = SDL_GetTicks() - this->_initTime;
	this->_frames++;
	if (this->_frames > 200000)
		this->_frames = 0;
	this->_avgFps = this->_frames / (this->_relativeTime / 1000.);
}

void	Timer::capFps(int & maxFps)
{
	static bool	capFps = g_set.getSetBool("cap_fps");

	int	framesTicks = SDL_GetTicks() - this->_initTime - this->_relativeTime;
	if (capFps && framesTicks < 1000 / maxFps)
		SDL_Delay(1000 / maxFps - framesTicks);
	this->_update();
	if (g_set.getSetBool("debug_fps"))
		std::cout << this->_avgFps << std::endl;
}

double	Timer::getAvgFps(void) const
{
	return this->_avgFps;
}
