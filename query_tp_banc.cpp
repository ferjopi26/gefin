#include "query_tp_banc.h"

QueryTpBanc::QueryTpBanc()
{
    conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "fernando", "ferjopi26", "gefin_sdbox", 0, NULL, 0);
    mysql_set_character_set(conn, "utf8");
}

QueryTpBanc::~QueryTpBanc(){}

std::list<TpBanc> *QueryTpBanc::GetTpBanc()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    const char *sql = "SELECT idtipo, tipo FROM tpbanc";

    listTpBanc = new std::list<TpBanc>;

    mysql_query(conn, sql);

    result = mysql_store_result(conn);

    for (int i = 0; i < result->row_count; i++)
    {
        TpBanc tpbanc;
        row = mysql_fetch_row(result);

        tpbanc.set_idtipo(row[0]);
        tpbanc.set_tipo(row[1]);

        listTpBanc->push_back(tpbanc);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listTpBanc;
}
