#include "query_item.h"
#include <cstdio>
#include <cstring>

QueryItem::QueryItem(){}

QueryItem::~QueryItem(){}

std::list<Item> *QueryItem::GetItens(const char *dataini, const char *datafin) //itens
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    listItens = new std::list<Item>;

    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT itens.iditem, itens.item, DATE_FORMAT(itens.data, '%%d/%%m/%Y'), itens.valor, classes.classe, \
    itens.banco, itens.tporc, itens.tpbanc FROM itens INNER JOIN classes ON itens.classe = classes.idclasse WHERE data BETWEEN '%s' AND '%s' \
    AND itens.tporc between 1 AND 2 ORDER BY itens.iditem", dataini, datafin);
    
    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        
        item.set_iditem(row[0]);
        item.set_item(row[1]);
        item.set_data(row[2]);
        item.set_valor(row[3]);
        item.set_classe(row[4]);
        item.set_banco(row[5]);
        item.set_tporc(row[6]);
        item.set_tpbanc(row[7]);

        listItens->push_back(item);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listItens;
}

std::list<Item> *QueryItem::GetItens(const char *dataini, const char *datafin, const char *banco) //bancos
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    listItens = new std::list<Item>;
    
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT itens.iditem, itens.item, DATE_FORMAT(itens.data, '%%d/%%m/%Y'), itens.valor, \
    tpbanc.tipo FROM itens INNER JOIN tpbanc ON itens.tpbanc = tpbanc.idtipo WHERE itens.data BETWEEN '%s' AND '%s' AND itens.banco = %s\
     AND itens.tpbanc between 1 AND 2 ORDER BY itens.iditem", dataini, datafin, banco);
    
    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        
        item.set_iditem(row[0]);
        item.set_item(row[1]);
        item.set_data(row[2]);
        item.set_valor(row[3]);
        item.set_tpbanc(row[4]);
        
        listItens->push_back(item);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listItens;
}

std::list<Item> *QueryItem::GetItens(const char *dataini, const char *datafin, int tpbanc) /* especie */
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    listItens = new std::list<Item>;
    
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT iditem, item, valor, DATE_FORMAT(data, '%%d/%%m/%Y') FROM itens WHERE data BETWEEN '%s' \
    AND '%s' AND tpbanc = %d", dataini, datafin, tpbanc);
    
    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        
        item.set_iditem(row[0]);
        item.set_item(row[1]);
        item.set_valor(row[2]);
        item.set_data(row[3]);
        item.set_tpbanc(row[4]);
        
        listItens->push_back(item);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listItens;

}

std::list<Item> *QueryItem::GetTotaisItens(const char *dataini, const char *datafin)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    listItens = new std::list<Item>;
    
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT receitas, despesas, receitas - despesas AS saldo FROM (SELECT IFNULL(SUM(valor), 0) AS receitas FROM itens WHERE data  BETWEEN '%s' AND '%s' \
    AND tporc = 2) AS receitas, (SELECT IFNULL(SUM(valor), 0) AS despesas FROM itens WHERE data  BETWEEN '%s' AND '%s' AND tporc = 1) AS despesas", 
    dataini, datafin, dataini, datafin);

    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        
        item.set_receitas(row[0]);
        item.set_despesas(row[1]);
        item.set_saldo(row[2]);

        listItens->push_back(item);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listItens;
}

std::list<Item> *QueryItem::GetTotaisItens(const char *dataini, const char *datafin, const char *banco)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    listItens = new std::list<Item>;
    
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT creditos, debitos, creditos - debitos AS saldo FROM (SELECT IFNULL(SUM(valor), 0) AS creditos FROM itens WHERE data  BETWEEN '%s' AND '%s' \
    AND tpbanc = 1 AND banco = %s) AS creditos, (SELECT IFNULL(SUM(valor), 0) AS debitos FROM itens WHERE data  BETWEEN '%s' AND '%s' AND tpbanc = 2 AND banco = %s) \
    AS despesas", dataini, datafin, banco, dataini, datafin, banco);

    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        Item item;
        
        item.set_creditos(row[0]);
        item.set_debitos(row[1]);
        item.set_saldo(row[2]);

        listItens->push_back(item);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listItens;
}

char *QueryItem::GetTotaisItens(const char *dataini, const char *datafin, int tpbanc)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    char *total;

    listItens = new std::list<Item>;
    
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("SELECT IFNULL(SUM(valor), 0) FROM itens WHERE data BETWEEN '%s' AND '%s' AND tpbanc = %d", 
    dataini, datafin, tpbanc);
    
    mysql_query(conn, usql.c_str());

    result = mysql_store_result(conn);

    while ((row = mysql_fetch_row(result)) != NULL)
    {
        total = row[0];
    }

    mysql_free_result(result);
    mysql_close(conn);

    return total;
}

int QueryItem::InsertItem(Item *item)
{
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("INSERT INTO itens(item, valor, data, classe, banco, tporc, tpbanc) VALUES('%s', %s, '%s', %s, %s, %s, %s)", 
    item->get_item(), item->get_valor(), item->get_data(), item->get_classe(), item->get_banco(), item->get_tporc(), item->get_tpbanc());
    
    mysql_query(conn, usql.c_str());
    
    mysql_close(conn);

    return mysql_insert_id(conn);
}

int QueryItem::UpdateItem(Item *item)
{
    const char *iditem, *item_desc, *valor, *data, *classe, *banco, *tporc, *tpbanc;
    
    iditem = item->get_iditem().c_str();
    item_desc = item->get_item().c_str();
    valor = item->get_valor().c_str();
    data = item->get_data().c_str();
    classe = item->get_classe().c_str();
    banco = item->get_banco().c_str();
    tporc = item->get_tporc().c_str();
    tpbanc = item->get_tpbanc().c_str();

    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("UPDATE itens SET item = '%s', valor = %s, data ='%s', classe = %s, banco = %s, tporc = %s, tpbanc = %s \
    WHERE iditem = %s", item->get_item(), item->get_valor(), item->get_data(), item->get_classe(), item->get_banco(), item->get_tporc(), 
    item->get_tpbanc(), item->get_iditem());
    
    mysql_query(this->conn, usql.c_str());

    int affectedRows = mysql_affected_rows(this->conn);

    mysql_close(this->conn);

    return affectedRows;

}

int QueryItem::DeleteItem(Glib::ustring iditem)
{
    Glib::ustring usql = Glib::ustring::sprintf<Glib::ustring>("DELETE FROM itens WHERE iditem = %s", iditem);

    mysql_query(this->conn, usql.c_str());

    int affectedRows = mysql_affected_rows(this->conn);

    mysql_close(this->conn);

    return affectedRows;
}
