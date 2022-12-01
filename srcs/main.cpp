/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 18:14:10 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Sky.hpp"

void	loopExample(Sky & sky)
{
	static	int	count = 0;
	Coord	flockPos;

	if (count <= 0)
	{
		if (sky.size())
		{
			sky[0].getAvgPos(flockPos);
			std::cout << "First Flock average postion: " << flockPos << std::endl;
		}
		else
		{
			std::cout << "Not a single Flock in this Sky !" << std::endl;
		}
		count = 60;
	}
	else
	{
		count--;
	}
}

void	inputExample(Sky & sky, int key)
{
	switch (key)
	{
		case SDLK_a:
			sky.addFlock(randNb(50, 500));
			break;
		case SDLK_s:
			sky.delFlock(-1);
			break;
	}
}

int main(int argc, char **argv)
{
	Scene	sc(".conf");
	Sky		sky;

	sky.addFlock(500, 255, 0, 0);

	sc.setLoopFnct(&loopExample);
	sc.setInputFnct(&inputExample);
	sc.mainLoop(sky);
	return (0);
}
