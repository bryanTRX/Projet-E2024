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

    // Méthode pour obtenir le nom de l'objet
    std::string getNom() const { return nom_; }

    // Méthode pour obtenir la description de l'objet
    std::string getDescription() const { return description_; }

    // Methode pour obtenir la piece ou l'objet sera utilisable
    std::string getPieceUtilisable() const { return pieceUtilisable_; }

    // Méthode virtuelle pure pour utiliser l'objet
    virtual std::string utiliser() = 0;

protected:
    std::string nom_; 
    std::string description_; 
    std::string pieceUtilisable_;
};

// Classe dérivée pour les objets de type clé
class ObjetCle : public ObjetInteractif {
public:
    // Constructeur prenant un nom, une description, la zone à déverrouiller et dans quelle piece elle est activable 
    ObjetCle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller, const std::string& pieceUtilisable)
        : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // Implémentation de la méthode utiliser pour l'objet clé
    std::string utiliser() override {
        return "The key was used to unlock " + zoneADeverrouiller_;
    }

    // Méthode pour obtenir la zone à déverrouiller
    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_; 
};

// Classe dérivée pour les objets de type échelle
class ObjetEchelle : public ObjetInteractif {
public:
    // Constructeur prenant un nom, une description, la zone à déverrouiller et dans quelle piece elle est activable 
    ObjetEchelle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller, const std::string& pieceUtilisable)
        : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // Implémentation de la méthode utiliser pour l'objet échelle
    std::string utiliser() override {
        return "You use the ladder to access the " + zoneADeverrouiller_;
    }

    // Méthode pour obtenir la zone à accéder
    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_; 
};

// Classe dérivée pour les objets de type piano
class ObjetPiano : public ObjetInteractif {
public:
    // Constructeur prenant un nom, une description, la zone à déverrouiller et dans quelle piece elle est activable 
    ObjetPiano(const std::string& nom, const std::string& description, const std::string& pieceUtilisable)
        : ObjetInteractif(nom, description, pieceUtilisable) {}

    // Implémentation de la méthode utiliser pour l'objet piano
    std::string utiliser() override {
        return "You play a beautiful melody on the piano.";
    }
};
