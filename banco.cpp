#include "banco.h"

Glib::ustring Banco::get_idbanco(){return idbanco;}
Glib::ustring Banco::get_banco(){return banco;}
Glib::ustring Banco::get_conta(){return conta;}
Glib::ustring Banco::get_agencia(){return agencia;}

void Banco::set_idbanco(Glib::ustring idbanco){this->idbanco = idbanco;}
void Banco::set_banco(Glib::ustring banco){this->banco = banco;}
void Banco::set_conta(Glib::ustring conta){this->conta = conta;}
void Banco::set_agencia(Glib::ustring agencia){this->agencia = agencia;}

Banco::Banco(){}

Banco::~Banco(){}
