#pragma once

#include <string>
#include <iostream>

class ObjetInteractif
{
public:
    ObjetInteractif(const std::string& nom, const std::string& description) : nom_(nom), description_(description) {}

    virtual ~ObjetInteractif() = default;

    std::string getNom() const { return nom_; }
    std::string getDescription() const { return description_; }

    virtual void utiliser() const
    {
        std::cout << "You use the " << nom_ << ". " << std::endl;
    }

private:
    std::string nom_;
    std::string description_;
};

class ObjetDeverrouillage : public ObjetInteractif
{
public:
    ObjetDeverrouillage(const std::string& nom, const std::string& description, const std::string& zoneDeverrouillee)
        : ObjetInteractif(nom, description), zoneDeverrouillee_(zoneDeverrouillee) {}

    std::string getZoneDeverrouillee() const { return zoneDeverrouillee_; }

    void utiliser() const override
    {
        std::cout << "You use the " << getNom() << " to unlock " << zoneDeverrouillee_ << "." << std::endl;
    }

private:
    std::string zoneDeverrouillee_;
};
class Echelle : public ObjetInteractif
{
public:
    Echelle(const std::string& nom, const std::string& description, const std::string& zoneCible)
        : ObjetInteractif(nom, description), zoneCible_(zoneCible) {}

    std::string getZoneCible() const { return zoneCible_; }

    void utiliser() const override
    {
        std::cout << "You use the " << getNom() << " to go to " << zoneCible_ << "." << std::endl;
    }

private:
    std::string zoneCible_;
};