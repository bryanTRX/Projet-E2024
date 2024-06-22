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

    // M�thodes -----------------------------------------------------------------------------------------------------------------------------------------

    // M�thode pour obtenir le nom de l'objet
    string getNom() const { return nom_; }

    // M�thode pour obtenir la description de l'objet
    string getDescription() const { return description_; }

    // Methode pour obtenir la piece ou l'objet sera utilisable
    string getPieceUtilisable() const { return pieceUtilisable_; }

    // M�thode virtuelle pure pour utiliser l'objet
    virtual string utiliser() = 0;

protected:
    string nom_; 
    string description_; 
    string pieceUtilisable_;
};

// Classe d�riv�e pour les objets de type cl�
class ObjetCle : public ObjetInteractif
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur prenant un nom, une description, la zone � d�verrouiller et dans quelle piece elle est activable 
    ObjetCle(const string& nom, const string& description, const string& zoneADeverrouiller, const string& pieceUtilisable) : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // M�thodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Impl�mentation de la m�thode utiliser pour l'objet cl�
    string utiliser() override { return "The key was used to unlock " + zoneADeverrouiller_; }

    // M�thode pour obtenir la zone � d�verrouiller
    string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    string zoneADeverrouiller_; 
};

// Classe d�riv�e pour les objets de type �chelle
class ObjetEchelle : public ObjetInteractif
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur prenant un nom, une description, la zone � d�verrouiller et dans quelle piece elle est activable 
    ObjetEchelle(const string& nom, const string& description, const string& zoneADeverrouiller, const string& pieceUtilisable) : ObjetInteractif(nom, description, pieceUtilisable), zoneADeverrouiller_(zoneADeverrouiller) {}

    // M�thodes -----------------------------------------------------------------------------------------------------------------------------------------

    // Impl�mentation de la m�thode utiliser pour l'objet �chelle
    string utiliser() override { return "You use the ladder to access the " + zoneADeverrouiller_; }

    // M�thode pour obtenir la zone � acc�der
    string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    string zoneADeverrouiller_; 
};

// Classe d�riv�e pour les objets de type piano
class ObjetPiano : public ObjetInteractif
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------------------------------------------------

    // Constructeur prenant un nom, une description, la zone � d�verrouiller et dans quelle piece elle est activable 
    ObjetPiano(const string& nom, const string& description, const string& pieceUtilisable) : ObjetInteractif(nom, description, pieceUtilisable) {}

    // M�thodes -----------------------------------------------------------------------------------------------------------------------------------------
    
    // Impl�mentation de la m�thode utiliser pour l'objet piano
    string utiliser() override { return "You play a beautiful melody on the piano."; }
};
