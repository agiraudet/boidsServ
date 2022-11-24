/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:03:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/24 09:01:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOCK_HPP
# define FLOCK_HPP

# include "Boid.hpp"
# include <vector>
# include <iostream>

class	Flock
{
	public:

		Flock(size_t size);
		Flock(Flock const & src);
		~Flock(void);
		
		Flock & operator=(Flock const & rhs);

		size_t			size(void) const;
		Coord const &	getPos(size_t id) const;
		Coord const &	getDir(size_t id) const;
		Boid const &	getBoid(size_t id) const;
		void			randomizePos(double const & maxX, double const & maxY);
		void			randomizeDir(double const & maxX, double const & maxY);
		void			update(void);

void	debugDraw(void);

	private:

		Flock(void);
		void	_init(void);

		std::vector<Boid>					_boids;
		size_t								_size;
};

std::ostream &	operator<<(std::ostream & o, Flock const & rhs);

#endif
