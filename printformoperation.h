#ifndef PRINTFORMOPERATION_H
#define PRINTFORMOPERATION_H

#include <gtkmm.h>

class PrintFormOperation : public Gtk::PrintOperation
{
    public:
        virtual ~PrintFormOperation();
        PrintFormOperation();

    protected:
        char time_string[100];
        int fill = 1;
        
        void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context);
        void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context, int page_nr);
        virtual void header(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context)=0;
        virtual void footer(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context)=0;
        virtual void body(const Cairo::RefPtr<Cairo::Context>& cr, const Glib::RefPtr<Gtk::PrintContext>& print_context, int page_nr)=0;
        void current_time();
        void fill_color(const Cairo::RefPtr<Cairo::Context>& cr, int y, int current_x, double width, int fontSize);

        Glib::RefPtr<Pango::Layout> m_refLayout;
};

#endif
