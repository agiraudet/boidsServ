/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:01:20 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/21 16:44:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boid.hpp"
#include "Flock.hpp"
#include <unistd.h>

Boid::Boid(void)
: _id(0), _pos(Coord(0., 0.)), _dir(Coord(0., 0.)), _flock(NULL)
{
}

Boid::Boid(unsigned int id)
: _id(id), _pos(Coord(0., 0.)), _dir(Coord(0., 0.)), _flock(NULL)
{
}

Boid::Boid(unsigned int id, Flock *flock)
: _id(id), _pos(Coord(0., 0.)), _dir(Coord(0., 0.)), _flock(flock)
{
}

Boid::Boid(unsigned int id, Coord pos)
: _id(id), _pos(pos), _dir(Coord(0., 0.)), _flock(NULL)
{
}

Boid::Boid(unsigned int id, Coord pos, Coord dir)
: _id(id), _pos(pos), _dir(dir), _flock(NULL)
{
}

Boid::Boid(Boid const & src)
{
	*this = src;
}

Boid::~Boid(void)
{
}

Boid & Boid::operator=(Boid const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_dir = rhs._dir;
	this->_pos = rhs._pos;
	this->_id = rhs._id;
	this->_flock = rhs._flock;
	return *this;
}

Coord const &	Boid::getPos(void) const
{
	return this->_pos;
}

void	Boid::setPos(Coord const & pos)
{
	this->_pos = pos;
}

Coord const &	Boid::getDir(void) const
{
	return this->_dir;
}

void	Boid::setDir(Coord const & dir)
{
	this->_dir = dir;
}

void	Boid::setFlock(Flock *flock)
{
	this->_flock =  flock;
}

unsigned int Boid::getId(void) const
{
	return this->_id;
}

void	Boid::setId(unsigned int id)
{
	this->_id = id;
}

bool	Boid::canSee(Boid const & neighbour) const
{
	return (this->_pos.getDist(neighbour.getPos()) < BOID_VIEWRANGE);
}

void	Boid::scan(void)
{
	Coord			r1, r2, r3;
	unsigned int	nbNeighbour = 0;

	for (size_t i = 0; i < this->_flock->size(); i++)
	{
		if (i != this->_id)
		{
			Boid const &	neighbour = this->_flock->getBoid(i);
			double			neighDist = this->_pos.getDist(neighbour.getPos());

			if (neighDist < BOID_VIEWRANGE)
			{
				r1 += neighbour.getPos();
				r3 += neighDist.getDir();
				nbNeighbour++;
			}
			if (neighDist < BOID_CLOSENESS)
			{
				r2 -= (this->_pos - neighbour.getPos());
			}





		}
	}
	if (nbNeighbour > 0)
	{
		r1 / static_cast<double>(nbNeighbour);
		r1 = (r1 - this->_pos) / BOID_R1SPEED;
		r3 / static_cast<double>(nbNeighbour);
		r3 = (r3 - 
	}

}

void	Boid::live(void)
{
	for (;;)
	{
		usleep(10);
	}
}

std::ostream &	operator<<(std::ostream & o, Boid const & rhs)
{
	o << "B" << rhs.getId() << rhs.getPos();
	return o;
}
