#pragma once 

#include "Piece.hpp"
#include <unordered_map>
#include <memory>
#include <string>

class MapDuJeu
{
public:
    MapDuJeu()
    {
        initialiser();
    }

    ~MapDuJeu()
    {
        pieces.clear();
    }

    void ajouterPiece(const std::string& nom, const std::string& description)
    {
        pieces[nom] = std::make_shared<Piece>(nom, description);
    }

    void setVoisin(const std::string& precedant, const std::string& direction, const std::string& suivante)
    {
        auto piecePrecedante = pieces.find(precedant);
        auto pieceSuivante = pieces.find(suivante);

        if (piecePrecedante != pieces.end() && pieceSuivante != pieces.end())
        {
            piecePrecedante->second->setVoisins(direction, pieceSuivante->second);
        }
    }

    std::shared_ptr<Piece> getPieces(const std::string& nom) const
    {
        auto it = pieces.find(nom);
        if (it != pieces.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Piece>> pieces;

    void initialiser()
    {
        ajouterPiece("Entrance", "This is the entrance of the house. There is a sturdy carpet on the floor.");
        ajouterPiece("Main Hall", "This is the main hallway. There is a bunch of boxes against the wall.");
        ajouterPiece("Living Room", "This is the living room. It has a cozy fireplace.");
        ajouterPiece("Kitchen", "This is the kitchen. It has a delicious smell.");
        ajouterPiece("Small Bedroom", "This is the small bedroom. It is not particularly clean or well organised. There is a small window.");

        setVoisin("Entrance", "N", "Main Hall");
        setVoisin("Main Hall", "S", "Entrance");
        setVoisin("Main Hall", "E", "Living Room");
        setVoisin("Living Room", "W", "Main Hall");
        setVoisin("Main Hall", "N", "Kitchen");
        setVoisin("Kitchen", "S", "Main Hall");
        setVoisin("Main Hall", "W", "Small Bedroom");
        setVoisin("Small Bedroom", "E", "Main Hall");
    }
};
