#include "Polynomial.hpp"
#include <cmath>

using namespace std;

Polynomial::Polynomial(OrderType order) {
    current_order = order;
}

Polynomial::Polynomial(vector<Term> t, OrderType order) {
    terms = t;
    current_order = order;
    sort_terms();
}

bool Polynomial::is_zero() {
    return terms.empty();
}

Term Polynomial::get_leading_term() const {
    return terms[0];
}

vector<Term>& Polynomial::get_terms() {
    return terms;
}

void Polynomial::remove_term(const int index) {
    if (index < terms.size()) {
        terms.erase(terms.begin() + index);
    }
}

void Polynomial::add_term(Term& term) {
    terms.push_back(term);
    sort_terms();
}

void Polynomial::sort_terms() {
    sort(terms.begin(), terms.end(), [this] (Term& a, Term& b) {
        return is_greater(a,b);
    });
}

Polynomial::OrderType& Polynomial::get_current_order() {
    return current_order;
}

bool Polynomial::is_greater(Term& a, Term& b) {
    if (current_order == OrderType::LEX) {
        return a.get_powers() > b.get_powers();
    }
    else if (current_order == OrderType::GRADED_LEX) {
        int sum_a = a.get_total_degree();
        int sum_b = b.get_total_degree();
        if (sum_a != sum_b) {
            return sum_a > sum_b;
        }
        return a.get_powers() > b.get_powers();
    }
    else if (current_order == OrderType::GREVLEX) {
        int sum_a = a.get_total_degree();
        int sum_b = b.get_total_degree();
        if (sum_a != sum_b) {
            return sum_a > sum_b;
        }
        vector<int> a_p = a.get_powers();
        vector<int> b_p = b.get_powers();
        for (int i = a_p.size() - 1; i >= 0; i--) {
            if (a_p[i] != b_p[i]) {
                return a_p[i] < b_p[i];
            }
        }
        return false;
    }
    return false;
}

Polynomial Polynomial::operator +(Polynomial& right) {
    auto it_l = terms.begin();
    auto it_r = right.terms.begin();
    Polynomial result(current_order);
    while (it_l != terms.end() && it_r != terms.end()) {
        if (is_greater(*it_l, *it_r)) {
            result.add_term(*it_l);
            it_l++;
        }
        else if (is_greater(*it_r, *it_l)) {
            result.add_term(*it_r);
            it_r++;
        }
        else if (it_l->get_powers() == it_r->get_powers()) {
            vector<int>& pow = it_l->get_powers();
            Term to_add(pow, it_l->get_coef() + it_r->get_coef());
            result.add_term(to_add);
            it_l++;
            it_r++;
        }
    }
    while (it_l != terms.end()) {
        result.add_term(*it_l);
        it_l++;
    }
    while (it_r != terms.end()) {
        result.add_term(*it_r);
        it_r++;
    }
    return result;
}

Polynomial Polynomial::operator -(Polynomial& right) {
    auto it_l = terms.begin();
    auto it_r = right.terms.begin();
    Polynomial result(current_order);
    
    while (it_l != terms.end() && it_r != right.terms.end()) {
        if (it_l->get_powers() == it_r->get_powers()) {
            vector<int>& pow = it_l->get_powers();
            double diff = it_l->get_coef() - it_r->get_coef();
            
            if (abs(diff) > 1e-9) {
                Term to_add(pow, diff);
                result.add_term(to_add);
            }
            it_l++;
            it_r++;
        }
        else if (is_greater(*it_l, *it_r)) {
            Term first = *it_l;
            result.add_term(first);
            it_l++;
        }
        else if (is_greater(*it_r, *it_l)) {
            Term second = (*it_r) * -1.0;
            result.add_term(second);
            it_r++;
        }
    }
    while (it_l != terms.end()) {
        result.add_term(*it_l);
        it_l++;
    }
    while (it_r != right.terms.end()) {
        Term to_add = (*it_r) * -1.0;
        result.add_term(to_add);
        it_r++;
    }
    return result;
}

Polynomial Polynomial::operator*(Term& term) const {
    Polynomial result = *this;
    for (int i = 0; i < result.terms.size(); i++) {
        result.terms[i] = result.terms[i] * term;
    }
    return result;
}

Polynomial Polynomial::operator *(double coef) const {
    Polynomial res = *this;
    for (auto& t : res.terms) {
        t = t * coef;
    }
    if (res.terms.size() == 0) {
       // cerr << "Returned a 0 polynomial" << endl;
       return res;
    }
    return res;
}

Polynomial Polynomial::operator *(const Polynomial& right) const {
    vector<Term> raw_terms;
    raw_terms.reserve(this->terms.size() * right.terms.size());

    for (const Term& t1 : this->terms) {
        for (const Term& t2 : right.terms) {
            raw_terms.push_back(t1 * t2);
        }
    }

    if (raw_terms.empty()) {
        return Polynomial(current_order);
    }

    Polynomial result(current_order);
    
    sort(raw_terms.begin(), raw_terms.end(),
        [this](Term& a, Term& b) {
            return const_cast<Polynomial*>(this)->is_greater(a, b);
        }
    );

    Term current = raw_terms[0];

    for (size_t i = 1; i < raw_terms.size(); ++i) {
        Term& next = raw_terms[i];

        if (current.get_powers() == next.get_powers()) {
            double new_coeff = current.get_coef() + next.get_coef();
            current = Term(current.get_powers(), new_coeff);
        }
        else {
            if (abs(current.get_coef()) > 1e-9) {
                result.terms.push_back(current);
            }
            current = next;
        }
    }

    if (abs(current.get_coef()) > 1e-9) {
        result.terms.push_back(current);
    }

    return result;
}

Polynomial operator *(double scalar, const Polynomial& p) {
    return p * scalar;
}
