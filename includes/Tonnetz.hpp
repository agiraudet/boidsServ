#pragma once

#include <iostream>
#include <map>
#include <array>

class Tonnetz
{
    public:
        struct Pos
        {
            double x;
            double y;
        };
        struct chord
        {
            double i;
            double ii;
            double iii;
        };

    	static constexpr std::array<std::array<char, 7>, 6> hidden_grid = 
    	{{
        	{'7', '2', '9', '4', 'B', '6', '1'},
        	{'3', 'A', '5', '0', '7', '2', '9'},
        	{'B', '6', '1', '8', '3', 'A', '5'},
        	{'7', '2', '9', '4', 'B', '6', '1'},
        	{'3', 'A', '5', '0', '7', '2', '9'},
        	{'B', '6', '1', '8', '3', 'A', '5'}
   	}};
        std::map<char, double> symbol_to_frequency;
// Tonnetz variables works as a square grid
// squares are then split into two triangles during calculation
    private:
        Pos screen_res;
        Pos boid_pos;
        Pos tonnetz_screen_res;
        Pos tonnetz_boid_pos;

    public:
        Tonnetz(int screnres_x, int screenres_y, int sctonnetz_x, int sctonnetz_y);
        Tonnetz(Tonnetz const &other);
        ~Tonnetz();
	
	Pos     toTonnetz(Pos const &boid);
        chord    triangleFinder(Pos const &v);
        float   crossProduct(Pos const &a, Pos const &b);
        Pos     soustraction(Pos const &a, Pos const &b);
        bool    triangleFinderBis(Pos const &v);
        void    loadFrequency(double tonic);
};

