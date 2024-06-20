#pragma once

#include "Monde.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>

class Jeu {
public:
    Jeu() {
        piecePresente_ = map_.getPieces("Entrance");
        initialiserCommandes();
    }

    ~Jeu() {
        std::cout << "Cleaning up the game resources..." << std::endl;
        piecePresente_.reset();
    }

    void jouer() {
        afficherBanniere();
        std::string commande;

        while (true) {
            piecePresente_->affichage();
            std::cout << "> ";
            std::getline(std::cin, commande);
            if (commande == "exit") {
                std::cout << "Thank you for playing!" << std::endl;
                break;
            }
            traiterCommande(commande);
        }
    }

private:
    Monde map_;
    std::shared_ptr<Piece> piecePresente_;
    std::unordered_map<std::string, std::function<void(const std::string&)>> commandes_;

    void initialiserCommandes() {
        commandes_["move"] = [this](const std::string& args) { deplacer(args); };
        commandes_["look"] = [this](const std::string& args) { regarder(args); };
        commandes_["take"] = [this](const std::string& args) { prendreObjet(args); };
        commandes_["use"] = [this](const std::string& args) { utiliserObjet(args); };
        commandes_["N"] = [this](const std::string& arg) { commandeDeMouvement("N"); };
        commandes_["E"] = [this](const std::string& arg) { commandeDeMouvement("E"); };
        commandes_["S"] = [this](const std::string& arg) { commandeDeMouvement("S"); };
        commandes_["W"] = [this](const std::string& arg) { commandeDeMouvement("W"); };
    }

    void commandeDeMouvement(const std::string& direction) {
        auto nouvellePiece = piecePresente_->getPieceVoisin(direction);
        if (nouvellePiece) {
            piecePresente_ = nouvellePiece;
        }
        else {
            std::cout << "You can't go that way." << std::endl;
        }
    }

    void traiterCommande(const std::string& input) {
        auto pos = input.find(' ');
        std::string commande = (pos == std::string::npos) ? input : input.substr(0, pos);
        std::string args = (pos == std::string::npos) ? "" : input.substr(pos + 1);

        auto it = commandes_.find(commande);
        if (it != commandes_.end()) {
            it->second(args);
        }
        else {
            std::cout << "Invalid command." << std::endl;
        }
    }

    void deplacer(const std::string& direction) {
        if (piecePresente_) {
            auto nextPiece = piecePresente_->getPieceVoisin(direction);
            if (nextPiece) {
                piecePresente_ = nextPiece;
            }
            else {
                std::cout << "You can't move in that direction." << std::endl;
            }
        }
    }

    void regarder(const std::string& args) {
        if (piecePresente_) {
            if (args.empty()) {
                piecePresente_->affichage();
            }
            else {
                auto objet = piecePresente_->getObjet(args);
                if (objet) {
                    std::cout << objet->getDescription() << std::endl;
                }
                else {
                    std::cout << "There is no " << args << " here." << std::endl;
                }
            }
        }
    }

    void prendreObjet(const std::string& nomObjet) {
        if (piecePresente_) {
            auto objet = piecePresente_->retirerObjet(nomObjet);
            if (objet) {
                std::cout << "You picked up the " << nomObjet << "." << std::endl;
            }
            else {
                std::cout << "There is no " << nomObjet << " here." << std::endl;
            }
        }
    }

    void utiliserObjet(const std::string& nomObjet) {
        if (piecePresente_) {
            auto objet = piecePresente_->getObjet(nomObjet);
            if (objet) {
                std::cout << objet->utiliser() << std::endl;
                if (auto cle = std::dynamic_pointer_cast<ObjetCle>(objet)) {
                    auto zoneADeverrouiller = cle->getZoneADeverrouiller();
                    auto zone = map_.getPieces(zoneADeverrouiller);
                    if (zone) {
                        piecePresente_->setVoisins("E", zone); // Assumed 'E' for East; change accordingly.
                        std::cout << "You unlocked the " << zoneADeverrouiller << "." << std::endl;
                    }
                }
            }
            else {
                std::cout << "You don't have a " << nomObjet << " to use." << std::endl;
            }
        }
    }

    void afficherBanniere() {
        std::cout << "\033[1;34mWelcome to the interactive adventure game!\033[0m" << std::endl;
        std::cout << "\033[1;34mType 'exit' to quit.\033[0m" << std::endl;
    }

    void affichageDeLaPiecePresente() const {
        if (piecePresente_) {
            std::cout << "\033[1;32m" << piecePresente_->getNom() << "\033[0m" << std::endl;
            std::cout << piecePresente_->getDescription() << std::endl;
        }
    }
};
