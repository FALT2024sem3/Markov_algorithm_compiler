#include "get_AST.h"

void wstring_to_AST(std::wstring wstr, QStandardItem *parent_item)
{
    QString qtString = QString::fromWCharArray(wstr.c_str());
    QStandardItem *item = new QStandardItem(qtString);
    parent_item->appendRow(item);
}

void cond_to_QSIM(std::shared_ptr<ParseTree::Expr> root, QStandardItem *parent_item)
{
    if (root->Type == ParseTree::NodeType::SinglExpr)
    {
        std::wstring expr = std::dynamic_pointer_cast<ParseTree::SinglExpr>(root)->GetExpr();
        wstring_to_AST(expr, parent_item);
    }
    else if (root->Type == ParseTree::NodeType::BinLogOp)
    {
        std::shared_ptr<ParseTree::BinLogOp> bin_logop = std::dynamic_pointer_cast<ParseTree::BinLogOp>(root);
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
        std::shared_ptr<ParseTree::SinglLogOp> singl_expr = std::dynamic_pointer_cast<ParseTree::SinglLogOp>(root);
        QStandardItem *singl_expr_item = new QStandardItem("Not");
        parent_item->appendRow(singl_expr_item);
        cond_to_QSIM(singl_expr->GetOp(), singl_expr_item);
    }
}

void get_AST(const std::vector<std::shared_ptr<ParseTree::Stat>> &st, QStandardItem *parent_item)
{ // обход нашего дерева
    for (size_t i = 0; i < st.size(); i++)
    {
        if (st[i]->Type == ParseTree::NodeType::BinExpr)
        { // вывод бинарных выражений
            std::shared_ptr<ParseTree::BinExpr> bin_expr = std::dynamic_pointer_cast<ParseTree::BinExpr>(st[i]);

            QStandardItem *bin_item = new QStandardItem("Bin Expr");
            parent_item->appendRow(bin_item);

            std::wstring left_value = bin_expr->GetLeftExpr();
            wstring_to_AST(left_value, bin_item);

            std::wstring right_value = bin_expr->GetRightExpr();
            wstring_to_AST(right_value, bin_item);
        }
        else if (st[i]->Type == ParseTree::NodeType::Block)
        { // вывод блока
            std::shared_ptr<ParseTree::Block> block = std::dynamic_pointer_cast<ParseTree::Block>(st[i]);

            QStandardItem *block_item = new QStandardItem("Block");
            parent_item->appendRow(block_item);
            get_AST(block->Getstats(), block_item);
        }
        else if (st[i]->Type == ParseTree::NodeType::IfElse)
        { // вывод конструкции ifelse
            std::shared_ptr<ParseTree::IfElse> ifelse = std::dynamic_pointer_cast<ParseTree::IfElse>(st[i]);
            QStandardItem *if_else_item = new QStandardItem("If Else");
            parent_item->appendRow(if_else_item);

            // вывод условия if
            std::shared_ptr<ParseTree::Expr> cond = ifelse->GetCond();
            QStandardItem *cond_item = new QStandardItem("Condition");
            if_else_item->appendRow(cond_item);
            cond_to_QSIM(cond, cond_item);

            // вывод внутренностей if
            std::shared_ptr<ParseTree::Block> if_block = ifelse->GetIfBlock();
            QStandardItem *if_block_expr = new QStandardItem("Do if");
            if_else_item->appendRow(if_block_expr);
            get_AST(if_block->Getstats(), if_block_expr);

            // вывод внустренностей else
            std::shared_ptr<ParseTree::Block> else_block = ifelse->GetElseBlock();
            if (!else_block->Getstats().empty())
            {
                QStandardItem *else_block_item = new QStandardItem("Do else");
                if_else_item->appendRow(else_block_item);
                get_AST(else_block->Getstats(), else_block_item);
            }
        }
        else if (st[i]->Type == ParseTree::NodeType::Link)
        {
            QStandardItem *link_item = new QStandardItem("Link");
            parent_item->appendRow(link_item);

            std::shared_ptr<ParseTree::Link> link = std::dynamic_pointer_cast<ParseTree::Link>(st[i]);
            std::wstring link_value = link->GetName();
            wstring_to_AST(link_value, link_item);
        }
        else if (st[i]->Type == ParseTree::NodeType::Goto)
        {
            QStandardItem *gt_item = new QStandardItem("Goto");
            parent_item->appendRow(gt_item);

            std::shared_ptr<ParseTree::Goto> gt = std::dynamic_pointer_cast<ParseTree::Goto>(st[i]);
            std::wstring gt_value = gt->GetLink();
            wstring_to_AST(gt_value, gt_item);
        }
    }
};
