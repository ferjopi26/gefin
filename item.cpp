#include "item.h"

Glib::ustring Item::get_iditem(){return this->iditem;}
Glib::ustring Item::get_item(){return this->item;}
Glib::ustring Item::get_data(){return this->data;}
Glib::ustring Item::get_valor(){return this->valor;}
Glib::ustring Item::get_classe(){return this->classe;}
Glib::ustring Item::get_banco(){return this->banco;}
Glib::ustring Item::get_tporc(){return this->tporc;}
Glib::ustring Item::get_tpbanc(){return this->tpbanc;}
Glib::ustring Item::get_receitas(){return this->receitas;}
Glib::ustring Item::get_despesas(){return this->despesas;}
Glib::ustring Item::get_saldo(){return this->saldo;}
Glib::ustring Item::get_creditos(){return this->creditos;}
Glib::ustring Item::get_debitos(){return this->debitos;}
Glib::ustring Item::get_total_classe(){return this->total_classe;}

void Item::set_iditem(Glib::ustring iditem){this->iditem = iditem;}
void Item::set_item(Glib::ustring item){this->item = item;}
void Item::set_data(Glib::ustring data){this->data = data;}
void Item::set_valor(Glib::ustring valor){this->valor = valor;}
void Item::set_classe(Glib::ustring classe){this->classe = classe;}
void Item::set_banco(Glib::ustring banco){this->banco = banco;}
void Item::set_tporc(Glib::ustring tporc){this->tporc = tporc;}
void Item::set_tpbanc(Glib::ustring tpbanc){this->tpbanc = tpbanc;}
void Item::set_receitas(Glib::ustring receitas){this->receitas = receitas;}
void Item::set_despesas(Glib::ustring despesas){this->despesas = despesas;}
void Item::set_saldo(Glib::ustring saldo){this->saldo = saldo;}
void Item::set_creditos(Glib::ustring creditos){this->creditos = creditos;}
void Item::set_debitos(Glib::ustring debitos){this->debitos = debitos;}
void Item::set_total_classe(Glib::ustring total_classe){this->total_classe = total_classe;}

Item::Item(){}

Item::~Item(){}
