/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuleSet.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:26 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 15:28:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RuleSet.hpp"
#include "Setting.hpp"

RuleSet::RuleSet(void)
: _centering(0.005), _matching(0.05), _avoiding(0.05), _turning(1.0),
_minDist(10.0), _viewRange(75.0), _speedLimit(10.0)
{
	int	margin = g_set.getSetInt("screen_margin");

	this->_setBorders(margin, margin,
			g_set.getSetInt("screen_width") - margin,
			g_set.getSetInt("screen_height") - margin);
}

RuleSet::RuleSet(double c, double m, double a, double t, double md, double vr,
		double sl, int nX, int nY, int xX, int xY)
: _centering(c), _matching(m), _avoiding(a), _turning(t), _minDist(md),
_viewRange(vr), _speedLimit(sl)
{
	this->_setBorders(nX, nY, xX, xY);
}

RuleSet::RuleSet(RuleSet const & src)
{
	*this = src;
}

RuleSet::~RuleSet(void)
{
}

RuleSet & RuleSet::operator=(RuleSet const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_centering = rhs._centering;
	this->_matching = rhs._matching;
	this->_avoiding = rhs._avoiding;
	this->_turning = rhs._turning;
	this->_minDist = rhs._minDist;
	this->_viewRange = rhs._viewRange;
	this->_speedLimit = rhs._speedLimit;
	return *this;
}

void	RuleSet::_setBorders(int minX, int minY, int maxX, int maxY)
{
	this->_minX = minX;
	this->_minY = minY;
	this->_maxX = maxX;
	this->_maxY = maxY;
}
