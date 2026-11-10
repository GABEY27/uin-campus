#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

constexpr std::size_t nbMentions = 5;
constexpr double noteMin = 0.0;
constexpr double noteMax = 20.0;
constexpr double seuilValidation = 10.0;
constexpr int nbEtudiantsMin = 1;
constexpr int nbEtudiantsMax = 200;

constexpr double seuilPassable = 12.0;
constexpr double seuilAssezBien = 14.0;
constexpr double seuilBien = 16.0;

Mention mentionPour(double note)
{
    if (note < seuilValidation) { return Mention::Ajourne; }
    if (note < seuilPassable) { return Mention::Passable; }
    if (note < seuilAssezBien) { return Mention::AssezBien; }
    if (note < seuilBien) { return Mention::Bien; }
    return Mention::TresBien;
}

std::string_view libelle(Mention m)
{
    using enum Mention;
    switch (m) {
        case Ajourne: return "Ajourné";
        case Passable: return "Passable";
        case AssezBien: return "Assez bien";
        case Bien: return "Bien";
        case TresBien: return "Très bien";
    }
    return "Inconnue";
}

// Lit un entier entre min et max, redemande si invalide
int lireEntier(std::string_view invite, int min, int max)
{
    while (true) {
        std::cout << invite;
        std::string ligne{};
        if (!std::getline(std::cin, ligne)) {
            return min;
        }
        std::istringstream flux{ligne};
        int val{0};
        char reste{'\0'};
        if (!(flux >> val) || (flux >> reste)) {
            std::cout << "  Saisie invalide.\n";
        } else if (val < min || val > max) {
            std::cout << "  Entrez un nombre entre " << min << " et " << max << ".\n";
        } else {
            return val;
        }
    }
}

// Lit une note entre 0 et 20, accepte la virgule
double lireNote(std::string_view invite)
{
    while (true) {
        std::cout << invite;
        std::string ligne{};
        if (!std::getline(std::cin, ligne)) {
            return noteMin;
        }
        for (char& c : ligne) {
            if (c == ',') { c = '.'; }
        }
        std::istringstream flux{ligne};
        double note{0.0};
        char reste{'\0'};
        if (!(flux >> note) || (flux >> reste)) {
            std::cout << "  Saisie invalide.\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "  La note doit être comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
}

int main()
{
    std::cout << "Nom de l'UE : ";
    std::string ue{};
    std::getline(std::cin, ue);

    const int nb = lireEntier("Nombre d'étudiants (1 à 200) : ", nbEtudiantsMin, nbEtudiantsMax);

    std::vector<double> notes{};
    notes.reserve(static_cast<std::size_t>(nb));
    for (int i = 1; i <= nb; ++i) {
        notes.push_back(lireNote("Note de l'étudiant " + std::to_string(i) + " : "));
    }

    double minimum = notes.at(0);
    double maximum = notes.at(0);
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{0, 0, 0, 0, 0};

    for (double n : notes) {
        minimum = std::min(minimum, n);
        maximum = std::max(maximum, n);
        somme += n;
        if (n >= seuilValidation) { ++admis; }
        repartition.at(static_cast<std::size_t>(mentionPour(n)))++;
    }

    const double moyenne = somme / static_cast<double>(notes.size());

    double sommeEcarts{0.0};
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    const double ecartType = std::sqrt(sommeEcarts / static_cast<double>(notes.size()));
    const double pourcentage = 100.0 * static_cast<double>(admis) / static_cast<double>(notes.size());

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nStatistiques — " << ue << " (" << nb << " étudiants)\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "Note minimale     : " << minimum << '\n';
    std::cout << "Note maximale     : " << maximum << '\n';
    std::cout << "Moyenne           : " << moyenne << '\n';
    std::cout << "Écart-type        : " << ecartType << '\n';
    std::cout << "Admis             : " << admis << " (" << std::setprecision(1) << pourcentage << " %)\n";

    std::cout << "\nRépartition par mention\n";
    for (std::size_t i = 0; i < nbMentions; ++i) {
        const Mention m = static_cast<Mention>(i);
        std::cout << std::left << std::setw(12) << libelle(m) << ' '
                  << std::string(static_cast<std::size_t>(repartition.at(i)), '*')
                  << " (" << repartition.at(i) << ")\n";
    }
    return 0;
}