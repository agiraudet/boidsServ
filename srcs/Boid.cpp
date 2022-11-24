/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:01:20 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/23 21:51:37 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boid.hpp"
#include "Flock.hpp"
#include "conf.hpp"
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

void	Boid::keepWithinBounds(void)
{
	if (this->_pos.getX() < MARGIN)
		this->_dir.setX(this->_dir.getX() + BOID_TURNFACTOR);
	if (this->_pos.getX() > DFLT_SCWD - MARGIN)
		this->_dir.setX(this->_dir.getX() - BOID_TURNFACTOR);
	if (this->_pos.getY() < MARGIN)
		this->_dir.setY(this->_dir.getY() + BOID_TURNFACTOR);
	if (this->_pos.getY() > DFLT_SCHG - MARGIN)
		this->_dir.setY(this->_dir.getY() - BOID_TURNFACTOR);
}

void	Boid::flyTowardCenter(void)
{
	Coord			center(0., 0.);
	unsigned int	nbNeighbour = 0;

	for (size_t i = 0; i < this->_flock->size(); i++)
	{
		if (i != this->_id && this->_flock->getDist(i, this->_id) < BOID_VIEWRANGE)
		{
			center += this->_flock->getPos(i);
			nbNeighbour++;
		}
	}
	if (nbNeighbour)
	{
		center /= nbNeighbour;
		this->_dir += ((center - this->_pos) * BOID_CENTERINGFACTOR);
	}
}

void	Boid::avoidOthers(void)
{
	Coord	avoid(0., 0.);

	for (size_t i = 0; i < this->_flock->size(); i++)
	{
		if (i != this->_id && this->_flock->getDist(i, this->_id) < BOID_MINDIST)
			avoid += (this->_pos - this->_flock->getPos(i));
	}
	this->_dir += (avoid * BOID_AVOIDFACTOR);
}

void	Boid::matchVelocity(void)
{
	Coord			avg(0., 0.);
	unsigned int	nbNeighbour = 0;

	for (size_t i = 0; i < this->_flock->size(); i++)
	{
		if (i != this->_id && this->_flock->getDist(i, this->_id) < BOID_VIEWRANGE)
		{
			avg += this->_flock->getDir(i);
			nbNeighbour++;
		}
	}
	if (nbNeighbour)
	{
		avg /= static_cast<double>(nbNeighbour);
		this->_dir += ((avg - this->_dir) * BOID_MATCHINGFACTOR);
	}
}

void	Boid::limitSpeed(void)
{
	double	speed = this->_dir.getVel();

	if (speed > BOID_SPEEDLIMIT)
		this->_dir = (this->_dir / speed) * BOID_SPEEDLIMIT;
}

void	Boid::update(void)
{
	Coord			avgPos(0., 0.);
	Coord			avoid(0., 0.);
	Coord			avgDir(0., 0.);
	unsigned int	nbNear = 0;
	size_t			flockSize = this->_flock->size();

	for (size_t i = 0; i < flockSize; i++)
	{
		if (i != this->_id)
		{
			Coord const &	neighPos = this->_flock->getPos(i);
			double			dist = this->_pos.getDist(neighPos);

			if (dist < BOID_MINDIST)
			{
				avoid += (this->_pos - neighPos);
			}
			if (dist < BOID_VIEWRANGE)
			{
				avgPos += neighPos;
				avgDir += this->_flock->getDir(i);
				nbNear++;
			}
		}
	}
	if (nbNear)
	{
		avgPos /= nbNear;
		this->_dir += ((avgPos - this->_pos) * BOID_CENTERINGFACTOR);
		avgDir /= nbNear;
		this->_dir += ((avgDir - this->_dir) * BOID_MATCHINGFACTOR);
	}
	this->_dir += (avoid * BOID_AVOIDFACTOR);
}

void	Boid::loop(void)
{
	this->update();
	this->limitSpeed();
	this->keepWithinBounds();
	this->applyDir();
}

void	Boid::live(void)
{
	this->flyTowardCenter();
	this->avoidOthers();
	this->matchVelocity();
	this->limitSpeed();
	this->keepWithinBounds();
}

void	Boid::applyDir(void)
{
	this->_pos += this->_dir;
}

std::ostream &	operator<<(std::ostream & o, Boid const & rhs)
{
	o << "B" << rhs.getId() << ": " << rhs.getPos() << " " << rhs.getDir() << rhs.getDir().getVel();
	return o;
}
