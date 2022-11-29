/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuleSet.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:56:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/29 17:06:03 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULESET_HPP
# define RULESET_HPP

struct	RuleSet
{
	double	centering;
	double	matching;
	double	avoiding;
	double	turning;
	double	minDist;
	double	viewRange;
	double	speedLimit;

	RuleSet(void)
	: centering(0.005), matching(0.05), avoiding(0.05), turning(1.0),
	minDist(10.0), viewRange(75.0), speedLimit(10.0) {};

	RuleSet(double c, double m, double a, double t, double md,
			double vr, double sl)
	: centering(c), matching(m), avoiding(a), turning(t), minDist(md),
	viewRange(vr), speedLimit(sl) {};
};



#endif
