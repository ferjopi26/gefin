#include "query_classe.h"

QueryClasse::QueryClasse(){}

QueryClasse::~QueryClasse(){}

std::list<Classe> *QueryClasse::GetClasses()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    const char *sql = "SELECT idclasse, classe FROM classes ORDER BY classe";

    listClasses = new std::list<Classe>;

    mysql_query(conn, sql);

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Classe classe;
        
        classe.set_idclasse(row[0]);
        classe.set_classe(row[1]);

        listClasses->push_back(classe);
    }

    mysql_free_result(result);
    mysql_close(conn);
    
    return listClasses;
}

std::list<Item> *QueryClasse::GetItens(char *dataini, char *datafin, const char *classe)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    std::list<Item> *listItens = new std::list<Item>;

    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT iditem, item, valor, DATE_FORMAT(data, '%%d/%%m/%Y') AS data FROM itens WHERE data BETWEEN '%s' \
    AND '%s' AND classe = %s AND itens.tporc between 1 AND 2 ORDER BY itens.iditem", dataini, datafin, classe);
    
    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        
        item.set_iditem(row[0]);
        item.set_item(row[1]);
        item.set_valor(row[2]);
        item.set_data(row[3]);

        listItens->push_back(item);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listItens;
}

std::list<Item> *QueryClasse::GetTotaisItens(char *dataini, char *datafin, const char *classe)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    listTotalClasse = new std::list<Item>;
    
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT IFNULL(SUM(valor), 0) AS total FROM itens WHERE data  BETWEEN '%s' AND '%s' AND classe = %s", 
    dataini, datafin, classe);

    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        item.set_total_classe(row[0]);
        listTotalClasse->push_back(item);
    }

    return listTotalClasse;
}

int QueryClasse::InsertClasse(const char *classe)
{
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("INSERT INTO classes (classe) VALUES('%s')", classe);

    mysql_query(conn, usql.c_str());

    mysql_close(conn);

    return mysql_insert_id(conn);
}
