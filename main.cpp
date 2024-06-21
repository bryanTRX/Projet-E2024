// Programme contenant le projet.
// file		main.cpp
// author	Iliass Khider et Bryan Alexandre Tavares
// date		4 mai 2024
// Créé le	10 mai 2024

#include "Jeu.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <set>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"

int main() 
{
#pragma region "Bibliothèque du cours"
    // Permet sous Windows les "ANSI escape code" pour changer de couleur
    // https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
    // les supportent normalement par défaut.
    bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

    Jeu game;
    game.jouer();
    return 0;
}