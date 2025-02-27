#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <QMessageBox>
#include "controlpanel.h"
#include <QFile>
#include "userpanel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static std::vector<std::string> split(const std::string& str, char delimiter);

private slots:
    void on_logIn_clicked();

    void on_SignUp_clicked();

private:
    Ui::MainWindow *ui;
    ControlPanel *cp;
    UserPanel *up;
};
#endif // MAINWINDOW_H
