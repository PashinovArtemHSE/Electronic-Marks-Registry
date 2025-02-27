#include "ratings.h"
#include "ui_ratings.h"
#include <fstream>
#include "mainwindow.h"
#include <algorithm>

std::map<QString, std::string> __map = {
    {"Lineal Algebra", "marks_la.csv"},
    {"Calculus", "marks_calc.csv"},
    {"Computer Science (CS)", "marks_cs.csv"},
    {"Math Statistics", "marks_ms.csv"},
    {"Geometric analysis", "marks_ga.csv"},
    {"Data Bases", "marks_db.csv"},
    {"Machine Learning", "marks_ml.csv"},
    {"English", "marks_eng.csv"}
};


Ratings::Ratings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ratings)
{
    ui->setupUi(this);

    std::map<std::string, double> rate;
    std::fstream file_outer("students.csv", std::ios::in);
    std::string line_outer;

    while (std::getline(file_outer, line_outer)) {
        if (!line_outer.empty()) {
            std::vector<std::string> st_name = MainWindow::split(line_outer, ';');
            std::string student_name = st_name[0];

            double total_grades = 0;
            int total_subjects = 0;

            for (const auto &filik : __map) {
                std::string line_inner;
                std::fstream file_inner(filik.second, std::ios::in);

                while (std::getline(file_inner, line_inner)) {
                    std::vector<std::string> grades = MainWindow::split(line_inner, ';');

                    if (grades.empty()) continue;

                    if (grades[0] == student_name) {
                        double subject_total = 0;
                        int grade_count = 0;

                        for (size_t i = 2; i < grades.size(); i++) {
                            if (!grades[i].empty() && grades[i] != " ") {
                                try {
                                    subject_total += std::stod(grades[i]);
                                    grade_count++;
                                } catch (const std::invalid_argument &e) {}
                            }
                        }

                        if (grade_count > 0) {
                            total_grades += (subject_total / grade_count);
                            total_subjects++;
                        }
                    }
                }
            }

            if (total_subjects > 0) {
                rate[student_name] = total_grades / total_subjects;
            }
        }
    }

    std::vector<std::pair<std::string, double>> sorted_rate(rate.begin(), rate.end());

    std::sort(sorted_rate.begin(), sorted_rate.end(),
              [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                  return a.second > b.second;
              });

    ui->Rate->clear();
    ui->Rate->setRowCount(sorted_rate.size());
    ui->Rate->setColumnCount(2);

    // Установка заголовков столбцов
    QStringList headers;
    headers << "Student" << "GPA";
    ui->Rate->setHorizontalHeaderLabels(headers);

    // Заполнение таблицы
    int row = 0;
    for (const auto &entry : sorted_rate) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(entry.first));
        QTableWidgetItem *gradeItem = new QTableWidgetItem(QString::number(entry.second, 'f', 2)); // 2 знака после запятой

        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        gradeItem->setFlags(gradeItem->flags() & ~Qt::ItemIsEditable);

        ui->Rate->setItem(row, 0, nameItem);
        ui->Rate->setItem(row, 1, gradeItem);
        row++;
    }

    // Автоматическое подгонка ширины столбцов
    ui->Rate->resizeColumnsToContents();
    ui->Rate->setSortingEnabled(true);
    ui->Rate->setSortingEnabled(true);
    connect(ui->Rate->horizontalHeader(), &QHeaderView::sectionClicked, this, &Ratings::on_Rate_horizontalHeader_clicked);
}

Ratings::~Ratings()
{
    delete ui;
}

void Ratings::on_Rate_horizontalHeader_clicked(int column)
{
    if (column == 1) { // Если нажата колонка "ФИО"
        static bool ascending = true; // Флаг направления сортировки
        ui->Rate->sortItems(column, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending; // Инвертируем направление сортировки
    }
}
