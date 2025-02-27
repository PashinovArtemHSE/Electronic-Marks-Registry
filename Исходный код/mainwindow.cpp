#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::vector<std::string> homeworkData = {
        "Lineal_Algebra; ; ; ; ; ; ; ; ; ;",
        "Calculus; ; ; ; ; ; ; ; ; ; ;",
        "Computer_Science_(CS); ; ; ; ; ; ; ; ; ; ; ; ; ;",
        "Math_Statistics; ; ; ; ; ; ; ; ; ;",
        "Geometric_Anylysis; ; ; ; ; ; ; ; ; ; ;",
        "Data_Bases; ; ; ; ; ; ; ; ; ;",
        "Machine_Learning; ; ; ; ; ; ; ; ; ;",
        "English; ; ; ; ; ; ; ; ; ; ;"
    };
    std::map<QString, std::string> mapp = {
        {"Students", "students.csv"},
        {"Groups", "groups.csv"},
        {"users", "users.csv"},
        {"hw", "hw.csv"},
        {"Lineal Algebra", "marks_la.csv"},
        {"Calculus", "marks_calc.csv"},
        {"Computer Science (CS)", "marks_cs.csv"},
        {"Math Statistics", "marks_ms.csv"},
        {"Geometric analysis", "marks_ga.csv"},
        {"Data Bases", "marks_db.csv"},
        {"Machine Learning", "marks_ml.csv"},
        {"English", "marks_eng.csv"}
    };
    //Создаём файлы .csv для хранения всей информации о студентах
    for (const auto& item : mapp) {
        struct stat buffer;
        if (stat(item.second.c_str(), &buffer) == 1){
            std::ofstream file(item.second);
            file.close();
        }
    }
    //записываем в файл поля для домашнего задания
    std::ofstream file("hw.csv");
    for (const auto &line : homeworkData){
        file << line+"\n";
    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//функция для разделения строки на слова, разделённые ';'
std::vector<std::string> MainWindow::split(const std::string& str, char delimiter){
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

//Внесение в .csv файл данные преподавателя
void MainWindow::on_logIn_clicked()
{
    std::string filename_;
    if (ui->position->currentText() == "Tutor")
        filename_ = "users.csv";
    else
        filename_ = "students.csv";

    std::ifstream file(filename_);
    std::string line;
    bool is_user = false;
    bool is_password = false;

    while (std::getline(file, line)) {
        if (line != ""){
            std::vector<std::string> tokens = split(line, ';');
            if (tokens[0] == ui->login->text().toStdString())
            {
                is_user = true;
                if (tokens[1] == ui->password->text().toStdString()){
                    QMessageBox::information(this, "Right!", "You are logged in!");
                    is_password = true;
                    if (ui->position->currentText() == "Tutor"){
                        cp = new ControlPanel();
                        cp->show();
                    }
                    else
                    {
                        up = new UserPanel(ui->login->text(), this);
                        up->show();
                    }
                    this->hide();
                }
            }
        }
    }
    if (is_user == true && is_password == false)
        QMessageBox::information(this, "Error!", "Incorrent password!");
    else if (is_user == false)
        QMessageBox::information(this, "Error!", "No such user");

    file.close();
}


void MainWindow::on_SignUp_clicked()
{
    if (ui->position->currentText() == "Tutor")
    {
        std::ifstream file("users.csv"); // Открытие файла

        std::string line;
        bool is_in = false;

        while (std::getline(file, line)) {
            if (line != ""){
                std::vector<std::string> tokens = split(line, ';');
                if (tokens[0] == ui->login->text().toStdString()){
                    is_in = true;
                    QMessageBox::information(this, "Error!", "User is already in database");
                }
            }
        }
        file.close();

        if (is_in == false){
            std::ofstream file("users.csv", std::ios::app); // Открываем файл в режиме добавления
            file << ui->login->text().toStdString()+";"+ui->password->text().toStdString()+"\n" << std::endl;
            QMessageBox::information(this, "Success!", "User is added to database");
            file.close();
        }
    }
    else
        QMessageBox::warning(this, "Error!", "Student cannot register himself!");
}
