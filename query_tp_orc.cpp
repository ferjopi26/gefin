#include "query_tp_orc.h"

QueryTpOrc::QueryTpOrc()
{
    conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "fernando", "ferjopi26", "gefin_sdbox", 0, NULL, 0);
    mysql_set_character_set(conn, "utf8");
}

QueryTpOrc::~QueryTpOrc(){}

std::list<TpOrc> *QueryTpOrc::GetTpOrc()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    const char *sql = "SELECT idtipo, tipo FROM tporc";

    listTpOrc = new std::list<TpOrc>;

    mysql_query(conn, sql);

    result = mysql_store_result(conn);

    for (int i = 0; i < result->row_count; i++)
    {
        TpOrc tporc;
        row = mysql_fetch_row(result);

        tporc.set_idtipo(row[0]);
        tporc.set_tipo(row[1]);

        listTpOrc->push_back(tporc);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return listTpOrc;
}
