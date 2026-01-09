#include "Term.hpp"

using namespace std;

Term::Term(vector<int>& pow, double coef) {
    powers = pow;
    coefficient = coef;
}

int Term::get_total_degree() const {
    int sum = 0;
    for (auto& pow : powers) {
        sum += pow;
    }
    return sum;
}

vector<int>& Term::get_powers() {
    return powers;
}

double Term::get_coef() const {
    return coefficient;
}

bool Term::operator == (const Term& other) {
    return (powers == other.powers && coefficient == other.coefficient);
}

Term Term::operator / (const Term& right) const {
    vector<int> new_powers;
    double new_coef = coefficient / right.coefficient;
    for (int i = 0; i < powers.size(); i++) {
        new_powers.push_back(powers[i] - right.powers[i]);
    }
    Term res(new_powers, new_coef);
    return res;
}

Term Term::operator / (double scalar) {
    Term res(powers, coefficient / scalar);
    return res;
}

Term Term::operator *(double scalar) const {
    Term res = *this;
    res.coefficient *= scalar;
    return res;
}

Term Term::operator *(const Term& other) const {
    double new_coef = other.coefficient * coefficient;
    vector<int> new_pows;
    const vector<int>& orig_pows = this->powers;
    const vector<int>& other_pows = other.powers;
    
    new_pows.reserve(orig_pows.size());
    for (int i = 0; i < powers.size(); i++) {
        new_pows.push_back(orig_pows[i] + other_pows[i]);
    }
    return Term(new_pows, new_coef);
}

Term operator*(double scalar, const Term& t) {
    return t * scalar;
}
