# TP6 - Bibliotheques et modules

## Partie A - Bibliotheques a la main
- Statique : `ar rcs libuincalculs.a`, executable 31568 octets, `Moyenne: 12.75 - Assez bien`
- Dynamique : executable 24872 octets. Sans LD_LIBRARY_PATH : `error while loading shared libraries: libuincalculs.so: cannot open shared object file`
- Avec `LD_LIBRARY_PATH=.` : `Moyenne: 12.75 - Assez bien`
- Statique > Dynamique : le statique contient le code de la biblio.
- `nm -C calculs.o` : `U pow`, `U sqrt` = definis ailleurs (libm / libstdc++), l'editeur de liens les resoudra. `T uin::arrondir(double, int)`
- `nm` sans -C : `_ZN3uin8arrondirEdi`, `c++filt` -> `uin::arrondir(double, int)`
- `ldd ./bulletin_dyn` : `libuincalculs.so => not found` sans LD_LIBRARY_PATH, `libstdc++.so.6`, `libm.so.6`, `libc.so.6`

## Partie B - Module C++20 (GCC 15.2.0, CMake 3.28+, Ninja)
- `cmake --build build` puis `./build/demo` affiche `Bien`
- B.2 Retirer `export` devant `namespace uin` : `error: 'uin' has not been declared`, main ne voit plus `libelle` / `mentionPour`
- B.3 Fonction non exportee dans regles.cppm : invisible hors du module, meme erreur, sans besoin d'espace de noms anonyme
- B.4 Macro `#define SEUIL 10` dans fragment global : `SEUIL NON visible dans main.cpp`. Les macros ne traversent jamais un module.
- `import std;` : C++23, teste selon compilateur (GCC 15 OK).

## Partie C - Temps de compilation / PCH
- `target_precompile_headers(uin_regles PRIVATE <array> <string_view> <span> <vector> <cmath>)` : en-tetes lourds compiles une fois.
- Modifier `regles_impl.cpp` (.cpp) : 1 seul fichier recompile + link.
- Modifier `regles.cppm` (interface) : cascade, tous les importateurs recompilent (regles + impl + main).
- Meme principe que regles.hpp dans UIN-Campus : modifier un en-tete recompile tous ses includers.

## Correctif Partie C - PCH et modules
- PCH teste sur le module : ECHEC. `target_precompile_headers` injecte `-include cmake_pch.hxx` avant `module;`, GCC : `module-declaration only permitted as first declaration`.
- Conclusion : PCH = pour bibliotheque classique a en-tetes (Partie A / UIN-Campus), PAS pour un module C++20.
- Apres retrait du PCH, rebuild : `Bien`.
