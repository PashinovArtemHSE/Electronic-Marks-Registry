#include "homeworkstudent.h"
#include "ui_homeworkstudent.h"

HomeWorkStudent::HomeWorkStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomeWorkStudent)
{
    ui->setupUi(this);

    //Добавление информации из .csv в таблицу для домашнего задания
    QFile file("hw.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    ui->tableWidget->setRowCount(0);

    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.isEmpty()) continue;

        ui->tableWidget->insertRow(row);
        for (int col = 0; col < fields.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[col].trimmed());
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }

    file.close();

    //Подгоняем размер ячеек таблицы под содержимое
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

HomeWorkStudent::~HomeWorkStudent()
{
    delete ui;
}
