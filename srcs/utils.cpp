/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:38:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/24 15:44:36 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <random>
#include <ctime>
#include "Flock.hpp"
#include "conf.hpp"

double	randDouble(double const & min, double const & max)
{
	static bool	seeded = false;

	if (!seeded)
	{
		std::srand(time(NULL));
		seeded = true;
	}
	return min + static_cast<double>(rand() / static_cast<double>(RAND_MAX / (max - min)));
}

void	threadBoid(int threadId, Flock *flock, size_t id) 
{
	if (THREAD_DEBUG)
		printf("thID: -%d-\n", threadId);
	flock->getBoid(id).update();
}
