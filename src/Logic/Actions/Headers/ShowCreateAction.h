//
// Created by sapiest on 05.10.2019.
//

#ifndef SELSQL_SHOWCREATEACTION_H
#define SELSQL_SHOWCREATEACTION_H

#include "BaseAction.h"
class ShowCreateAction : public BaseAction {
   public:
    BigResponse execute(BigRequest& _request, MainEngine* mainEngine) override;
};

#endif  // SELSQL_SHOWCREATEACTION_H