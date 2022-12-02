
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Predator.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:31:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 08:58:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Predator.hpp"

Predator::Predator(void) : ABoid() {}

Predator::Predator(unsigned int id) : ABoid(id) {}

Predator::Predator(unsigned int id, Flock *flock) : ABoid(id, flock) {}

Predator::Predator(Predator const & src) {*this = src;}

Predator::~Predator(void) {}

Predator & Predator::operator=(Predator const & rhs)
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

void	Predator::_baseRules(void)
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
	/*
	if (nbNear)
	{
		avgPos /= nbNear;
		this->_dir += ((avgPos - this->_pos) * this->_ruleset->getCenter());
		avgDir /= nbNear;
		this->_dir += ((avgDir - this->_dir) * this->_ruleset->getMatch());
	}
	this->_dir += (avoid * this->_ruleset->getAvoid());
	*/
}
