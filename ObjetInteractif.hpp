#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Classe pour les objets interactifs
class ObjetInteractif {
public:
   
    ObjetInteractif(const std::string& nom, const std::string& description, const std::string& pieceUtilisable)
        : nom_(nom), description_(description), pieceUtilisable_(pieceUtilisable) {}

   
    virtual ~ObjetInteractif() {}

    // M�thode pour obtenir le nom de l'objet
    std::string getNom() const { return nom_; }

    // M�thode pour obtenir la description de l'objet
    std::string getDescription() const { return description_; }

    // Methode pour obtenir la piece ou l'objet sera utilisable
    std::string getPieceUtilisable() const { return pieceUtilisable_; }

    // M�thode virtuelle pure pour utiliser l'objet
    virtual std::string utiliser() = 0;

protected:
    std::string nom_; 
    std::string description_; 
    std::string pieceUtilisable_;
};

// Classe d�riv�e pour les objets de type cl�
class ObjetCle : public ObjetInteractif {
public:
    // Constructeur prenant un nom, une description, la zone � d�verrouiller et dans quelle piece elle est activable 
    ObjetCle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller, const std::string& pieceUtilisable)
        : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // Impl�mentation de la m�thode utiliser pour l'objet cl�
    std::string utiliser() override {
        return "The key was used to unlock " + zoneADeverrouiller_;
    }

    // M�thode pour obtenir la zone � d�verrouiller
    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_; 
};

// Classe d�riv�e pour les objets de type �chelle
class ObjetEchelle : public ObjetInteractif {
public:
    // Constructeur prenant un nom, une description, la zone � d�verrouiller et dans quelle piece elle est activable 
    ObjetEchelle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller, const std::string& pieceUtilisable)
        : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // Impl�mentation de la m�thode utiliser pour l'objet �chelle
    std::string utiliser() override {
        return "You use the ladder to access the " + zoneADeverrouiller_;
    }

    // M�thode pour obtenir la zone � acc�der
    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_; 
};

// Classe d�riv�e pour les objets de type piano
class ObjetPiano : public ObjetInteractif {
public:
    // Constructeur prenant un nom, une description, la zone � d�verrouiller et dans quelle piece elle est activable 
    ObjetPiano(const std::string& nom, const std::string& description, const std::string& pieceUtilisable)
        : ObjetInteractif(nom, description, pieceUtilisable) {}

    // Impl�mentation de la m�thode utiliser pour l'objet piano
    std::string utiliser() override {
        return "You play a beautiful melody on the piano.";
    }
};
