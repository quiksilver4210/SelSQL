//
// Created by sapiest on 05.10.2019.
//

#ifndef SELSQL_SELECTACTION_H
#define SELSQL_SELECTACTION_H

#include <sstream>
#include "BaseAction.h"
class SelectAction : public BaseAction {
   public:
    std::stringstream stringstream;

    explicit SelectAction(std::shared_ptr<TreeVisitor> _visitor) : BaseAction(std::move(_visitor)) {}

    Error execute(std::shared_ptr<BaseActionNode>) override;
    // BigResponse execute(std::shared_ptr<BigRequest>, MainEngine* mainEngine) override;

   private:
    void printAll(BigResponse& response);

    void printAllHeader(std::shared_ptr<Table> table);

    void printField(std::string field);

    std::pair<std::shared_ptr<Table>, std::shared_ptr<Cursor>> cursor;
    // std::vector<std::pair<std::string, std::string>> record;
};

#endif  // SELSQL_SELECTACTION_H
