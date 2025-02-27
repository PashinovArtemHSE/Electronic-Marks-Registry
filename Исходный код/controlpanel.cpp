#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QDebug>

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::on_addstudent_clicked()
{
    add_student = new AddStudent();
    add_student->show();
}

void ControlPanel::on_removestudent_clicked()
{
    rs = new RemoveStudent();
    rs->show();
}

void ControlPanel::on_selectsubject_clicked()
{
    marks = new Marks();
    marks->show();
}

void ControlPanel::on_ratings_clicked()
{
    rt = new Ratings();
    rt->show();
}


void ControlPanel::on_add_homework_clicked()
{
    homework = new Homework();
    homework->show();
}
