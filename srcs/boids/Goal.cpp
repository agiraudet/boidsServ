/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Goal.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:31:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 14:53:21 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Goal.hpp"

Goal::Goal(unsigned int id, Flock& flock) : ABoid(id, flock) {}

Goal::Goal(Goal const & src) : ABoid(src) {*this = src;}

Goal::~Goal(void) {}

Goal & Goal::operator=(Goal const & rhs)
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

void	Goal::_baseRules(void)
{
	this->_dir = Coord(0., 0.);
}
