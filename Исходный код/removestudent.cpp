#include "removestudent.h"
#include "ui_removestudent.h"
#include "mainwindow.h"
#include <fstream>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDataStream>

std::map<QString, std::string> mm = {
    {"students", "students.csv"},
    {"Lineal Algebra", "marks_la.csv"},
    {"Calculus", "marks_calc.csv"},
    {"Computer Science (CS)", "marks_cs.csv"},
    {"Math Statistics", "marks_ms.csv"},
    {"Geometric analysis", "marks_ga.csv"},
    {"Data Bases", "marks_db.csv"},
    {"Machine Learning", "marks_ml.csv"},
    {"English", "marks_eng.csv"}
};


RemoveStudent::RemoveStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveStudent)
{
    ui->setupUi(this);
}

RemoveStudent::~RemoveStudent()
{
    delete ui;
}

void RemoveStudent::on_removestudent_clicked() {
    std::string studentNameStd = ui->lusername->text().toStdString();
    if (ui->lpassword->text().toStdString() == "qwerty"){
        for (const auto& pair : mm) {
            removeStudentFromFile(pair.second, studentNameStd);
        }
    }

}

void RemoveStudent::removeStudentFromFile(const std::string& filename, const std::string& studentName) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name;
        std::getline(iss, name, ';'); // Получаем имя студента
        if (name != studentName) {
            lines.push_back(line); // Сохраняем строки, кроме удаляемой
        }
    }
    inputFile.close();

    // Перезаписываем файл без удалённого студента
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Ошибка: не удалось открыть файл для записи " << filename << std::endl;
        return;
    }
    for (const auto& l : lines) {
        outputFile << l << "\n";
    }
    outputFile.close();
}
