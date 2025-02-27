#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QMainWindow>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <QMessageBox>
#include "addstudent.h"
#include "removestudent.h"
#include "marks.h"
#include <QFile>
#include "ratings.h"
#include "homework.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

private slots:
    void on_addstudent_clicked();

    void on_removestudent_clicked();

    void on_selectsubject_clicked();

    void on_ratings_clicked();

    void on_add_homework_clicked();

private:
    Ui::ControlPanel *ui;
    AddStudent *add_student;
    Marks *marks;
    RemoveStudent *rs;
    Ratings *rt;
    Homework *homework;
};

#endif // CONTROLPANEL_H
