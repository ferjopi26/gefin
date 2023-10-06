#ifndef QUERY_CLASSE_H
#define QUERY_CLASSE_H

#include <iostream>
#include <mysql.h>
#include "classe.h"
#include "item.h"
#include "connection.h"
#include <list>

class QueryClasse : public Connection
{
    protected:
        std::list<Classe> *listClasses;
        std::list<Item> *listTotalClasse;

    public:
        QueryClasse();
        virtual ~QueryClasse();
        std::list<Classe> *GetClasses();
        std::list<Item> *GetItens(char *dataini, char *datafin, const char *classe);
        std::list<Item> *GetTotaisItens(char *dataini, char *datafin, const char *classe);
        int InsertClasse(const char *classe);
};

#endif
