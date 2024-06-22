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
    ~Monde() { pieces.clear(); }

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Méthode pour ajouter une nouvelle pièce au monde. Prend en paramètre le nom et la description de la pièce.
    void ajouterPiece(const string& nom, const string& description) { pieces[nom] = make_shared<Piece>(nom, description); }

    // Méthode pour définir une pièce voisine. Prend en paramètre le nom de la pièce actuelle, la direction, et le nom de la pièce voisine.
   
    void setVoisin(const string& precedant, const string& direction, const string& suivante) 
    {
        auto piecePrecedante = pieces.find(precedant);
        auto pieceSuivante = pieces.find(suivante);

       
        if (piecePrecedante != pieces.end() && pieceSuivante != pieces.end())
        {
            piecePrecedante->second->setVoisins(direction, pieceSuivante->second);
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
        ajouterPiece("Entrance", "This is the entrance of the house. There is a sturdy carpet on the floor.");
        ajouterPiece("Main Hall", "This is the main hallway. There is a bunch of boxes against the wall.");
        ajouterPiece("Living Room", "This is the living room. It has a cozy fireplace.");
        ajouterPiece("Kitchen", "This is the kitchen. It has a delicious smell.");
        ajouterPiece("Small Bedroom", "This is the small bedroom. It is not particularly clean or well organised. There is a small window.There is something hanging on the ceiling that seems unreachable");
        ajouterPiece("Attic", "The attic is a dusty, dimly lit space filled with the remnants of a bygone era.");
        ajouterPiece("R Room", "This is the hidden room, revealed only by using a special key. ");

        setVoisin("Entrance", "E", "Living Room");
        setVoisin("Living Room", "W", "Entrance");
        setVoisin("Entrance", "N", "Main Hall");
        setVoisin("Main Hall", "S", "Entrance");
        setVoisin("Main Hall", "N", "Kitchen");
        setVoisin("Kitchen", "S", "Main Hall");
        setVoisin("Main Hall", "W", "Small Bedroom");
        setVoisin("Small Bedroom", "E", "Main Hall");
        setVoisin("R Room", "W", "Main Hall");
        setVoisin("Attic", "S", "Small Bedroom");

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
