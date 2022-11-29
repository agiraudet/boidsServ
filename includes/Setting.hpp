/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setting.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:29:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/29 14:01:21 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_HPP
# define SETTING_HPP

# include <iostream>
# include <map>
# include <string>

class	Setting
{
	public:

		Setting(void);
		Setting(std::string const & confFile);
		Setting(Setting const & src);
		~Setting(void);
		
		Setting & operator=(Setting const & rhs);

		bool	loadFile(std::string const & confFile);
		int		getSetInt(std::string const & setting) const;
		double	getSetDbl(std::string const & setting) const;
		bool	getSetBool(std::string const & setting) const;
		void	printAllDebug(std::ostream & o) const;
		void	printAll(std::ostream & o) const;

	private:

		void	_dfltValues(void);
		std::string &	_trim(std::string & str);

		std::map<std::string, int>		_intSet;
		std::map<std::string, double>	_dblSet;
		std::map<std::string, bool>		_boolSet;

};

std::ostream &	operator<<(std::ostream & o, Setting const & rhs);

extern	Setting g_set;

#endif
