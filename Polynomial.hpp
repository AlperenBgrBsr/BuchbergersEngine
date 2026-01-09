#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>
#include <algorithm>
#include <iostream>
#include "Term.hpp"

class Polynomial {
    public:
        enum class OrderType {
            LEX,
            GRADED_LEX,
            GREVLEX
        };

        Polynomial(OrderType order);
        Polynomial(std::vector<Term> t, OrderType order);

        bool is_zero();
        Term get_leading_term() const;
        std::vector<Term>& get_terms();
        
        void remove_term(const int index);
        void add_term(Term& term);
        OrderType& get_current_order();
        bool is_greater(Term& a, Term& b);

        // Operator Overloads
        Polynomial operator +(Polynomial& right);
        Polynomial operator -(Polynomial& right);
        Polynomial operator *(Term& term) const;
        Polynomial operator *(double coef) const;
        Polynomial operator *(const Polynomial& right) const;

    private:
        OrderType current_order;
        std::vector<Term> terms;
        void sort_terms();
};

// Global operator overload for double * Polynomial
Polynomial operator *(double scalar, const Polynomial& p);

#endif
