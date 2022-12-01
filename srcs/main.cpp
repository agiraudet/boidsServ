/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:04:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 15:15:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.hpp"
#include "Sky.hpp"

void	test(Sky & sky)
{
	sky.addFlock(500, 255, 0, 0);
}

int main(int argc, char **argv)
{
	Scene	sc(".conf");
	Sky					sky;

	test(sky);
	sc.mainLoop(sky);
	return (0);
}
