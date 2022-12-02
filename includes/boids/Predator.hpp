/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Predator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 09:59:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/01 10:28:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDATOR_HPP
# define PREDATOR_HPP

# include "ABoid.hpp"

class	Predator : public ABoid
{
	public:

		Predator(void);
		Predator(unsigned int id);
		Predator(unsigned int id, Flock *flock);
		Predator(Predator const & src);
		~Predator(void);
		
		Predator & operator=(Predator const & rhs);

	private:
		void	_baseRules(void);
};

#endif
