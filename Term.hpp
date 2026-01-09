#ifndef TERM_HPP
#define TERM_HPP

#include <vector>

class Term {
    private:
        std::vector<int> powers;
        double coefficient;

    public:
        Term(std::vector<int>& pow, double coef);
        
        int get_total_degree() const;
        std::vector<int>& get_powers();
        double get_coef() const;

        bool operator == (const Term& other);
        Term operator / (const Term& right) const;
        Term operator / (double scalar);
        Term operator *(double scalar) const;
        Term operator *(const Term& other) const;
};

// Global operator overload for double * Term
Term operator*(double scalar, const Term& t);

#endif
