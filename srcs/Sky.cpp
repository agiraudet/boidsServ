/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sky.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:25:24 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/28 15:43:06 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sky.hpp"
#include "conf.hpp"

Sky::Sky(void)
{
}

Sky::Sky(Sky const & src)
{
	*this = src;
}

Sky::~Sky(void)
{
	for (size_t i = 0; i < this->_flocks.size(); i++)
		delete this->_flocks[i];
}

Sky & Sky::operator=(Sky const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_flocks = rhs._flocks;
	return *this;
}
void	Sky::addFlock(size_t size)
{
	Flock	*newFlock = new Flock(size);

	this->_randomizeFlock(*newFlock);
	newFlock->randomizeColor();
	this->_flocks.push_back(newFlock);
}

void	Sky::addFlock(size_t size, Uint8 r, Uint8 g, Uint8 b)
{
	Flock	*newFlock = new Flock(size);

	this->_randomizeFlock(*newFlock);
	newFlock->setColor(r, g, b);
	this->_flocks.push_back(newFlock);
}

void	Sky::addFlock(size_t size, SDL_Color const & color)
{
	Flock	*newFlock = new Flock(size, color);

	this->_randomizeFlock(*newFlock);
	this->_flocks.push_back(newFlock);
}

void	Sky::_randomizeFlock(Flock & flock)
{
	flock.randomizePos(DFLT_SCWD - BS_WD, DFLT_SCHG - BS_HG);
	flock.randomizeDir(10., 10.);
}

void	Sky::delFlock(size_t id)
{
	if (id < this->_flocks.size())
		this->_flocks.erase(this->_flocks.begin() + id);
}

size_t	Sky::size(void) const
{
	return this->_flocks.size();
}

void	Sky::update(void)
{
	//TODO add multithreading here
	for (size_t i = 0; i < this->_flocks.size(); i++)
		this->_flocks[i]->update();
}

void	Sky::render(SDL_Renderer *ren) const
{
	if (!ren)
		return ;
	for (size_t i = 0; i < this->_flocks.size(); i++)
		this->_flocks[i]->render(ren);
}
