#ifndef MARKS_H
#define MARKS_H

#include <QDialog>
#include <fstream>
#include <QDebug>

namespace Ui {
class Marks;
}

class Marks : public QDialog
{
    Q_OBJECT

public:
    explicit Marks(QWidget *parent = nullptr);
    ~Marks();

private slots:
    void on_tableWidget_cellChanged(int row, int column);

    void on_Subjects_currentTextChanged(const QString &arg1);

    void on_cb_currentTextChanged();

    void on_tableWidget_horizontalHeader_clicked(int column);

private:
    Ui::Marks *ui;

    void filltable();
    std::string joinStrings(const std::vector<std::string>& vec, const std::string& delimiter);
    double calculateAverage(const QStringList &data);
};

#endif // MARKS_H
