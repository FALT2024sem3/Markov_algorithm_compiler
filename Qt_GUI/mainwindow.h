#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QMainWindow>
#include <QTreeWidgetItem>
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

private slots:
    void loadCode(const QString &filePath);

    void on_buildTreeButton_clicked();
    void on_loadCodeButton_clicked();

private:
    Ui::MainWindow *ui;
    codeHighLighter *m_codehighlighter;

    void createTempFile(const QString filePath);
    void deleteTempFile(const QString filePath);

    void build_tree(QStandardItemModel *table_tree);
    void tree_add_children(QStandardItem *table_item, QTreeWidgetItem *tree_item);
};
#endif // MAINWINDOW_H
