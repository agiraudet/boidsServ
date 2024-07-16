/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StkWrap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:18:56 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/05 14:54:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StkWrap.hpp"
# include "stk/BeeThree.h"
# include "stk/Flute.h"
# include "stk/PercFlut.h"

static int	tick(void *outBuf, void *inBuf, unsigned int nBufFrames, double streamTime,
		RtAudioStreamStatus status, void *voicerPtr)
{
	stk::Voicer		*voicer = (stk::Voicer*)voicerPtr;
	stk::StkFloat	*samples = (stk::StkFloat*)outBuf;
	int				nTicks = (int)nBufFrames;

	for (int i = 0; i < nTicks; i++)
		*samples++ = voicer->tick();
	return 0;
}

StkWrap::StkWrap(void)
: _voicer(NULL), _dac(NULL)
{
	stk::Stk::setSampleRate(44100.);
	stk::Stk::setRawwavePath("rawwaves/");

	this->_dac = new RtAudio;
	this->_voicer = new stk::Voicer;
	this->_param.deviceId = this->_dac->getDefaultOutputDevice();
	this->_param.nChannels = 1;
	this->_format = (sizeof(stk::StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	this->_bufFrames = stk::RT_BUFFER_SIZE;
	try
	{
		this->_dac->openStream(&this->_param, NULL, this->_format,
				(unsigned int)stk::Stk::sampleRate(), &this->_bufFrames, &tick,
				(void*)this->_voicer);
	}
	catch (RtAudioErrorType error) {
    		std::cerr << "RtAudio error: " << error << std::endl;
	}	
	try
	{
		this->_dac->startStream();
	}
	catch (RtAudioErrorType error) {
    		std::cerr << "RtAudio error: " << error << std::endl;
	}
}

StkWrap::StkWrap(StkWrap const & src)
{
	*this = src;
}

StkWrap::~StkWrap(void)
{
	try
	{
		this->_dac->closeStream();
	}
	catch (RtAudioErrorType error) {
	    std::cerr << "RtAudio error: " << error << std::endl;
	}
	if (this->_dac)
		delete this->_dac;
	if (this->_voicer)
		delete this->_voicer;
	for (size_t i = 0; i < this->_instrLst.size(); i++)
		delete this->_instrLst[i];
}

StkWrap & StkWrap::operator=(StkWrap const & rhs)
{
	if (this == &rhs)
		return *this;
	return *this;
}

int	StkWrap::addInstru(e_instru type)
{
	return this->addInstru(type, 0);
}

int	StkWrap::addInstru(e_instru type, int group)
{
	stk::Instrmnt	*newInstru;

	switch (type)
	{
		case BEETHREE:
			newInstru = new stk::BeeThree();
			break;
		case FLUTE:
			newInstru = new stk::Flute(1.);
			break;
		case PERCFLUT:
			newInstru = new stk::PercFlut();
			break;
		default:
			return -1;
	}
	this->_instrLst.push_back(newInstru);
	this->_voicer->addInstrument(newInstru, group);
	return 0;
}

stk::Voicer	*StkWrap::getVoicer(void)
{
	return this->_voicer;
}

