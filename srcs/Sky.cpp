/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sky.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:25:24 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 13:06:22 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sky.hpp"

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

Flock &	Sky::operator[](int i) const
{
	return *(this->_flocks[loopIndex(i, static_cast<int>(this->_flocks.size()))]);
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

void	Sky::addFlock(size_t size, std::string type, Uint8 r, Uint8 g, Uint8 b)
{
	Flock	*newFlock = new Flock(size, type);

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

void	Sky::addFlock(Flock& flock)
{
	Flock	*newFlock = new Flock(flock);

	this->_flocks.push_back(newFlock);
}

void	Sky::_randomizeFlock(Flock & flock)
{
	flock.randomizePos();
	flock.randomizeDir(10., 10.);
}

void	Sky::delFlock(int id)
{
	if (id < 0)
		id = this->_flocks.size() + id;
	if (id >= 0 && id < static_cast<int>(this->_flocks.size()))
		this->_flocks.erase(this->_flocks.begin() + id);
}

void	Sky::update(void)
{
	bool	singleThread = true;

	if (singleThread)
	{
		for (size_t i = 0; i < this->_flocks.size(); i++)
			this->_flocks[i]->update();
	}
	else
	{
		std::vector<std::future<void>>	ftr;
		for (size_t i = 0; i < this->_flocks.size(); i++)
			ftr.push_back(g_thPool.push(flockThreadUpdate, this->_flocks[i]));
		for (size_t i = 0; i < ftr.size(); i++)
			ftr[i].wait();
	}
}
