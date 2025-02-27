#include "homework.h"
#include "ui_homework.h"
#include <fstream>
#include <vector>
#include <sstream>

Homework::Homework(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Homework)
{
    ui->setupUi(this);
    loadHomework();  // Загружаем данные при открытии окна

    connect(ui->hw, &QTableWidget::cellChanged, this, &Homework::on_hw_cellChanged);
}

Homework::~Homework()
{
    delete ui;
}

//Подгружаем информацию о домашнем задании в таблицу для её дальнейшего просмотра
void Homework::loadHomework()
{
    isUpdating = true;

    QFile file("hw.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;  // Прерываем выполнение, если не можем открыть файл
    }

    QTextStream in(&file);
    ui->hw->setRowCount(0);

    int row = 0;
    int columnCount = 0;

    // Читаем данные из файла
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.isEmpty()) continue;

        // Устанавливаем количество столбцов, основываясь на первой строке
        if (row == 0) {
            columnCount = fields.size();  // Устанавливаем количество столбцов
            ui->hw->setColumnCount(columnCount);
        }

        ui->hw->insertRow(row);
        for (int col = 0; col < fields.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[col].trimmed());
            ui->hw->setItem(row, col, item);
        }
        row++;
    }

    file.close();
    isUpdating = false;
}


void Homework::on_hw_cellChanged(int row, int column)
{
    if (isUpdating) return;

    std::ifstream file("hw.csv");
    std::vector<std::string> lines;
    std::string line;
    int currentLine = 0;

    while (std::getline(file, line)) {
        if (currentLine == row) {
            std::vector<std::string> tokens = split(line, ';');

            QTableWidgetItem *item = ui->hw->item(row, column);
            if (item) {
                tokens[column] = item->text().toStdString();
            }

            line = joinStrings(tokens, ";");
        }
        lines.push_back(line);
        currentLine++;
    }
    file.close();

    std::ofstream outFile("hw.csv", std::ios::trunc);
    for (const auto &l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
}

std::vector<std::string> Homework::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string Homework::joinStrings(const std::vector<std::string> &vec, const std::string &delimiter)
{
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << delimiter;
        }
    }
    return oss.str();
}
