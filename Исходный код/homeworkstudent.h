#ifndef HOMEWORKSTUDENT_H
#define HOMEWORKSTUDENT_H

#include <QDialog>
#include "homework.h"

namespace Ui {
class HomeWorkStudent;
}

class HomeWorkStudent : public QDialog
{
    Q_OBJECT

public:
    explicit HomeWorkStudent(QWidget *parent = nullptr);
    ~HomeWorkStudent();

private:
    Ui::HomeWorkStudent *ui;
};

#endif // HOMEWORKSTUDENT_H
