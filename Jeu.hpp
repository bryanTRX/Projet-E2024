// Jeu.hpp

#pragma once

#include "Monde.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>   

// La classe Jeu représente le jeu principal.
class Jeu {
public:
    // Constructeur initialisant le jeu et définissant la pièce présente à l'entrée.
    Jeu() {
        piecePresente_ = map_.getPieces("Entrance");
        initialiserCommandes();
    }

    // Destructeur du jeu, libérant les ressources utilisées.
    ~Jeu() {
        std::cout << "Cleaning up the game resources..." << std::endl;
        piecePresente_.reset();
    }

    // Méthode principale pour jouer au jeu.Elle affiche la bannière de bienvenue, les informations de la pièce présente et traite la commande entrée par l'utilisateur.
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
    std::shared_ptr<Piece> piecePresente_;  // Pièce où le joueur se trouve actuellement.
    std::unordered_map<std::string, std::function<void(const std::string&)>> commandes_;  // Commandes du jeu.
    std::vector<std::shared_ptr<ObjetInteractif>> objetsJoueur_;  // Objets que le joueur possède.

    // Initialise les commandes disponibles dans le jeu.
    void initialiserCommandes() {
        commandes_["look"] = [this](const std::string& args) { regarder(args); };
        commandes_["take"] = [this](const std::string& args) { prendreObjet(args); };
        commandes_["use"] = [this](const std::string& args) { utiliserObjet(args); };
        commandes_["N"] = [this](const std::string& arg) { commandeDeMouvement("N"); };
        commandes_["E"] = [this](const std::string& arg) { commandeDeMouvement("E"); };
        commandes_["S"] = [this](const std::string& arg) { commandeDeMouvement("S"); };
        commandes_["W"] = [this](const std::string& arg) { commandeDeMouvement("W"); };
    }

    // Traite une commande de mouvement dans une direction spécifiée.
    void commandeDeMouvement(const std::string& direction) {
        auto nouvellePiece = piecePresente_->getPieceVoisin(direction);
        if (nouvellePiece) {
            piecePresente_ = nouvellePiece;
        }
        else {
            std::cout << "You can't go that way." << std::endl;
        }
    }

    // Traite les commandes entrées par l'utilisateur.
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

    // Affiche les informations sur la pièce actuelle ou sur un objet spécifique.
    void regarder(const std::string& args) {
        if (piecePresente_) {
            if (args.empty()) {
                piecePresente_->affichage();
                afficherObjetsJoueur();
            }
            else {
                auto objet = piecePresente_->getObjet(args);
                if (!objet) {
                    for (const auto& obj : objetsJoueur_) {
                        if (obj->getNom().find(args) != std::string::npos) {
                            objet = obj;
                            break;
                        }
                    }
                }
                if (objet) {
                    std::cout << objet->getDescription() << std::endl;
                }
                else {
                    std::cout << "There is no " << args << " here." << std::endl;
                }
            }
        }
    }

    // Permet au joueur de prendre un objet dans la pièce actuelle.
    void prendreObjet(const std::string& nomObjet) {
        if (piecePresente_) {
            auto objet = piecePresente_->retirerObjet(nomObjet);
            if (objet) {
                objetsJoueur_.push_back(objet);
                std::cout << "You picked up the " << nomObjet << "." << std::endl;
            }
            else {
                std::cout << "There is no " << nomObjet << " here." << std::endl;
            }
        }
    }

    // Permet au joueur d'utiliser un objet qu'il possède ou qui se trouve dans la pièce actuelle.
    void utiliserObjet(const std::string& nomObjet) {
        std::shared_ptr<ObjetInteractif> objet;
        for (const auto& obj : objetsJoueur_) {
            if (obj->getNom().find(nomObjet) != std::string::npos) {
                objet = obj;
                break;
            }
        }
        if (!objet) {
            objet = piecePresente_->getObjet(nomObjet);
        }
        if (objet) {
            if (piecePresente_->getNom() == objet->getPieceUtilisable()) {
                std::cout << objet->utiliser() << std::endl;
                if (auto cle = std::dynamic_pointer_cast<ObjetCle>(objet)) {
                    auto zoneADeverrouiller = cle->getZoneADeverrouiller();
                    auto pieceADeverrouiller = map_.getPieces(zoneADeverrouiller);
                    if (pieceADeverrouiller) {
                        piecePresente_->setVoisins("E", pieceADeverrouiller);
                        std::cout << "The " << zoneADeverrouiller << " has been unlocked!" << std::endl;
                    }
                }
                else if (auto echelle = std::dynamic_pointer_cast<ObjetEchelle>(objet)) {
                    auto zoneADeverrouiller = echelle->getZoneADeverrouiller();
                    auto pieceADeverrouiller = map_.getPieces(zoneADeverrouiller);
                    if (pieceADeverrouiller) {
                        std::string direction = piecePresente_->getNom() == "Attic" ? "down" : "up";
                        std::cout << "Going " << direction << " with the ladder." << std::endl;
                        piecePresente_->setVoisins(direction == "up" ? "N" : "S", pieceADeverrouiller);
                    }
                }
            }
            else {
                std::cout << "You can't use the " << nomObjet << " here." << std::endl;
            }
        }
        else {
            std::cout << "You don't have the " << nomObjet << "." << std::endl;
        }
    }


    // Affiche la bannière de bienvenue du jeu.
    void afficherBanniere() {
        std::cout << "Welcome to the interactive text-based adventure game!" << std::endl;
        std::cout << "Type 'exit' to quit the game." << std::endl;
    }

    // Affiche les objets que le joueur possède.
    void afficherObjetsJoueur() {
        std::cout << "You have:" << std::endl;
        for (const auto& obj : objetsJoueur_) {
            std::cout << "  " << obj->getNom() << std::endl;
        }
    }
};
