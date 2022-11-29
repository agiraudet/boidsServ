/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flock.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:03:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/29 16:40:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOCK_HPP
# define FLOCK_HPP

# include "Boid.hpp"
# include <vector>
# include <iostream>
# include "cptl_stl.h"
# include "SDL2/SDL.h"

class	Flock
{
	public:

		Flock(size_t size);
		Flock(size_t size, SDL_Color const & color);
		Flock(Flock const & src);
		~Flock(void);
		
		Flock & operator=(Flock const & rhs);

		size_t			size(void) const;
		void			setColor(Uint8 r, Uint8 g, Uint8 b);
		void			setColor(SDL_Color const & color);
		Coord const &	getPos(size_t id) const;
		Coord const &	getDir(size_t id) const;
		Boid &	getBoid(size_t id);
		Boid const &	getCBoid(size_t id) const;
		void			randomizePos(double const & maxX, double const & maxY);
		void			randomizeDir(double const & maxX, double const & maxY);
		void			randomizeColor(void);
		void			update(void);
		void			render(SDL_Renderer *ren) const;

	private:

		Flock(void);
		void	_init(void);

		std::vector<Boid*>	_boids;
		size_t				_size;
		SDL_Color			_color;
};

void			flockThreadUpdate(int threadId, Flock *flock);
std::ostream &	operator<<(std::ostream & o, Flock const & rhs);

#endif
