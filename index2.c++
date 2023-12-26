#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Auteur
{
public:
  Auteur(const string& nom, bool prix = false)
    : nom_(nom), prix_(prix) {}

  const string& getNom() const { return nom_; }
  bool getPrix() const { return prix_; }

  // Méthode `==`
  bool operator==(const Auteur& autre) const
  {
    return nom_ == autre.nom_ && prix_ == autre.prix_;
  }
  

private:
  string nom_;
  bool prix_;
};

class Oeuvre
{
public:
  Oeuvre(const string& titre, const Auteur& auteur, const string& langue)
    : titre_(titre), auteur_(auteur), langue_(langue) {}

  const string& getTitre() const { return titre_; }
  const Auteur& getAuteur() const { return auteur_; }
  const string& getLangue() const { return langue_; }

  void afficher() const {
    cout << titre_ << ", " << auteur_.getNom() << ", en " << langue_ << endl;
  }

  ~Oeuvre() {
    cout << "L’oeuvre \"" << titre_ << ", " << auteur_.getNom() << ", en " << langue_ << "\" n’est plus disponible." << endl;
  }

  // Méthode `==`
  bool operator==(const Oeuvre& autre) const
  {
    return titre_ == autre.titre_ && auteur_ == autre.auteur_ && langue_ == autre.langue_;
  }

private:
  string titre_;
  const Auteur& auteur_;
  string langue_;
};

class Exemplaire
{
public:
  Exemplaire(const Oeuvre& oeuvre) : oeuvre_(oeuvre) {}
  Exemplaire(const Exemplaire& autre) : oeuvre_(autre.oeuvre_) {}
  ~Exemplaire() {}

  Oeuvre getOeuvre() const { return oeuvre_; }

  void afficher() const {
    cout << "Exemplaire de : " << oeuvre_.getTitre() << ", "
      << oeuvre_.getAuteur().getNom() << ", en " << oeuvre_.getLangue() << endl;
  }

private:
  Oeuvre oeuvre_;
};

class Bibliotheque
{
public:
  Bibliotheque(const string& nom) : nom_(nom) {}
  ~Bibliotheque() {}

  const string& getNom() const { return nom_; }

  void stocker(const Oeuvre& oeuvre, int n = 1)
  {
    for (int i = 0; i < n; i++) {
      exemplaires_.push_back(new Exemplaire(oeuvre));
    }
  }

  void lister_exemplaires(const string& langue = "") const
  {
    if (langue == "") {
      for (Exemplaire* exemplaire : exemplaires_) {
        exemplaire->afficher();
      }
    } else {
      for (Exemplaire* exemplaire : exemplaires_) {
        if (exemplaire->getOeuvre().getLangue() == langue) {
          exemplaire->afficher();
        }
      }
    }
  }

  int compter_exemplaires(const Oeuvre& oeuvre) const
{
  int count = 0;
  for (Exemplaire* exemplaire : exemplaires_) {
    if (exemplaire->getOeuvre() == oeuvre) {
      count++;
    }
  }
  return count;
}


  void afficher_auteurs(bool prix = false) const
  {
    for (Exemplaire* exemplaire : exemplaires_) {
      if (prix && !exemplaire->getOeuvre().getAuteur().getPrix()) {
        continue;
      }
      cout << exemplaire->getOeuvre().getAuteur().getNom() << endl;
    }
  }

private:
  string nom_;
  vector<Exemplaire*> exemplaires_;
};


int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les MisÃ©rables"           , a1, "franÃ§ais" ),
         o2("L'Homme qui rit"          , a1, "franÃ§ais" ),
         o3("Le Comte de Monte-Cristo" , a2, "franÃ§ais" ),
         o4("Zazie dans le mÃ©tro"      , a3, "franÃ§ais" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothÃ¨que " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs Ã  succÃ¨s sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}