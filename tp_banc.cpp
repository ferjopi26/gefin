#include "tp_banc.h"

TpBanc::TpBanc(){}

TpBanc::~TpBanc(){}

Glib::ustring TpBanc::get_idtipo(){return idtipo;}
Glib::ustring TpBanc::get_tipo(){return tipo;}

void TpBanc::set_idtipo(Glib::ustring idtipo){this->idtipo = idtipo;}
void TpBanc::set_tipo(Glib::ustring tipo){this->tipo = tipo;}
