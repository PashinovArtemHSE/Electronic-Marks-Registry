#ifndef ALLSTUDENTS_H
#define ALLSTUDENTS_H

#include <QDialog>

namespace Ui {
class AllStudents;
}

class AllStudents : public QDialog
{
    Q_OBJECT

public:
    explicit AllStudents(QWidget *parent = nullptr);
    ~AllStudents();

private:
    Ui::AllStudents *ui;
};

#endif // ALLSTUDENTS_H
