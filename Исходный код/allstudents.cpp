#include "allstudents.h"
#include "ui_allstudents.h"

AllStudents::AllStudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllStudents)
{
    ui->setupUi(this);
}

AllStudents::~AllStudents()
{
    delete ui;
}
