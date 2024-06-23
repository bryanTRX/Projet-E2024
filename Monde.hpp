#pragma once

#include "Piece.hpp"
#include "ObjetInteractif.hpp"
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

// La classe Monde représente le monde du jeu, avec ses différentes pièces et objets.
class Monde 
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur
    Monde() { initialiser(); }

    // Destructeurs -------------------------------------------------------------------------------------------------------------------------------------

    // Destructeur
    ~Monde() = default;

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------

    void setVoisin(const string& piece, const std::initializer_list<std::pair<string, string>>& voisins) 
    {
        auto pieceIt = pieces.find(piece);
        if (pieceIt != pieces.end()) 
        {
            for (const auto& voisin : voisins) 
            {
                auto voisinIt = pieces.find(voisin.second);
                if (voisinIt != pieces.end())
                {
                    pieceIt->second->setVoisins(voisin.first, voisinIt->second);
                }
            }
        }
    }

    // Méthode pour obtenir une pièce à partir de son nom. Retourne un pointeur vers la pièce, ou nullptr si la pièce n'existe pas.
    shared_ptr<Piece> getPieces(const string& nom) const 
    {
        auto it = pieces.find(nom);
        if (it != pieces.end())
        {
            return it->second;
        }
        return nullptr;
    }

private:
    unordered_map<string, shared_ptr<Piece>> pieces;

    void initialiser()
    {
        pieces["Entrance"] = std::make_shared<Piece>("Entrance", "You are at the entrance of the house.");
        pieces["Living Room"] = std::make_shared<Piece>("Living Room", "You are in the living room.");
        pieces["Main Hall"] = std::make_shared<Piece>("Main Hall", "You are in the main hallway.");
        pieces["Kitchen"] = std::make_shared<Piece>("Kitchen", "You are in the kitchen.");
        pieces["Small Bedroom"] = std::make_shared<Piece>("Small Bedroom", "You are in a small bedroom.");
        pieces["R Room"] = std::make_shared<Piece>("R Room", "You are in the R room.");
        pieces["Attic"] = std::make_shared<Piece>("Attic", "You are in the attic.");

        // Utilisation de la méthode setVoisin pour configurer plusieurs voisins à la fois
        setVoisin("Entrance", { {"E", "Living Room"}, {"N", "Main Hall"} });
        setVoisin("Living Room", { {"W", "Entrance"} });
        setVoisin("Main Hall", { {"S", "Entrance"}, {"N", "Kitchen"}, {"W", "Small Bedroom"} });
        setVoisin("Kitchen", { {"S", "Main Hall"} });
        setVoisin("Small Bedroom", { {"E", "Main Hall"}});
        setVoisin("R Room", { {"W", "Main Hall"} });
        setVoisin("Attic", { {"S", "Small Bedroom"} });


        // Ajout d'objets interactifs dans certaines pièces
        auto livingRoom = getPieces("Living Room");
        if (livingRoom)
        {
            livingRoom->ajouterObjet(make_shared<ObjetCle>("Key", "A small brass key that can be used in the main Hallway.", "R Room", "Main Hall"));
            livingRoom->ajouterObjet(make_shared<ObjetPiano>("Piano", "An old grand piano that can be used in the Attic.", "Attic"));
        }

        auto smallBedroom = getPieces("Small Bedroom");
        if (smallBedroom)
        {
            smallBedroom->ajouterObjet(make_shared<ObjetEchelle>("Ladder", "A sturdy wooden ladder that can be used in the Small Bedroom.", "Attic", "Small Bedroom"));
        }
    }
};
