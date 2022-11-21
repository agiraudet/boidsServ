/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:03:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/21 15:25:17 by agiraude         ###   ########.fr       */
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

		void			setPos(size_t id, Coord const & pos);
		size_t			size(void) const;
		Coord const &	getPos(size_t id) const;
		Boid const &	getBoid(size_t id) const;

	private:

		Flock(void);

		void	_init(void);

		std::vector<Coord>	_oldPos;
		std::vector<Coord>	_newPos;
		std::vector<Boid>	_boids;
		size_t				_size;
};

std::ostream &	operator<<(std::ostream & o, Flock const & rhs);

#endif
