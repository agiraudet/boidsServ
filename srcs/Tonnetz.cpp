#include "Tonnetz.hpp"
#include <cmath>

Tonnetz::Tonnetz(int screenres_x, int screenres_y,
                    int sctonnetz_x, int scrtonnetz_y)
{
    this->screen_res.x = screenres_x;
    this->screen_res.y = screenres_y;
    this->tonnetz_screen_res.x = sctonnetz_x;
    this->tonnetz_screen_res.y = scrtonnetz_y;
    this->loadFrequency(51.91);
}

Tonnetz::~Tonnetz() {}

Tonnetz::Pos     Tonnetz::toTonnetz(Pos const &boid)
{
    this->tonnetz_boid_pos.x = (boid.x * tonnetz_screen_res.x) / screen_res.x ;
    this->tonnetz_boid_pos.y = (boid.y * tonnetz_screen_res.y) / screen_res.y ;
    return this->tonnetz_boid_pos;
}

float           Tonnetz::crossProduct(Pos const &a,  Pos const &b)
{
    return ((a.x * b.y) - (a.y * b.x));
}


Tonnetz::Pos           Tonnetz::soustraction(Pos const &a, Pos const &b)
{
    Pos Pector;
    Pector.x = b.x - a.x;
    Pector.y = b.y - a.y;
    return (Pector);
}

Tonnetz::chord     Tonnetz::triangleFinder(Pos const &P)
{
    Pos A;
    Pos B;
    Pos C;
    chord chord;

    A.x = std::floor(P.x);
    A.y = std::floor(P.y) + 1;
    B.x = A.x;
    B.y = A.y - 1;
    C.x = A.x + 1;
    C.y = A.y;
    double wA = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) /
               ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));

    double wB = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) /
               ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));

    double wC = 1 - wA - wB;
    if (0 <= wA && wA <= 1 && 0 <= wB && wB <= 1 && 0 <= wC && wC <= 1)
    {
      //  std::cout <<  this->hidden_grid[static_cast<int>(A.x)][static_cast<int>(A.y)] << std::endl;
      //  std::cout <<  this->hidden_grid[static_cast<int>(B.x)][static_cast<int>(B.y)] << std::endl;
      //  std::cout <<  this->hidden_grid[static_cast<int>(C.x)][static_cast<int>(C.y)] << std::endl;
        chord.i = this->symbol_to_frequency[
            this->hidden_grid[static_cast<int>(A.x)][static_cast<int>(A.y)]];
        std::cout << this->hidden_grid[static_cast<int>(A.x)][static_cast<int>(A.y)];
        chord.ii = this->symbol_to_frequency[
            this->hidden_grid[static_cast<int>(B.x)][static_cast<int>(B.y)]];
        std::cout << this->hidden_grid[static_cast<int>(B.x)][static_cast<int>(B.y)];
        chord.iii = this->symbol_to_frequency[
            this->hidden_grid[static_cast<int>(C.x)][static_cast<int>(C.y)]];
        std::cout << this->hidden_grid[static_cast<int>(C.x)][static_cast<int>(C.y)] << std::endl;
    }
    else
    {
    // std::cout <<  this->hidden_grid[static_cast<int>(A.x) + 1][static_cast<int>(A.y) + 1] << std::endl;
     //   std::cout <<  this->hidden_grid[static_cast<int>(B.x)][static_cast<int>(B.y)] << std::endl;
     //   std::cout <<  this->hidden_grid[static_cast<int>(C.x)][static_cast<int>(C.y)] << std::endl;
        chord.i = this->symbol_to_frequency[
            this->hidden_grid[static_cast<int>(A.x) + 1][static_cast<int>(A.y) + 1]];
        std::cout << this->hidden_grid[static_cast<int>(A.x) + 1][static_cast<int>(A.y) + 1];
        chord.ii = this->symbol_to_frequency[
            this->hidden_grid[static_cast<int>(B.x)][static_cast<int>(B.y)]];
        std::cout << this->hidden_grid[static_cast<int>(B.x)][static_cast<int>(B.y)];
        chord.iii = this->symbol_to_frequency[
            this->hidden_grid[static_cast<int>(C.x)][static_cast<int>(C.y)]];
        std::cout << this->hidden_grid[static_cast<int>(C.x)][static_cast<int>(C.y)] << std::endl;
    }
    return chord;
}

void       Tonnetz::loadFrequency(double tonic)
{
    int i = 0;
    double twelfthRootOfTwo = std::pow(2.0, 1.0 / 12.0);
    this->symbol_to_frequency['0'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['1'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['2'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['3'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['4'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['5'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['6'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['7'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['8'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['9'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['A'] = tonic * std::pow(twelfthRootOfTwo, i++);
    this->symbol_to_frequency['B'] = tonic * std::pow(twelfthRootOfTwo, i++);
}

/*bool     Tonnetz::triangleFinderBis(Pos const &P)
{
    Pos A;
    Pos B;
    Pos C;

    A.x = std::floor(P.x);
    A.y = std::floor(P.y);
    B.x = A.x;
    B.y = A.y + 1;
    C.x = A.x + 1;
    C.y = A.y + 1;

    std::cout << std::endl;
    std::cout << this->crossProduct(P, C)   << std::endl;
    std::cout << this->crossProduct(A, C)   << std::endl;
    std::cout << this->crossProduct(B, C)   << std::endl;
    std::cout << std::endl;
    std::cout << this->crossProduct(P, B)   << std::endl;
    std::cout << this->crossProduct(A, B)   << std::endl;
    std::cout << this->crossProduct(B, C)   << std::endl;
    float alpha = ((this->crossProduct(P, C) - this->crossProduct(A, C))) 
                    / this->crossProduct(B, C);
    std::cout << "alpha " << alpha << std::endl;
    float beta = ((this->crossProduct(P, B) - this->crossProduct(A, B))) 
                    / this->crossProduct(B, C);
    std::cout << "beta " << beta << std::endl;
    if (alpha > 0 && beta > 0)
        if ((alpha + beta) < 1)
            return true;
    return false;
}   */