#ifndef CLASSE_H
#define CLASSE_H

#include <gtkmm.h>

class Classe
{
    protected:
        Glib::ustring idclasse;
        Glib::ustring classe;

    public:
        Classe();
        virtual ~Classe();

        Glib::ustring get_idclasse();
        Glib::ustring get_classe();

        void set_idclasse(Glib::ustring idclasse);
        void set_classe(Glib::ustring classe);
};

#endif
