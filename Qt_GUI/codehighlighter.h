#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextCharFormat;
QT_END_NAMESPACE

class codeHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit codeHighLighter(QTextDocument * parent = 0);
protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
private:
    enum States {
        None,       // No highlighting
        Pointer,    // Pointer name highlightting
        Quote,      // Text inside "" and " itself
        IfElse,     // If and Else commands
        GoTo,       // Goto command
        DAFE        // DAFE in the bigining
    };

    struct HighLightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QRegularExpression pointer_block;   // Ending sybol for links - ":"
    QTextCharFormat pointerFormat;      // Format for links

    QRegularExpression quotes_block;    // RegExpr for text inside ""
    QTextCharFormat quotationFormat;    // Format text inside ""

    QRegularExpression if_block;         // RegExpr for ifs
    QRegularExpression else_block;      // RegExpt for elses
    QTextCharFormat ifelseFormat;       // Format for ifs and elses

    QRegularExpression goto_block;      // RegExpr for goto
    QTextCharFormat gotoFormat;         // Format for goto

    QRegularExpression dafe_block;      // DAFE in the begining of file
    QTextCharFormat dafeFormat;         // Format DAFE

    void highlightKeywords(const QString &text);
    void highlightKeywords(const QString &text, int startIndex, int endIndex);

};

#endif // CODEHIGHLIGHTER_H
