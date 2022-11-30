/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:05:56 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 16:41:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Flock.hpp"
#include "utils.hpp"
#include <functional>

Flock::Flock(void)
: _size(0)
{
	this->randomizeColor();
	this->_init();
}

Flock::Flock(size_t size)
: _size(size)
{
	this->randomizeColor();
	this->_init();
}

Flock::Flock(size_t size, SDL_Color const & color)
: _size(size)
{
	this->setColor(color);
	this->_init();
}

Flock::Flock(Flock const & src)
{
	*this = src;
}

Flock::~Flock(void)
{
	for (size_t i = 0; i < this->_boids.size(); i++)
		delete this->_boids[i];
}

Flock & Flock::operator=(Flock const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_size = rhs._size;
	this->_boids = rhs._boids;
	this->setColor(rhs._color);
	this->ruleset = rhs.ruleset;
	return *this;
}

void	Flock::_init(void)
{
	for (size_t i = 0; i < this->_size; i++)
	{
		Boid	*newBoid = new Boid(i, this);
		this->_boids.push_back(newBoid);
	}
}

size_t	Flock::size(void) const
{
	return this->_size;
}

Coord const &	Flock::getPos(size_t id) const
{
	return this->_boids[id]->getPos();
}

Coord const &	Flock::getDir(size_t id) const
{
	return this->_boids[id]->getDir();
}

Boid*	Flock::getBoid(size_t id)
{
	while (id >= this->_size)
		id -= this->_size;
	while (id < 0)
		id = this->_size + id;
	return this->_boids[id];
}

Boid const &	Flock::getCBoid(size_t id) const
{
	if (id >= this->_size)
		throw std::exception();
	return *(this->_boids[id]);
}


SDL_Color const &	Flock::getColor(void) const
{
	return this->_color;
}

void	Flock::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	this->_color.r = r;
	this->_color.g = g;
	this->_color.b = b;
	this->_color.a = 0;
}

void	Flock::setColor(SDL_Color const & color)
{
	this->_color.r = color.r;
	this->_color.g = color.g;
	this->_color.b = color.b;
	this->_color.a = color.a;
}

void	Flock::randomizePos(void)
{
	for (size_t i = 0; i < this->_size; i++)
		this->_boids[i]->setPos(Coord(
					randNb(this->ruleset.getMinX(), this->ruleset.getMaxX()),
					randNb(this->ruleset.getMinY(), this->ruleset.getMaxY())));
}

void	Flock::randomizePos(double const & maxX, double const & maxY)
{
	for (size_t i = 0; i < this->_size; i++)
		this->_boids[i]->setPos(Coord(randNb(0., maxX), randNb(0., maxY)));
}

void	Flock::randomizeDir(double const & maxX, double const & maxY)
{
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_boids[i]->setDir(Coord(randNb(-maxX, maxX), randNb(-maxY, maxY)));
	}
}

void	Flock::randomizeColor(void)
{
	this->_color.r = randNb(0, 255);
	this->_color.g = randNb(0, 255);
	this->_color.b = randNb(0, 255);
	this->_color.a = 0;
}

void	Flock::update(void)
{
	static bool multiThread = g_set.getSetBool("multithreading");

	if (!multiThread)
	{
		for (size_t i = 0; i < this->_size; i++)
			this->_boids[i]->update();
	}
	else
	{
		std::vector<std::future<void>>	ftr;
		for (size_t i = 0; i < this->_size; i++)
			ftr.push_back(g_thPool.push(boidThreadUpdate, this->_boids[i]));
		for (size_t i = 0; i < ftr.size(); i++)
			ftr[i].wait();
	}
}

void	flockThreadUpdate(int threadId, Flock *flock)
{
	flock->update();
}

std::ostream &	operator<<(std::ostream & o, Flock const & rhs)
{
	size_t	fSize = rhs.size();

	o << "Flock of size " << fSize << ":" << std::endl;
	for (size_t i = 0; i < fSize; i++)
	{
		o << rhs.getCBoid(i);
		if (i < fSize - 1)
			o << std::endl;
	}
	return o;
}
