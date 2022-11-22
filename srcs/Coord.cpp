/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:57:25 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/22 11:58:20 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Coord.hpp"
#include <math.h>

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

Coord	Coord::operator/(double const & rhs) const
{
	return Coord(this->_x / rhs, this->_y / rhs);
}

Coord	Coord::operator*(double const & rhs) const
{
	return Coord(this->_x * rhs, this->_y * rhs);
}

Coord	Coord::operator/(Coord const & rhs) const
{
	return Coord(this->_x / rhs._x, this->_y / rhs._y);
}

Coord	Coord::operator*(Coord const & rhs) const
{
	return Coord(this->_x * rhs._x, this->_y * rhs._y);
}

Coord &	Coord::operator/=(double const & rhs)
{
	this->_x /= rhs;
	this->_y /= rhs;
	return *this;
}

Coord &	Coord::operator*=(double const & rhs)
{
	this->_x *= rhs;
	this->_y *= rhs;
	return *this;
}

Coord &	Coord::operator/=(Coord const & rhs)
{
	this->_x /= rhs._x;
	this->_y /= rhs._y;
	return *this;
}

Coord &	Coord::operator*=(Coord const & rhs)
{
	this->_x *= rhs._x;
	this->_y *= rhs._y;
	return *this;
}

void	Coord::setXY(double x, double y)
{
	this->_x = x;
	this->_y = y;
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

double Coord::getDist(Coord const & c) const
{
	return (sqrt(pow((c.getX() - this->_x), 2) + pow((c.getY() - this->_y), 2)));
}

double	Coord::getVel(void) const
{
	return sqrt(this->_x * this->_x + this->_y * this->_y);
}

double	coordDist(Coord const & a, Coord const & b)
{
	return a.getDist(b);
}

std::ostream &	operator<<(std::ostream & o, Coord const & rhs)
{
	o << "(" << rhs.getX() << "," << rhs.getY() << ")";
	return o;
}
