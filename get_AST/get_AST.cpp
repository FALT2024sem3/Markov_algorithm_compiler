#include "get_AST.h"

// Функция для вывода "дерева" в консоль. На вход давать parent_item(тото который model.invisibleRootItem())
// Может понадобиться для тестов
// void printItems(const QStandardItem *parent, int level = 0)
// {

//     for (int i{}; i < parent->rowCount(); i++)
//     {
//         for (int j{}; j < level; j++)
//         {
//             std::cout << "  "; // для отделения дочерних узлов выводим пробелы
//         }
//         QStandardItem *item = parent->child(i, 0);
//         std::cout << item->data(Qt::DisplayRole).toString().toStdString() << std::endl;
//         printItems(item, level + 1);
//     }
// }

void wstring_to_AST(std::wstring wstr, QStandardItem *parent_item)
{
    QString qtString = QString::fromWCharArray(wstr.c_str());
    QStandardItem *item = new QStandardItem(qtString);
    parent_item->appendRow(item);
}

void cond_to_QSIM(ParseTree::Expr *root, QStandardItem *parent_item)
{
    if (root->Type == ParseTree::NodeType::SinglExpr)
    {
        std::wstring expr = dynamic_cast<ParseTree::SinglExpr *>(root)->GetExpr();
        wstring_to_AST(expr, parent_item);
    }
    else if (root->Type == ParseTree::NodeType::BinLogOp)
    {
        ParseTree::BinLogOp *bin_logop = dynamic_cast<ParseTree::BinLogOp *>(root);
        QStandardItem *bin_logop_item;
        if (bin_logop->GetTypeLogOp() == ParseTree::TypeOfLogicOp::AND)
            bin_logop_item = new QStandardItem("And");
        else if (bin_logop->GetTypeLogOp() == ParseTree::TypeOfLogicOp::OR)
            bin_logop_item = new QStandardItem("Or");
        parent_item->appendRow(bin_logop_item);
        cond_to_QSIM(bin_logop->GetLeftOp(), bin_logop_item);
        cond_to_QSIM(bin_logop->GetRighttOp(), bin_logop_item);
    }
    else if (root->Type == ParseTree::NodeType::SinglLogOp)
    {
        ParseTree::SinglLogOp *singl_expr = dynamic_cast<ParseTree::SinglLogOp *>(root);
        QStandardItem *singl_expr_item = new QStandardItem("Not");
        parent_item->appendRow(singl_expr_item);
        cond_to_QSIM(singl_expr->GetOp(), singl_expr_item);
    }
}

void get_AST(const std::vector<ParseTree::Stat *> &st, QStandardItem *parent_item)
{ // обход нашего дерева
    for (size_t i = 0; i < st.size(); i++)
    {
        if (st[i]->Type == ParseTree::NodeType::BinExpr)
        { // вывод бинарных выражений
            ParseTree::BinExpr *elem = dynamic_cast<ParseTree::BinExpr *>(st[i]);

            QStandardItem *bin_expr = new QStandardItem("Bin Expr");
            parent_item->appendRow(bin_expr);

            std::wstring left_value = elem->GetLeftExpr();
            wstring_to_AST(left_value, bin_expr);

            std::wstring right_value = elem->GetRightExpr();
            wstring_to_AST(right_value, bin_expr);
        }
        else if (st[i]->Type == ParseTree::NodeType::Block)
        { // вывод блока
            ParseTree::Block *block = dynamic_cast<ParseTree::Block *>(st[i]);

            QStandardItem *block_item = new QStandardItem("Block");
            parent_item->appendRow(block_item);
            get_AST(block->Getstats(), block_item);
        }
        else if (st[i]->Type == ParseTree::NodeType::IfElse)
        { // вывод конструкции ifelse
            ParseTree::IfElse *ifelse = dynamic_cast<ParseTree::IfElse *>(st[i]);
            QStandardItem *if_else_item = new QStandardItem("If Else");
            parent_item->appendRow(if_else_item);

            // вывод условия if
            ParseTree::Expr *cond_expr = ifelse->GetCond();
            QStandardItem *cond_item = new QStandardItem("Condition");
            if_else_item->appendRow(cond_item);
            cond_to_QSIM(cond_expr, cond_item);

            // вывод внутренностей if
            ParseTree::Block *if_block = ifelse->GetIfBlock();
            QStandardItem *if_block_expr = new QStandardItem("Do if");
            if_else_item->appendRow(if_block_expr);
            get_AST(if_block->Getstats(), if_block_expr);

            // вывод внустренностей else
            ParseTree::Block *else_block = ifelse->GetElseBlock();
            if (!else_block->Getstats().empty())
            {
                QStandardItem *else_block_expr = new QStandardItem("Do else");
                if_else_item->appendRow(else_block_expr);
                get_AST(else_block->Getstats(), else_block_expr);
            }
        }
        else if (st[i]->Type == ParseTree::NodeType::Link)
        {
            QStandardItem *link_item = new QStandardItem("Link");
            parent_item->appendRow(link_item);

            ParseTree::Link *link = dynamic_cast<ParseTree::Link *>(st[i]);
            std::wstring link_value = link->GetName();
            wstring_to_AST(link_value, link_item);
        }
        else if (st[i]->Type == ParseTree::NodeType::Goto)
        {
            QStandardItem *gt_item = new QStandardItem("Goto");
            parent_item->appendRow(gt_item);

            ParseTree::Goto *gt = dynamic_cast<ParseTree::Goto *>(st[i]);
            std::wstring gt_value = gt->GetLink();
            wstring_to_AST(gt_value, gt_item);
        }
    }
};
