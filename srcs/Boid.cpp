/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:01:20 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 15:14:21 by agiraude         ###   ########.fr       */
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
	if (flock)
		this->_ruleset = &(flock->ruleset);
	else
		this->_ruleset = NULL;
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
	if (flock)
		this->_ruleset = &(flock->ruleset);
	else
		this->_ruleset = NULL;
}

unsigned int Boid::getId(void) const
{
	return this->_id;
}

void	Boid::setId(unsigned int id)
{
	this->_id = id;
}

void	Boid::_keepWithinBounds(void)
{
	double	turnFactor = this->_ruleset->getTurn();

	if (this->_pos.getX() < this->_ruleset->getMinX())
		this->_dir.setX(this->_dir.getX() + turnFactor);
	if (this->_pos.getX() > this->_ruleset->getMaxX())
		this->_dir.setX(this->_dir.getX() - turnFactor);
	if (this->_pos.getY() < this->_ruleset->getMinY())
		this->_dir.setY(this->_dir.getY() + turnFactor);
	if (this->_pos.getY() > this->_ruleset->getMaxY())
		this->_dir.setY(this->_dir.getY() - turnFactor);
}

void	Boid::_limitSpeed(void)
{
	double	speed = this->_dir.getVel();

	if (speed > this->_ruleset->getSpeedL())
		this->_dir = (this->_dir / speed) * this->_ruleset->getSpeedL();
}

void	Boid::_baseRules(void)
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

			if (dist < this->_ruleset->getMinD())
			{
				avoid += (this->_pos - neighPos);
			}
			if (dist < this->_ruleset->getViewR())
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
		this->_dir += ((avgPos - this->_pos) * this->_ruleset->getCenter());
		avgDir /= nbNear;
		this->_dir += ((avgDir - this->_dir) * this->_ruleset->getMatch());
	}
	this->_dir += (avoid * this->_ruleset->getAvoid());
}

void	Boid::update(void)
{
	this->_baseRules();
	this->_limitSpeed();
	this->_keepWithinBounds();
	this->_applyDir();
}

void	Boid::_applyDir(void)
{
	this->_pos += this->_dir;
}

void	boidThreadUpdate(int threadId, Boid *boid)
{
	boid->update();
}

std::ostream &	operator<<(std::ostream & o, Boid const & rhs)
{
	o << "B" << rhs.getId() << ": " << rhs.getPos() << " " << rhs.getDir() << rhs.getDir().getVel();
	return o;
}

