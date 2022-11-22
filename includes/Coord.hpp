/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coord.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:56:22 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/22 11:58:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORD_HPP
# define COORD_HPP

# include <iostream>

class	Coord
{
	public:

		Coord(void);
		Coord(Coord const & src);
		Coord(double x, double y);
		~Coord(void);
		
		Coord & operator=(Coord const & rhs);
		Coord & operator+=(Coord const & rhs);
		Coord & operator-=(Coord const & rhs);
		Coord	operator+(Coord const & rhs) const;
		Coord	operator-(Coord const & rhs) const;
		Coord	operator*(double const & rhs) const;
		Coord	operator/(double const & rhs) const;
		Coord	operator*(Coord const & rhs) const;
		Coord	operator/(Coord const & rhs) const;
		Coord &	operator*=(double const & rhs);
		Coord &	operator/=(double const & rhs);
		Coord &	operator*=(Coord const & rhs);
		Coord &	operator/=(Coord const & rhs);

		void	setXY(double x, double y);
		double	getX(void) const;
		void	setX(double x);
		double	getY(void) const;
		void	setY(double y);
		double	getDist(Coord const & c) const;
		double	getVel(void) const;

	private:

		double	_x;
		double	_y;

};

std::ostream &	operator<<(std::ostream & o, Coord const & rhs);
double			coordDist(Coord const & a, Coord const & b);

#endif
