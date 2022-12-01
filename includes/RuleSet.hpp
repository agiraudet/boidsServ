/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuleSet.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:05:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 09:32:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULESET_HPP
# define RULESET_HPP

class	RuleSet
{
	public:
		RuleSet(void);
		RuleSet(double c, double m, double a, double t, double md, double vr,
				double sl, int nX, int nY, int xX, int xY);
		RuleSet(double c, double m, double a, double t, double md, double vr,
				double sl);
		RuleSet(RuleSet const & src);
		~RuleSet(void);
		RuleSet & operator=(RuleSet const & rhs);
	
	public:
		inline double	getCenter(void) const	{return this->_centering;}
		inline double	getMatch(void) const	{return this->_matching;}
		inline double	getAvoid(void) const	{return this->_avoiding;}
		inline double	getTurn(void) const		{return this->_turning;}
		inline double	getMinD(void) const		{return this->_minDist;}
		inline double	getViewR(void) const	{return this->_viewRange;}
		inline double	getSpeedL(void) const	{return this->_speedLimit;}
		inline double	getMinX(void) const		{return this->_minX;}
		inline double	getMinY(void) const		{return this->_minY;}
		inline double	getMaxX(void) const		{return this->_maxX;}
		inline double	getMaxY(void) const		{return this->_maxY;}

	private:
		void	_setBorders(int minX, int minY, int maxX, int maxY);

		double	_centering;
		double	_matching;
		double	_avoiding;
		double	_turning;
		double	_minDist;
		double	_viewRange;
		double	_speedLimit;
		double	_minX;
		double	_minY;
		double	_maxX;
		double	_maxY;

};
#endif
