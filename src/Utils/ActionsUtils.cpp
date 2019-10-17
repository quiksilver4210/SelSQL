//
// Created by sapiest on 02.10.2019.
//

#include "Headers/ActionsUtils.h"
#include <queue>

std::string ActionsUtils::makeRequestCreateFromTable(Table table) {
    const char space = ' ';
    const char semicolon = ';';
    const char comma = ',';
    std::string str = "CREATE TABLE ";
    str += table.name + '(';
    for (int i = 0; i < table.getFields().size(); ++i) {
        auto field = table.getFields()[i];
        str += field.first + space;
        str += parserUtils.typeToString(field.second.type) + space;
        for (auto& constraint : field.second.getConstraints()) {
            str += parserUtils.constraintToString(constraint) + space;
        }
        if (i != table.getFields().size() - 1 && table.getFields().size() > 1) {
            str += comma;
        }
    }
    str += ')';
    str += semicolon;

    return str;
}

Error ActionsUtils::checkConstraint(std::vector<std::string> columns, std::vector<std::string> values,
                                    std::pair<std::shared_ptr<Table>, std::shared_ptr<Cursor>> cursor) {
    std::string val;
    Error error;
    std::shared_ptr<Table> table = cursor.first;

    do {
        auto record = cursor.second->Fetch();
        /// for rows data
        for (int i = 0; i < table->getFields().size(); ++i) {
            auto tableCol = table->getFields()[i];
            if (columns.empty()) {
                val = values[i];
            } else {
                auto valIt = std::find(columns.begin(), columns.end(), tableCol.first);
                if (valIt == columns.end()) {
                    val = "null";
                } else {
                    int columnIndex = std::distance(columns.begin(), valIt);
                    val = values[columnIndex];
                    std::transform(val.begin(), val.end(), val.begin(),
                                   [](unsigned char c) { return std::tolower(c); });
                }
            }

            for (int j = 0; j < tableCol.second.getConstraints().size(); ++j) {
                auto id = tableCol.second.getConstraints()[j];
                if (record.empty()) {
                    if (!id || id == PRIMARY_KEY) {
                        error = checkNotNull(val, val);
                        if (error.getErrorCode()) {
                            return error;
                        }
                    }
                }
                for (auto& elem : record) {
                    if (tableCol.first == elem.first) {
                        auto curVal = elem.second;
                        std::transform(curVal.begin(), curVal.end(), curVal.begin(),
                                       [](unsigned char c) { return std::tolower(c); });
                        error = constraintsCheckers[id](val, curVal);
                        if (error.getErrorCode()) {
                            return error;
                        }
                        break;
                    }
                }
            }
        }
    } while (!cursor.second->Next());

    return error;
}

Error ActionsUtils::checkNotNull(const std::string& newVal, const std::string& oldVal) {
    std::string temp = newVal;
    std::transform(temp.begin(), temp.end(), temp.begin(), [](unsigned char c) { return std::tolower(c); });
    if (temp == "null") {
        return Error(ErrorConstants::ERR_NOT_NULL);
    }
    return Error();
}

Error ActionsUtils::checkUnique(const std::string& newVal, const std::string& oldVal) {
    std::string val;
    if (newVal[0] == '\'') {
        val = newVal.substr(1, newVal.length() - 1);
    } else {
        val = newVal;
    }
    if (val == oldVal) {
        return Error(ErrorConstants::ERR_UNIQUE);
    }
    return Error();
}

Error ActionsUtils::checkPrimaryKey(const std::string& newVal, const std::string& oldVal) {
    Error err = checkNotNull(newVal, oldVal);
    if (err.getErrorCode()) {
        return err;
    }
    err = checkUnique(newVal, oldVal);
    if (err.getErrorCode()) {
        return err;
    }
    return Error();
}

RecordsData ActionsUtils::checkExpression(std::pair<Expr, vecString> expr, RecordsData recordsData) {
    RecordsData newRecords;
    std::vector<std::pair<std::string, Condition>> exprRes;
    std::vector<int> binRes;
    for (auto& row : recordsData) {
        for (auto& record : row) {
            std::vector<std::pair<Cmp, std::string>> res = countExpr(record, row, expr.first);
            if (res.empty())
                continue;
            for (auto& exp : res) {
                exprRes.emplace_back(std::make_pair(record.second, Condition(exp.first, exp.second)));
            }
        }
        for (auto& res : exprRes) {
            int out = checkSign[res.second.sign](res.first, res.second.value);
            binRes.push_back(out);
        }
        auto total = checkLogic(binRes, expr.second);
        if (total) {
            newRecords.emplace_back(row);
        }
        binRes.clear();
        exprRes.clear();
    }
    return newRecords;
}

std::vector<std::pair<Cmp, std::string>> ActionsUtils::countExpr(std::pair<std::string, std::string> record,
                                                                 std::vector<std::pair<std::string, std::string>> row,
                                                                 Expr exprs) {
    std::vector<std::pair<Cmp, std::string>> res;
    std::queue<double> curExpr;
    auto columnName = record.first;
    auto val = record.second;
    for (int index = 0; index < exprs.size(); index++) {
        auto expr = exprs[index];
        auto valExpr = expr.first.first;
        if (valExpr != columnName)
            continue;
        if (std::isdigit(*val.c_str())) {
            auto cmp = expr.first.second;
            auto tempExpr = expr.second;
            if (tempExpr.empty()) {
                continue;
            }
            int i = 0;
            while (i != tempExpr.size()) {
                auto elem = tempExpr[i];
                i++;
                for (auto& col : row) {
                    if (elem == col.first) {
                        elem = col.second;
                    }
                }

                if (std::isdigit(*elem.c_str())) {
                    curExpr.push(std::stoi(elem));
                    continue;
                }
                double a = curExpr.front();
                curExpr.pop();
                double b = curExpr.front();
                curExpr.pop();
                curExpr.push(ActionsUtils::calculate[elem](a, b));
            }
            res.emplace_back(std::make_pair(cmp, std::to_string(curExpr.front())));
        } else {
            auto curExprVal = expr.second[0].substr(1, expr.second[0].length() - 2);
            auto cmp = expr.first.second;
            res.emplace_back(std::make_pair(cmp, curExprVal));
        }
    }
    return res;
}
int ActionsUtils::checkLogic(std::vector<int> binRes, std::vector<std::string> logicElems) {
    // TODO починить со скобками.
    std::queue<int> elems;
    int j = logicElems.size() - 1;
    if (j < 0)
        return binRes[0];
    for (int i = binRes.size() - 1; i >= 0; --i) {
        if (elems.empty()) {
            if (logicElems[j] == "not") {
                elems.push(!binRes[i]);
                j--;
            } else {
                elems.push(binRes[i]);
            }
            continue;
        }
        if (logicElems[j] == "not") {
            elems.push(!binRes[i]);
            j--;
        } else {
            elems.push(binRes[i]);
        }
        auto a = elems.front();
        elems.pop();
        auto b = elems.front();
        elems.pop();
        elems.push(logicCalculate[logicElems[j--]](a, b));
    }
    return elems.front();
}
