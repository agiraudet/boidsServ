/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Basic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:51:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 12:56:48 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_HPP
# define BASIC_HPP

# include "ABoid.hpp"

class	Basic : public ABoid
{
	public:

		Basic(unsigned int id, Flock& flock);
		Basic(Basic const & src);
		~Basic(void);
		
		Basic & operator=(Basic const & rhs);

	private:
		Basic(void);
		void	_baseRules(void);

};
#endif
