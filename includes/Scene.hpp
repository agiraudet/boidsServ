/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:47:23 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/23 09:16:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_HPP
# define SCENE_HPP

# include "Timer.hpp"
# include "Flock.hpp"
# include <SDL2/SDL.h>

class	Scene
{
	public:

		Scene(void);
		Scene(int scWd, int scHg, bool fullSc);
		Scene(Scene const & src);
		~Scene(void);
		
		Scene & operator=(Scene const & rhs);

		void	render(Flock *flock);
		double	getAvgFps(void) const;

	private:

		void			_initSdl(void);
		void			_renderSingleBoid(Boid const & boid);

		int				_scWd;
		int				_scHg;
		bool			_fullSc;
		int				_maxFps;
		Timer			_timer;
		SDL_Window*		_win;
		SDL_Renderer*	_ren;

};
#endif
