/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Prey.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:59:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 14:40:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Prey_HPP
# define Prey_HPP

# include "ABoid.hpp"

class	Prey : public ABoid
{
	public:

		Prey(unsigned int id, Flock& flock);
		Prey(Prey const & src);
		~Prey(void);
		
		Prey & operator=(Prey const & rhs);

	private:
		Prey(void);
		void	_baseRules(void);
};

#endif
