
#ifndef SELSQL_TRANSACTMANAGER_H
#define SELSQL_TRANSACTMANAGER_H
#include "../../Utils/Headers/ErrorConstants.h"
#include "EngineUtils.h"

class TransactManager {
    std::map<std::string, std::map<Position, long>> in_use;
    std::vector<size_t> restricted;
    std::map<std::string, std::map<int, std::shared_ptr<DataBlock>>> in_use_block;

   public:
    std::map<std::string, std::vector<std::pair<int, long>>> ignore;
    TransactManager();
    long GetTransactionSP();
    void ClearUsed(long transaction_sp);
    int SetUsed(const std::string& table_name, Position position, long transaction_sp);
    int IsSuccessful(long transaction_sp);
    void RestrictTransaction(long transaction_sp);
    void SetNewPos(const std::string& table_name, int pos, long tr);
    void Clear(const std::string& table_name, long tr);
    std::shared_ptr<DataBlock> GetDataBlock(std::string table_name, int block_id);
    void SetDataBlock(std::string table_name, int block_id, std::shared_ptr<DataBlock> data_block);
};
#endif  // SELSQL_TRANSACTMANAGER_H
