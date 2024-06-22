// Jeu.hpp

#pragma once

#include "Monde.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>   

using namespace std;

// La classe Jeu représente le jeu principal.
class Jeu
{
public:
    // Constructeur initialisant le jeu et définissant la pièce présente à l'entrée.
    Jeu() 
    {
        piecePresente_ = map_.getPieces("Entrance");
        initialiserCommandes();
    }

    // Destructeur du jeu, libérant les ressources utilisées.
    ~Jeu()
    {
        cout << "Cleaning up the game resources..." << endl;
        piecePresente_.reset();
    }

    // Méthode principale pour jouer au jeu.Elle affiche la bannière de bienvenue, les informations de la pièce présente et traite la commande entrée par l'utilisateur.
    void jouer() 
    {
        afficherBanniere(); 
        string commande;
        while (true)
        {
            piecePresente_->affichage();  
            cout << "> ";
            getline(cin, commande);
            if (commande == "exit") {
                cout << "Thank you for playing!" << endl;
                break;  
            }
            traiterCommande(commande);  
        }
    }

private:
    Monde map_;  
    shared_ptr<Piece> piecePresente_;  // Pièce où le joueur se trouve actuellement.
    unordered_map<string, function<void(const string&)>> commandes_;  // Commandes du jeu.
    vector<shared_ptr<ObjetInteractif>> objetsJoueur_;  // Objets que le joueur possède.

    // Initialise les commandes disponibles dans le jeu.
    void initialiserCommandes()
    {
        commandes_["look"] = [this](const string& args) { regarder(args); };
        commandes_["take"] = [this](const string& args) { prendreObjet(args); };
        commandes_["use"] = [this](const string& args) { utiliserObjet(args); };
        commandes_["N"] = [this](const string arg) { commandeDeMouvement("N"); };
        commandes_["E"] = [this](const string arg) { commandeDeMouvement("E"); };
        commandes_["S"] = [this](const string arg) { commandeDeMouvement("S"); };
        commandes_["W"] = [this](const string arg) { commandeDeMouvement("W"); };
    }

    // Traite une commande de mouvement dans une direction spécifiée.
    void commandeDeMouvement(const string& direction)
    {
        auto nouvellePiece = piecePresente_->getPieceVoisin(direction);

        if (nouvellePiece) 
        {
            piecePresente_ = nouvellePiece;
        }

        else
        {
            cout << "You can't go that way." << endl;
        }
    }

    // Traite les commandes entrées par l'utilisateur.
    void traiterCommande(const string& input) 
    {
        auto pos = input.find(' ');
        string commande = (pos == string::npos) ? input : input.substr(0, pos);
        string args = (pos == string::npos) ? "" : input.substr(pos + 1);

        auto it = commandes_.find(commande);

        if (it != commandes_.end()) 
        {
            it->second(args);
        }

        else
        {
            cout << "Invalid command." << endl;
        }
    }

    // Affiche les informations sur la pièce actuelle ou sur un objet spécifique.
    void regarder(const string& args)
    {
        if (piecePresente_) 
        {
            if (args.empty()) 
            {
                piecePresente_->affichage();
                afficherObjetsJoueur();
            }

            else 
            {
                auto objet = piecePresente_->getObjet(args);

                if (!objet) 
                {
                    for (const auto& obj : objetsJoueur_) 
                    {
                        if (obj->getNom().find(args) != string::npos) 
                        {
                            objet = obj;
                            break;
                        }
                    }
                }

                if (objet) 
                {
                    cout << objet->getDescription() << endl;
                }

                else 
                {
                    cout << "There is no " << args << " here." << endl;
                }
            }
        }
    }

    // Permet au joueur de prendre un objet dans la pièce actuelle.
    void prendreObjet(const string& nomObjet) 
    {
        if (piecePresente_)
        {
            auto objet = piecePresente_->retirerObjet(nomObjet);

            if (objet)
            {
                objetsJoueur_.push_back(objet);
                cout << "You picked up the " << nomObjet << "." << endl;
            }

            else 
            {
                cout << "There is no " << nomObjet << " here." << endl;
            }
        }
    }

    // Permet au joueur d'utiliser un objet qu'il possède ou qui se trouve dans la pièce actuelle.
    void utiliserObjet(const string& nomObjet) 
    {
        shared_ptr<ObjetInteractif> objet;

        for (const auto& obj : objetsJoueur_)
        {
            if (obj->getNom().find(nomObjet) != string::npos)
            {
                objet = obj;
                break;
            }
        }

        if (!objet) 
        {
            objet = piecePresente_->getObjet(nomObjet);
        }

        if (objet) 
        {
            if (piecePresente_->getNom() == objet->getPieceUtilisable())
            {
                cout << objet->utiliser() << endl;

                if (auto cle = dynamic_pointer_cast<ObjetCle>(objet))
                {
                    auto zoneADeverrouiller = cle->getZoneADeverrouiller();

                    auto pieceADeverrouiller = map_.getPieces(zoneADeverrouiller);
                    if (pieceADeverrouiller) 
                    {
                        piecePresente_->setVoisins("E", pieceADeverrouiller);
                        cout << "The " << zoneADeverrouiller << " has been unlocked!" << endl;
                    }
                }
                else if (auto echelle = dynamic_pointer_cast<ObjetEchelle>(objet))
                {
                    auto zoneADeverrouiller = echelle->getZoneADeverrouiller();
                    auto pieceADeverrouiller = map_.getPieces(zoneADeverrouiller);

                    if (pieceADeverrouiller) 
                    {
                        string direction = piecePresente_->getNom() == "Attic" ? "down" : "up";
                        cout << "Going " << direction << " with the ladder." << endl;
                        piecePresente_->setVoisins(direction == "up" ? "N" : "S", pieceADeverrouiller);
                    }
                }
            }
            else 
            {
                cout << "You can't use the " << nomObjet << " here." << endl;
            }
        }
        else 
        {
            cout << "You don't have the " << nomObjet << "." << endl;
        }
    }

    // Affiche la bannière de bienvenue du jeu.
    void afficherBanniere()
    {
        cout << "\033[1;32mWelcome to the interactive text-based adventure game!\033[0m" << endl;
        cout << "\033[1;34mVoici les commandes de déplacement disponibles :\033[0m" << endl;
        cout << "\033[1;33m - N (North) : Pour aller au nord (En haut)"
            << "\n - E (East) : Pour aller à l'est (À droite)"
            << "\n - S (South) : Pour aller au sud (En bas)"
            << "\n - W (West) : Pour aller à l'ouest (À gauche)\033[0m" << endl;
        cout << "\033[1;34mVoici les commandes interactives durant le jeu :\033[0m" << endl;
        cout << "\033[1;33m - look : Pour regarder les salles accessibles."
            << "\n - look (nom de l'objet) : Pour regarder la description de l'objet."
            << "\n - take (nom de l'objet) : Pour prendre l'objet à votre disposition."
            << "\n - use (nom de l'objet) : Pour utiliser un objet à votre disposition.\033[0m" << endl;
        cout << "\033[1;31mVoici la commande pour sortir du jeu : 'exit'.\033[0m" << endl;
    }

    // Affiche les objets que le joueur possède.
    void afficherObjetsJoueur()
    {
        cout << "You have:" << endl;
        for (const auto& obj : objetsJoueur_) 
        {
            cout << "  " << obj->getNom() << endl;
        }
    }
};
