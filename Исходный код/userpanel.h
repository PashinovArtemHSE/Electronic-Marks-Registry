#ifndef USERPANEL_H
#define USERPANEL_H

#include <QDialog>
#include "homeworkstudent.h"

namespace Ui {
class UserPanel;
}

class UserPanel : public QDialog
{
    Q_OBJECT

public:
    explicit UserPanel(QString studentName, QWidget *parent = nullptr);
    ~UserPanel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserPanel *ui;
    HomeWorkStudent *hws;
    void loadStudentGrades();
};

#endif // USERPANEL_H
