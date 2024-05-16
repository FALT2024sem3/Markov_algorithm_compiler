#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>

#include "get_AST.h"
#include "build_AST.h"
#include "AST.h"
#include "qdir.h"
#include "codehighlighter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadSettings();
    void saveSettings();

private slots:
    void loadCode(const QString &filePath);

    void on_buildTreeButton_clicked();
    void on_loadCodeButton_clicked();

private:
    Ui::MainWindow *ui;
    codeHighLighter *m_codehighlighter;
    QSettings settings;

    void createTempFile(const QString filePath);
    void deleteTempFile(const QString filePath);

    void build_tree(QStandardItemModel *table_tree);
    void tree_add_children(QStandardItem *table_item, QTreeWidgetItem *tree_item);
};
#endif // MAINWINDOW_H
