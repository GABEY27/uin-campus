#include "calculs.hpp"
#include <iostream>
#include <vector>
int main() {
    std::vector<double> notes{12.0, 15.5, 9.0, 14.5};
    const double m = uin::arrondir(uin::moyenne(notes));
    std::cout << "Moyenne: " << m << " - " << uin::libelle(uin::mentionPour(m)) << "\n";
}
