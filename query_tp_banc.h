#ifndef QUERY_TP_BANC_H
#define QUERY_TP_BANC_H

#include <iostream>
#include <mysql.h>
#include "tp_banc.h"
#include <list>

class QueryTpBanc
{
    protected:
        MYSQL *conn;
        std::list<TpBanc> *listTpBanc;

    public:
        QueryTpBanc();
        virtual ~QueryTpBanc();
        std::list<TpBanc> *GetTpBanc();
};

#endif
