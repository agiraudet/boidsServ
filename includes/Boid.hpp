/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:54:55 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/22 16:17:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOID_HPP
# define BOID_HPP

# include "Coord.hpp"
# include <iostream>
# include <vector>

class	Flock;

class	Boid
{
	public:

		Boid(void);
		Boid(unsigned int id);
		Boid(unsigned int id, Flock *flock);
		Boid(unsigned int id, Coord pos);
		Boid(unsigned int id, Coord pos, Coord dir);
		Boid(Boid const & src);
		~Boid(void);
		
		Boid & operator=(Boid const & rhs);

		unsigned int	getId(void) const;
		void			setId(unsigned int id);
		Coord const &	getPos(void) const;
		void			setPos(Coord const & pos);
		Coord const &	getDir(void) const;
		void			setDir(Coord const & dir);
		void			setFlock(Flock *flock);
		void			live(void);
		void	limitSpeed(void);
void	applyDir(void);

	private:

		void	lookAround(void);
		void	flyTowardCenter(void);
		void	avoidOthers(void);
		void	matchVelocity(void);
		void	keepWithinBounds(void);
		void	_initOtherBoids(void);

		unsigned int	_id;
		Coord			_pos;
		Coord			_dir;
		std::vector<double>	_otherBoids;
		Flock			*_flock;

};

std::ostream &	operator<<(std::ostream & o, Boid const & rhs);

#endif
