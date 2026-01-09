#include "Buchbergers.hpp"
#include <cmath>

using namespace std;

Term Buchbergers::find_lcm(Term& a, Term& b) {
    vector<int> new_powers;
    double new_coef = a.get_coef() * b.get_coef();
    for (int i = 0; i < a.get_powers().size(); i++) {
        new_powers.push_back(max(a.get_powers()[i], b.get_powers()[i]));
    }
    Term res(new_powers, new_coef);
    return res;
}
Polynomial Buchbergers::find_s_poly(Polynomial p1, Polynomial p2) {
    if (p1.is_zero() || p2.is_zero()) return Polynomial(p1.get_current_order());
    Term l1 = p1.get_leading_term();
    Term l2 = p2.get_leading_term();
    Term lcm = find_lcm(l1, l2);
    
    Term m1 = lcm / l1;
    m1 = m1 * l2.get_coef();

    Term m2 = lcm / l2;
    m2 = m2 * l1.get_coef();

    Polynomial poly1 = p1 * m1;
    Polynomial poly2 = p2 * m2;

    Polynomial res = poly1 - poly2;
    return res;
}

bool Buchbergers::can_divide(Term& divisor, Term& target) {
    const vector<int>& div_pow = divisor.get_powers();
    const vector<int>& tar_pow = target.get_powers();
    
    for (size_t i = 0; i < div_pow.size(); i++) {
        if (div_pow[i] > tar_pow[i]) {
            return false;
        }
    }
    return true;
}

vector<Polynomial> Buchbergers::minimize_basis(vector<Polynomial>& basis) {
    vector<Polynomial> reduced_g;

    for (int i = 0; i < basis.size(); i++) {
        Term current_lm = basis[i].get_leading_term();
        bool redundant = false;
        for (int j = 0; j < basis.size(); j++) {
            if (i == j) continue;
            Term att_lm = basis[j].get_leading_term();
            if (can_divide(att_lm, current_lm)) {
                if (att_lm.get_powers() == current_lm.get_powers()) {
                    if (j < i) {
                        redundant = true;
                        break;
                    }
                }
                else {
                    redundant = true;
                    break;
                }
            }
        }
        if (!redundant) {
            reduced_g.push_back(basis[i]);
        }
    }
    return reduced_g;
}

Polynomial Buchbergers::reduce_poly(Polynomial candidate, vector<Polynomial>& divisors) {
    Polynomial remainder(candidate.get_current_order());
    while (!candidate.is_zero()) {
        bool div_ocurred = false;
        Term candidate_head = candidate.get_leading_term();

        for (auto& div : divisors) {
            Term divisor_head = div.get_leading_term();
           if (can_divide(divisor_head, candidate_head)) {
                div_ocurred = true;
                Term res = candidate_head / divisor_head;
                Polynomial sub = div * res;
                candidate = candidate - sub;
                div_ocurred = true;
                break;
           }
        }
        if (!div_ocurred) {
            remainder.add_term(candidate_head);
            candidate.remove_term(0);
        }
    }
    return remainder;
}

vector<Polynomial> Buchbergers::clean_basis(vector<Polynomial>& basis) {
    vector<Polynomial> cleaned_basis;
    for (int i = 0; i < basis.size(); i++) {
        Polynomial P = basis[i];
        vector<Polynomial> divisors;
        for(int j = 0; j < basis.size(); j++) {
            if(i != j) {
                divisors.push_back(basis[j]);
            }
        }
        Polynomial clean = reduce_poly(P, divisors);
        cleaned_basis.push_back(clean);
    }
    return cleaned_basis;
}

vector<Polynomial> Buchbergers::buchbergers(vector<Polynomial>& F) {
    vector<Polynomial> G = F;

    vector<pair<int,int>> pairs;

    for (int i = 0; i < G.size(); i++) {
        for (int j = i + 1; j < G.size(); j++) {
            pairs.push_back({i, j});
        }
    }
    while (!pairs.empty()) {
        pair<int,int> p = pairs.back();
        pairs.pop_back();
        Polynomial& f = G[p.first];
        Polynomial& g = G[p.second];

        Polynomial s = find_s_poly(f, g);
        Polynomial remainder = reduce_poly(s, G);

        if (!remainder.is_zero()) {
            double lead_coeff = remainder.get_leading_term().get_coef();
            if (abs(lead_coeff) > 1e-9) {
                remainder = remainder * (1.0 / lead_coeff);
            }
            G.push_back(remainder);
            int new_index = G.size() - 1;
            for (int i = 0; i < new_index; i++) {
                pairs.push_back({i, new_index});
            }
        }
    }
    G = minimize_basis(G);
    G = clean_basis(G);
    return G;
}
vector<Polynomial> Buchbergers::solve(vector<Polynomial>& F) {
    vector<Polynomial> G = buchbergers(F);
    return G;
}
