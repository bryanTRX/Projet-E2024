#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "ObjetInteractif.hpp"

using namespace std;

// La classe Piece représente une pièce dans le jeu, avec ses voisins et objets interactifs.
class Piece 
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur par défaut 
    Piece() : nom_(""), description_("") {}

    // Constructeur initialisant une pièce avec un nom et une description spécifiés.
    Piece(const string& nom, const string& description) : nom_(nom), description_(description) {}

    // Destructeurs -------------------------------------------------------------------------------------------------------------------------------------

    // Destructeur de la classe Piece
    ~Piece() { cout << "Destruction of Piece: " << nom_ << endl; }

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Méthode pour définir un voisin pour cette pièce dans une direction spécifiée.
    void setVoisins(const string& direction, shared_ptr<Piece> voisin) { pieceVoisins_[direction] = voisin; }

    // Méthode pour obtenir le nom de la pièce.
    string getNom() const { return nom_; }

    // Méthode pour obtenir la description de la pièce.
    string getDescription() const { return description_; }

    // Méthode pour obtenir un voisin de la pièce dans une direction spécifiée.
    shared_ptr<Piece> getPieceVoisin(const string& direction) const 
    {
        auto it = pieceVoisins_.find(direction);

        if (it != pieceVoisins_.end())
        {
            return it->second.lock();
        }
        return nullptr;
    }

    // Méthode pour ajouter un objet interactif à la pièce.
    void ajouterObjet(shared_ptr<ObjetInteractif> objet) { objets_.push_back(objet); }

    // Méthode pour retirer un objet interactif de la pièce par son nom. Retourne un pointeur  vers l'objet retiré ou nullptr si l'objet n'est pas trouvé.
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

    // Méthode pour obtenir un objet interactif de la pièce par son nom. Retourne un pointeur vers l'objet ou nullptr si l'objet n'est pas trouvé.
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

    // Méthode pour obtenir tous les objets interactifs de la pièce.
    vector<shared_ptr<ObjetInteractif>> getObjets() const { return objets_; }

    // Méthode pour afficher les informations de la pièce, y compris ses voisins et objets.
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
