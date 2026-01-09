#ifndef BUCHBERGER_HPP
#define BUCHBERGER_HPP

#include <vector>
#include "Polynomial.hpp"

class Buchbergers {
public:
    
    static std::vector<Polynomial> solve(std::vector<Polynomial>& F);

private:
    
    static Term find_lcm(Term& a, Term& b);
    static Polynomial find_s_poly(Polynomial p1, Polynomial p2);
    static bool can_divide(Term& divisor, Term& target);
    static std::vector<Polynomial> buchbergers(std::vector<Polynomial>& F);
    static Polynomial reduce_poly(Polynomial candidate, std::vector<Polynomial>& divisors);
    static std::vector<Polynomial> minimize_basis(std::vector<Polynomial>& basis);
    static std::vector<Polynomial> clean_basis(std::vector<Polynomial>& basis);
};

#endif
