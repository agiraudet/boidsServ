/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABoid.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:54:55 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 13:09:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOID_HPP
# define BOID_HPP

# include "Coord.hpp"
# include "RuleSet.hpp"
# include "Flock.hpp"
# include <iostream>
# include <vector>


class	ABoid
{
	public:
		ABoid(unsigned int id, Flock& flock);
		ABoid(ABoid const & src);
		virtual ~ABoid(void);
		
		ABoid & operator=(ABoid const & rhs);
		void			update(void);

	public:
		inline unsigned int		getId(void) const			{return this->_id;}
		inline void				setId(unsigned int id)		{this->_id = id;}
		inline Coord const &	getPos(void) const			{return this->_pos;}
		inline void				setPos(Coord const & pos)	{this->_pos = pos;}
		inline Coord const &	getDir(void) const			{return this->_dir;}
		inline void				setDir(Coord const & dir)	{this->_dir = dir;}

	protected:
		virtual void	_baseRules(void) = 0;
		void			_applyDir(void);
		void			_keepWithinBounds(void);
		void			_limitSpeed(void);

		unsigned int	_id;
		Coord			_pos;
		Coord			_dir;
		Flock&	_flock;
		RuleSet&	_ruleset;
	
	private:
		ABoid(void);
		
};

void			boidThreadUpdate(int threadId, ABoid *boid);
std::ostream &	operator<<(std::ostream & o, ABoid const & rhs);

#endif
