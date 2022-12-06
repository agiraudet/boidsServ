/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RuleSet.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:05:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 08:44:03 by agiraude         ###   ########.fr       */
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
		inline void		setCenter(double c)		{this->_centering = c;}
		inline double	getMatch(void) const	{return this->_matching;}
		inline void		setMatch(double m)		{this->_matching = m;}
		inline double	getAvoid(void) const	{return this->_avoiding;}
		inline void		setAvoid(double a)		{this->_avoiding = a;}
		inline double	getTurn(void) const		{return this->_turning;}
		inline void		setTurn(double t)		{this->_turning = t;}
		inline double	getMinD(void) const		{return this->_minDist;}
		inline void		setMinD(double mD)		{this->_minDist = mD;}
		inline double	getViewR(void) const	{return this->_viewRange;}
		inline void		setViewR(double vR)		{this->_viewRange = vR;}
		inline double	getSpeedL(void) const	{return this->_speedLimit;}
		inline void		setSpeedL(double sL)	{this->_speedLimit = sL;}
		inline double	getMinX(void) const		{return this->_minX;}
		inline void		setMinX(double nX)		{this->_minX = nX;}
		inline double	getMinY(void) const		{return this->_minY;}
		inline void		setMinY(double nY)		{this->_minY = nY;}
		inline double	getMaxX(void) const		{return this->_maxX;}
		inline void		setMaxX(double xX)		{this->_maxX = xX;}
		inline double	getMaxY(void) const		{return this->_maxY;}
		inline void		setMaxY(double xY)		{this->_maxY = xY;}
		inline void		setBorder(double nX, double nY, double xX, double xY)
		{this->_minX = nX; this->_minY = nY; this->_maxX = xX; this->_maxY = xY;}

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
