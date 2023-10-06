#include "tp_orc.h"

TpOrc::TpOrc(){}

TpOrc::~TpOrc(){}

Glib::ustring TpOrc::get_idtipo(){return idtipo;}
Glib::ustring TpOrc::get_tipo(){return tipo;}

void TpOrc::set_idtipo(Glib::ustring idtipo){this->idtipo = idtipo;}
void TpOrc::set_tipo(Glib::ustring tipo){this->tipo = tipo;}
