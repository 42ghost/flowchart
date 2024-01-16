#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <thread>
#include "analyzer.hpp"
#include "graphic.hpp"

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QImage>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
