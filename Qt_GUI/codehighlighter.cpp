#include "codehighlighter.h"
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include <iostream>
#include <QFont>

codeHighLighter::codeHighLighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    /********/
}

void codeHighLighter::loadFormatsOld()
{
    quote_rule.pattern = QRegularExpression("\"");
    quote_rule.format.setForeground(QBrush(QColor("#008500")));
    quote_rule.format.setFontWeight(QFont::Normal);
    quote_rule.format.setFontItalic(false);


    change_rule.pattern = QRegularExpression("->");
    change_rule.format.setForeground(QBrush(QColor("#0a0000")));
    change_rule.format.setFontWeight(QFont::DemiBold);
    change_rule.format.setFontItalic(false);

    pointer_rule.pattern = QRegularExpression("[a-zA-Z][a-zA-Z0-9_]+:");
    pointer_rule.format.setForeground(QBrush(QColor("#e32636")));
    pointer_rule.format.setFontWeight(QFont::Normal);
    pointer_rule.format.setFontItalic(true);

    if_rule.pattern = QRegularExpression("if");
    if_rule.format.setForeground(QBrush(QColor("#1164b4")));
    if_rule.format.setFontWeight(QFont::Normal);
    if_rule.format.setFontItalic(true);

    else_rule.pattern = QRegularExpression("else");
    else_rule.format.setForeground(QBrush(QColor("#1164b4")));
    else_rule.format.setFontWeight(QFont::Normal);
    else_rule.format.setFontItalic(true);

    goto_rule.pattern = QRegularExpression("goto");
    goto_rule.format.setForeground(QBrush(QColor("#1164b4")));
    goto_rule.format.setFontWeight(QFont::Normal);
    goto_rule.format.setFontItalic(true);

    dafe_rule.pattern = QRegularExpression("DAFE");
    dafe_rule.format.setForeground(QBrush(QColor("#0a0000")));
    dafe_rule.format.setFontWeight(QFont::Bold);
    dafe_rule.format.setFontItalic(false);
}

void codeHighLighter::loadFormats()
{
    for (HighLightingRule *i_rule : all_rules)
    {
        i_rule->pattern = QRegularExpression(i_rule->style.reg_expr);
        i_rule->format.setForeground(QBrush(QColor(i_rule->style.color)));
        i_rule->format.setFontWeight(i_rule->style.boldness);
        i_rule->format.setFontItalic(i_rule->style.is_italic);
    }
}


void codeHighLighter::highlightBlock(const QString &text)
{
    setCurrentBlockState(None);

//  ------------| QUOTES |--------------
    int endIndex = 0;
    int startIndex = 0;

    // If there's no unclosed quotes in previous line
    if (previousBlockState() != Quote)
        // We're try to find quote in this line
        startIndex = text.indexOf(quote_rule.pattern);

    while (startIndex >= 0) {
        // Highlight text between quotes
        highlightKeywords(text, endIndex, startIndex);

        QRegularExpressionMatch endMatch;
        // Searching closing quote
        endIndex = text.indexOf(quote_rule.pattern, startIndex + 1, &endMatch);
        int quotationLength;
        // If there's no closing quote
        if (endIndex == -1) {
            // Then we put the rest of the text in quotation
            setCurrentBlockState(Quote);
            quotationLength = text.length() - startIndex;
        } else {
            quotationLength = endIndex - startIndex
                            + endMatch.capturedLength();
        }
        setFormat(startIndex, quotationLength, quote_rule.format);
        startIndex = text.indexOf(quote_rule.pattern,
                                  startIndex + quotationLength);
    }

    // If there's still text to highlight
    if (endIndex != -1)
    {
        highlightKeywords(text, endIndex, text.length());
    }
}

void codeHighLighter::highlightKeywords(const QString &text)
{
    highlightKeywords(text, 0, text.length());
}


void codeHighLighter::highlightKeywords(const QString &text, int startIndex, int endIndex)
{
    int length = endIndex - startIndex;
    //std::cout << startIndex << " " << endIndex << " " << text.sliced(startIndex, length).toStdString() << '\n';
    QRegularExpressionMatchIterator i;

    for (HighLightingRule *i_rule : basic_rules)
    {
        QRegularExpressionMatchIterator i = i_rule->pattern.globalMatch(text.sliced(startIndex, length));
        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            setFormat(startIndex + match.capturedStart(), match.capturedLength(), i_rule->format);
        }
    }

}

codeHighLighter::HighLightingRule* codeHighLighter::get_rule(States state)
{
    for (HighLightingRule *i_rule : all_rules)
    {
        if (i_rule->state == state) {
            return i_rule;
        }
    }
    return &none_rule;
}
