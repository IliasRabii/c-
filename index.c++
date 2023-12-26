#include <iostream>
#include <string>
using namespace std;

class Souris
{
public:
  Souris(double poids, string couleur, unsigned int age = 0, unsigned int esperance_vie = 36)
  {
    cout << "Une nouvelle souris !" << endl;
    this->poids = poids;
    this->couleur = couleur;
    this->age = age;
    this->esperance_vie = esperance_vie;
    this->clonee = false;
  }

  Souris(const Souris& source)
  {
    cout << "Clonage d’une souris !" << endl;
    this->poids = source.poids;
    this->couleur = source.couleur;
    this->age = source.age;
    this->esperance_vie = source.esperance_vie / 5 * 4;
    this->clonee = true;
  }

  ~Souris() { cout << "Fin d’une souris..." << endl; }

  void afficher() const
  {
    cout << "Une souris ";
    if (clonee)
      cout << ", clonee, ";
    cout << age << " mois et pesant " << poids << " grammes" << endl;
  }

  void vieillir()
  {
    age++;
    if (clonee && age >= esperance_vie / 2)
      couleur = "verte";
  }

  void evolue()
  {
    while (age < esperance_vie)
      vieillir();
  }

private:
  double poids;
  string couleur;
  unsigned int age;
  unsigned int esperance_vie;
  bool clonee;
};

int main()
{
  Souris s1(50.0, "blanche", 2);
  Souris s2(45.0, "grise");
  Souris s3(s2);
  
  s1.afficher();
  s2.afficher();
  s3.afficher();
  s1.evolue();
  s2.evolue();
  s3.evolue();
  s1.afficher();
  s2.afficher();
  s3.afficher();
  return 0;
}