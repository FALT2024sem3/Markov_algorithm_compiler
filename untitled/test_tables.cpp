#include "test_tables.h"


const void build_table1(QStandardItemModel *model) {
    QStandardItem *parent_item = model->invisibleRootItem();

    QStandardItem *expr = new QStandardItem("Expresion");
    QStandardItem *stt = new QStandardItem("Statement");
    parent_item->appendRow(expr);
    parent_item->appendRow(stt);

    QStandardItem *bin_expr = new QStandardItem("Binary Expresion");
    QStandardItem *block = new QStandardItem("Block");
    QStandardItem *if_else = new QStandardItem("If Else");
    stt->appendRow(bin_expr);
    stt->appendRow(block);
    stt->appendRow(if_else);

    QStandardItem *log_op = new QStandardItem("Logic Operator");
    expr->appendRow(log_op);

    QStandardItem *log_op2 = new QStandardItem("Logic Operator");
    log_op->appendRow(log_op2);
}

const void build_table2(QStandardItemModel *model) {
    QStandardItem *parent_item = model->invisibleRootItem();

    QStandardItem *DAFE = new QStandardItem("DAFE");
    parent_item->appendRow(DAFE);

    QStandardItem *bin_expr1 = new QStandardItem("'d'->'o';");
    QStandardItem *bin_expr2 = new QStandardItem("'c'->'t';");
    QStandardItem *if_expr = new QStandardItem("if ('a' and 's' or 'w')");
    QStandardItem *else_expr = new QStandardItem("else");
    QStandardItem *bin_expr3 = new QStandardItem("'who'->'?';");
    QStandardItem *bin_expr4 = new QStandardItem("''->'r';");
    DAFE->appendRow(bin_expr1);
    DAFE->appendRow(bin_expr2);
    DAFE->appendRow(if_expr);
    DAFE->appendRow(else_expr);
    DAFE->appendRow(bin_expr3);
    DAFE->appendRow(bin_expr4);

    QStandardItem *bin_expr5 = new QStandardItem("'o'->'p';");
    if_expr->appendRow(bin_expr5);

    QStandardItem *bin_expr6 = new QStandardItem("'Vostok' -> 'Gagarin';");
    else_expr->appendRow(bin_expr6);
}


void build_QSIM(QStandardItemModel *model, std::string AST)
{
    if (AST == "Placeholder TM: \n1"){
        build_table1(model);
    }
    else if (AST == "Placeholder TM: \n2"){
        build_table2(model);
    }
}

std::string build_AST(std::string code)
{
    return "Placeholder TM: \n" + code;
}

