#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <QDialog>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <string>

namespace Ui {
class Homework;
}

class Homework : public QDialog
{
    Q_OBJECT

public:
    explicit Homework(QWidget *parent = nullptr);
    ~Homework();
    std::vector<std::string> split(const std::string &s, char delimiter);  // Функция для разделения строки
    std::string joinStrings(const std::vector<std::string> &vec, const std::string &delimiter);  // Функция для объединения строки

private slots:
    void on_hw_cellChanged(int row, int column);

private:
    Ui::Homework *ui;
    void loadHomework();  // Загрузка данных
    bool isUpdating = false; // Флаг для предотвращения рекурсивного вызова
};

#endif // HOMEWORK_H
