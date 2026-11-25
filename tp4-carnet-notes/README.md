# TP4 - Carnet de notes (C++20 - Fonctions)

Programme qui gere le carnet de notes d'une UE avec un menu.

## Fonctionnalites
1. Ajouter / 2. Afficher / 3. Modifier / 4. Supprimer
5. Trier (croissant / decroissant) / 6. Statistiques / 7. Bonus

## Notions du chapitre 4 appliquees
- Namespace `carnet`, tout sauf `main` est dedans
- Passage par `const vector<double>&` en lecture, par `vector<double>&` en modification
- Retour par `struct Statistiques` + liaison structuree
- Lambdas pour `sort` et `for_each`
- `[[nodiscard]]`, `assert` pour les preconditions, `std::clamp` pour borner a 20

## Compilation
```bash
cmake -S . -B build
cmake --build build
./build/tp4