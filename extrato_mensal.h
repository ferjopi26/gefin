#ifndef EXTRATO_MENSAL_H
#define ESTRATO_MENSAL_H

#include "printformoperation.h"
#include "item.h"
#include "banco.h"
#include "query_item.h"
#include <mysql.h>
#include <gtkmm.h>
#include <pangomm.h>
#include <iostream>

class ExtratoMensal : public PrintFormOperation
{
    protected:
        char *sql_itens, *sql_totais;
        Glib::ustring data_ini, data_fin, interval, idbanco;
        std::list<Item> *listItens;
        std::list<Banco> *listBanco;
        int num_rows, print_context_height, num_pages = 1, resto, page = 1, indiceInicial, indiceFinal, rows_per_page = 70, page_nr = 1;
        double n_pages = 1;

    public:
        ExtratoMensal();
        virtual ~ExtratoMensal();
        void header(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context);
        void footer(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context);
        void body(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr);
        void list_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring banco, std::list<Banco> *listBanco);
        void get_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring banco);
        void get_totais_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring idbanci);
};

#endif
