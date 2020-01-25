// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "GestionnaireAuteurs.h" 
#include "Auteur.h" 


// TODO: Constructeur par défault en utilisant la liste d'initialisation
GestionnaireAuteurs::GestionnaireAuteurs()
{
	Auteur auteurs_[NB_AUTEURS_MAX];

	for (int i = 0; i< NB_AUTEURS_MAX ; i++)
	{
		auteurs_[i] = Auteur();
	}
	nbAuteurs_ = 0;
}


// TODO ajouterAuteur(const Auteur& auteur)
// Ajouter un auteur au tableau des auteurs.
// Retourner false si il n'y a plus de place dans le tableau.
bool GestionnaireAuteurs::ajouterAuteur(const Auteur& auteur)
{
	if (nbAuteurs_ < NB_AUTEURS_MAX-1 )
	{
		auteurs_[nbAuteurs_] = auteur;
		nbAuteurs_++;
		return true;
	}
	else {
		return false;
	}
}


// TODO chercherAuteur(const std::string& nomAuteur)
// Chercher dans la liste des auteurs si un auteur comporte le nom passé en paramètre.
// Retourner un nullptr si ce n'est pas le cas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
	Auteur* ptrAuteur = nullptr; 

	for (int i = 0; i < nbAuteurs_; i++)
	{
		if (auteurs_[i].getNom() == nomAuteur)
		{
			ptrAuteur = &auteurs_[i];
		}
	}
	return ptrAuteur;
}


//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs.
//! \param nomFichier   Le nom du fichier à charger.
//! \return             Un bool représentant si le chargement a été un succès.
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        // TODO: envoyer chaque ligne à lireLigneAuteur
		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (lireLigneAuteur(ligne) == false)
			{
				return false;
			}
			

		}
	}
	else
	{  std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez-vous de le mettre au bon endroit.\n";
         return false;
	}
    
}



//! Méthode qui affiche la liste des auteurs.
//! \param stream Le stream dans lequel afficher.
void GestionnaireAuteurs::afficher(std::ostream& stream) const
{
    // Ne pas modifier cette méthode
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {

        auteurs_[i].afficher(stream);
        stream << '\n';

    }
}

// TODO getNbAuteurs() const: Retourner le nombre d'auteurs dans la liste
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
	return nbAuteurs_;
}


//! Méthode qui ajoute un auteur avec un string.
//! \param ligne Le string qui comporte tous les attributs de l'auteur.
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{

    // TODO
    // Utiliser l'opérateur d'extraction (>>) depuis le stream
    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)
	// "NOM AUTEUR" 1998;

    std::istringstream stream(ligne);
    std::string nom;
    unsigned int anneeDeNaissance;
	std::string nomAuteur;
	stream >> std::quoted(nom) >> anneeDeNaissance;
	Auteur ajoute(nom,anneeDeNaissance);
	ajouterAuteur(ajoute);
	if (stream.fail() == true)
	{
		return false;
	}
	else{
	
		return true; 
	}



}