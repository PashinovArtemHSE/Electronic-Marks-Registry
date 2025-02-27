#include "marks.h"
#include "ui_marks.h"
#include "mainwindow.h"
#include <QDate>

std::map<QString, std::string> _mapp_ = {
    {"Lineal Algebra", "marks_la.csv"},
    {"Calculus", "marks_calc.csv"},
    {"Computer Science (CS)", "marks_cs.csv"},
    {"Math Statistics", "marks_ms.csv"},
    {"Geometric analysis", "marks_ga.csv"},
    {"Data Bases", "marks_db.csv"},
    {"Machine Learning", "marks_ml.csv"},
    {"English", "marks_eng.csv"}
};

QString _fil = QString::fromStdString(_mapp_["Lineal Algebra"]);

Marks::Marks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Marks)
{
    ui->setupUi(this);
    std::ifstream groupsFile("groups.csv");
    std::string group;
    while (std::getline(groupsFile, group)) {
        ui->cb->addItem(QString::fromStdString(group));
    }
    groupsFile.close();
    filltable();
    ui->tableWidget->setSortingEnabled(true);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &Marks::on_tableWidget_horizontalHeader_clicked);
}

Marks::~Marks()
{
    delete ui;
}

void Marks::on_tableWidget_horizontalHeader_clicked(int column)
{
    if (column == 0) { // Если нажата колонка "ФИО"
        static bool ascending = true; // Флаг направления сортировки
        ui->tableWidget->sortItems(column, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending; // Инвертируем направление сортировки
    }
}

void Marks::filltable(){
    ui->tableWidget->blockSignals(true);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setColumnCount(13);
    QDate todayDate = QDate::currentDate();

    QStringList headers = {"ФИО","Группа"};
    for (int i = 0; i < 10; i++)
        headers.append(todayDate.addDays(i).toString("dd.MM.yyyy"));
    headers.append("Средний балл");
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Получаем выбранную группу из comboBox
    QString selectedGroup = ui->cb->currentText();

    std::ifstream file(_fil.toStdString());
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            // Разделяем строку на токены
            std::vector<std::string> tokens = MainWindow::split(line, ';');
            if (tokens.size() < 2) continue; // Проверка на корректность данных

            QString studentGroup = QString::fromStdString(tokens[1]);
            if (studentGroup != selectedGroup) continue; // Фильтр по группе

            QStringList data;
            for (const auto &token : tokens) {
                data.append(QString::fromStdString(token));
            }

            // Добавляем новую строку в таблицу
            int currentRow = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(currentRow);

            // Заполняем ячейки строки
            for (int col = 0; col < data.size(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(data[col]);
                ui->tableWidget->setItem(currentRow, col, item);
            }
            double average = calculateAverage(data);
            QTableWidgetItem *averageItem = new QTableWidgetItem(QString::number(average, 'f', 2));
            averageItem->setFlags(averageItem->flags() & ~Qt::ItemIsEditable); // Делаем ячейку недоступной для редактирования
            ui->tableWidget->setItem(currentRow, 12, averageItem);
        }
    }
    file.close();

    ui->tableWidget->blockSignals(false);
}

double Marks::calculateAverage(const QStringList &data) {
    double sum = 0.0;
    int count = 0;

    for (int i = 2; i < data.size(); ++i) { // Пропускаем первую колонку (ФИО)
        bool ok;
        double value = data[i].toDouble(&ok);
        if (ok) { // Учитываем только числовые значения
            sum += value;
            count++;
        }
    }

    return (count > 0) ? (sum / count) : 0.0; // Возвращаем средний балл или 0, если все ячейки пустые
}

void Marks::on_tableWidget_cellChanged(int row, int column)
{
    qDebug() << "Изменение в строке:" << row << ", столбце:" << column;

    std::ifstream file(_fil.toStdString());
    std::string line;
    std::vector<std::string> remained_strings;

    QString studentName = ui->tableWidget->item(row, 0)->text(); // Получаем ФИО студента в строке
    QString studentGroup = ui->tableWidget->item(row, 1)->text(); // Получаем группу студента

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = MainWindow::split(line, ';');
        if (tokens.size() < 2) continue; // Проверяем, что в строке есть ФИО и группа

        QString fileStudentName = QString::fromStdString(tokens[0]);
        QString fileStudentGroup = QString::fromStdString(tokens[1]);

        if (fileStudentName == studentName && fileStudentGroup == studentGroup) {
            // Совпадение найдено, обновляем только нужную ячейку
            QTableWidgetItem *_item = ui->tableWidget->item(row, column);
            if (_item) {
                tokens[column] = _item->text().toStdString();
            }
        }

        // Добавляем строку (обновленную или нет) в список
        remained_strings.push_back(joinStrings(tokens, ";"));
    }
    file.close();

    // Перезаписываем файл с обновлёнными данными
    std::ofstream _file(_fil.toStdString(), std::ios::trunc | std::ios::out);
    for (const auto &str : remained_strings) {
        _file << str << "\n";
    }
    _file.close();
}

std::string Marks::joinStrings(const std::vector<std::string>& vec, const std::string& delimiter) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) { // Add delimiter except after the last element
            oss << delimiter;
        }
    }
    return oss.str();
}

void Marks::on_Subjects_currentTextChanged(const QString &arg1)
{
    _fil = QString::fromStdString(_mapp_[arg1]);
    filltable();
}

void Marks::on_cb_currentTextChanged()
{
    filltable();
}

