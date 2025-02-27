#include "userpanel.h"
#include "ui_userpanel.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

std::map<QString, std::string> _map1 = {
    {"Lineal Algebra", "marks_la.csv"},
    {"Calculus", "marks_calc.csv"},
    {"Computer Science (CS)", "marks_cs.csv"},
    {"Math Statistics", "marks_ms.csv"},
    {"Geometric analysis", "marks_ga.csv"},
    {"Data Bases", "marks_db.csv"},
    {"Machine Learning", "marks_ml.csv"},
    {"English", "marks_eng.csv"}
};

UserPanel::UserPanel(QString studentName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
    ui->label_2->setText(studentName);
    loadStudentGrades();  // Загружаем оценки при открытии окна
}

UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::loadStudentGrades()
{
    QString studentName = ui->label_2->text();
    ui->assessment->setRowCount(0); // Очищаем таблицу

    // Отключаем возможность редактировать ячейки
    ui->assessment->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Добавляем новую колонку для среднего балла
    ui->assessment->insertColumn(11);
    ui->assessment->setHorizontalHeaderItem(11, new QTableWidgetItem("Средний балл"));

    int row = 0; // Индекс строки в таблице
    for (const auto& ww : _map1)
    {
        QFile file(QString::fromStdString(ww.second));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Не удалось открыть файл: " << ww.second.c_str();
            continue;
        }

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList values = line.split(';', QString::KeepEmptyParts);

            qDebug() << "Читаем строку:" << line;

            // Пропускаем строки, если они не содержат имя студента
            if (values.isEmpty() || values[0] != studentName) {
                continue;
            }

            // Добавляем новую строку в таблицу для текущего предмета
            ui->assessment->insertRow(row);
            ui->assessment->setItem(row, 0, new QTableWidgetItem(ww.first));

            // Переменные для подсчета среднего балла
            int totalGrade = 0;
            int gradeCount = 0;

            // Заполняем оставшиеся 10 колонок оценками
            for (int i = 2; i <= 10; ++i) {
                QString grade = (i < values.size()) ? values[i].trimmed() : ""; // Убираем пробелы
                ui->assessment->setItem(row, i, new QTableWidgetItem(grade));

                // Если оценка непустая, добавляем её в расчет среднего балла
                if (!grade.isEmpty()) {
                    totalGrade += grade.toInt(); // Преобразуем оценку в число
                    gradeCount++;
                }
            }

            // Вычисляем средний балл
            double averageGrade = (gradeCount > 0) ? static_cast<double>(totalGrade) / gradeCount : 0.0;

            // Добавляем средний балл в новую колонку
            ui->assessment->setItem(row, 11, new QTableWidgetItem(QString::number(averageGrade, 'f', 2)));

            row++;
            break; // Если нашли нужную строку, прекращаем обработку файла
        }
        file.close();
    }

    // Автоматическое изменение размера строк в таблице по содержимому
    ui->assessment->resizeRowsToContents();

    if (row == 0) {
        qWarning() << "Для студента" << studentName << "оценки не найдены.";
    }
}


void UserPanel::on_pushButton_clicked()
{
    hws = new HomeWorkStudent();
    hws->show();
}

