/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/07 11:56:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StkWrap.hpp"
#include "Scene.hpp"
#include "Sky.hpp"
#include "Tonnetz.hpp"

//The Data struct is only use to make it easier to pass references to the
//Scene input and loop hooks.
struct	Data
{
	StkWrap&	stkWrap;
	Sky&		sky;

	Data(StkWrap& wrap, Sky& sk) : stkWrap(wrap), sky(sk) {}
};

void	loopExample(void* arg)
{
	static int		count = 0;
	bool			bypassCount = true;
	Data*			data = (Data*)arg;
	Coord			flockPos;
	Tonnetz			test(1920, 1080, 6, 5);
	Tonnetz::chord	chord;
	Tonnetz::Pos    res;
	Tonnetz::Pos 	boid;
	//Running at 60fps means this function is called 60 time per seconds.
	//Adding this counter allows to only change the note 6 times per seconds
	//(You can ignore this counter by setting bypassCount to true).
	if (count >= 10 || bypassCount)
	{
		stk::Voicer*	voic = data->stkWrap.getVoicer();
		if (data->sky.size())
		{
			//Using average (x,y) of a flock as note frequencies
			data->sky[0].getAvgPos(flockPos);
			boid.x = flockPos.getX();
			std::cout << "position of boid.x " << boid.x << std::endl;
			boid.y = flockPos.getY();
			std::cout << "position of boid.y " << boid.y << std::endl;
			res = test.toTonnetz(boid);
			chord = test.triangleFinder(res);
			double note_number = 12 * log2(chord.i / 440.0) + 69;
			voic->noteOn(note_number, 50., 1);
			std::cout << "chord.i " << note_number << " " << chord.i << std::endl;
			note_number = 12 * log2(chord.ii / 440.0) + 69;
			voic->noteOn(note_number, 100., 2);
			std::cout << "chord.ii " << note_number << " " << chord.ii << std::endl;
			note_number = 12 * log2(chord.iii / 440.0) + 69;
			voic->noteOn(note_number, 100., 3);
			std::cout << "chord.iii " << note_number << " " << chord.iii << std::endl;		
		}
		else
			voic->silence();

		count = 0;
	}
	else
		count++;
}


//Example of a fucntion called on each Scene loop, making sound.
/* void	loopExample(void* arg)
{
	static int	count = 0;
	bool		bypassCount = true;
	Data*		data = (Data*)arg;
	Coord		flockPos;

	//Running at 60fps means this function is called 60 time per seconds.
	//Adding this counter allows to only change the note 6 times per seconds
	//(You can ignore this counter by setting bypassCount to true).
	if (count >= 10 || bypassCount)
	{
		stk::Voicer*	voic = data->stkWrap.getVoicer();
		if (data->sky.size())
		{
			//Using average (x,y) of a flock as note frequencies
			data->sky[0].getAvgPos(flockPos);
			double posX = flockPos.getX();
			double maxX = data->sky[0].ruleset.getMaxX();
			double posY = flockPos.getY();
			double maxY = data->sky[0].ruleset.getMaxY();

			//make sure pos dont not exceed the bounds
			//(can happen with a low turn factor in ruleset)
			posX = posX < 0. ? 0. : (posX > maxX ? maxX : posX );
			posY = posY < 0. ? 0. : (posY > maxY ? maxY : posY );

			// map this pos to a 0-100 value. stk::noteOn() allow 0-128. values,
			// but the to high ones make my head hurt.
			double freqX = posX * 100. / maxX;
			double freqY = posY * 100. / maxY;

			//play the notes. GroupId 0 should not by used as it's for default
			voic->noteOn(freqX, 50., 1);
			voic->noteOn(freqY, 100., 2);
		}
		else
			voic->silence();

		count = 0;
	}
	else
		count++;
} */

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
		case SDLK_SPACE:
			data->sky.togglePause();
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

	//Tuning the flock behavior's paramters (check Ruleset class)
	sky[0].ruleset.setTurn(1.05);
	sky[0].ruleset.setViewR(50.);
	sky[0].ruleset.setSpeedL(0.75);


	//Creating one (and only one) stkWrap. It's a class making it easier to use
	//the stk::Voicer class it's wrapping.
	StkWrap	wrap;
	wrap.addInstru(BEETHREE, 1);
	wrap.addInstru(BEETHREE, 2);
	wrap.addInstru(BEETHREE, 3);

	//Using our Data struct to old a reference to both the Sky and the STkWrap
	Data	data(wrap, sky);

	//Setting up the hooks.
	sc.setLoopFnct(&loopExample, (void*)&data);
	sc.setInputFnct(&inputExample, (void*)&data);

	//Starting the Scene loop
	sc.mainLoop(sky);

	return (0);
}
