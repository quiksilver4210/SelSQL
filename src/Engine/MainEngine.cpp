//
// Created by quiks on 01.10.2019.
//

#include "Headers/MainEngine.h"
int MainEngine::CreateTable(Table* table) {
    return file_manager_->CreateFile(table);
}  // returns 0 if table is created and 1 if table exists

Table* MainEngine::ShowCreateTable(std::string table_name) {
    if (file_manager_->OpenFile(table_name)) {
        return nullptr;
    }
    return file_manager_->GetTableData(table_name);
}  // returns Table* if ok or nullptr if table doesnt exist

int MainEngine::DropTable(std::string table_name) {
    return file_manager_->DeleteTable(table_name);
}  // returns 0 if table is dropped and non-zero if table doesnt exist

MainEngine::MainEngine() { file_manager_ = new FileManager(); }