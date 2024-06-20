// Monde.hpp

#pragma once

#include "Piece.hpp"
#include "ObjetInteractif.hpp"
#include <unordered_map>
#include <memory>
#include <string>

class Monde
{
public:
    Monde()
    {
        initialiser();
    }

    ~Monde()
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
        if (it != pieces.end())
        {
            return it->second;
        }
        return nullptr;
    }

    void affichageDesPieces() const {
        std::cout << "\033[1;34mAvailable Rooms:\033[0m" << std::endl;
        for (const auto& pair : pieces) {
            std::cout << "- " << pair.first << std::endl;
        }
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
        ajouterPiece("Attic", "The attic is a dusty, dimly lit space filled with the remnants of a bygone era.");
        ajouterPiece("Salle R", "This is the hidden room, revealed only by using a special key.");

        setVoisin("Entrance", "E", "Living Room");
        setVoisin("Living Room", "W", "Entrance");
        setVoisin("Entrance", "N", "Main Hall");
        setVoisin("Main Hall", "S", "Entrance");
        setVoisin("Main Hall", "N", "Kitchen");
        setVoisin("Kitchen", "S", "Main Hall");
        setVoisin("Main Hall", "W", "Small Bedroom");
        setVoisin("Small Bedroom", "E", "Main Hall");
        setVoisin("Salle R", "W", "Main Hall");

        // Adding interactive objects to rooms
        auto livingRoom = getPieces("Living Room");
        if (livingRoom) {
            livingRoom->ajouterObjet(std::make_shared<ObjetCle>("Key", "A small rusty key.", "Salle R"));
        }

        auto salleR = getPieces("Salle R");

        if (salleR)
        {
            salleR->ajouterObjet(std::make_shared<ObjetCle>("Ladder", "Test", "Attic"));
        }

        auto attic = getPieces("Attic");

        if (attic)
        {
            attic->ajouterObjet(std::make_shared<ObjetPiano>("Piano", "Alllliiii"));
        }
    }
};