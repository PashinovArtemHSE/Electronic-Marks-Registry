#include "addstudent.h"
#include "ui_addstudent.h"
#include "mainwindow.h"

std::map<QString, std::string> mapp = {
    {"Lineal Algebra", "marks_la.csv"},
    {"Calculus", "marks_calc.csv"},
    {"Computer Science (CS)", "marks_cs.csv"},
    {"Math Statistics", "marks_ms.csv"},
    {"Geometric analysis", "marks_ga.csv"},
    {"Data Bases", "marks_db.csv"},
    {"Machine Learning", "marks_ml.csv"},
    {"English", "marks_eng.csv"}
};

AddStudent::AddStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStudent)
{
    ui->setupUi(this);
}

AddStudent::~AddStudent()
{
    delete ui;
}

//
void AddStudent::on_addst_clicked()
{
    //Проверка на присутствие похожей записи на уже внесённую в .csv
    std::ifstream file("students.csv"); // Открытие файла
    std::string line;
    bool is_in = false;
    while (std::getline(file, line)) {
        if (line != ""){
            std::vector<std::string> tokens = MainWindow::split(line, ';');
            if (tokens[0] == ui->name->text().toStdString()){
                is_in = true;
                QMessageBox::information(this, "Error!", "User is already in database");
            }
        }
    }
    file.close();

     //Добавление студента в students.csv
    if (is_in == false){
        std::ofstream file("students.csv", std::ios::app); // Открываем файл в режиме добавления
        for (const auto &t: mapp)
        {
            std::ofstream file2(t.second, std::ios::app);
            file2 << ui->name->text().toStdString()+";"+ui->group->text().toStdString()+"; ; ; ; ; ; ; ; ; ; ;"+"\n";
            file2.close();
        }
        file << ui->name->text().toStdString()+";"+ui->passwd->text().toStdString()+";"+ui->group->text().toStdString()+"\n";
        file.close();

        // Проверка уникальности группы
        std::ifstream groupsFile("groups.csv");
        std::string groupNumber = ui->group->text().toStdString();
        bool groupExists = false;
        while (std::getline(groupsFile, line)) {
            if (line == groupNumber) {
                groupExists = true;
                break;
            }
        }
        groupsFile.close();

        // Если группы нет, добавляем её в файл
        if (!groupExists) {
            std::ofstream groupsFileOut("groups.csv", std::ios::app);
            groupsFileOut << groupNumber << "\n";
            groupsFileOut.close();
        }

        QMessageBox::information(this, "Success!", "User is added to database");
        this->hide();
    }
}

