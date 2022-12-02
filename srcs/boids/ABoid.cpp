/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABoid.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:01:20 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 10:34:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABoid.hpp"
#include "Flock.hpp"
#include <unistd.h>

ABoid::ABoid(void)
: _id(0), _pos(Coord(0., 0.)), _dir(Coord(0., 0.)), _flock(NULL)
{
}

ABoid::ABoid(unsigned int id)
: _id(id), _pos(Coord(0., 0.)), _dir(Coord(0., 0.)), _flock(NULL)
{
}

ABoid::ABoid(unsigned int id, Flock *flock)
: _id(id), _pos(Coord(0., 0.)), _dir(Coord(0., 0.)), _flock(flock)
{
	if (flock)
		this->_ruleset = &(flock->ruleset);
	else
		this->_ruleset = NULL;
}

ABoid::ABoid(ABoid const & src)
{
	*this = src;
}

ABoid::~ABoid(void)
{
}

ABoid & ABoid::operator=(ABoid const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_dir = rhs._dir;
	this->_pos = rhs._pos;
	this->_id = rhs._id;
	this->_flock = rhs._flock;
	this->_ruleset = rhs._ruleset;
	return *this;
}

void	ABoid::_keepWithinBounds(void)
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

void	ABoid::_limitSpeed(void)
{
	double	speed = this->_dir.getVel();

	if (speed > this->_ruleset->getSpeedL())
		this->_dir = (this->_dir / speed) * this->_ruleset->getSpeedL();
}

void	ABoid::update(void)
{
	this->_baseRules();
	this->_limitSpeed();
	this->_keepWithinBounds();
	this->_applyDir();
}

void	ABoid::_applyDir(void)
{
	this->_pos += this->_dir;
}

void	boidThreadUpdate(int threadId, ABoid *boid)
{
	boid->update();
}

std::ostream &	operator<<(std::ostream & o, ABoid const & rhs)
{
	o << "B" << rhs.getId() << ": " << rhs.getPos() << " " << rhs.getDir()
		<< rhs.getDir().getVel();
	return o;
}

