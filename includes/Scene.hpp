/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:47:23 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 13:07:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_HPP
# define SCENE_HPP

# include "Timer.hpp"
# include "Sky.hpp"
# include "Flock.hpp"
# include "ABoid.hpp"
# include <SDL2/SDL.h>

class	Scene
{
	public:

		Scene(void);
		Scene(std::string const & confFile);
		Scene(Scene const & src);
		~Scene(void);
		
		Scene & operator=(Scene const & rhs);

		void	render(Sky const& sky);
		void	mainLoop(Sky& sky);
		double	getAvgFps(void) const;
		void	reload(void);
		void	reloadConf(std::string const & confFile);
		void	setLoopFnct(void (*loopFnct)(void* arg), void* arg);
		void	setInputFnct(void (*inputFnct)(void* arg, int key), void* arg);

	private:

		void			_initValues(void);
		void			_initSdl(void);
		void			_initThreads(void);
		void			_render(Sky const& sky);
		void			_render(Flock const& flock);
		void			_render(ABoid const& boid);

		int				_scWd;
		int				_scHg;
		bool			_fullSc;
		int				_maxFps;
		Timer			_timer;
		SDL_Window*		_win;
		SDL_Renderer*	_ren;
		void*			_dataLoop;
		void*			_dataInput;
		void			(*_loopFnct)(void* arg);
		void			(*_inputFnct)(void* arg, int key);

};
#endif
