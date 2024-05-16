#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./get_AST.h"
#include "./build_AST.h"
#include "AST.h"
#include "qdir.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings("./settings.ini", QSettings::IniFormat );

    m_codehighlighter = new codeHighLighter(ui->codeTextEdit->document());

    loadSettings();

    m_codehighlighter->loadFormats();
}


MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::loadSettings()
{
    QSettings settings("./settings.ini", QSettings::IniFormat );

    auto* rule = m_codehighlighter->get_rule(codeHighLighter::None);
    // Quote
    rule = m_codehighlighter->get_rule(codeHighLighter::Quote);
    settings.beginGroup("quotes_block");
    rule->style.reg_expr = settings.value("reg_expr", "\"").toString();
    rule->style.color = settings.value("color", "#008500").toString();
    rule->style.boldness = settings.value("boldness", QFont::Normal).toInt();
    rule->style.is_italic = settings.value("is_italic", false).toBool();
    settings.endGroup();
    // Change
    rule = m_codehighlighter->get_rule(codeHighLighter::Change);
    settings.beginGroup("change_block");
    rule->style.reg_expr = settings.value("reg_expr", "->").toString();
    rule->style.color = settings.value("color", "#0a0000").toString();
    rule->style.boldness = settings.value("boldness", QFont::DemiBold).toInt();
    rule->style.is_italic = settings.value("is_italic", false).toBool();
    settings.endGroup();
    // Pointer
    rule = m_codehighlighter->get_rule(codeHighLighter::Pointer);
    settings.beginGroup("pointer_block");
    rule->style.reg_expr = settings.value("reg_expr", "[a-zA-Z][a-zA-Z0-9_]+:").toString();
    rule->style.color = settings.value("color", "#e32636").toString();
    rule->style.boldness = settings.value("boldness", QFont::Normal).toInt();
    rule->style.is_italic = settings.value("is_italic", true).toBool();
    settings.endGroup();
    // If
    rule = m_codehighlighter->get_rule(codeHighLighter::If);
    settings.beginGroup("if_block");
    rule->style.reg_expr = settings.value("reg_expr", "if").toString();
    rule->style.color = settings.value("color", "#1164b4").toString();
    rule->style.boldness = settings.value("boldness", QFont::Normal).toInt();
    rule->style.is_italic = settings.value("is_italic", true).toBool();
    settings.endGroup();
    // Else
    rule = m_codehighlighter->get_rule(codeHighLighter::Else);
    settings.beginGroup("else_block");
    rule->style.reg_expr = settings.value("reg_expr", "else").toString();
    rule->style.color = settings.value("color", "#1164b4").toString();
    rule->style.boldness = settings.value("boldness", QFont::Normal).toInt();
    rule->style.is_italic = settings.value("is_italic", true).toBool();
    settings.endGroup();
    // GoTo
    rule = m_codehighlighter->get_rule(codeHighLighter::GoTo);
    settings.beginGroup("goto_block");
    rule->style.reg_expr = settings.value("reg_expr", "goto").toString();
    rule->style.color = settings.value("color", "#1164b4").toString();
    rule->style.boldness = settings.value("boldness", QFont::Normal).toInt();
    rule->style.is_italic = settings.value("is_italic", true).toBool();
    settings.endGroup();
    // DAFE
    rule = m_codehighlighter->get_rule(codeHighLighter::DAFE);
    settings.beginGroup("dafe_block");
    rule->style.reg_expr = settings.value("reg_expr", "DAFE").toString();
    rule->style.color = settings.value("color", "#0a0000").toString();
    rule->style.boldness = settings.value("boldness", QFont::Bold).toInt();
    rule->style.is_italic = settings.value("is_italic", false).toBool();
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings("./settings.ini", QSettings::IniFormat );

    auto *rule = m_codehighlighter->get_rule(codeHighLighter::None);
    // Quote
    rule = m_codehighlighter->get_rule(codeHighLighter::Quote);
    settings.beginGroup("quotes_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
    // Change
    rule = m_codehighlighter->get_rule(codeHighLighter::Change);
    settings.beginGroup("change_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
    // Pointer
    rule = m_codehighlighter->get_rule(codeHighLighter::Pointer);
    settings.beginGroup("pointer_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
    // If
    rule = m_codehighlighter->get_rule(codeHighLighter::If);
    settings.beginGroup("if_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
    // Else
    rule = m_codehighlighter->get_rule(codeHighLighter::Else);
    settings.beginGroup("else_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
    // GoTo
    rule = m_codehighlighter->get_rule(codeHighLighter::GoTo);
    settings.beginGroup("goto_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
    // DAFE
    rule = m_codehighlighter->get_rule(codeHighLighter::DAFE);
    settings.beginGroup("dafe_block");
    settings.setValue("reg_expr", rule->style.reg_expr);
    settings.setValue("color", rule->style.color);
    settings.setValue("boldness", rule->style.boldness);
    settings.setValue("is_italic", rule->style.is_italic);
    settings.endGroup();
}

void MainWindow::build_tree(QStandardItemModel *table_tree)
{
    ui->ASTtreeWidget->clear();

    QStandardItem *parent = table_tree->invisibleRootItem();
    tree_add_children(parent, ui->ASTtreeWidget->invisibleRootItem());
    ui->ASTtreeWidget->expandAll();
    ui->ASTtreeWidget->setStyleSheet( "QTreeView::branch {  border-image: url(none.png); }" );
}

void MainWindow::tree_add_children(QStandardItem *table_item, QTreeWidgetItem *tree_item)
{
    for (int i = 0; i < table_item->rowCount(); i++)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem;
        child->setText(0, table_item->child(i)->text());
		child->setForeground(0, table_item->child(i)->foreground());
        tree_add_children(table_item->child(i), child);
        tree_item->addChild(child);

    }

}

void MainWindow::on_buildTreeButton_clicked()
{
    try
    {
    createTempFile("./temp.temp");
    ParseTree::AST* ast = build_AST("./temp.temp");
    deleteTempFile("./temp.temp");

    QStandardItemModel *model = new QStandardItemModel();
    get_AST(ast->GetRoot()->Getstats(), model->invisibleRootItem());

    build_tree(model);
    }
    catch (MyException e)
    {
        ParseTree::AST* ast = new ParseTree::AST;
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "In line:" << e.GetLineNumber() << std::endl;
        ui->ASTtreeWidget->clear();

    }
}


void MainWindow::on_loadCodeButton_clicked()
{
    QFileDialog *wnd = new QFileDialog(this, tr("Open File"), "C://", "All files (*.*);; Text File (*.txt)");
    wnd->show();

    connect(wnd, SIGNAL(fileSelected(QString)), this, SLOT(loadCode(QString)));
}


void MainWindow::loadCode(const QString &filePath)
{
    QFile code_file(filePath);
    if (!code_file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "ERROR", "Unable to open file!");
    }

    QString code = QTextStream(&code_file).readAll();
    ui->codeTextEdit->setPlainText(code);
}

void MainWindow::createTempFile(const QString filePath)
{
    QFile temp_file(filePath);
    if (!temp_file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "ERROR", "Unable to create temp file!");
    }

    QTextStream temp_stream(&temp_file);
    temp_stream << ui->codeTextEdit->toPlainText();

}

void MainWindow::deleteTempFile(const QString filePath)
{
    QFile temp_file(filePath);
    temp_file.remove();
}
