/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:57:25 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/21 16:17:16 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Coord.hpp"

Coord::Coord(void)
: _x(0.), _y(0.)
{
}

Coord::Coord(double x, double y)
: _x(x), _y(y)
{
}

Coord::Coord(Coord const & src)
{
	*this = src;
}

Coord::~Coord(void)
{
}

Coord & Coord::operator=(Coord const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_x = rhs._x;
	this->_y = rhs._y;
	return *this;
}

Coord & Coord::operator+=(Coord const & rhs)
{
	this->_x += rhs._x;
	this->_y += rhs._y;
	return *this;
}

Coord & Coord::operator-=(Coord const & rhs)
{
	this->_x -= rhs._x;
	this->_y -= rhs._y;
	return *this;
}

Coord	Coord::operator+(Coord const & rhs) const
{
	return Coord(this->_x + rhs._x, this->_y + rhs._y);
}

Coord	Coord::operator-(Coord const & rhs) const
{
	return Coord(this->_x - rhs._x, this->_y - rhs._y);
}

double Coord::getX(void) const
{
	return this->_x;
}

void	Coord::setX(double x)
{
	this->_x = x;
}

double	Coord::getY(void) const
{
	return this->_y;
}

void	Coord::setY(double y)
{
	this->_y = y;
}

void	Coord::divX(double div)
{
	if (div == 0.)
		throw std::exception();
	this->_x /= div;
}

void	Coord::divY(double div)
{
	if (div == 0.)
		throw std::exception();
	this->_y /= div;
}

void	Coord::divXY(double div)
{
	if (div == 0.)
		throw std::exception();
	this->_x /= div;
	this->_y /= div;
}

double Coord::getDist(Coord const & c)
{
	return (sqrt(pow((c.getX() - this->_x), 2) + pow((c.getY() - this->_y), 2)));
}

double	coordDist(Coord const & a, Coord const & b)
{
	return (sqrt(pow((b.getX() - a.getX()), 2) + pow((b.getY() - a.getY()), 2)));
}

std::ostream &	operator<<(std::ostream & o, Coord const & rhs)
{
	o << "(" << rhs.getX() << "," << rhs.getY() << ")";
	return o;
}
