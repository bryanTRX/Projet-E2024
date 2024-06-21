#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ObjetInteractif {
public:
    ObjetInteractif(const std::string& nom, const std::string& description)
        : nom_(nom), description_(description) {}
    virtual ~ObjetInteractif() {}

    std::string getNom() const { return nom_; }
    std::string getDescription() const { return description_; }
    virtual std::string utiliser() = 0;

protected:
    std::string nom_;
    std::string description_;
};

class ObjetCle : public ObjetInteractif {
public:
    ObjetCle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller)
        : ObjetInteractif(nom, description), zoneADeverrouiller_(zoneADeverrouiller) {}

    std::string utiliser() override {
        return "La clé a été utilisée pour déverrouiller " + zoneADeverrouiller_;
    }

    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_;
};

class ObjetEchelle : public ObjetInteractif {
public:
    ObjetEchelle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller)
        : ObjetInteractif(nom, description), zoneADeverrouiller_(zoneADeverrouiller) {}

    std::string utiliser() override {
        return "Vous utilisez l'échelle pour accéder à " + zoneADeverrouiller_;
    }

    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_;
};

class ObjetPiano : public ObjetInteractif {
public:
    ObjetPiano(const std::string& nom, const std::string& description)
        : ObjetInteractif(nom, description) {}

    std::string utiliser() override {
        return "You play a beautiful melody on the piano.";
    }
};
