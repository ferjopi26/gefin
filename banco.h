#ifndef BANCO_H
#define BANCO_H

#include <gtkmm.h>

class Banco
{
    protected:
        Glib::ustring idbanco;
        Glib::ustring banco;
        Glib::ustring conta;
        Glib::ustring agencia;

    public:
        Banco();
        virtual ~Banco();

        Glib::ustring get_idbanco();
        Glib::ustring get_banco();
        Glib::ustring get_conta();
        Glib::ustring get_agencia();

        void set_idbanco(Glib::ustring idbanco);
        void set_banco(Glib::ustring banco);
        void set_conta(Glib::ustring conta);
        void set_agencia(Glib::ustring agencia);
};

#endif
