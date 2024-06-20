#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <vector>
#include "ObjetInteractif.hpp"

class Piece {
public:
    Piece() : nom_(""), description_("") {}
    Piece(const std::string& nom, const std::string& description) : nom_(nom), description_(description) {}

    ~Piece() {
        std::cout << "Destruction of Piece: " << nom_ << std::endl;
    }

    void setVoisins(const std::string& direction, std::shared_ptr<Piece> voisin) {
        pieceVoisins_[direction] = voisin;
    }

    std::string getNom() const { return nom_; }
    std::string getDescription() const { return description_; }
    std::shared_ptr<Piece> getPieceVoisin(const std::string& direction) const {
        auto it = pieceVoisins_.find(direction);

        if (it != pieceVoisins_.end()) {
            return it->second.lock();
        }
        return nullptr;
    }

    void ajouterObjet(std::shared_ptr<ObjetInteractif> objet) {
        objets_.push_back(objet);
    }

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

    std::shared_ptr<ObjetInteractif> getObjet(const std::string& nom) {
        for (auto& objet : objets_) {
            if (objet->getNom() == nom) {
                return objet;
            }
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<ObjetInteractif>> getObjets() const {
        return objets_;
    }

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
