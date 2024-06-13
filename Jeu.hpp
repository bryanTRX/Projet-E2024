#pragma once 

#include "MapJeu.hpp"
#include <string>
#include <iostream>

class Jeu
{
public:
    Jeu()
    {
        initialiser();
        piecePresente_ = map_.getPieces("Entrance");
    }

    ~Jeu()
    {
        std::cout << "Cleaning up the game resources..." << std::endl;
        piecePresente_.reset(); // Optionnel, shared_ptr se nettoie automatiquement
        map_.vider();
    }

    void initialiser()
    {
        map_.ajouterPiece("Entrance", "This is the entrance of the house. There is a sturdy carpet on the floor.");
        map_.ajouterPiece("Main Hall", "This is the main hallway. There is a bunch of boxes against the wall.");
        map_.ajouterPiece("Living Room", "This is the living room. It has a cozy fireplace.");
        map_.ajouterPiece("Kitchen", "This is the kitchen. It has a delicious smell.");
        map_.ajouterPiece("Small Bedroom", "This is the small bedroom. It is not particularly clean or well organised. There is a small window.");

        map_.setVoisin("Entrance", "N", "Main Hall");
        map_.setVoisin("Main Hall", "S", "Entrance");
        map_.setVoisin("Main Hall", "E", "Living Room");
        map_.setVoisin("Living Room", "W", "Main Hall");
        map_.setVoisin("Main Hall", "N", "Kitchen");
        map_.setVoisin("Kitchen", "S", "Main Hall");
        map_.setVoisin("Main Hall", "W", "Small Bedroom");
        map_.setVoisin("Small Bedroom", "E", "Main Hall");
    }

    void jouer()
    {
        afficherBanniere();
        std::string commande;

        while (true)
        {
            affichageDeLaPiecePresente();
            std::cout << "> ";
            std::getline(std::cin, commande);
            if (commande == "exit")
            {
                std::cout << "Thank you for playing! Goodbye!" << std::endl;
                break;
            }
            commandeDeMouvement(commande);
        }
    }

private:
    MapDuJeu map_;
    std::shared_ptr<Piece> piecePresente_;

    void afficherBanniere() const
    {
        std::cout << ">>>>> INF1015 DUNGEON CRAWLER 2021 <<<<<" << std::endl;
        std::cout << "> > > > GAME OF THE YEAR EDITION < < < <" << std::endl << std::endl;
    }

    void affichageDeLaPiecePresente() const
    {
        piecePresente_->affichage();
    }

    void commandeDeMouvement(const std::string& commande)
    {
        if (commande == "look")
        {
            affichageDeLaPiecePresente();
        }
        else if (commande == "N" || commande == "E" || commande == "S" || commande == "W")
        {
            auto pieceSuivante = piecePresente_->getPieceVoisin(commande);

            if (pieceSuivante)
            {
                piecePresente_ = pieceSuivante;
                std::cout << "Going " << commande << std::endl;
            }
            else
            {
                std::cout << "Cannot go there." << std::endl;
            }
        }
        else
        {
            std::cout << "Unknown command." << std::endl;
        }
    }
};
