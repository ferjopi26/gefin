#ifndef ESPECIE_H
#define ESPECIE_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include "item.h"
#include "query_item.h"

class Especie{
    protected:
        Gtk::Window* win_especie;
    
    public:
        Especie();
        virtual ~Especie();
        Gtk::Window *getWindow();
        void getItens();
        void getTotal();

        void on_calendar_dataini_day_selected();
        void on_calendar_datafin_day_selected();
        bool on_entry_dataini_release_event(GdkEventButton* release_event);
        bool on_entry_datafin_release_event(GdkEventButton* release_event);
        void on_btn_fechar_clicked();
    
        class ModelColumnsEspecie : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsEspecie()
                {
                    add(iditem);
                    add(item);
                    add(valor);
                    add(data);
                }

                Gtk::TreeModelColumn<Glib::ustring> iditem;
                Gtk::TreeModelColumn<Glib::ustring> item;
                Gtk::TreeModelColumn<Glib::ustring> valor;
                Gtk::TreeModelColumn<Glib::ustring> data;
        };

        ModelColumnsEspecie m_Columns_Especie;

        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
