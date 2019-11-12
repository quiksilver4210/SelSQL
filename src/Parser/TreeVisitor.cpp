//
// Created by sapiest on 20.10.2019.
//

#include "Headers/TreeVisitor.h"
#include <iostream>
#include "../Logic/Actions/Headers/CreateAction.h"
#include "../Logic/Actions/Headers/DeleteAction.h"
#include "../Logic/Actions/Headers/DropAction.h"
#include "../Logic/Actions/Headers/InsertAction.h"
#include "../Logic/Actions/Headers/SelectAction.h"
#include "../Logic/Actions/Headers/ShowCreateAction.h"
#include "../Logic/Actions/Headers/UpdateAction.h"
#include "Headers/CreateVisitor.h"
#include "Headers/DeleteVisitor.h"
#include "Headers/DropVisitor.h"
#include "Headers/InsertVisitor.h"
#include "Headers/SelectVisitor.h"
#include "Headers/ShowCreateVisitor.h"
#include "Headers/UpdateVisitor.h"
#include "Nodes/ActionNodes/CreateNode.h"
#include "Nodes/ActionNodes/DeleteNode.h"
#include "Nodes/ActionNodes/DropNode.h"
#include "Nodes/ActionNodes/InsertNode.h"
#include "Nodes/ActionNodes/SelectNode.h"
#include "Nodes/ActionNodes/ShowCreateNode.h"
#include "Nodes/ActionNodes/UpdateNode.h"
#include "Nodes/ColumnNode.h"
#include "Nodes/ColumnsAndExprNode.h"
#include "Nodes/ColumnsAndValuesNode.h"
#include "Nodes/ConstraintNode.h"
#include "Nodes/ExpressionsNodes/CompareNodes/EqualsNode.h"
#include "Nodes/ExpressionsNodes/CompareNodes/LessEqNode.h"
#include "Nodes/ExpressionsNodes/CompareNodes/MoreEqNode.h"
#include "Nodes/ExpressionsNodes/CompareNodes/MoreNode.h"
#include "Nodes/ExpressionsNodes/CompareNodes/NoEqualsNode.h"
#include "Nodes/ExpressionsNodes/ExprNode.h"
#include "Nodes/ExpressionsNodes/IndentExprNode.h"
#include "Nodes/ExpressionsNodes/IndentNode.h"
#include "Nodes/ExpressionsNodes/LogicNodes/AndLogicNode.h"
#include "Nodes/ExpressionsNodes/LogicNodes/NotLogicNode.h"
#include "Nodes/ExpressionsNodes/LogicNodes/OrLogicNode.h"
#include "Nodes/ExpressionsNodes/UpdateExprNode.h"
#include "Nodes/JoinNodes/IntersectJoinNode.h"
#include "Nodes/JoinNodes/UnionJoinNode.h"
#include "Nodes/RootNode.h"
#include "Nodes/UpdatesAndExprNode.h"
#include "Nodes/ValuesNodes/CharValueNode.h"
#include "Nodes/ValuesNodes/FloatValueNode.h"
#include "Nodes/ValuesNodes/IntValueNode.h"
#include "Nodes/ValuesNodes/NullValueNode.h"
#include "Nodes/VariableListNode.h"
#include "Nodes/VariableNode.h"

void TreeVisitor::visit(RootNode* node) {
    for (auto& child : node->getChildren()) {
        // request->clear(); перед заходом в новую функцию, возможно, стоит отчищать
        child->accept(this);
    }
}

void TreeVisitor::visit(CreateNode* node) {
    auto visitor = std::make_shared<CreateVisitor>(CreateVisitor());
    auto action = std::make_shared<CreateNode>(*node);
    message = CreateAction(visitor).execute(action);
}

void TreeVisitor::visit(DropNode* node) {
    auto visitor = std::make_shared<DropVisitor>(DropVisitor());
    auto action = std::make_shared<DropNode>(*node);
    message = DropAction(visitor).execute(action);
}

void TreeVisitor::visit(ShowCreateNode* node) {
    auto visitor = std::make_shared<ShowCreateVisitor>(ShowCreateVisitor());
    auto action = std::make_shared<ShowCreateNode>(*node);
    message = ShowCreateAction(visitor).execute(action);
}

void TreeVisitor::visit(InsertNode* node) {
    auto visitor = std::make_shared<InsertVisitor>(InsertVisitor());
    auto action = std::make_shared<InsertNode>(*node);
    message = InsertAction(visitor).execute(action);
}

void TreeVisitor::visit(SelectNode* node) {
    auto visitor = std::make_shared<SelectVisitor>(SelectVisitor());
    auto action = std::make_shared<SelectNode>(*node);
    message = SelectAction(visitor).execute(action);
}

Message countRecordsForUnioinIntersect(UnionIntersectNode* node, const std::shared_ptr<SelectVisitor>& visitor,
                                       std::map<std::string, int>& colExist,
                                       std::vector<std::vector<std::pair<std::pair<std::string, std::string>,
                                                                         std::string>>>& tempRecords,
                                       std::vector<std::pair<std::string, std::string>>& cols) {
    Message message;
    for (auto& action : node->getChildren()) {
        int countColumns = 0;
        SelectAction(visitor).execute(std::make_shared<SelectNode>(*action));
        auto tempCols = visitor->getColumns();
        for (auto& col : tempCols) {
            col.first.erase();
            if (colExist.find(col.second) != colExist.end()) {
                if (!colExist[col.second]) {
                    countColumns++;
                }
            } else if (colExist.empty()) {
                colExist.insert(colExist.end(), std::make_pair(col.second, 0));
                countColumns++;
            } else {
                return Message(ErrorConstants::ERR_NO_SUCH_FIELD);  // TODO сделать другую ошибку
            }
        }
        if (countColumns != colExist.size()) {
            return Message(ErrorConstants::ERR_NO_SUCH_FIELD);  // TODO сделать другую ошибку
        }

        auto records = visitor->getRecords();
        for (auto& rec : records) {
            std::vector<std::pair<std::pair<std::string, std::string>, std::string>> tempRec;
            for (int i = 0; i < rec.size(); i++) {
                auto col = rec[i];
                if (colExist.find(col.first.second) != colExist.end()) {
                    col.first.first.erase();
                    tempRec.emplace_back(col);
                }
            }
            tempRecords.emplace_back(tempRec);
        }
    }

    for (auto& col : colExist) {
        cols.emplace_back(std::make_pair("", col.first));
    }

    return Message();
}

void TreeVisitor::visit(UnionJoinNode* node) {
    auto visitor = std::make_shared<SelectVisitor>(SelectVisitor());
    std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::string>>> tempRecords;
    std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::string>>> allRecords;
    std::map<std::string, int> colExist;
    std::vector<std::pair<std::string, std::string>> cols;

    message = countRecordsForUnioinIntersect(node, visitor, colExist, tempRecords, cols);

    if (message.getErrorCode()) {
        return;
    }

    for (int i = 0; i < tempRecords.size(); i++) {
        for (int j = i + 1; j < tempRecords.size(); j++) {
            if (tempRecords[i] == tempRecords[j]) {
                tempRecords.erase(tempRecords.begin() + j);
                break;
            }
        }
    }

    message = Message(ActionsUtils::checkSelectColumns(tempRecords, cols));
}

void TreeVisitor::visit(IntersectJoinNode* node) {
    auto visitor = std::make_shared<SelectVisitor>(SelectVisitor());
    std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::string>>> tempRecords;
    std::vector<std::vector<std::pair<std::pair<std::string, std::string>, std::string>>> allRecords;
    std::map<std::string, int> colExist;
    std::vector<std::pair<std::string, std::string>> cols;

    message = countRecordsForUnioinIntersect(node, visitor, colExist, tempRecords, cols);

    if (message.getErrorCode()) {
        return;
    }

    for (int i = 0; i < tempRecords.size(); i++) {
        for (int j = i + 1; j < tempRecords.size(); j++) {
            if (tempRecords[i] == tempRecords[j]) {
                allRecords.emplace_back(tempRecords[i]);
            }
        }
    }

    message = Message(ActionsUtils::checkSelectColumns(allRecords, cols));
}

void TreeVisitor::visit(UpdateNode* node) {
    auto visitor = std::make_shared<UpdateVisitor>(UpdateVisitor());
    auto action = std::make_shared<UpdateNode>(*node);
    message = UpdateAction(visitor).execute(action);
}

void TreeVisitor::visit(DeleteNode* node) {
    auto visitor = std::make_shared<DeleteVisitor>(DeleteVisitor());
    auto action = std::make_shared<DeleteNode>(*node);
    message = DeleteAction(visitor).execute(action);
}

void TreeVisitor::visit(ConstraintNode* node) {}
void TreeVisitor::visit(VariableNode* node) {}
void TreeVisitor::visit(IntValueNode* node) {}
void TreeVisitor::visit(CharValueNode* node) {}
void TreeVisitor::visit(FloatValueNode* node) {}
void TreeVisitor::visit(NullValueNode* node) {}
void TreeVisitor::visit(ColumnNode* node) {}
void TreeVisitor::visit(ColumnsAndValuesNode* node) {}
void TreeVisitor::visit(ExprNode* node) {}
void TreeVisitor::visit(AndLogicNode* node) {}
void TreeVisitor::visit(OrLogicNode* node) {}
void TreeVisitor::visit(NotLogicNode* node) {}
void TreeVisitor::visit(AddNode* node) {}
void TreeVisitor::visit(DivNode* node) {}
void TreeVisitor::visit(SubNode* node) {}
void TreeVisitor::visit(MultNode* node) {}
void TreeVisitor::visit(EqualsNode* node) {}
void TreeVisitor::visit(NoEqualsNode* node) {}
void TreeVisitor::visit(MoreEqNode* node) {}
void TreeVisitor::visit(MoreNode* node) {}
void TreeVisitor::visit(LessEqNode* node) {}
void TreeVisitor::visit(LessNode* node) {}
void TreeVisitor::visit(IdentNode* node) {}
void TreeVisitor::visit(VariableListNode* node) {}
void TreeVisitor::visit(ColumnsAndExprNode* node) {}
void TreeVisitor::visit(UpdateExprNode* node) {}
void TreeVisitor::visit(UpdatesAndExprNode* node) {}
void TreeVisitor::visit(IndentExprNode* node) {}
void TreeVisitor::visit(ValueExprNode* node) {}
void TreeVisitor::visit(AssignUpdateNode* node) {}
void TreeVisitor::visit(SourceJoinNode* node) {}
void TreeVisitor::visit(JoinNode* node) {}
void TreeVisitor::visit(TableNode* node) {}
void TreeVisitor::visit(LeftJoinNode* node) {}
void TreeVisitor::visit(RightJoinNode* node) {}
void TreeVisitor::visit(FullJoinNode* node) {}
