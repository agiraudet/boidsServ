/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StkWrap.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:42:15 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/05 11:01:10 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STKWRAP_HPP
# define STKWRAP_HPP

# include "stk/BeeThree.h"
# include "stk/Flute.h"
# include "stk/RtAudio.h"
# include "stk/Voicer.h"

enum	e_instru
{
	BEETHREE,
	FLUTE
};

class	StkWrap
{
	public:
		StkWrap(void);
		~StkWrap(void);

	private:
		StkWrap & operator=(StkWrap const & rhs);
		StkWrap(StkWrap const & src);
	
	public:
		int				addInstru(e_instru type);
		int				addInstru(e_instru type, int group);
		stk::Voicer*	getVoicer(void);

	private:
		stk::Voicer					*_voicer;
		RtAudio						*_dac;
		RtAudio::StreamParameters	_param;
		RtAudioFormat				_format;
		unsigned int				_bufFrames;
		std::vector<stk::Instrmnt*>	_instrLst;
};
#endif
