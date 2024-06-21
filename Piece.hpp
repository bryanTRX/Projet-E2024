#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "ObjetInteractif.hpp"

// La classe Piece représente une pièce dans le jeu, avec ses voisins et objets interactifs.
class Piece {
public:
    // Constructeur par défaut 
    Piece() : nom_(""), description_("") {}

    // Constructeur initialisant une pièce avec un nom et une description spécifiés.
    Piece(const std::string& nom, const std::string& description) : nom_(nom), description_(description) {}

    // Destructeur de la classe Piece
    ~Piece() {
        std::cout << "Destruction of Piece: " << nom_ << std::endl;
    }

    // Méthode pour définir un voisin pour cette pièce dans une direction spécifiée.
    void setVoisins(const std::string& direction, std::shared_ptr<Piece> voisin) {
        pieceVoisins_[direction] = voisin;
    }

    // Méthode pour obtenir le nom de la pièce.
    std::string getNom() const { return nom_; }

    // Méthode pour obtenir la description de la pièce.
    std::string getDescription() const { return description_; }

    // Méthode pour obtenir un voisin de la pièce dans une direction spécifiée.
    std::shared_ptr<Piece> getPieceVoisin(const std::string& direction) const {
        auto it = pieceVoisins_.find(direction);
        if (it != pieceVoisins_.end()) {
            return it->second.lock();
        }
        return nullptr;
    }

    // Méthode pour ajouter un objet interactif à la pièce.
    void ajouterObjet(std::shared_ptr<ObjetInteractif> objet) {
        objets_.push_back(objet);
    }

    // Méthode pour retirer un objet interactif de la pièce par son nom. Retourne un pointeur  vers l'objet retiré ou nullptr si l'objet n'est pas trouvé.
    std::shared_ptr<ObjetInteractif> retirerObjet(const std::string& nom) {
        for (auto it = objets_.begin(); it != objets_.end(); ++it) {
            if ((*it)->getNom() == nom) {
                auto obj = *it;
                objets_.erase(it);
                return obj;
            }
        }
        return nullptr;
    }

    // Méthode pour obtenir un objet interactif de la pièce par son nom. Retourne un pointeur vers l'objet ou nullptr si l'objet n'est pas trouvé.
    std::shared_ptr<ObjetInteractif> getObjet(const std::string& nom) {
        for (auto& objet : objets_) {
            if (objet->getNom() == nom) {
                return objet;
            }
        }
        return nullptr;
    }

    // Méthode pour obtenir tous les objets interactifs de la pièce.
    std::vector<std::shared_ptr<ObjetInteractif>> getObjets() const {
        return objets_;
    }

    // Méthode pour afficher les informations de la pièce, y compris ses voisins et objets.
    void affichage() const {
        std::cout << "-- " << nom_ << " --" << std::endl;
        std::cout << description_ << std::endl;

        for (const auto& voisins : pieceVoisins_) {
            std::string direction = voisins.first;
            std::string directionComplete;
            if (direction == "N") directionComplete = "North (N)";
            else if (direction == "E") directionComplete = "East (E)";
            else if (direction == "S") directionComplete = "South (S)";
            else if (direction == "W") directionComplete = "West (W)";

            if (auto voisin = voisins.second.lock()) {
                std::cout << "To the " << voisins.first << " there is " << voisin->getNom() << " " << directionComplete << std::endl;
            }
        }

        if (!objets_.empty()) {
            std::cout << "Objects in this room: " << std::endl;
            for (const auto& objet : objets_) {
                std::cout << "- " << objet->getNom() << std::endl;
            }
        }
    }

private:
    std::string nom_;
    std::string description_;
    std::map<std::string, std::weak_ptr<Piece>> pieceVoisins_;
    std::vector<std::shared_ptr<ObjetInteractif>> objets_;
};