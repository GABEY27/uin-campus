#include "carnet/carnet.hpp"
#include <vector>

int main() {
    std::vector<double> notes;
    int choix{};

    do {
        choix = carnet::afficherMenu();
        switch (choix) {
            case 1: carnet::ajouter(notes); break;
            case 2: carnet::afficherNotes(notes); break;
            case 3: carnet::modifier(notes); break;
            case 4: carnet::supprimer(notes); break;
            case 5: {
                const int sens = carnet::lireEntier("1. Croissant 2. Decroissant : ", 1, 2);
                carnet::trier(notes, sens == 1 ? carnet::Ordre::Croissant
                                               : carnet::Ordre::Decroissant);
                break;
            }
            case 6: carnet::afficherStatistiques(notes); break;
            case 7: carnet::appliquerBonus(notes, carnet::lireNote("Bonus : ")); break;
            default: break;
        }
    } while (choix != 0);
    return 0;
}