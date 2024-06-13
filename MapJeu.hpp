#pragma once 

#include "Piece.hpp"
#include <unordered_map>
#include <memory>
#include <string>

class MapDuJeu
{
public:
    MapDuJeu() {}
    ~MapDuJeu()
    {
        vider();
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

    void vider()
    {
        pieces.clear();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Piece>> pieces;
};