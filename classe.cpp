#include "classe.h"

Classe::Classe(){}

Classe::~Classe(){}

Glib::ustring Classe::get_idclasse(){return idclasse;}
Glib::ustring Classe::get_classe(){return classe;}

void Classe::set_idclasse(Glib::ustring idclasse){this->idclasse = idclasse;}
void Classe::set_classe(Glib::ustring classe){this->classe = classe;}
