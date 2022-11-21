/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:05:56 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/21 15:57:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Flock.hpp"

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
	this->_newPos = rhs._newPos;
	this->_boids = rhs._boids;
	return *this;
}

void	Flock::_init(void)
{
	for (size_t i = 0; i < this->_size; i++)
	{
		Boid	newBoid(i, this);

		this->_oldPos.push_back(newBoid.getPos());
		this->_newPos.push_back(newBoid.getPos());
		this->_boids.push_back(newBoid);
	}
}

size_t	Flock::size(void) const
{
	return this->_size;
}

void Flock::setPos(size_t id, Coord const & pos)
{
	if (id >= this->_size)
		throw std::exception();
	this->_newPos[id] = pos;
}

Coord const &	Flock::getPos(size_t id) const
{
	if (id >= this->_size)
		throw std::exception();
	return this->_oldPos[id];
}

Boid const &	Flock::getBoid(size_t id) const
{
	if (id >= this->_size)
		throw std::exception();
	return this->_boids[id];
}

std::ostream &	operator<<(std::ostream & o, Flock const & rhs)
{
	size_t	fSize = rhs.size();

	o << "Flock of size " << fSize << ":" << std::endl;
	for (size_t i = 0; i < fSize; i++)
	{
		o << rhs.getBoid(i);
		if (i < fSize - 1)
			o << ", ";
	}
	return o;
}
