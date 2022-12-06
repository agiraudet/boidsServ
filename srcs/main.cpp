/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 11:04:27 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StkWrap.hpp"
#include "Scene.hpp"
#include "Sky.hpp"

//The Data struct is only use to make it easier to pass references to the
//Scene input and loop hooks.
struct	Data
{
	StkWrap&	stkWrap;
	Sky&		sky;

	Data(StkWrap& wrap, Sky& sk) : stkWrap(wrap), sky(sk) {}
};

//Example of a fucntion called on each Scene loop, making sound.
void	loopExample(void* arg)
{
	static int	count = 0;
	bool		always = true;
	Data*		data = (Data*)arg;
	Coord		flockPos;

	if (count >= 10 || always)
	{
		if (data->sky.size())
		{
			data->sky[0].getAvgPos(flockPos);
			double freqX = flockPos.getX() * 100. / data->sky[0].ruleset.getMaxX();
			double freqY = flockPos.getY() * 100. / data->sky[0].ruleset.getMaxY();

			stk::Voicer*	voic = data->stkWrap.getVoicer();
			voic->noteOn(freqX, 50., 0);
			voic->noteOn(freqY, 50., 1);
		}
		count = 0;
	}
	else
		count++;
}

//Example of a function called on each input, managing the Sky.
void	inputExample(void* arg, int key)
{
	Data*	data = (Data*)arg;

	switch (key)
	{
		case SDLK_a:
			data->sky.addFlock(randNb(50, 500));
			break;
		case SDLK_s:
			data->sky.delFlock(-1);
			break;
	}
}

int main(int argc, char **argv)
{
	//First, creating one (and only one) Scene object.
	Scene	sc(".conf");

	//Creating a sky, adding a single Flock to it.
	Sky		sky;
	sky.addFlock(500, 255, 0, 0);

	//Creating one (and only one) stkWrap. It's a class making it easier to use
	//the stk::Voicer class it's wrapping.
	StkWrap	wrap;
	wrap.addInstru(BEETHREE, 0);
	wrap.addInstru(PERCFLUT, 1);

	//Using our Data struct to old a reference to both the Sky and the STkWrap
	Data	data(wrap, sky);

	//Setting up the hooks.
	sc.setLoopFnct(&loopExample, (void*)&data);
	sc.setInputFnct(&inputExample, (void*)&data);

	//Starting the Scene loop
	sc.mainLoop(sky);

	return (0);
}
