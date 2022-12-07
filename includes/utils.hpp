/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:39:14 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/07 11:04:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "cptl_stl.h"

class Flock;

template<typename T>
T	randNb(T const & min, T const & max)
{
	return (min + (rand() / (RAND_MAX / (max - min))));
}

template<typename T>
T	loopIndex(T i, T size)
{
	while (i >= size)
		i -= size;
	while (i < 0)
		i += size;
	return i;
}

template<typename T>
T	scale(T const& x, T const& xMin, T const& xMax, T const& scaleMin, T const& scaleMax)
{
	return (x - xMin) * (scaleMax - scaleMin) / (xMax - xMin);
}

double	randDouble(double const & min, double const & max);
void	threadBoid(int threadId, Flock *flock, size_t id);

extern ctpl::thread_pool	g_thPool;

#endif
