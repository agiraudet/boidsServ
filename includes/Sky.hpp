/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sky.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:22:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 14:55:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKY_HPP
# define SKY_HPP

# include <SDL2/SDL.h>
# include "Flock.hpp"

class	Sky
{
	public:

		Sky(void);
		Sky(Sky const & src);
		~Sky(void);
		
		Sky & operator=(Sky const & rhs);

		void	addFlock(size_t size);
		void	addFlock(size_t size, Uint8 r, Uint8 g, Uint8 b);
		void	addFlock(size_t size, SDL_Color const & color);
		void	delFlock(int id);
		void	update(void);
	
	public:
		inline size_t	size(void) const {return this->_flocks.size();}
		inline Flock*	getFlock(int id)
		{
			if (this->_flocks.size() == 0)
				return 0;
			while (id < 0)
				id = this->_flocks.size() + id;
			if (id >= static_cast<long>(this->_flocks.size()))
				return 0;
			return this->_flocks[id];
		}

	private:

		void	_randomizeFlock(Flock & flock);

		std::vector<Flock*>	_flocks;

};
#endif
