/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:03:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/24 08:50:43 by agiraude         ###   ########.fr       */
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
		double		getDist(size_t const & idA, size_t const & idB) const;
		void			processDist(void);
		void			processDist(size_t const & id);
		void			update(void);

void	debugDraw(void);

	private:

		Flock(void);
		void	_init(void);

		std::vector<Boid>	_boids;
		std::vector<std::vector<double>>	_dist;
		/*
		Boid	*_boids;
		double	**_dist;
		*/
		size_t				_size;
};

std::ostream &	operator<<(std::ostream & o, Flock const & rhs);

#endif
