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

// void logop_handle(const std::vector<ParseTree::Expr*> &expr, QStandardItem *parent_item, std::wstring flag, std::wstring word)
// {
//     std::vector<std::wstring> words;
//     for (size_t i = 0; i < expr.size(); i++) {
//         ParseTree::SinglExpr *curr = dynamic_cast<ParseTree::SinglExpr *>(expr[i]);
//         words.push_back(curr->GetExpr());
//     }
//     auto is_exist = std::find(words.begin(), words.end(), word);
//     if (is_exist != words.end()) {
//         std::vector<ParseTree::Expr*> ord1(expr.begin(), is_exist);
//         std::vector<ParseTree::Expr*> ord2(is_exist + 1, expr.end());
//         if (flag != word) {
//             QString qtString_word = QString::fromWCharArray( word.c_str() );
//             QStandardItem *is_item = new QStandardItem(qtString_word);
//             parent_item->appendRow(is_item);
//             flag = word;
//         }
//         pin_cond_to_QSIM(ord1, parent_item, flag);
//         pin_cond_to_QSIM(ord2, parent_item, flag);
//     }
// }

// void pin_cond_to_QSIM(const std::vector<ParseTree::Expr*> &expr, QStandardItem *parent_item, std::wstring flag) {
//     logop_handle(expr, parent_item, flag, "or");
//     logop_handle(expr, parent_item, flag, "and");
//     logop_handle(expr, parent_item, flag, "not");

//     for (size_t i = 0; i < expr.size(); i++) {
//         ParseTree::SinglExpr *elem = dynamic_cast<ParseTree::SinglExpr *>(expr[i]);
//         std::wstring value = elem->GetExpr();
//         QString qtString_value = QString::fromWCharArray( value.c_str() );
//         QStandardItem *value_item = new QStandardItem(qtString_value);
//         parent_item->appendRow(value_item);
//     }
// };

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
            QString qtString_left_value = QString::fromWCharArray( left_value.c_str() );
            std::wstring right_value = elem->GetRightExpr();
            QString qtString_right_value = QString::fromWCharArray( right_value.c_str() );
            QStandardItem *left = new QStandardItem(qtString_left_value);
            QStandardItem *right = new QStandardItem(qtString_right_value);
            bin_expr->appendRow(left);
            bin_expr->appendRow(right);
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

            // Пока что не рабочий прототип
            // вывод условия if
            // std::vector<ParseTree::Expr *> conds = ifelse->GetCond();
            // QStandardItem *cond = new QStandardItem("Condition");
            // if_else_item->appendRow(cond);
            // pin_cond_to_QSIM(conds, cond, "");

            // вывод внутренностей if
            ParseTree::Block *if_block = ifelse->GetIfBlock();
            QStandardItem *if_block_expr = new QStandardItem("Do if");
            if_else_item->appendRow(if_block_expr);
            get_AST(if_block->Getstats(), if_block_expr);

            // вывод внустренностей else
            ParseTree::Block *else_block = ifelse->GetElseBlock();
            QStandardItem *else_block_expr = new QStandardItem("Do else");
            if_else_item->appendRow(else_block_expr);
            get_AST(else_block->Getstats(), else_block_expr);
        }
    }
};
