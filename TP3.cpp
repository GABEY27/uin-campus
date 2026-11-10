#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// Remplace la virgule par un point : 12,5 -> 12.5
double convertirNote(string s) {
    for (char &c : s) {
        if (c == ',') c = '.';
    }
    return stod(s);
}

// Lit un entier entre min et max, redemande si invalide
int lireEntier(string invite, int min, int max) {
    while (true) {
        cout << invite;
        string ligne;
        getline(cin, ligne);
        try {
            int val = stoi(ligne);
            if (val >= min && val <= max) return val;
            cout << "Erreur : entrez un nombre entre " << min << " et " << max << endl;
        } catch (...) {
            cout << "Erreur : entrez un nombre entier." << endl;
        }
    }
}

// Lit une note entre 0 et 20, accepte la virgule
double lireNote(string invite) {
    while (true) {
        cout << invite;
        string ligne;
        getline(cin, ligne);
        try {
            double note = convertirNote(ligne);
            if (note >= 0 && note <= 20) return note;
            cout << "Erreur : la note doit etre entre 0 et 20." << endl;
        } catch (...) {
            cout << "Erreur : entrez une note valide ex: 12,5" << endl;
        }
    }
}

// 0=Ajourne, 1=Passable, 2=Assez bien, 3=Bien, 4=Tres bien
int mentionPour(double note) {
    if (note < 10) return 0;
    if (note < 12) return 1;
    if (note < 14) return 2;
    if (note < 16) return 3;
    return 4;
}

int main() {
    cout << "Nom de l'UE : ";
    string ue;
    getline(cin, ue);

    int nb = lireEntier("Nombre d'etudiants (1 a 200) : ", 1, 200);

    vector<double> notes;
    for (int i = 1; i <= nb; i++) {
        notes.push_back(lireNote("Note de l'etudiant " + to_string(i) + " : "));
    }

    double minimum = notes[0];
    double maximum = notes[0];
    double somme = 0;
    int admis = 0;
    int repartition[5] = {0, 0, 0, 0, 0};

    for (double n : notes) {
        minimum = min(minimum, n);
        maximum = max(maximum, n);
        somme += n;
        if (n >= 10) admis++;
        repartition[mentionPour(n)]++;
    }

    double moyenne = somme / notes.size();

    double sommeEcarts = 0;
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    double ecartType = sqrt(sommeEcarts / notes.size());
    double pourcentage = 100.0 * admis / notes.size();

    string noms[5] = {"Ajourne", "Passable", "Assez bien", "Bien", "Tres bien"};

    cout << fixed << setprecision(2);
    cout << "\nStatistiques - " << ue << " (" << nb << " etudiants)" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Note minimale : " << minimum << endl;
    cout << "Note maximale : " << maximum << endl;
    cout << "Moyenne : " << moyenne << endl;
    cout << "Ecart-type : " << ecartType << endl;
    cout << "Admis : " << admis << " (" << setprecision(1) << pourcentage << " %)" << endl;
    cout << "\nRepartition par mention" << endl;
    cout << setprecision(0);
    for (int i = 0; i < 5; i++) {
        cout << left << setw(12) << noms[i] << " ";
        for (int j = 0; j < repartition[i]; j++) cout << "*";
        cout << " (" << repartition[i] << ")" << endl;
    }
    return 0;
}