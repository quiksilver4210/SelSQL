//
// Created by sapiest on 24.10.2019.
//

#ifndef SELSQL_CREATEVISITOR_H
#define SELSQL_CREATEVISITOR_H
#include <utility>

#include "../Nodes/ActionNodes/CreateNode.h"
#include "../Nodes/ConstraintNode.h"
#include "../Nodes/VariableListNode.h"
#include "../Nodes/VariableNode.h"
#include "TreeVisitor.h"
class CreateVisitor : public TreeVisitor {
   public:
    void visit(VariableListNode* node) override {
        for (auto& var : node->getVariables()) {
            var->accept(this);
        }
    }

    void visit(ConstraintNode* node) override { table.addConstraint(node->getConstraint()); }

    void visit(VariableNode* node) override {
        if (values.find(node->getVarName()) != values.end()) {
            table.addField(node->getVarName(), node->getVarType());
            for (auto& child : node->getConstraints()) {
                child->accept(this);
            }
        } else {
            error = Message(ErrorConstants::ERR_SAME_COLUMN);
        }
    }

    Table getTable() { return table; }

    void setTableName(std::string _name) { table.name = std::move(_name); }

    Message getError() { return error; }

   private:
    Message error;
    std::map<std::string, int> values;
    Table table;
};

#endif  // SELSQL_CREATEVISITOR_H
