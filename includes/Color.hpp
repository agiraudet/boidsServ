/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:41:55 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/28 14:45:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_HPP
# define COLOR_HPP

# include "SDL2/SDL.h"

class	Color
{
	public:

		Color(void);
		Color(Uint8 r, Uint8 g, Uint8 b);
		Color(Color const & src);
		~Color(void);
		
		Color & operator=(Color const & rhs);

		void	randomize(void);

		Uint8	r;
		Uint8	b;
		Uint8	g;
		Uint8	a;

};
#endif
