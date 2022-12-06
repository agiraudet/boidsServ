/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:03:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 13:03:18 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOCK_HPP
# define FLOCK_HPP

# include "Coord.hpp"
# include "Setting.hpp"
# include "RuleSet.hpp"
# include <vector>
# include <iostream>
# include "SDL2/SDL.h"

class	ABoid;

class	Flock
{
	public:

		Flock(size_t size);
		Flock(size_t size, std::string type);
		Flock(size_t size, SDL_Color const & color);
		Flock(size_t size, SDL_Color const & color, std::string type);
		Flock(Flock const & src);
		~Flock(void);
		
		Flock & operator=(Flock const & rhs);
		ABoid &	operator[](int i) const;

		size_t			size(void) const;
		void			setRuleset(RuleSet const & ruleset);
		void			setColor(Uint8 r, Uint8 g, Uint8 b);
		void			setColor(SDL_Color const & color);
		SDL_Color const &	getColor(void) const;
		void			getAvgPos(Coord & pos) const;
		void			getAvgDir(Coord & pos) const;
		void			randomizePos(void);
		void			randomizePos(double const & maxX, double const & maxY);
		void			randomizeDir(double const & maxX, double const & maxY);
		void			randomizeColor(void);
		void			update(void);

		RuleSet			ruleset;

	private:

		Flock(void);
		void	_init(std::string type);

		std::vector<ABoid*>	_boids;
		size_t				_size;
		SDL_Color			_color;
};

void			flockThreadUpdate(int threadId, Flock *flock);
std::ostream &	operator<<(std::ostream & o, Flock const & rhs);

#endif
