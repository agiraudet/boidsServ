/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:39:14 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/29 17:05:29 by agiraude         ###   ########.fr       */
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

double	randDouble(double const & min, double const & max);
void	threadBoid(int threadId, Flock *flock, size_t id);

extern ctpl::thread_pool	g_thPool;

#endif
