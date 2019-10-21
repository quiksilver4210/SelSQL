
#ifdef __WIN32
#include "../Client/Win/WinClient.h"
#elif __linux
#include "../Client/Linux/LinuxClient.h"
#endif
#include <gtest/gtest.h>
#include "../src/Logic/Headers/MainLogic.h"
#include "../src/Utils/Structures/Data/Table.h"
#include "../src/Utils/Structures/Data/Variable.h"
#include "Headers/TestUtils.h"
#include "parser.cpp"

//// TEST(CREATE_TEST, TEST2) {
////    std::string str = "CREATE TABLE name1(ID INT);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ("name1", res.ddlData.table.name);
////    auto field = *(res.ddlData.table.getFields().begin());
////    EXPECT_EQ("ID", field.first);
////    EXPECT_EQ(0, field.second.type);
////}
//// TEST(CREATE_TEST, TEST3) {
////    std::string str = "CREATE TABLE name2(col1 FLOAT NOT NULL);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ("name2", res.ddlData.table.name);
////    auto field = *(res.ddlData.table.getFields().begin());
////    EXPECT_EQ("col1", field.first);
////    EXPECT_EQ(1, field.second.type);
////    EXPECT_EQ(0, field.second.getConstraints()[0]);
////}
////// TEST(CREATE_TEST, TEST4) {
//////    std::string str = "CREATE TABLE name3(col1 BOOLEAN UNIQUE, col2 INT PRIMARY KEY);";
//////    res = parse_request(str.c_str());
//////    std::vector<std::pair<std::string, Variable>> fields = {{"col1",
//////                                                             Variable(BOOLEAN, std::vector<Constraint>{UNIQUE})},
//////                                                            {"col2",
//////                                                             Variable(INT,
/// std::vector<Constraint>{PRIMARY_KEY})}};
//////    Error err;
//////    BigResponse obj(CREATE, "name3", DDLdata(Table(string("name"), fields), ""), DMLdata(), DQLdata(), err);
//////    TestUtils::compareTables(obj, res);
//////}
////
//// TEST(CREATE_TEST, TEST5) {
////    std::string str = "CREATE TABLE name4(col1 INT UNIQUE NOT NULL, col2 CHAR, col3 FLOAT NOT NULL);";
////    res = parse_request(str.c_str());
////    std::vector<std::pair<std::string, Variable>> fields = {{"col1",
////                                                             Variable(TYPE_INT,
////                                                                      std::vector<Constraint>{UNIQUE, NOT_NULL})},
////                                                            {"col2", Variable(TYPE_CHAR,
/// std::vector<Constraint>{})}, /                                                            {"col3", /
/// Variable(TYPE_FLOAT, / std::vector<Constraint>{NOT_NULL})}}; /    Error err; /    BigResponse obj(CREATE, "name4",
/// DDLdata(Table("name4", fields), ""), DMLdata(), DQLdata(), err); /    TestUtils::compareTables(obj, res);
////}
////// TEST(CREATE_TEST, TEST6) {
//////    std::string str = "CREATE TABLE name5(col1 FLOAT UNIQUE PRIMARY KEY, col2 CHAR NOT NULL PRIMARY KEY UNIQUE,
/// col3
/////" /                      "BOOLEAN);"; /    res = parse_request(str.c_str()); / std::vector<std::pair<std::string,
///// Variable>> fields = {{"col1", /                                                             Variable(FLOAT, /
///// std::vector<Constraint>{UNIQUE, PRIMARY_KEY})}, / {"col2", Variable(CHAR, std::vector<Constraint>{NOT_NULL, /
///// PRIMARY_KEY, / UNIQUE})}, / {"col3", Variable(BOOLEAN, std::vector<Constraint>{})}}; /    Error err; / BigResponse
///// obj(CREATE, "name5", DDLdata(Table("name5", fields),
/////""), DMLdata(), DQLdata(), err); /    TestUtils::compareTables(obj, res);
//////}
////// TEST(CREATE_TEST, TEST7) {
//////    std::string str = "CREATE TABLE name6(col1 BOOLEAN , col2 CHAR , col3 INT);";
//////    res = parse_request(str.c_str());
//////    std::vector<std::pair<std::string, Variable>> fields = {{"col1", Variable(BOOLEAN,
/// std::vector<Constraint>{})},
//////                                                            {"col2", Variable(CHAR, std::vector<Constraint>{})},
//////                                                            {"col3", Variable(INT, std::vector<Constraint>{})}};
//////    Error err;
//////    BigResponse obj(CREATE, "name6", DDLdata(Table("name6", fields), ""), DMLdata(), DQLdata(), err);
//////    TestUtils::compareTables(obj, res);
//////}
//// TEST(CREATE_TEST, TEST8) {
////    std::string str = "CREATE TABLE name7(col1 CHAR UNIQUE, col2 INT NOT NULL, col3 CHAR PRIMARY KEY); ";
////    res = parse_request(str.c_str());
////    std::vector<std::pair<std::string, Variable>> fields = {{"col1",
////                                                             Variable(FLOAT,
////                                                                      std::vector<Constraint>{UNIQUE,
/// PRIMARY_KEY})}, /                                                            {"col2", Variable(CHAR,
/// std::vector<Constraint>{NOT_NULL, / PRIMARY_KEY, / UNIQUE})}, / {"col3", Variable(BOOLEAN,
/// std::vector<Constraint>{})}}; /    Error err; /    BigResponse obj(CREATE, "name5", DDLdata(Table("name5", fields),
///""), DMLdata(), DQLdata(), err); /    TestUtils::compareTables(obj, res);
////}
//// TEST(CREATE_TEST, TEST7) {
////    std::string str = "CREATE TABLE name6(col1 BOOLEAN , col2 CHAR , col3 INT);";
////    res = parse_request(str.c_str());
////    std::vector<std::pair<std::string, Variable>> fields = {{"col1", Variable(BOOLEAN, std::vector<Constraint>{})},
////                                                            {"col2", Variable(CHAR, std::vector<Constraint>{})},
////                                                            {"col3", Variable(INT, std::vector<Constraint>{})}};
////    Error err;
////    BigResponse obj(CREATE, "name6", DDLdata(Table("name6", fields), ""), DMLdata(), DQLdata(), err);
////    TestUtils::compareTables(obj, res);
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST1) {
////    std::string str = "";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected $end (Str num 1, sym num 0): ", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST2) {
////    std::string str = "c";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 1): c", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST3) {
////    std::string str = "CREAT TABLE name1(ID INT);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 5): CREAT", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST4) {
////    std::string str = "CREATE TABLE name1(1565 INT);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 21): 1565",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST5) {
////    std::string str = "CREATE TABLE name1(ID IN);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting TYPE (Str num 1, sym num 21): IN",
/// res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST6) {
////    std::string str = "CREATE TABLE name1(ID INT NOT NU);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting COMMA or BRACKET or CONSTRAINT (Str num 1, sym num 25):
////    NOT",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST7) {
////    std::string str = "CREATE TABLE name1( );";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected BRACKET, expecting STRING (Str num 1, sym num 18): )",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST8) {
////    std::string str = "inser into y values ('s');";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 5): inser", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST9) {
////    std::string str = "insert ino y values('s');";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 6): insert", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST10) {
////    std::string str = "insert into t vles('asas');";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting BRACKET or VALUES (Str num 1, sym num 16): vles",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST11) {
////    std::string str = "insert into t ('asas');";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 14): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST12) {
////    std::string str = "insert into t values(asas);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting SEMICOLON (Str num 1, sym num 23): asas",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST13) {
////    std::string str = "insert into values(asas);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected VALUES, expecting STRING (Str num 1, sym num 17): values",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST14) {
////    std::string str = "insert into kkkk values ('asas', 3.14)";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected $end, expecting SEMICOLON (Str num 1, sym num 34): ",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST15) {
////    std::string str = "insert into kkkk values ('asas', 3.14) whre a = 'd';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting SEMICOLON (Str num 1, sym num 38): whre",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST16) {
////    std::string str = "insert into kkkk values ('asas', 3.14) where 'a' = 'd';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 40): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST17) {
////    std::string str = "insert into kkkk values ('asas', 3.14) where a ? 'd';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected OTHER, expecting EQUALLY or SIGN (Str num 1, sym num 41): ?",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST18) {
////    std::string str = "delte from a;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 5): delte", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST19) {
////    std::string str = "delete fro a;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 6): delete", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST20) {
////    std::string str = "delete from 'asdas';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 12): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST21) {
////    std::string str = "delete from 1;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 12): 1",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST22) {
////    std::string str = "delete from t (where a = b);";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected BRACKET, expecting SEMICOLON (Str num 1, sym num 13): (",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST23) {
////    std::string str = "upate t set a = '5';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 5): upate", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST24) {
////    std::string str = "update 't' set a = '5';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 7): '",
/// res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST25) {
////    std::string str = "update t se a = '5';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting SET (Str num 1, sym num 9): se", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST26) {
////    std::string str = "update t set 'a' = 's';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 11): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST27) {
////    std::string str = "update t set 5 = 's';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 11): 5",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST28) {
////    std::string str = "update t set a 's';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting EQUALLY (Str num 1, sym num 12): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST29) {
////    std::string str = "update t set a = ;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected SEMICOLON, expecting NUMBER or STROKE or VALNULL or FLOATNUM (Str num 1, sym
///" /              "num 13): ;", /              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST30) {
////    std::string str = "update t set a = 5 whee a = b;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting SEMICOLON (Str num 1, sym num 17): whee",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST31) {
////    std::string str = "update t set a = 5 where a  b;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting EQUALLY or SIGN (Str num 1, sym num 20): b",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST32) {
////    std::string str = "selec * from t;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 5): selec", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST33) {
////    std::string str = "select ** from t;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected OTHER, expecting STRING or ALL (Str num 1, sym num 8): **",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST34) {
////    std::string str = "select 'sdf' from t;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING or ALL (Str num 1, sym num 7): '",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST35) {
////    std::string str = "select sdf fsdd from t;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting COMMA or FROM (Str num 1, sym num 13): fsdd",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST36) {
////    std::string str = "select sdf frm t;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting COMMA or FROM (Str num 1, sym num 12): frm",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST37) {
////    std::string str = "select * from 't';";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 12): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST38) {
////    std::string str = "select * from 5;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 12): 5",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST39) {
////    std::string str = "select * from ttt whre a = 5;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting SEMICOLON (Str num 1, sym num 18): whre",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST40) {
////    std::string str = "select * from ttt where 'a' = 5;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STROKE, expecting STRING (Str num 1, sym num 20): '",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST41) {
////    std::string str = "select * from ttt where a  5;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting EQUALLY or SIGN (Str num 1, sym num 21): 5",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST42) {
////    std::string str = "dro table ddd;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 3): dro", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST43) {
////    std::string str = "drop tale ddd;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting TABLE (Str num 1, sym num 8): tale",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST44) {
////    std::string str = "drop table 15;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 11): 15",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST45) {
////    std::string str = "drop table asd, asd;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected COMMA, expecting SEMICOLON (Str num 1, sym num 13): ,",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST46) {
////    std::string str = "sho create table h;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 3): sho", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST47) {
////    std::string str = "show crate table h;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING (Str num 1, sym num 4): show", res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST48) {
////    std::string str = "show create tale h;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected STRING, expecting TABLE (Str num 1, sym num 15): tale",
////              res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST49) {
////    std::string str = "show create table 5;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 17): 5",
////    res.error.getErrorMsg());
////}
////
//// TEST(SYNTAX_ERROR_TEST, TEST50) {
////    std::string str = "show create table aa, df;";
////    res = parse_request(str.c_str());
////    EXPECT_EQ(1, res.error.getErrorCode());
////    EXPECT_EQ("syntax error, unexpected COMMA, expecting SEMICOLON (Str num 1, sym num 19): ,",
////              res.error.getErrorMsg());
////}
////
//// TEST(ERROR_TEST, TEST1) {
////    str = "CREATE TABLE name1(ID INT);";
////    res = parse_request(str.c_str());
////    res = MainLogic::executeRequest(res);
////    str = "CREATE TABLE name1(ID INT);";
////    res = parse_request(str.c_str());
////    res = MainLogic::executeRequest(res);
////    EXPECT_EQ(ErrorConstants::ERR_TABLE_EXISTS, res.error.getErrorCode());
////    EXPECT_EQ(ErrorConstants::ERR_TABLE_EXISTS_str, res.error.getErrorMsg());
////    str = "DROP TABLE name1;";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////}
////
//// TEST(ERROR_TEST, TEST2) {
////    str = "CREATE TABLE a(id INT);";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////    str = "insert into a(id, id, id) values (1, 2, 3);";
////    res = parse_request(str.c_str());
////    res = MainLogic::executeRequest(res);
////    EXPECT_EQ(7, res.error.getErrorCode());
////    // EXPECT_EQ(ErrorConstants::ERR_SAME_COLUMN, res.error.getErrorMsg());
////    str = "DROP TABLE a;";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////}
////
//// TEST(SHOW_CREATE, TEST1) {
////    std::string str = "CREATE TABLE name2(ID INT);";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////    str = "SHOW CREATE TABLE name2;";
////    res = parse_request(str.c_str());
////    res = MainLogic::executeRequest(res);
////    EXPECT_EQ(0, res.error.getErrorCode());
////    EXPECT_EQ("CREATE TABLE name2(ID INT );", res.ddlData.returnMsg);
////    str = "DROP TABLE name2;";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////}
////
//// TEST(SHOW_CREATE, TEST111) {
////    std::string str = "CREATE TABLE name2(ID INT );";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////    auto show_str = "SHOW CREATE TABLE name2;";
////    res = parse_request(show_str);
////    res = MainLogic::executeRequest(res);
////    EXPECT_EQ(0, res.error.getErrorCode());
////    EXPECT_EQ(str, res.ddlData.returnMsg);
////    str = "DROP TABLE name2;";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////}
//
//// TEST(SHOW_CREATE, TEST2) {
////    str = "CREATE TABLE name3(ID INT PRIMARY KEY);";
////    res = parse_request(str.c_str());
////    MainLogic::executeRequest(res);
////    str = "SHOW CREATE TABLE name3;";
////    res = parse_request(str.c_str());
////    res = MainLogic::executeRequest(res);
////    EXPECT_EQ(0, res.error.getErrorCode());
////    str = "DROP TABLE name3;";
////    BigResponse result = parse_request(str.c_str());
////    result = MainLogic::executeRequest(result);
////    EXPECT_EQ(0, result.error.getErrorCode());
////    result = parse_request(res.ddlData.returnMsg.c_str());
////    result = MainLogic::executeRequest(result);
////    EXPECT_EQ(0, result.error.getErrorCode());
////    // EXPECT_EQ(res.ddlData.table.name, result.ddlData.table.name);
////}

TEST(SERVER_TEST_SELECT, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE t(id INT PRIMARY KEY);", "Success"},
                              {"INSERT INTO t values(0);", "Success"},
                              {"INSERT INTO t values(1);", "Success"},
                              {"SELECT * from t;", " | id | \\n | 0 | \\n | 1 | \\n"},
                              {"DROP table t;", "Success"}});
}

TEST(SERVER_TEST_SELECT, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE b(id INT PRIMARY KEY, age int NOT NULL);", "Success"},
                              {"INSERT INTO b values(0, 10);", "Success"},
                              {"INSERT INTO b values(1, 20);", "Success"},
                              {"SELECT * from b;", " | id | age | \\n | 0 | 10 | \\n | 1 | 20 | \\n"},
                              {"DROP table b;", "Success"}});
}

TEST(SERVER_TEST_UPDATE, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE c(id INT PRIMARY KEY, age int NOT NULL);", "Success"},
                              {"INSERT INTO c values(1, 20);", "Success"},
                              {"UPDATE c SET id = 8;", "Success"},
                              {"SELECT * from c;", " | id | age | \\n | 8 | 20 | \\n"},
                              {"DROP table с;", "Success"}});
}

TEST(SERVER_TEST_UPDATE, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE d(id INT PRIMARY KEY, age int NOT NULL);", "Success"},
                              {"INSERT INTO d values(10, 20);", "Success"},
                              {"UPDATE d SET id = 15, age = 9;", "Success"},
                              {"SELECT * from d;", " | id | age | \\n | 15 | 9 | \\n"},
                              {"DROP table d;", "Success"}});
}

TEST(SERVER_TEST_DELETE, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE e(id INT PRIMARY KEY, age int NOT NULL);", "Success"},
                              {"DELETE FROM e;", "Success"},
                              {"SELECT * from e;", "Success"},
                              {"DROP table e;", "Success"}});
}

TEST(SERVER_TEST_DELETE, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE f(id INT , age int NOT NULL);", "Success"},
                              {"INSERT INTO f values(10, 20);", "Success"},
                              {"INSERT INTO f values(1, 2);", "Success"},
                              {"DELETE FROM f;", "Success"},
                              {"SELECT * from f;", "Success"},
                              {"DROP table f;", "Success"}});
}

TEST(SERVER_TEST_ALL, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE f(id INT , age int NOT NULL);", "Success"},
                              {"INSERT INTO f values(10, 20);", "Success"},
                              {"INSERT INTO f values(1, 2);", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 10 | 20 | \\n | 1 | 2 | \\n"},
                              {"UPDATE f SET id = 5;", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 5 | 20 | \\n | 5 | 2 | \\n"},
                              {"DROP table f;", "Success"}});
}

TEST(SERVER_TEST_WHERE, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE f(id INT , age int NOT NULL);", "Success"},
                              {"INSERT INTO f values(10, 20);", "Success"},
                              {"INSERT INTO f values(1, 2);", "Success"},
                              {"SELECT * from f where id = 2;", " | id | age | \\n"},
                              {"SELECT * from f where id = 1;", " | id | age | \\n | 1 | 2 | \\n"},
                              {"UPDATE f SET id = 5 where id = 4;", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 10 | 20 | \\n | 1 | 2 | \\n"},
                              {"UPDATE f SET id = 5 where not id = 10;", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 5 | 20 | \\n | 1 | 2 | \\n"},
                              {"DELETE FROM f where id = 5;", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 1 | 2 | \\n"},
                              {"DROP table f;", "Success"}});
}

TEST(SERVER_TEST_WHERE, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE f(id INT , age int NOT NULL);", "Success"},
                              {"INSERT INTO f values(10, 20);", "Success"},
                              {"INSERT INTO f values(1, 2);", "Success"},
                              {"SELECT * from f where id = 4*(7-2) - 10;", " | id | age | \\n"},
                              {"SELECT * from f where id = 1 or id = 2;", " | id | age | \\n | 1 | 2 | \\n"},
                              {"UPDATE f SET id = 5 where id = 2 and id = 1;", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 10 | 20 | \\n | 1 | 2 | \\n"},
                              {"UPDATE f SET id = 5 where not id = 10;", "Success"},
                              {"SELECT * from f;", " | id | age | \\n | 10 | 20 | \\n | 5 | 2 | \\n"},
                              {"DROP table f;", "Success"}});
}

TEST(SERVER_TEST_SHOW_CREATE, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE g(id INT PRIMARY KEY, age int NOT NULL);", "Success"},
                              {"SHOW CREATE TABLE g;", "CREATE TABLE g(id INT PRIMARY KEY, age INT NOT NULL );"},
                              {"DROP table g;", "Success"}});
}

TEST(SERVER_TEST_SHOW_CREATE, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE h(id INT);", "Success"},
                              {"SHOW CREATE TABLE h;", "CREATE TABLE h(id INT );"},
                              {"DROP table h;", "Success"}});
}

TEST(SERVER_TEST_ERROR, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE i(id INT);", "Success"},
                              {"CREATE TABLE i(id INT);", "Table already exists ERROR: 1"},
                              {"DROP table i;", "Success"}});
}

TEST(SERVER_TEST_ERROR, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE j(id INT);", "Success"}, {"insert into j values('sdfsdf');", ""}});
}

TEST(SERVER_TEST_ERROR, TEST3) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE k(id INT UNIQUE);", "Success"},
                              {"insert into k values(1);", "Success"},
                              {"insert into k values(1);", "Value already exists, use UNIQUE value ERROR: 9"}});
}

TEST(SERVER_TEST_ERROR, TEST4) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE m(id INT UNIQUE, di FLOAT NOT NULL);", "Success"},
                              {"insert into m values(1, 2);", "Success"},
                              {"insert into m values(3, 4);", "Null values unavailable ERROR: 8"}});
}

TEST(SERVER_TEST_ERROR, TEST5) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE m(id INT UNIQUE, di FLOAT NOT NULL);", "Success"},
                              {"insert into m values(1, 2);", "Success"},
                              {"insert into m values(3, 4);", "Success"},
                              {"update m set di = null, id = 3;", "Null values unavailable ERROR: 8"}});
}

TEST(SERVER_TEST_ERROR, TEST6) {
    TestUtils::clear();
    TestUtils::checkRequests({{"insert into qqq values(1, 2);", "Table doesn`t exist ERROR: 2"}});
}

TEST(SERVER_TEST_ERROR, TEST7) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE as(id INT UNIQUE, di FLOAT NOT NULL);", "Success"},
                              {"insert into as(id) values(1, 2);", "Invalid count of columns and values ERROR: 5"}});
}

TEST(SERVER_TEST_ERROR, TEST8) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE as(id INT UNIQUE, id FLOAT NOT NULL);", "Field name already used"}});
}

TEST(SERVER_TEST_ERROR, TEST9) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE asa(id INT UNIQUE UNIQUE, id1 FLOAT NOT NULL);",
                               "Constraint already exists"}});
}

TEST(SERVER_TEST_ERROR, TEST10) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE asas(id INT UNIQUE, id1 FLOAT NOT NULL);", "Success"},
                              {"insert into asas(id) values(1);", "Null values unavailable ERROR: 8"}});
}

TEST(SERVER_TEST_ERROR, TEST11) {
    TestUtils::clear();
    TestUtils::checkRequests({{"CREATE TABLE asas(id INT UNIQUE, id1 FLOAT);", "Success"},
                              {"insert into asas(isasfdasf, id) values(1, 2);", "Field doesnt exist ERROR: 6"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST0) {
    TestUtils::clear();
    TestUtils::checkRequests({{"", "syntax error, unexpected $end (Str num 1, sym num 0): "}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST1) {
    TestUtils::clear();
    TestUtils::checkRequests({{"creat table t (id int);",
                               "syntax error, unexpected STRING (Str num 1, sym num 5): creat"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST2) {
    TestUtils::clear();
    TestUtils::checkRequests({{"create tale t (id int);",
                               "syntax error, unexpected STRING (Str num 1, sym num 6): create"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST3) {
    TestUtils::clear();
    TestUtils::checkRequests({{"create table 555 (id int);",
                               "syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 15): 555"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST4) {
    TestUtils::clear();
    TestUtils::checkRequests({{"create table t (id innt);",
                               "syntax error, unexpected STRING, expecting TYPE (Str num 1, sym num 20): innt"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST5) {
    TestUtils::clear();
    TestUtils::checkRequests({{"dro table t;", "syntax error, unexpected STRING (Str num 1, sym num 3): dro"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST6) {
    TestUtils::clear();
    TestUtils::checkRequests({{"drop table t, y;",
                               "syntax error, unexpected COMMA, expecting SEMICOLON (Str num 1, sym num 12): ,"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST7) {
    TestUtils::clear();
    TestUtils::checkRequests({{"drop table t",
                               "syntax error, unexpected $end, expecting SEMICOLON (Str num 1, sym num 11): "}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST8) {
    TestUtils::clear();
    TestUtils::checkRequests({{"shw create table t;", "syntax error, unexpected STRING (Str num 1, sym num 3): shw"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST9) {
    TestUtils::clear();
    TestUtils::checkRequests({{"show crate table t;", "syntax error, unexpected STRING (Str num 1, sym num 4): show"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST10) {
    TestUtils::clear();
    TestUtils::checkRequests({{"insert into 'tt' values(1);", ""}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST11) {
    TestUtils::clear();
    TestUtils::checkRequests({{"inser into t values(1);",
                               "syntax error, unexpected STRING (Str num 1, sym num 5): inser"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST12) {
    TestUtils::clear();
    TestUtils::checkRequests({{"insert ito t values(1);",
                               "syntax error, unexpected STRING (Str num 1, sym num 6): insert"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST13) {
    TestUtils::clear();
    TestUtils::checkRequests({{"insert into t(1);",
                               "syntax error, unexpected NUMBER, expecting STRING (Str num 1, sym num 14): 1"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST14) {
    TestUtils::clear();
    TestUtils::checkRequests({{"insert into t(col) valus;",
                               "syntax error, unexpected STRING, expecting SEMICOLON (Str num 1, sym num 22): valus"}});
}

TEST(SERVER_TEST_SYN_ERROR, TEST15) {
    TestUtils::clear();
    TestUtils::checkRequests({{"insert into t(col) (5);",
                               "syntax error, unexpected NUMBER, expecting SEMICOLON (Str num 1, sym num 19): 5"}});
}