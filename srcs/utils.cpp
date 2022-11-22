/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:38:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/22 11:47:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <random>
#include <ctime>

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
