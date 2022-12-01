/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 13:22:57 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Sky.hpp"

void	test(Sky & sky)
{

	//sky.addFlock(500, 255, 0, 0);
	//sky.addFlock(300, 0, 255, 0);

	//sky[-1].setRuleset(RuleSet(0.01, 0.1, 0.1, 1.0, 15.0, 30.0, 5.0));
	
	sky.addFlock(50, "Predator", 255, 0, 0);
	sky.addFlock(50, "Basic", 0, 255, 0);
}

int main(int argc, char **argv)
{
	Scene	sc(".conf");
	Sky					sky;

	test(sky);
	sc.mainLoop(sky);
	return (0);
}
