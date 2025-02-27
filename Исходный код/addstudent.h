#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QDialog>
#include <QMainWindow>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <QMessageBox>
#include <QFile>

namespace Ui {
class AddStudent;
}

class AddStudent : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudent(QWidget *parent = nullptr);
    ~AddStudent();

private slots:
    void on_addst_clicked();

private:
    Ui::AddStudent *ui;
};

#endif // ADDSTUDENT_H
