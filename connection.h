#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <mysql.h>

class Connection{
    protected:
        MYSQL *conn;
    
    public:
        Connection();
        virtual ~Connection();
};

#endif