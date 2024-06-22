#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

// Classe pour les objets interactifs
class ObjetInteractif 
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    ObjetInteractif(const string& nom, const string& description, const string& pieceUtilisable) : nom_(nom), description_(description), pieceUtilisable_(pieceUtilisable) {}

    // Destructeurs -------------------------------------------------------------------------------------------------------------------------------------

    virtual ~ObjetInteractif() {}

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Méthode pour obtenir le nom de l'objet
    string getNom() const { return nom_; }

    // Méthode pour obtenir la description de l'objet
    string getDescription() const { return description_; }

    // Methode pour obtenir la piece ou l'objet sera utilisable
    string getPieceUtilisable() const { return pieceUtilisable_; }

    // Méthode virtuelle pure pour utiliser l'objet
    virtual string utiliser() = 0;

protected:
    string nom_; 
    string description_; 
    string pieceUtilisable_;
};

// Classe dérivée pour les objets de type clé
class ObjetCle : public ObjetInteractif
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur prenant un nom, une description, la zone à déverrouiller et dans quelle piece elle est activable 
    ObjetCle(const string& nom, const string& description, const string& zoneADeverrouiller, const string& pieceUtilisable) : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Implémentation de la méthode utiliser pour l'objet clé
    string utiliser() override { return "The key was used to unlock " + zoneADeverrouiller_; }

    // Méthode pour obtenir la zone à déverrouiller
    string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    string zoneADeverrouiller_; 
};

// Classe dérivée pour les objets de type échelle
class ObjetEchelle : public ObjetInteractif
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur prenant un nom, une description, la zone à déverrouiller et dans quelle piece elle est activable 
    ObjetEchelle(const string& nom, const string& description, const string& zoneADeverrouiller, const string& pieceUtilisable) : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Implémentation de la méthode utiliser pour l'objet échelle
    string utiliser() override { return "You use the ladder to access the " + zoneADeverrouiller_; }

    // Méthode pour obtenir la zone à accéder
    string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    string zoneADeverrouiller_; 
};

// Classe dérivée pour les objets de type piano
class ObjetPiano : public ObjetInteractif
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur prenant un nom, une description, la zone à déverrouiller et dans quelle piece elle est activable 
    ObjetPiano(const string& nom, const string& description, const string& pieceUtilisable) : ObjetInteractif(nom, description, pieceUtilisable) {}

    // Méthodes -----------------------------------------------------------------------------------------------------------------------------------------
    
    // Implémentation de la méthode utiliser pour l'objet piano
    string utiliser() override { return "You play a beautiful melody on the piano."; }
};
