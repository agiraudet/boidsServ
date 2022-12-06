/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Goal.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:51:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/12/06 14:51:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Goal_HPP
# define Goal_HPP

# include "ABoid.hpp"

class	Goal : public ABoid
{
	public:

		Goal(unsigned int id, Flock& flock);
		Goal(Goal const & src);
		~Goal(void);
		
		Goal & operator=(Goal const & rhs);

	private:
		Goal(void);
		void	_baseRules(void);

};
#endif
