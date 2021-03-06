//
// Created by quiks on 01.10.2019.
//

#include "Headers/MainEngine.h"
#include <mutex>
std::mutex mutex3;
Message MainEngine::CreateTable(const std::shared_ptr<Table>& table) {
    Message result;
    int error = file_manager_->CreateFile(table);
    if (error) {
        result = Message(ErrorConstants::ERR_TABLE_EXISTS);
    }
    data_manager_->ClearCached(table->name);
    return result;
}

std::shared_ptr<Table> MainEngine::ShowCreateTable(const std::string& tableName) {
    std::shared_ptr<Table> table(new Table());

    auto [meta, data] = file_manager_->OpenFile(tableName);
    if (meta == nullptr or data == nullptr) {
        return table;
    }
    file_manager_->ReadTableMetaData(tableName, meta);
    table = file_manager_->GetTable(tableName);
    return table;
}

Message MainEngine::DropTable(const std::string& tableName) {
    Message result;
    int error = file_manager_->DeleteFile(tableName);
    if (error) {
        result = Message(ErrorConstants::ERR_TABLE_NOT_EXISTS);
    }
    return result;
}

MainEngine::MainEngine() {
    transact_manager_ = std::make_shared<TransactManager>();
    file_manager_ = std::make_shared<FileManager>(transact_manager_);
    data_manager_ = std::make_shared<DataManager>(file_manager_);
}

std::pair<std::shared_ptr<Table>, std::shared_ptr<Cursor>> MainEngine::GetCursor(const std::string& tableName,
                                                                                 int64_t transaction_id) {
    std::lock_guard<std::mutex> guard(mutex3);
    std::shared_ptr<Table> table(new Table());
    std::shared_ptr<Cursor> cursor(new Cursor());
    auto [meta, data] = file_manager_->OpenFile(tableName);

    if (meta == nullptr or data == nullptr) {
        table = std::make_shared<Table>();
        return std::make_pair(table, cursor);
    }
    file_manager_->ReadTableMetaData(tableName, meta);
    table = file_manager_->GetTable(tableName);

    cursor = std::make_shared<Cursor>(table, data_manager_, transact_manager_, data, transaction_id);
    return std::make_pair(table, cursor);
}
int64_t MainEngine::GetTransactionSP() { return transact_manager_->GetTransactionSP(); }

void MainEngine::Commit(int64_t transaction_sp) {
    std::lock_guard<std::mutex> guard(mutex3);
    if (transact_manager_->IsSuccessful(transaction_sp)) {
        //        std::cerr << "COMMIT id = " << transaction_sp << std::endl;
        if (transact_manager_->block_usage_by_trans.find(transaction_sp) !=
            transact_manager_->block_usage_by_trans.end()) {
            auto vec = transact_manager_->block_usage_by_trans[transaction_sp];
            auto last = std::unique(vec.begin(), vec.end());
            vec.erase(last, vec.end());
            for (auto bl : vec) {
                data_manager_->CommitDataBlock(bl.first, bl.second,
                                               transact_manager_->GetPositionsNeedCommit(bl.first, bl.second,
                                                                                         transaction_sp),
                                               transaction_sp, file_manager_->GetTable(bl.first)->record_size);
                data_manager_->FreeDataBlock(bl.first, bl.second);
            }
        }
    }

    transact_manager_->ClearUsed(transaction_sp);
    transact_manager_->EndTransaction(transaction_sp);

    std::cerr << "IO = " << file_manager_->i_o_count << std::endl;
    std::cerr << "IO NO OPTIMIZE = " << data_manager_->i_o_count << std::endl;
}
void MainEngine::UpdateTableMeta(const std::shared_ptr<Table>& table) {
    auto [meta, data] = file_manager_->OpenFile(table->name);
    file_manager_->WriteTableMetaData(meta, table);
}
