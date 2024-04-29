#ifndef TEST_TABLES1
#define TEST_TABLES1
#include <QStandardItem>
#include <QStandardItemModel>
#include <QtGui>

const void build_table1(QStandardItemModel *model);

const void build_table2(QStandardItemModel *model);


void build_QSIM(QStandardItemModel *model, std::string AST);

std::string build_AST(std::string code);

#endif // TEST_TABLES1
