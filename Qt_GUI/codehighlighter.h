#ifndef CODEHIGHLIGHTER_H
#define CODEHIGHLIGHTER_H

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include <iostream>
#include <QFont>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextCharFormat;
QT_END_NAMESPACE


class codeHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit codeHighLighter(QTextDocument * parent = 0);

    enum States {
        None,       // No highlighting
        Quote,      // Pointer name highlightting
        Change,     // Arrow between lines
        Pointer,    // Text inside "" and " itself
        If,
        Else,       // If and Else commands
        GoTo,       // Goto command
        DAFE        // DAFE in the bigining
    };

    void loadFormatsOld();

    void loadFormats();

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
private:

    struct HighLightingRule
    {
        struct HighLightingStyle
        {
            QString reg_expr;
            QString color;
            int boldness;
            bool is_italic;
        };

        States state;
        QRegularExpression pattern;
        QTextCharFormat format;
        HighLightingStyle style;
    };

    HighLightingRule none_rule = {None};

    HighLightingRule quote_rule = {Quote};

    HighLightingRule change_rule = {Change};
    HighLightingRule pointer_rule = {Pointer};
    HighLightingRule if_rule = {If};
    HighLightingRule else_rule = {Else};
    HighLightingRule goto_rule = {GoTo};
    HighLightingRule dafe_rule = {DAFE};

    QVector<HighLightingRule*> all_rules =
        {&none_rule, &quote_rule, &change_rule, &pointer_rule,
        &if_rule, &else_rule, &goto_rule, &dafe_rule};
    QVector<HighLightingRule*> basic_rules =
        {&change_rule, &pointer_rule, &if_rule,
        &else_rule, &goto_rule, &dafe_rule};

    void highlightKeywords(const QString &text);
    void highlightKeywords(const QString &text, int startIndex, int endIndex);
public:
    HighLightingRule* get_rule(States state);
};

#endif // CODEHIGHLIGHTER_H
