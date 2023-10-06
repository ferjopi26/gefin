#include "connection.h"

Connection::Connection()
{
    conn = mysql_init(NULL);
    mysql_real_connect(conn, "host", "user", "password", "gefin", 0, NULL, 0);
    mysql_set_character_set(conn, "utf8");
}

Connection::~Connection()
{
    mysql_close(conn);
}
