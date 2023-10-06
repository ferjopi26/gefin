#ifndef RELATORIO_MENSAL_H
#define RELATORIO_MENSAL_H

#include "printformoperation.h"
#include <mysql.h>
#include <gtkmm.h>
#include <pangomm.h>
#include <iostream>
#include "query_item.h"
#include "item.h"

class RelatorioMensal : public PrintFormOperation
{
    protected:
        char *sql_itens, *sql_totais;
        Glib::ustring data_ini, data_fin, interval;
        std::list<Item> *listItens;
        int num_rows, print_context_height, num_pages = 1, resto, page = 1, indiceInicial, indiceFinal, rows_per_page = 70, page_nr = 1;
        double n_pages = 1;

    public:
        RelatorioMensal();
        virtual ~RelatorioMensal();
        Glib::RefPtr<RelatorioMensal> create();
        void header(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context);
        void footer(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context);
        void body(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr);
        void list_itens(Glib::ustring dataini, Glib::ustring datafin, Glib::ustring period);
        void get_itens(Glib::ustring dataini, Glib::ustring datafin);
        void get_totais_itens(Glib::ustring dataini, Glib::ustring datafin);
};

#endif
