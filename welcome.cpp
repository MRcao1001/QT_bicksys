#include "welcome.h"
#include "ui_welcome.h"
#include <QMovie>
welcome::welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);

}

welcome::~welcome()
{
    delete ui;
}
