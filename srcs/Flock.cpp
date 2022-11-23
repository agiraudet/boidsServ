/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:05:56 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/23 14:09:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Flock.hpp"
#include "utils.hpp"

Flock::Flock(void)
: _size(0)
{
	this->_init();
}

Flock::Flock(size_t size)
: _size(size)
{
	this->_init();
}

Flock::Flock(Flock const & src)
{
	*this = src;
}

Flock::~Flock(void)
{
}

Flock & Flock::operator=(Flock const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_size = rhs._size;
	this->_oldPos = rhs._oldPos;
	this->_oldDir = rhs._oldDir;
	this->_boids = rhs._boids;
	return *this;
}

void	Flock::_init(void)
{
	for (size_t i = 0; i < this->_size; i++)
	{
		Boid	newBoid(i, this);

		//DEBUG
		newBoid.setPos(Coord(50, 50));

		this->_oldPos.push_back(newBoid.getPos());
		this->_oldDir.push_back(newBoid.getDir());
		this->_boids.push_back(newBoid);
	}
}

size_t	Flock::size(void) const
{
	return this->_size;
}

Coord const &	Flock::getPos(size_t id) const
{
	if (id >= this->_size)
		throw std::exception();
	return this->_boids[id].getPos();
}

Coord const &	Flock::getDir(size_t id) const
{
	if (id >= this->_size)
		throw std::exception();
	return this->_boids[id].getDir();
}

Boid const &	Flock::getBoid(size_t id) const
{
	if (id >= this->_size)
		throw std::exception();
	return this->_boids[id];
}

void	Flock::randomizePos(double const & maxX, double const & maxY)
{
	for (size_t i = 0; i < this->_size; i++)
		this->_boids[i].setPos(Coord(randDouble(0., maxX), randDouble(0., maxY)));
}

void	Flock::randomizeDir(double const & maxX, double const & maxY)
{
	for (size_t i = 0; i < this->_size; i++)
	{
		this->_boids[i].setDir(Coord(randDouble(-maxX, maxX), randDouble(-maxY, maxY)));
	}
}

void	Flock::update(void)
{
	for (size_t i = 0; i < this->_size; i++)
		this->_boids[i].live();
	for (size_t i = 0; i < this->_size; i++)
		this->_boids[i].applyDir();
}

std::ostream &	operator<<(std::ostream & o, Flock const & rhs)
{
	size_t	fSize = rhs.size();

	o << "Flock of size " << fSize << ":" << std::endl;
	for (size_t i = 0; i < fSize; i++)
	{
		o << rhs.getBoid(i);
		if (i < fSize - 1)
			o << std::endl;
	}
	return o;
}
