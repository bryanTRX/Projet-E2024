#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "ObjetInteractif.hpp"

using namespace std;

// La classe Piece repr�sente une pi�ce dans le jeu, avec ses voisins et objets interactifs.
class Piece 
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur par d�faut 
    Piece() : nom_(""), description_("") {}

    // Constructeur initialisant une pi�ce avec un nom et une description sp�cifi�s.
    Piece(const string& nom, const string& description) : nom_(nom), description_(description) {}

    // Destructeurs -------------------------------------------------------------------------------------------------------------------------------------

    // Destructeur de la classe Piece
    ~Piece() { cout << "Destruction of Piece: " << nom_ << endl; }

    // M�thodes -----------------------------------------------------------------------------------------------------------------------------------------

    // M�thode pour d�finir un voisin pour cette pi�ce dans une direction sp�cifi�e.
    void setVoisins(const string& direction, shared_ptr<Piece> voisin) { pieceVoisins_[direction] = voisin; }

    // M�thode pour obtenir le nom de la pi�ce.
    string getNom() const { return nom_; }

    // M�thode pour obtenir la description de la pi�ce.
    string getDescription() const { return description_; }

    // M�thode pour obtenir un voisin de la pi�ce dans une direction sp�cifi�e.
    shared_ptr<Piece> getPieceVoisin(const string& direction) const 
    {
        auto it = pieceVoisins_.find(direction);

        if (it != pieceVoisins_.end())
        {
            return it->second.lock();
        }
        return nullptr;
    }

    // M�thode pour ajouter un objet interactif � la pi�ce.
    void ajouterObjet(shared_ptr<ObjetInteractif> objet) { objets_.push_back(objet); }

    // M�thode pour retirer un objet interactif de la pi�ce par son nom. Retourne un pointeur  vers l'objet retir� ou nullptr si l'objet n'est pas trouv�.
    shared_ptr<ObjetInteractif> retirerObjet(const string& nom) 
    {
        for (auto it = objets_.begin(); it != objets_.end(); ++it) 
        {
            if ((*it)->getNom() == nom)
            {
                auto obj = *it;
                objets_.erase(it);
                return obj;
            }
        }
        return nullptr;
    }

    // M�thode pour obtenir un objet interactif de la pi�ce par son nom. Retourne un pointeur vers l'objet ou nullptr si l'objet n'est pas trouv�.
    shared_ptr<ObjetInteractif> getObjet(const string& nom)
    {
        for (auto& objet : objets_)
        {
            if (objet->getNom() == nom) 
            {
                return objet;
            }
        }
        return nullptr;
    }

    // M�thode pour obtenir tous les objets interactifs de la pi�ce.
    vector<shared_ptr<ObjetInteractif>> getObjets() const { return objets_; }

    // M�thode pour afficher les informations de la pi�ce, y compris ses voisins et objets.
    void affichage() const 
    {
        cout << "\n\033[94m-- " << nom_ << " -- \033[0m" << endl;
        cout << "\033[94m" << description_ << "\033[0m" << endl;

        for (const auto& voisins : pieceVoisins_)
        {
            string direction = voisins.first;
            string directionComplete;

            if (direction == "N") directionComplete = "North (N)";
            else if (direction == "E") directionComplete = "East (E)";
            else if (direction == "S") directionComplete = "South (S)";
            else if (direction == "W") directionComplete = "West (W)";

            if (auto voisin = voisins.second.lock())
            {
                cout << "To the " << voisins.first << " there is " << voisin->getNom() << " " << directionComplete << endl;
            }
        }

        if (!objets_.empty()) 
        {
            cout << "Objects in this room: " << endl;
            for (const auto& objet : objets_) 
            {
                cout << "- " << objet->getNom() << endl;
            }
        }
    }

private:
    string nom_;
    string description_;
    map<string, weak_ptr<Piece>> pieceVoisins_;
    vector<shared_ptr<ObjetInteractif>> objets_;
};
