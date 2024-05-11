#include "file.h"
#include "ui_file.h"
#include <QPushButton>


File::File(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::File)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(okClicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(close()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}

void File::okClicked()
{
    emit filePath(ui->lineEdit->text());
}

File::~File()
{
    delete ui;
}
