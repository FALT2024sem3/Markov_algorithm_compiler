#include "codehighlighter.h"
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include <iostream>
#include <QFont>

codeHighLighter::codeHighLighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    change_block = QRegularExpression("->");
    changeFormat.setForeground(QBrush(QColor("#0a0000")));
    changeFormat.setFontWeight(QFont::DemiBold);

    pointer_block = QRegularExpression("[a-zA-Z][a-zA-Z0-9_]+:");
    pointerFormat.setForeground(QBrush(QColor("#e32636")));
    pointerFormat.setFontItalic(true);

    quotes_block = QRegularExpression("\"");
    quotationFormat.setForeground(QBrush(QColor("#008500")));

    if_block = QRegularExpression("if");
    else_block = QRegularExpression("else");
    ifelseFormat.setForeground(QBrush(QColor("#1164b4")));
    ifelseFormat.setFontItalic(true);

    goto_block = QRegularExpression("goto");
    gotoFormat.setForeground(QBrush(QColor("#1164b4")));
    gotoFormat.setFontItalic(true);

    dafe_block = QRegularExpression("DAFE");
    dafeFormat.setForeground(QBrush(QColor("#0a0000")));
    dafeFormat.setFontWeight(QFont::Bold);

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
        startIndex = text.indexOf(quotes_block);

    while (startIndex >= 0) {
        // Highlight text between quotes
        highlightKeywords(text, endIndex, startIndex);

        QRegularExpressionMatch endMatch;
        // Searching closing quote
        endIndex = text.indexOf(quotes_block, startIndex + 1, &endMatch);
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
        setFormat(startIndex, quotationLength, quotationFormat);
        startIndex = text.indexOf(quotes_block,
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
    // std::cout << startIndex << " " << endIndex << " " << text.sliced(startIndex, length).toStdString() << '\n';
    QRegularExpressionMatchIterator i;
//  ------------| DAFE |--------------
    i = dafe_block.globalMatch(text.sliced(startIndex, length));
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(startIndex + match.capturedStart(), match.capturedLength(), dafeFormat);
    }
//  ------------| IF |--------------
    i = if_block.globalMatch(text.sliced(startIndex, length));
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(startIndex + match.capturedStart(), match.capturedLength(), ifelseFormat);
    }
//  ------------| ELSE |--------------
    i = else_block.globalMatch(text.sliced(startIndex, length));
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(startIndex + match.capturedStart(), match.capturedLength(), ifelseFormat);
    }
//  ------------| GOTO |--------------
    i = goto_block.globalMatch(text.sliced(startIndex, length));
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(startIndex + match.capturedStart(), match.capturedLength(), gotoFormat);
    }
//  ------------| POINTER |--------------
    i = pointer_block.globalMatch(text.sliced(startIndex, length));
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(startIndex + match.capturedStart(), match.capturedLength(), pointerFormat);
    }
// ------------| CHANGE |--------------
    i = change_block.globalMatch(text.sliced(startIndex, length));
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        setFormat(startIndex + match.capturedStart(), match.capturedLength(), changeFormat);
    }
}
