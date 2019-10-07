
#ifndef SELSQL_CONSTANTS_H
#define SELSQL_CONSTANTS_H
#include "math.h"

class Constants {
   public:
    inline static const std::string FILE_TYPE = ".selDB";
    static const int MD_TABLE_NAME_SIZE = 256;
    static const int MD_TABLE_COLUMN_AMOUNT_SIZE = sizeof(int);
    static const int MD_TABLE_COLUMN_AMOUNT_MAX = 16;
    static const int MD_COLUMN_NAME_SIZE = 256;
    static const int MD_COLUMN_TYPE_SIZE = sizeof(int);
    static const int MD_COLUMN_CONSTR_SIZE = sizeof(int);
    static const int MD_COLUMN_CONSTR_AMOUNT_SIZE = sizeof(int);
    static const int MD_COLUMN_CONSTR_AMOUNT_MAX = 10;
    static const int DATA_PAGE_START_POS = MD_TABLE_NAME_SIZE + MD_TABLE_COLUMN_AMOUNT_SIZE +
                                           MD_TABLE_COLUMN_AMOUNT_MAX * (MD_COLUMN_NAME_SIZE + MD_COLUMN_TYPE_SIZE +
                                                                         MD_COLUMN_CONSTR_AMOUNT_SIZE +
                                                                         MD_COLUMN_CONSTR_AMOUNT_MAX * MD_COLUMN_CONSTR_SIZE);
    static const int DATA_PAGE_SIZE = 4 * 1024;
};

#endif  // SELSQL_CONSTANTS_H
