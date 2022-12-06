
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prey.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:31:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 08:58:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Prey.hpp"

Prey::Prey(unsigned int id, Flock& flock) : ABoid(id, flock)
{
}

Prey::Prey(Prey const & src) : ABoid(src)
{
	*this = src;
}

Prey::~Prey(void) {}

Prey & Prey::operator=(Prey const & rhs)
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

void	Prey::_baseRules(void)
{
	Coord			avgPos(0., 0.);
	Coord			avoid(0., 0.);
	Coord			avgDir(0., 0.);
	unsigned int	nbNear = 0;
	size_t			flockSize = this->_flock.size();

	for (size_t i = 0; i < flockSize; i++)
	{
		if (i != this->_id)
		{
			Coord const &	neighPos = this->_flock[i].getPos();
			double			dist = this->_pos.getDist(neighPos);

			if (dist < this->_ruleset.getMinD())
			{
				avoid += (this->_pos - neighPos);
			}
			if (dist < this->_ruleset.getViewR())
			{
				avgPos += neighPos;
				avgDir += this->_flock[i].getDir();
				nbNear++;
			}
		}
	}
	Flock*	target = this->_flock.getTarget();
	Coord	avgTarget;	
	unsigned int	nbTarget = 0;
	if (target)
	{
		for (size_t i = 0; i < target->size(); i++)
		{
			Coord const&	 targetPos = (*target)[i].getPos();
			double			dist = this->_pos.getDist(targetPos);
			if (dist < this->_ruleset.getViewR())
			{
				avgTarget += targetPos;
				nbTarget++;
			}
		}
	}
	if (nbNear)
	{
		avgPos /= nbNear;
		this->_dir += ((avgPos - this->_pos) * this->_ruleset.getCenter());
		avgDir /= nbNear;
		this->_dir += ((avgDir - this->_dir) * this->_ruleset.getMatch());
	}
	if (nbTarget)
	{
		avgTarget /= nbTarget;
		this->_dir -= ((avgTarget - this->_pos) * this->_ruleset.getCenter() * 2.);
	}
	this->_dir += (avoid * this->_ruleset.getAvoid());
}
