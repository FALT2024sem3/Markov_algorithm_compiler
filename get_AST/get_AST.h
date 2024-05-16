#ifndef GET_AST_H
#define GET_AST_H

#include <QStandardItemModel>
#include <QApplication>
#include <QList>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include "AST.h"

void wstring_to_AST(std::wstring, QStandardItem *);
void cond_to_QSIM(std::shared_ptr<ParseTree::Expr>, QStandardItem *);
void get_AST(const std::vector<std::shared_ptr<ParseTree::Stat>> &, QStandardItem *);

#endif // GET_AST_H
