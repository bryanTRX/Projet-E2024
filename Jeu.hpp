#pragma once 

#include "MapJeu.hpp"
#include <string>
#include <iostream>

class Jeu
{
public:
    Jeu()
    {
        piecePresente_ = map_.getPieces("Entrance");
    }

    ~Jeu()
    {
        std::cout << "Cleaning up the game resources..." << std::endl;
        piecePresente_.reset(); 
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
