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
    std::vector<std::string> motsClefs;

protected:
    std::string nom_;
    std::string description_;
};

class ObjetCle : public ObjetInteractif {
public:
    ObjetCle(const std::string& nom, const std::string& description, const std::string& zoneADeverrouiller)
        : ObjetInteractif(nom, description), zoneADeverrouiller_(zoneADeverrouiller) {}

    std::string utiliser() override {
        return "La cl� a �t� utilis�e pour d�verrouiller " + zoneADeverrouiller_;
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
        return "Vous utilisez l'�chelle pour acc�der � une nouvelle zone." + zoneADeverrouiller_;
    }

    std::string getZoneADeverrouiller() const { return zoneADeverrouiller_; }

private:
    std::string zoneADeverrouiller_;
};