#ifndef REMOVESTUDENT_H
#define REMOVESTUDENT_H

#include <QDialog>

namespace Ui {
class RemoveStudent;
}

class RemoveStudent : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveStudent(QWidget *parent = nullptr);
    ~RemoveStudent();

private slots:
    void on_removestudent_clicked();
    void removeStudentFromFile(const std::string& filename, const std::string& studentName);

private:
    Ui::RemoveStudent *ui;
};

#endif // REMOVESTUDENT_H
