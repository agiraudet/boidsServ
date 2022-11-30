/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:47:23 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/30 15:22:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_HPP
# define SCENE_HPP

# include "Timer.hpp"
# include "Sky.hpp"
# include "Flock.hpp"
# include "Boid.hpp"
# include <SDL2/SDL.h>

class	Scene
{
	public:

		Scene(void);
		Scene(int scWd, int scHg, bool fullSc);
		Scene(Scene const & src);
		~Scene(void);
		
		Scene & operator=(Scene const & rhs);

		void	render(Sky *sky);
		double	getAvgFps(void) const;

	private:

		void			_initSdl(void);
		void			_render(Sky *sky);
		void			_render(Flock *flock);
		void			_render(Boid *boid);

		int				_scWd;
		int				_scHg;
		bool			_fullSc;
		int				_maxFps;
		Timer			_timer;
		SDL_Window*		_win;
		SDL_Renderer*	_ren;

};
#endif
