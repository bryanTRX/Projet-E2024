#pragma once 

#include <string>
#include <map>
#include <memory>
#include <iostream>

class Piece
{
public:
	Piece() : nom_(""), description_("") {}
	Piece(const std::string& nom, const std::string& description) : nom_(nom), description_(description) {}

	~Piece()
	{
		std::cout << "Destruction of Piece: " << nom_ << std::endl;
	}

	void setVoisins(const std::string& direction, std::shared_ptr<Piece> voisin)
	{
		pieceVoisins_[direction] = voisin;
	}

	std::string getNom() const { return nom_; }
	std::string getDescription() const { return description_; }
	std::shared_ptr<Piece> getPieceVoisin(const std::string& direction) const 
	{
		auto it = pieceVoisins_.find(direction);

		if (it != pieceVoisins_.end())
		{
			return it->second.lock();
		}
		return nullptr;
	}

	void affichage() const
	{
		std::cout << "-- " << nom_ << " --" << std::endl;
		std::cout << description_ << std::endl;

		for (const auto& voisins : pieceVoisins_)
		{
			std::string direction = voisins.first;
			std::string directionComplete;
			if (direction == "N") directionComplete = "North (N)";
			else if (direction == "E") directionComplete = "East (E)";
			else if (direction == "S") directionComplete = "South (S)";
			else if (direction == "W") directionComplete = "West (W)";

			if (auto voisin = voisins.second.lock())
			{
				std::cout << "To the " << voisins.first << " there is " << voisin->getNom() << " " << directionComplete << std::endl;
			}
		}
	}

private: 
	std::string nom_;
	std::string description_;
	std::map<std::string, std::weak_ptr<Piece>> pieceVoisins_;
};