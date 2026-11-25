# TP5 - Reinventer std::vector pour comprendre

## Partie A - Tableau dynamique a la C
TableauDynamique { double* donnees, taille, capacite }
ajouter() : si plein, alloue 2x plus grand (4 au 1er ajout), copie, delete[] ancien, met a jour pointeur + capacite.
Capacites observees : 4,4,4,4,8,8,8,8,16,16
liberer() : delete[], nullptr, taille=0, capacite=0.
element() : assert(i < taille), retourne double&.

Tests sanitizers :
- Sans liberer() -> LeakSanitizer : Direct leak of 128 byte(s) (16 x 8 octets)
- delete au lieu de delete[] -> ASan : alloc-dealloc-mismatch

## Partie B - Piege de la copie
TableauDynamique copie = notes; copie membre par membre, meme adresse.
liberer(copie) + liberer(notes) -> ASan : attempting double-free.
Correction : copie profonde (regle des 3/5, chapitre 9).

## Partie C - std::vector
Meme resultat en 5 lignes, copie profonde automatique, liberation automatique.
Aucun new, aucun delete, aucune fuite possible.

## Compilation
cmake -B build && cmake --build build
./build/tp5
cmake -B build-san -DUSE_SANITIZERS=ON && cmake --build build-san
./build-san/tp5
