/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:51:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 10:28:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_HPP
# define BASIC_HPP

# include "ABoid.hpp"

class	Basic : public ABoid
{
	public:

		Basic(void);
		Basic(unsigned int id);
		Basic(unsigned int id, Flock *flock);
		Basic(Basic const & src);
		~Basic(void);
		
		Basic & operator=(Basic const & rhs);

	private:
		void	_baseRules(void);

};
#endif
