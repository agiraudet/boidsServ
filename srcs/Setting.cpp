/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Setting.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:02:26 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/29 14:14:56 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Setting.hpp"
# include <fstream>

Setting::Setting(void)
{
	this->_dfltValues();
}

Setting::Setting(std::string const & confFile)
{
	if (!this->loadFile(confFile))
		this->_dfltValues();
}

Setting::Setting(Setting const & src)
{
	*this = src;
}

Setting::~Setting(void)
{
}

Setting & Setting::operator=(Setting const & rhs)
{
	if (this == &rhs)
		return *this;
	this->_boolSet = rhs._boolSet;
	this->_intSet = rhs._intSet;
	this->_dblSet = rhs._dblSet;
	return *this;
}

bool	Setting::loadFile(std::string const & confFile)
{
	std::ifstream	file;

	file.open(confFile);
	if (!file.is_open())
	{
		std::cerr << "Cannot open " << confFile << std::endl;
		return false;
	}

	std::string	line;
	while (file)
	{
		std::getline(file, line);
		size_t sepPos = line.find('=');
		if (sepPos == std::string::npos)
			continue;
		std::string	key = line.substr(0, sepPos);
		this->_trim(key);
		std::string value = line.substr(sepPos + 1);
		this->_trim(value);

		if (std::isdigit(value[0]))
		{
			if (value.find('.') == std::string::npos)
				this->_intSet[key] = atoi(value.c_str());
			else
				this->_dblSet[key] = atof(value.c_str());
		}
		else if (value.compare("true") == 0)
			this->_boolSet[key] = true;
		else if (value.compare("false") == 0)
			this->_boolSet[key] = false;
	}
	file.close();
	return true;
}

std::string &	Setting::_trim(std::string & str)
{
	size_t	left = 0;

	for (; str[left]; left++)
		if (str[left] != ' ')
			break;
	if (left)
		str.erase(0, left);

	size_t	right = str.size() - 1;
	for (; right; right--)
		if (str[right] != ' ')
			break;
	if (right < str.size() - 1)
		str.erase(right + 1);
	return str;
}

void	Setting::_dfltValues(void)
{
	this->_intSet["boid_height"] = 5;
	this->_intSet["boid_width"] = 5;
	this->_intSet["fps_max"] = 60;
	this->_intSet["screen_height"] = 480;
	this->_intSet["screen_margin"] = 50;
	this->_intSet["screen_width"] = 720;
	this->_dblSet["avoid_factor"] = 0.05;
	this->_dblSet["centering_factor"] = 0.005;
	this->_dblSet["matching_factor"] = 0.05;
	this->_dblSet["min_dist"] = 10;
	this->_dblSet["speed_limit"] = 10;
	this->_dblSet["turn_factor"] = 1;
	this->_dblSet["view_range"] = 75;
	this->_boolSet["debug_fps"] = true;
	this->_boolSet["debug_fps_atexit"] = true;
	this->_boolSet["debug_info"] = true;
	this->_boolSet["debug_thread"] = true;
	this->_boolSet["multithreading"] = true;
	this->_boolSet["fullscreen"] = false;
	this->_boolSet["printSettings"] = false;
}

int Setting::getSetInt(std::string const & setting) const
{
	std::map<std::string, int>::const_iterator	it;

	it = this->_intSet.find(setting);
	if (it != this->_intSet.end())
		return it->second;
	std::cerr << "setting not found: " << setting << std::endl;
	return 0;
}
	
double Setting::getSetDbl(std::string const & setting) const
{
	std::map<std::string, double>::const_iterator	it;

	it = this->_dblSet.find(setting);
	if (it != this->_dblSet.end())
		return it->second;
	std::cerr << "setting not found: " << setting << std::endl;
	return 0.;
}

bool Setting::getSetBool(std::string const & setting) const
{
	std::map<std::string, bool>::const_iterator	it;

	it = this->_boolSet.find(setting);
	if (it != this->_boolSet.end())
		return it->second;
	std::cerr << "setting not found: " << setting << std::endl;
	return false;
}

void	Setting::printAll(std::ostream & o) const
{
	for (std::map<std::string, int>::const_iterator it = this->_intSet.begin();
			it != this->_intSet.end(); it++)
		o << it->first << " = " << it->second << std::endl;
	for (std::map<std::string, double>::const_iterator it = this->_dblSet.begin();
			it != this->_dblSet.end(); it++)
		o << it->first << " = " << it->second << std::endl;
	for (std::map<std::string, bool>::const_iterator it = this->_boolSet.begin();
			it != this->_boolSet.end(); it++)
	{
		o << it->first << " = ";
		if (it->second)
			o << "true";
		else
			o << "false";
		o << std::endl;
	}
}

void	Setting::printAllDebug(std::ostream & o) const
{
	for (std::map<std::string, int>::const_iterator it = this->_intSet.begin();
			it != this->_intSet.end(); it++)
		o << "this->_intSet[\"" << it->first << "\"] = " << it->second << ";" << std::endl;
	for (std::map<std::string, double>::const_iterator it = this->_dblSet.begin();
			it != this->_dblSet.end(); it++)
		o << "this->_dblSet[\"" << it->first << "\"] = " << it->second << ";" << std::endl;
	for (std::map<std::string, bool>::const_iterator it = this->_boolSet.begin();
			it != this->_boolSet.end(); it++)
	{
		o << "this->_boolSet[\"" << it->first << "\"] = ";
		if (it->second)
			o << "true";
		else
			o << "false";
		o << ";" << std::endl;
	}
}

std::ostream &	operator<<(std::ostream & o, Setting const & rhs)
{
	rhs.printAll(o);
	return o;
}

