#ifndef TP_ORC_H
#define TP_ORC_H

#include <gtkmm.h>

class TpOrc
{
    protected:
        Glib::ustring idtipo;
        Glib::ustring tipo;

    public:
        TpOrc();
        virtual ~TpOrc();

        Glib::ustring get_idtipo();
        Glib::ustring get_tipo();

        void set_idtipo(Glib::ustring idtipo);
        void set_tipo(Glib::ustring tipo);
};

#endif
