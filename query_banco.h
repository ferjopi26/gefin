#ifndef QUERY_BANCO_H
#define QUERY_BANCO_H

#include <iostream>
#include <mysql.h>
#include "banco.h"
#include "connection.h"
#include <list>

class QueryBanco : public Connection
{
    protected:
        //MYSQL *conn;
        std::list<Banco> *listBanco;

    public:
        QueryBanco();
        virtual ~QueryBanco();
        std::list<Banco> *get_bancos();
        int insert_banco(std::list<Banco> *listBanco);
};

#endif
