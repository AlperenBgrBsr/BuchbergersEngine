#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Buchbergers.hpp"

using namespace std;

void print_poly(Polynomial& p) {
    if (p.is_zero()) {
        cout << "0" << endl;
        return;
    }

    vector<Term>& terms = p.get_terms();
    for (size_t i = 0; i < terms.size(); i++) {
        Term& t = terms[i];
        double coef = t.get_coef();
        vector<int>& pows = t.get_powers();

        
        if (coef >= 0 && i > 0) cout << " + ";
        else if (coef < 0) cout << " - ";
        
        
        cout << abs(coef);

        string vars[] = {"x", "y", "z"};
        for (size_t j = 0; j < pows.size(); j++) {
            if (j < 3 && pows[j] > 0) {
                cout << vars[j];
                if (pows[j] > 1) cout << "^" << pows[j];
            }
        }
    }
    cout << endl;
}

void test_two_circles() {
    cout << "=== Running Test: Two Circles Intersection ===" << endl;
    cout << "Circle 1: x^2 + y^2 - 1 = 0" << endl;
    cout << "Circle 2: x^2 + y^2 - 4y = 0" << endl;

    // Index 0 = x, Index 1 = y
    vector<int> pow_x2 = {2, 0}; // x^2
    vector<int> pow_y2 = {0, 2}; // y^2
    vector<int> pow_y1 = {0, 1}; // y^1
    vector<int> pow_c  = {0, 0}; // Constant (degree 0)

    // Polynomial 1: x^2 + y^2 - 1
    vector<Term> t1;
    t1.push_back(Term(pow_x2, 1.0));
    t1.push_back(Term(pow_y2, 1.0));
    t1.push_back(Term(pow_c, -1.0));
    Polynomial p1(t1, Polynomial::OrderType::GREVLEX);

    // Polynomial 2: x^2 + y^2 - 4y
    vector<Term> t2;
    t2.push_back(Term(pow_x2, 1.0));
    t2.push_back(Term(pow_y2, 1.0));
    t2.push_back(Term(pow_y1, -4.0));
    Polynomial p2(t2, Polynomial::OrderType::GREVLEX);

    vector<Polynomial> basis;
    basis.push_back(p1);
    basis.push_back(p2);

    vector<Polynomial> gb = Buchbergers::solve(basis);
    
    cout << "-----------------------" << endl;
    cout << "Reduced Groebner Basis:" << endl;
    for (auto& p : gb) {
        print_poly(p);
    }
    cout << "-----------------------" << endl;
}

void test_no_solution() {
    cout << "\n=== Running Test: No Solution (Parallel Lines) ===" << endl;
    cout << "Line 1: x + y = 1" << endl;
    cout << "Line 2: x + y = 3" << endl;

    vector<int> px = {1, 0};
    vector<int> py = {0, 1};
    vector<int> pc = {0, 0};

    // P1: x + y - 1
    vector<Term> t1;
    t1.push_back(Term(px, 1.0));
    t1.push_back(Term(py, 1.0));
    t1.push_back(Term(pc, -1.0));
    Polynomial p1(t1, Polynomial::OrderType::GREVLEX);

    // P2: x + y - 3
    vector<Term> t2;
    t2.push_back(Term(px, 1.0));
    t2.push_back(Term(py, 1.0));
    t2.push_back(Term(pc, -3.0));
    Polynomial p2(t2, Polynomial::OrderType::GREVLEX);

    vector<Polynomial> basis = {p1, p2};
    vector<Polynomial> gb = Buchbergers::solve(basis);

    cout << "-----------------------" << endl;
    cout << "Reduced Groebner Basis (Expected: 1):" << endl;
    for (auto& p : gb) print_poly(p);
    cout << "-----------------------" << endl;
}

void test_twisted_cubic() {
    cout << "\n=== Running Test: Twisted Cubic ===" << endl;
    cout << "Relations: y - x^2 = 0, z - xy = 0" << endl;

    vector<int> p_y  = {0, 1, 0};
    vector<int> p_x2 = {2, 0, 0};
    vector<int> p_z  = {0, 0, 1};
    vector<int> p_xy = {1, 1, 0};

    // P1: y - x^2
    vector<Term> t1;
    t1.push_back(Term(p_y, 1.0));
    t1.push_back(Term(p_x2, -1.0));
    Polynomial p1(t1, Polynomial::OrderType::GREVLEX);

    // P2: z - xy
    vector<Term> t2;
    t2.push_back(Term(p_z, 1.0));
    t2.push_back(Term(p_xy, -1.0));
    Polynomial p2(t2, Polynomial::OrderType::GREVLEX);

    vector<Polynomial> basis = {p1, p2};
    vector<Polynomial> gb = Buchbergers::solve(basis);

    cout << "-----------------------" << endl;
    cout << "Reduced Groebner Basis:" << endl;
    for (auto& p : gb) print_poly(p);
    cout << "-----------------------" << endl;
}

void test_cyclic3() {
    cout << "\n=== Running Test: Cyclic-3 System ===" << endl;
    cout << "1. x + y + z = 0" << endl;
    cout << "2. xy + xz + yz = 0" << endl;
    cout << "3. xyz - 1 = 0" << endl;

    vector<int> x={1,0,0}, y={0,1,0}, z={0,0,1};
    vector<int> xy={1,1,0}, xz={1,0,1}, yz={0,1,1};
    vector<int> xyz={1,1,1}, c={0,0,0};

    // P1: x + y + z
    vector<Term> t1;
    t1.push_back(Term(x, 1.0)); t1.push_back(Term(y, 1.0)); t1.push_back(Term(z, 1.0));
    Polynomial p1(t1, Polynomial::OrderType::GREVLEX);

    // P2: xy + xz + yz
    vector<Term> t2;
    t2.push_back(Term(xy, 1.0)); t2.push_back(Term(xz, 1.0)); t2.push_back(Term(yz, 1.0));
    Polynomial p2(t2, Polynomial::OrderType::GREVLEX);

    // P3: xyz - 1
    vector<Term> t3;
    t3.push_back(Term(xyz, 1.0)); t3.push_back(Term(c, -1.0));
    Polynomial p3(t3, Polynomial::OrderType::GREVLEX);

    vector<Polynomial> basis = {p1, p2, p3};
    vector<Polynomial> gb = Buchbergers::solve(basis);

    cout << "-----------------------" << endl;
    cout << "Reduced Groebner Basis (Check for z^3 - 1):" << endl;
    for (auto& p : gb) print_poly(p);
    cout << "-----------------------" << endl;
}

int main() {
    test_two_circles();
    test_no_solution();
    test_twisted_cubic();
    test_cyclic3();
    return 0;
}
