#include "carnet/carnet.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>

namespace carnet {

// ---------- Saisie ----------
int lireEntier(const char* invite, int min, int max) {
    for (;;) {
        std::cout << invite;
        int valeur{};
        if (std::cin >> valeur && valeur >= min && valeur <= max) {
            return valeur;
        }
        std::cout << "Saisie invalide, entre " << min << " et " << max << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double lireNote(const char* invite) {
    for (;;) {
        std::cout << invite;
        double note{};
        if (std::cin >> note && note >= 0.0 && note <= 20.0) {
            return note;
        }
        std::cout << "Note invalide, entre 0 et 20.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// ---------- Calculs : purs, testables sans clavier ----------
Statistiques calculerStatistiques(const std::vector<double>& notes) {
    assert(!notes.empty() && "calculerStatistiques : notes vide");
    const auto [mini, maxi] = std::ranges::minmax(notes);

    double somme{0.0};
    int validees{0};
    for (double n : notes) {
        somme += n;
        if (n >= 10.0) ++validees;
    }
    return {mini, maxi, somme / static_cast<double>(notes.size()), validees};
}

void appliquerBonus(std::vector<double>& notes, double bonus) {
    // Lambda avec capture par valeur de bonus
    std::ranges::for_each(notes, [bonus](double& n) {
        n = std::clamp(n + bonus, 0.0, 20.0);
    });
}

void trier(std::vector<double>& notes, Ordre ordre) {
    if (ordre == Ordre::Croissant) {
        std::ranges::sort(notes);
    } else {
        // Lambda comparateur decroissant
        std::ranges::sort(notes, [](double a, double b) { return a > b; });
    }
}

// ---------- Interface ----------
void afficherNotes(const std::vector<double>& notes) {
    if (notes.empty()) {
        std::cout << "Aucune note.\n";
        return;
    }
    for (std::size_t i{0}; i < notes.size(); ++i) {
        std::cout << i + 1 << ". " << notes[i] << '\n';
    }
}

void ajouter(std::vector<double>& notes) {
    notes.push_back(lireNote("Note a ajouter (0-20) : "));
}

void modifier(std::vector<double>& notes) {
    if (notes.empty()) {
        std::cout << "Aucune note a modifier.\n";
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numero de la note : ", 1, static_cast<int>(notes.size()));
    notes[static_cast<std::size_t>(rang - 1)] = lireNote("Nouvelle valeur : ");
}

void supprimer(std::vector<double>& notes) {
    if (notes.empty()) {
        std::cout << "Aucune note a supprimer.\n";
        return;
    }
    afficherNotes(notes);
    const int rang = lireEntier("Numero de la note : ", 1, static_cast<int>(notes.size()));
    notes.erase(notes.begin() + (rang - 1));
}

void afficherStatistiques(const std::vector<double>& notes) {
    if (notes.empty()) {
        std::cout << "Aucune note.\n";
        return;
    }
    // Liaison structuree
    const auto [mini, maxi, moyenne, validees] = calculerStatistiques(notes);
    std::cout << "Min " << mini << " | Max " << maxi
              << " | Moyenne " << moyenne
              << " | Validees " << validees << '/' << notes.size() << '\n';
}

int afficherMenu() {
    std::cout << "\n=== Carnet de notes ===\n"
              << "1. Ajouter une note\n"
              << "2. Afficher les notes\n"
              << "3. Modifier une note\n"
              << "4. Supprimer une note\n"
              << "5. Trier les notes\n"
              << "6. Statistiques\n"
              << "7. Appliquer un bonus\n"
              << "0. Quitter\n";
    return lireEntier("Votre choix : ", 0, 7);
}

} // namespace carnet