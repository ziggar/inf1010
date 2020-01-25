// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "debogageMemoire.h"
#include "typesafe_enum.h"
#include "Librairie.h"

namespace
{
    constexpr std::size_t CAPACITE_FILMS_INITIALE = 2;
    constexpr int FILM_INEXSISTANT = -1;
}


// TODO: Constructeur par défault en utilisant la liste d'initialisation
// Utiliser CAPACITE_FILMS_INITIALE pour la taille initiale de films_ (allocation dynamique!)
Librairie::Librairie():films_(nullptr),nbFilms_(0),capaciteFilms_(0)
{
}


// TODO: Destructeur
// Faire appel à la fonction supprimerFilms()
// Ne pas oublier de désallouer le tableau ET les films
Librairie::~Librairie()
{
    supprimerFilms();
    delete[] films_;
}




//! Méthode qui ajoute un film à la liste des films.
//! \param film Le film alloué dynamiquement à ajouter à la liste. La classe devient propriétaire du
//!             film.
void Librairie::ajouterFilm(Film* film)
{
    static constexpr unsigned int AUGMENTATION_CAPACITE_FILMS = 2;

    // TODO
    // Verifier si assez de mémoire est allouée
    // Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_CAPACITE_FILMS)
    // Ajouter le film au tableau seulement si film n'est pas un nullptr

    if (capaciteFilms_ > nbFilms_)
    {
        films_[nbFilms_] = film;
    }
    else
    {

        Film** doubleFilm = new Film* [CAPACITE_FILMS_INITIALE*AUGMENTATION_CAPACITE_FILMS];

        for (int i = 0; i < (nbFilms_); i++)
        {
            doubleFilm[i] = films_[i];
            delete films_[i];
        }

        films_ = doubleFilm;

        films_[nbFilms_] = film;
    }


}

// TODO: retirerFilm(const std::string& nomFilm)
// Retirer un film ayant le même nom que celui envoyé en paramètre
// Si le film n'existe pas, ne rien faire
// Faire appel à la fonction trouverIndexFilm
void Librairie::retirerFilm(const std::string& nomFilm)
{
    int indexFilm = trouverIndexFilm(nomFilm);

    if (indexFilm != -1)
    {
        delete films_[indexFilm];
        nbFilms_--;

        for (int i = indexFilm; i < (nbFilms_ - 1); i++)
        {
            films_[i] = films_[i + 1];
        }

    }
    /// ne fait rien si index ==-1
}






// TODO chercherFilm(const std::string& nomFilm)
// Retourner un pointeur vers le film recherché
// Si le film n'existe pas, retourner nullptr
// Utiliser la fonction trouverIndexFilm
Film* Librairie::chercherFilm(const std::string& nomFilm)
{    
    Film* ptrFilm = nullptr;

    int indexFilm = trouverIndexFilm(nomFilm);

    if (indexFilm != -1)
    {
        ptrFilm = films_[indexFilm];
    }
    return ptrFilm;
    // fait la mëme chose aussi 
  //  return (trouverIndexFilm(nomFilm) != -1) ? films_[trouverIndexFilm(nomFilm)] : nullptr; 
}

//! Méthode qui charge les films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerFilmsDepuisFichier(const std::string& nomFichier,
                                          GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // TODO

        supprimerFilms(); // suppression de tous les film

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneFilm(ligne, gestionnaireAuteurs) == false)
            {
                return false;
            }
           
        }


    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui charge les restrictions des films à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // TODO
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
    return false;
}

//! Méthode qui affiche la liste des films.
//! \param stream Le stream dans lequel afficher.
void Librairie::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbFilms_; i++)
    {
        films_[i]->afficher(stream);
        stream << '\n';
    }
}

// TODO getNbFilms() const: Retourner le nombre de films

// TODO supprimerFilms()
// Supprimer les films du tableau (delete)
void supprimerFilms()
{
    for (int i = 0; i < nbFilms_; i++)
    {
        delete films_[i];
    }

    nbFilms_ = 0;
}


//! Méthode qui ajoute les restrictions d'un film avec un string.
//! \param ligne Le string comportant les restrictions du film.
//! \return      Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    // TODO
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    // Utiliser l'opérateur d'extraction (>>) pour retrouver le nom du film
    // Trouver le film qui comporte le nom
    // Si le film n'existe pas, retourner false
    // Faire une boucle while (stream >> int), puis utiliser ce int pour appeler la fonction
    // film->ajouterPaysRestreint
}

//! Méthode qui ajoute un film avec un string comportant les attributs du film.
//! \param ligne                Le string comportant les attributs du film.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un film à un
//!                             auteur.
//! \return                     Un bool représentant si l'opération est un succès.
bool Librairie::lireLigneFilm(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    std::istringstream stream(ligne);
    std::string nomFilm;
    unsigned int anneeSortie;
    int genreValeurEnum;
    int paysValeurEnum;
    bool estRestreintParAge;
    std::string nomAuteur;

    // TODO
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
    // Utiliser l'opérateur d'extraction (>>) pour retrouver les attributs du films
    // Si l'auteur n'existe pas, retourner false
    // Utiliser la fonction ajouter film
    stream >> std::quoted(nomFilm) >> anneeSortie;
    stream >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge;
    stream >> std::quoted(nomAuteur);
    Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur); // creation de l'Auteur* 

   
    Film::Genre genre;

    switch (genreValeurEnum) {

    case (-1):
        genre = Film::Genre::first_;
        break;
    case (0):
        genre = Film::Genre::Action;
        break;
    case (1):
        genre = Film::Genre::Aventure;
        break;
    case (2):
        genre = Film::Genre::Comedie;
        break;
    case (3):
        genre = Film::Genre::Horreur;
        break;
    case (4):
        genre = Film::Genre::Romance;
        break;
    case (5):
        genre = Film::Genre::last_;
        break;
    }



    Pays pays;

    switch (paysValeurEnum) {

    case (-1):
        pays = Pays::first_;
        break;
    case (0):
        pays = Pays::Bresil;
        break;
    case (1):
        pays = Pays::Canada;
        break;
    case (2):
        pays = Pays::Chine;
        break;
    case (3):
        pays = Pays::EtatsUnis;
        break;
    case (4):
        pays = Pays::France;
        break;
    case (5):
        pays = Pays::Japon;
        break;
    case (6):
        pays = Pays::RoyaumeUni;
        break;
    case (7):
        pays = Pays::Russie;
        break;
    case (8):
        pays = Pays::Mexique;
        break;
    case (9):
        pays = Pays::last_;
        break;
    }

    Film* ajoute = new Film(nomFilm, anneeSortie, genre, pays, estRestreintParAge,auteur);

    ajouterFilm(ajoute);
    if (stream.fail() == true)
    {
        return false;
    }
    else {
        return true;
    }
}
// TODO: trouverIndexFilm(const std::string& nomFilm) const
// Retourner l'indexe du film comportant le nom envoyé en paramètre
// Si le film n'existe pas, retourner -1 (FILM_INEXSISTANT)
int Librairie::trouverIndexFilm(const std::string& nomFilm) const
{
    int index(-1);
    for (int i = 0; i < nbFilms_; i++)
    {
        if (films_[i]->getNom() == nomFilm)
        {
            index = i;
        }
    }
    return index;
}
