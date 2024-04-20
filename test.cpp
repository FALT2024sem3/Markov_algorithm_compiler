#include "AST.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QList>
#include <iostream>

// Функция для вывода "дерева" в консоль. На вход давать parent_item(тото который model.invisibleRootItem())
// void printItems(const QStandardItem* parent, int level = 0)
// {

//     for(int i{};i<parent->rowCount(); i++)
//     {
//         for(int j{}; j < level; j++)
//         {
//             std::cout << "  ";  // для отделения дочерних узлов выводим пробелы
//         }
//         QStandardItem* item = parent->child(i, 0);
//         std::cout << item->data(Qt::DisplayRole).toString().toStdString() << std::endl;
//         printItems(item, level+1);
//     }
// }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStandardItemModel model;
    QStandardItem *parent_item = model.invisibleRootItem();

    QStandardItem *expr = new QStandardItem("Expresion");
    QStandardItem *stat = new QStandardItem("Statement");
    parent_item->appendRow(expr);
    parent_item->appendRow(stat);

    QStandardItem *bin_expr = new QStandardItem("Binary Expresion");
    QStandardItem *block = new QStandardItem("Block");
    QStandardItem *if_else = new QStandardItem("If Else");
    stat->appendRow(bin_expr);
    stat->appendRow(block);
    stat->appendRow(if_else);

    QStandardItem *log_op = new QStandardItem("Logic Operator");
    expr->appendRow(log_op);

    return a.exec();
}
