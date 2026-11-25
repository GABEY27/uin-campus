#pragma once
#include <vector>

namespace carnet {

enum class Ordre { Croissant, Decroissant };

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    int nbValidees{};
};

// --- Saisie (interface) ---
[[nodiscard]] int lireEntier(const char* invite, int min, int max);
[[nodiscard]] double lireNote(const char* invite);

// --- Calculs : aucune entree-sortie ici ---
/// @pre notes n'est pas vide
[[nodiscard]] Statistiques calculerStatistiques(const std::vector<double>& notes);
void appliquerBonus(std::vector<double>& notes, double bonus);
void trier(std::vector<double>& notes, Ordre ordre);

// --- Interface : une fonction par option du menu ---
void ajouter(std::vector<double>& notes);
void afficherNotes(const std::vector<double>& notes);
void modifier(std::vector<double>& notes);
void supprimer(std::vector<double>& notes);
void afficherStatistiques(const std::vector<double>& notes);
[[nodiscard]] int afficherMenu();

} // namespace carnet