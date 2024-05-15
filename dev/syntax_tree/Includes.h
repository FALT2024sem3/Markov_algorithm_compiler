#include "AST.h"
#include <memory>

namespace Includes
{
    // Псевдонимы для умных указателей
    using PtrExpr = std::shared_ptr<ParseTree::Expr>;
    using PtrBinExpr = std::shared_ptr<ParseTree::BinExpr>;
    using PtrStat = std::shared_ptr<ParseTree::Stat>;
    using PtrBlock = std::shared_ptr<ParseTree::Block>;
}