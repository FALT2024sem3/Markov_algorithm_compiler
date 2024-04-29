#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "test_tables.h"
#include "file.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build_tree(QStandardItemModel *table_tree)
{
    ui->ASTtreeWidget->clear();

    QStandardItem *parent = table_tree->invisibleRootItem();
    tree_add_children(parent, ui->ASTtreeWidget->invisibleRootItem());

    ui->ASTtreeWidget->expandAll();
}

void MainWindow::tree_add_children(QStandardItem *table_item, QTreeWidgetItem *tree_item)
{
    for (int i = 0; i < table_item->rowCount(); i++)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem;
        child->setText(0, table_item->child(i)->text());
        tree_item->addChild(child);

        tree_add_children(table_item->child(i), child);
    }
}

void MainWindow::on_buildTreeButton_clicked()
{
    std::string AST_tree = build_AST(ui->codeTextEdit->toPlainText().toStdString());

    QStandardItemModel *model = new QStandardItemModel();
    build_QSIM(model, AST_tree);

    build_tree(model);
}


void MainWindow::on_loadCodeButton_clicked()
{
    File *wnd = new File(this);
    wnd->show();

    connect(wnd, SIGNAL(filePath(QString)), this, SLOT(loadCode(QString)));
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
