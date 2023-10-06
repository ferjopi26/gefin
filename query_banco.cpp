#include "query_banco.h"

QueryBanco::QueryBanco(){}

QueryBanco::~QueryBanco(){}

std::list<Banco> *QueryBanco::get_bancos()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    const char *sql = "SELECT idbanco, banco, conta, agencia FROM bancos ORDER BY banco";

    listBanco = new std::list<Banco>;

    mysql_query(conn, sql);

    result = mysql_store_result(conn);

    for (int i = 0; i < result->row_count; i++)
    {
        Banco banco;
        row = mysql_fetch_row(result);

        banco.set_idbanco(row[0]);
        banco.set_banco(row[1]);
        banco.set_conta(row[2]);
        banco.set_agencia(row[3]);

        listBanco->push_back(banco);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listBanco;
}

int QueryBanco::insert_banco(std::list<Banco> *listBanco)
{
    const char *banco, *conta, *agencia;
    char sql[1000];

    for (auto new_banco = listBanco->begin(); new_banco != listBanco->end(); ++new_banco)
    {
        banco = new_banco->get_banco().c_str();
        conta = new_banco->get_conta().c_str();
        agencia = new_banco->get_agencia().c_str();
    }

    sprintf(sql, "INSERT INTO bancos(banco, conta, agencia) VALUES('%s', '%s', '%s')", banco, conta, agencia);
    
    mysql_query(conn, sql);

    return mysql_insert_id(conn);
}
