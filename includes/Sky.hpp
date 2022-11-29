/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sky.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:22:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/29 17:11:54 by agiraude         ###   ########.fr       */
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
		size_t	size(void) const;
		void	update(void);
		void	render(SDL_Renderer *ren) const;

	private:

		void	_randomizeFlock(Flock & flock);

		std::vector<Flock*>	_flocks;

};
#endif
