#ifndef QUERY_ITEM_H
#define QUERY_ITEM_H

#include <iostream>
#include <mysql.h>
#include "item.h"
#include <list>
#include "connection.h"


class QueryItem : public Connection
{
    protected:
        //MYSQL *conn;
        std::list<Item> *listItens;
        
    public:
        QueryItem();
        virtual ~QueryItem();
        std::list<Item> *GetItens(const char *dataini, const char *datafin);
        std::list<Item> *GetItens(const char *dataini, const char *datafin, const char *banco);
        std::list<Item> *GetItens(const char *dataini, const char *datafin, int tpbanc);
        std::list<Item> *GetTotaisItens(const char *dataini, const char *datafin);
        std::list<Item> *GetTotaisItens(const char *dataini, const char *datafin, const char *banco);
        char *GetTotaisItens(const char *dataini, const char *datafin, int tpbanc);
        int InsertItem(Item *item);
        int UpdateItem(Item *item);
        int DeleteItem(Glib::ustring iditem);
};

#endif
