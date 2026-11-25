#include "calculs.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
namespace uin {
double somme(std::span<const double> valeurs) { return std::accumulate(valeurs.begin(), valeurs.end(), 0.0); }
double moyenne(std::span<const double> notes) {
    assert(!notes.empty());
    return somme(notes) / static_cast<double>(notes.size());
}
double moyenne(std::span<const double> notes, std::span<const double> coefficients) {
    assert(!notes.empty() && notes.size() == coefficients.size());
    double s{0.0}; double sc{0.0};
    for (std::size_t i{0}; i < notes.size(); ++i) { s += notes[i] * coefficients[i]; sc += coefficients[i]; }
    return s / sc;
}
Statistiques calculerStatistiques(std::span<const double> notes) {
    assert(!notes.empty());
    const double m = moyenne(notes);
    double var{0.0};
    for (double n : notes) var += (n - m) * (n - m);
    var /= static_cast<double>(notes.size());
    return {*std::min_element(notes.begin(), notes.end()), *std::max_element(notes.begin(), notes.end()), m, std::sqrt(var)};
}
int compterValidees(std::span<const double> notes, double seuil) {
    int c{0}; for (double n : notes) if (n >= seuil) ++c; return c;
}
double arrondir(double valeur, int decimales) {
    const double f = std::pow(10.0, decimales);
    return std::round(valeur * f) / f;
}
}
