#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_codehighlighter = new codeHighLighter(ui->codeTextEdit->document());
    loadSettings();
}


MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::loadSettings()
{

}

void MainWindow::saveSettings()
{

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
