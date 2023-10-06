#ifndef CLASSES_H
#define CLASSES_H

#include <gtkmm.h>
#include <mysql.h>
#include <iostream>
#include "query_classe.h"
#include"query_item.h"
#include "nova_classe.h"

class Classes
{
    protected:
        Gtk::Window* win_classes;
        Gtk::ComboBox *cmb_classes;
        Glib::RefPtr<Gtk::ListStore> store_classes;
        Glib::ustring idclasse, selected_idclasse;
    
    public:
        Classes();
        virtual ~Classes();
        Gtk::Window *getWindow();
        
        void getClasses();
        void getItens();
        void getTotais();

        void on_cmb_classes_changed();
        void quit();
        bool on_entry_dataini_release_event(GdkEventButton* release_event);
        bool on_entry_datafin_release_event(GdkEventButton* release_event);
        void on_calendar_dataini_day_selected();
        void on_itm_nova_classe_activate_cb();
        void on_calendar_datafin_day_selected();
        bool novaClasse(GdkEventAny * ea);
    
        class ModelColumnsClasses : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsClasses()
                {
                    add(idclasse);
                    add(classe);
                }

                Gtk::TreeModelColumn<Glib::ustring> idclasse;
                Gtk::TreeModelColumn<Glib::ustring> classe;
        };

        class ModelColumnsItens : public Gtk::TreeModel::ColumnRecord
        {
            public:
                ModelColumnsItens()
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

        ModelColumnsClasses m_Columns_Classes;
        ModelColumnsItens m_Columns_Itens;

        Glib::RefPtr<Gtk::Builder> builder;
};

#endif
