#ifndef ITEM_H
#define ITEM_H

#include <gtkmm.h>

class Item
{
    protected:
        Glib::ustring iditem;
        Glib::ustring item;
        Glib::ustring data;
        Glib::ustring valor;
        Glib::ustring classe;
        Glib::ustring banco;
        Glib::ustring tpbanc;
        Glib::ustring tporc;
        Glib::ustring receitas;
        Glib::ustring despesas;
        Glib::ustring saldo;
        Glib::ustring creditos;
        Glib::ustring debitos;
        Glib::ustring total_classe;

    public:
        Item();
        ~Item();
        Glib::ustring get_iditem();
        Glib::ustring get_item();
        Glib::ustring get_data();
        Glib::ustring get_valor();
        Glib::ustring get_classe();
        Glib::ustring get_banco();
        Glib::ustring get_tpbanc();
        Glib::ustring get_tporc();
        Glib::ustring get_receitas();
        Glib::ustring get_despesas();
        Glib::ustring get_saldo();
        Glib::ustring get_creditos();
        Glib::ustring get_debitos();
        Glib::ustring get_total_classe();

        void set_iditem(Glib::ustring iditem);
        void set_item(Glib::ustring item);
        void set_data(Glib::ustring data);
        void set_valor(Glib::ustring valor);
        void set_classe(Glib::ustring classe);
        void set_banco(Glib::ustring banco);
        void set_tpbanc(Glib::ustring tpbanc);
        void set_tporc(Glib::ustring tporc);
        void set_receitas(Glib::ustring receitas);
        void set_despesas(Glib::ustring despesas);
        void set_saldo(Glib::ustring saldo);
        void set_creditos(Glib::ustring creditos);
        void set_debitos(Glib::ustring debitos);
        void set_total_classe(Glib::ustring total_classe);
};

#endif
