/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Predator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:59:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 12:59:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDATOR_HPP
# define PREDATOR_HPP

# include "ABoid.hpp"

class	Predator : public ABoid
{
	public:

		Predator(unsigned int id, Flock& flock);
		Predator(Predator const & src);
		~Predator(void);
		
		Predator & operator=(Predator const & rhs);

	private:
		Predator(void);
		void	_baseRules(void);
};

#endif
