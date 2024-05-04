#ifndef GET_AST_H
#define GET_AST_H

#include <QStandardItemModel>
#include <QApplication>
#include <QList>
#include <algorithm>
#include <iostream>
#include <vector>
#include "AST.h"


void printItems(const QStandardItem *, int);
void logop_handle(const std::vector<ParseTree::Expr*> &, QStandardItem *, std::wstring, std::wstring);
void pin_cond_to_QSIM(const std::vector<ParseTree::Expr*> &, QStandardItem *, std::wstring);
void get_AST(const std::vector<ParseTree::Stat *> &, QStandardItem *);


#endif // GET_AST_H
