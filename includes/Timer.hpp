/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:15:10 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/19 15:28:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_HPP
# define TIMER_HPP

#include <SDL2/SDL.h>


class	Timer
{
	public:

		Timer(void);
		Timer(Timer const & src);
		~Timer(void);
		
		Timer & operator=(Timer const & rhs);

		void	capFps(int & maxFps);

	private:

		void		_update(void);

		uint32_t	_initTime;
		int			_relativeTime;
		int			_frames;
		double		_avgFps;

};
#endif
