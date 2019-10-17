//
// Created by toxaxab on 30.09.2019.
//

#ifndef SELSQL_COMMONUTILS_H
#define SELSQL_COMMONUTILS_H

#include <map>
#include <string>
#include <vector>
enum Type { TYPE_INT, TYPE_FLOAT, TYPE_CHAR };

enum Constraint { NOT_NULL, PRIMARY_KEY, UNIQUE };

enum Action { SHOW_CREATE, DROP, CREATE, SELECT, DELETE_ACT, INSERT, UPDATE };

enum Cmp { GREATEREQUALS, GREATER, NOEQUALS, EQUALS, LOWER, LOWEREQUALS };

struct Condition {
    Condition(Cmp _sign, std::string _value) : sign(_sign), value(_value) {}
    Condition() = default;
    Cmp sign;
    std::string value;
};

typedef std::vector<std::string> vecString;
typedef std::vector<std::pair<std::pair<std::string, Cmp>, vecString>> Expr;
typedef std::vector<std::vector<std::pair<std::string, std::string>>> RecordsData;

#endif  // SELSQL_COMMONUTILS_H
