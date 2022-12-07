/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sky.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:22:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/07 11:46:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKY_HPP
# define SKY_HPP

# include <SDL2/SDL.h>
# include "Flock.hpp"
# include "utils.hpp"

class	Sky
{
	public:

		Sky(void);
		Sky(Sky const & src);
		~Sky(void);
		
		Sky &	operator=(Sky const & rhs);
		Flock &	operator[](int i) const;

		void	addFlock(size_t size);
		void	addFlock(size_t size, Uint8 r, Uint8 g, Uint8 b);
		void	addFlock(size_t size, std::string type, Uint8 r, Uint8 g, Uint8 b);
		void	addFlock(size_t size, SDL_Color const & color);
		void	addFlock(Flock& flock);
		void	delFlock(int id);
		void	togglePause(void);
		void	update(void);
	
	public:
		inline size_t	size(void) const {return this->_flocks.size();}
		inline Flock*	getFlock(int id)
		{
			if (this->_flocks.size() == 0)
				return 0;
			return this->_flocks[loopIndex(id, static_cast<int>(this->_flocks.size()))];
		}

	private:

		void	_randomizeFlock(Flock & flock);

		std::vector<Flock*>	_flocks;
		bool				_pause;

};
#endif
