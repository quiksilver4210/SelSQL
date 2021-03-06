//
// Created by sapiest on 20.10.2019.
//

#ifndef SELSQL_VISITOR_H
#define SELSQL_VISITOR_H

class RootNode;
class CreateNode;
class DropNode;
class ShowCreateNode;
class ConstraintNode;
class VariableNode;
class IntValueNode;
class CharValueNode;
class FloatValueNode;
class NullValueNode;
class ColumnNode;
class SelectNode;
class InsertNode;
class UpdateNode;
class DeleteNode;
class ColumnsAndValuesNode;
class AndLogicNode;
class OrLogicNode;
class NotLogicNode;
class ExprNode;
class AddNode;
class DivNode;
class MultNode;
class SubNode;
class EqualsNode;
class NoEqualsNode;
class MoreNode;
class MoreEqNode;
class LessNode;
class LessEqNode;
class IdentNode;
class VariableListNode;
class ColumnsAndExprNode;
class UpdateExprNode;
class UpdatesAndExprNode;
class IndentExprNode;
class ValueExprNode;
class AssignUpdateNode;
class JoinNode;
class SourceJoinNode;
class TableNode;
class LeftJoinNode;
class RightJoinNode;
class FullJoinNode;
class UnionJoinNode;
class IntersectJoinNode;
class UnionIntersectListNode;
class SystemTimeNode;
class SystemTimeAllNode;
class IndexNode;

class Visitor {
   public:
    virtual void visit(RootNode* node) = 0;

    virtual void visit(CreateNode* node) = 0;
    virtual void visit(DropNode* node) = 0;
    virtual void visit(ShowCreateNode* node) = 0;
    virtual void visit(InsertNode* node) = 0;
    virtual void visit(SelectNode* node) = 0;
    virtual void visit(UpdateNode* node) = 0;
    virtual void visit(DeleteNode* node) = 0;
    virtual void visit(IndexNode* node) = 0;

    virtual void visit(TableNode* node) = 0;

    virtual void visit(ConstraintNode* node) = 0;
    virtual void visit(VariableNode* node) = 0;
    virtual void visit(IdentNode* node) = 0;

    virtual void visit(ColumnsAndValuesNode* node) = 0;

    virtual void visit(IntValueNode* node) = 0;
    virtual void visit(CharValueNode* node) = 0;
    virtual void visit(FloatValueNode* node) = 0;
    virtual void visit(NullValueNode* node) = 0;

    virtual void visit(ColumnNode* node) = 0;

    virtual void visit(ExprNode* node) = 0;

    virtual void visit(AndLogicNode* node) = 0;
    virtual void visit(OrLogicNode* node) = 0;
    virtual void visit(NotLogicNode* node) = 0;

    virtual void visit(AddNode* node) = 0;
    virtual void visit(DivNode* node) = 0;
    virtual void visit(SubNode* node) = 0;
    virtual void visit(MultNode* node) = 0;

    virtual void visit(EqualsNode* node) = 0;
    virtual void visit(NoEqualsNode* node) = 0;
    virtual void visit(MoreEqNode* node) = 0;
    virtual void visit(MoreNode* node) = 0;
    virtual void visit(LessEqNode* node) = 0;
    virtual void visit(LessNode* node) = 0;

    virtual void visit(VariableListNode* node) = 0;
    virtual void visit(ColumnsAndExprNode* node) = 0;

    virtual void visit(UpdateExprNode* node) = 0;
    virtual void visit(UpdatesAndExprNode* node) = 0;
    virtual void visit(IndentExprNode* node) = 0;
    virtual void visit(ValueExprNode* node) = 0;

    virtual void visit(AssignUpdateNode* node) = 0;

    virtual void visit(SourceJoinNode* node) = 0;
    virtual void visit(JoinNode* node) = 0;
    virtual void visit(LeftJoinNode* node) = 0;
    virtual void visit(RightJoinNode* node) = 0;
    virtual void visit(FullJoinNode* node) = 0;

    virtual void visit(UnionJoinNode* node) = 0;
    virtual void visit(IntersectJoinNode* node) = 0;
    virtual void visit(UnionIntersectListNode* node) = 0;

    virtual void visit(SystemTimeNode* node) = 0;
    virtual void visit(SystemTimeAllNode* node) = 0;
};
#endif  // SELSQL_VISITOR_H
