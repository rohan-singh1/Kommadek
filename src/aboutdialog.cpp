#include "include/aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    this->close();
}


void AboutDialog::on_logoButton_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->logoButton, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(67, 136, 2, 2));     // 67, 136, 2, 2
    animation->setEndValue(QRect(20, 90, 96, 96));   // 20, 90, 96, 96
    animation->start();
}

