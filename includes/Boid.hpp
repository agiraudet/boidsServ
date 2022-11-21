/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:54:55 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/21 15:56:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOID_HPP
# define BOID_HPP

# include "Coord.hpp"
# include <iostream>

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
		void			ruleOne(void);
		void			live(void);

	private:

		unsigned int	_id;
		Coord			_pos;
		Coord			_dir;
		Flock			*_flock;

};

std::ostream &	operator<<(std::ostream & o, Boid const & rhs);

#endif
