#ifndef TP_BANC_H
#define TP_BANC_H

#include <gtkmm.h>

class TpBanc
{
    protected:
        Glib::ustring idtipo;
        Glib::ustring tipo;

    public:
        TpBanc();
        virtual ~TpBanc();

        Glib::ustring get_idtipo();
        Glib::ustring get_tipo();

        void set_idtipo(Glib::ustring idtipo);
        void set_tipo(Glib::ustring tipo);
};

#endif
