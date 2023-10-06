#ifndef QUERY_TP_ORC_H
#define QUERY_TP_ORC_H

#include <iostream>
#include <mysql.h>
#include "tp_orc.h"
#include <list>

class QueryTpOrc
{
    protected:
        MYSQL *conn;
        std::list<TpOrc> *listTpOrc;

    public:
        QueryTpOrc();
        virtual ~QueryTpOrc();
        std::list<TpOrc> *GetTpOrc();
};

#endif
