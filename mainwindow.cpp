#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_clicked(){
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)){
        QString str = file.readAll();
        ui->plainTextEdit->setPlainText(str);
        file.close();
    } else {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл!");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str1 = ui->plainTextEdit->toPlainText();
    QString funcname = ui->textEdit_2->toPlainText();
    if (str1.length() > 0 && funcname.length() > 0){
        QString imageName = ui->textEdit->toPlainText();
        FileAnalyzer* analyzer = new FileAnalyzer(str1.toStdString(), funcname.toStdString());
        if (analyzer->getBlocks().size()){
                Graphic* image = new Graphic();
                image->create(analyzer->getBlocks());
                image->draw((imageName + ".png"));
                delete image;
        } else {
            QMessageBox::critical(nullptr, "Ошибка", "Функция не найдена");
        }

        QString lst = QString::fromStdString(analyzer->getSubProg());
        ui->plainTextEdit_2->setPlainText(lst);

        std::string res = "";
        std::istringstream istrm;
        istrm.str(analyzer->getSubProg());
        std::regex rgx("^\\s*(\\w+)\\s*\\((.*)\\);$");

        for (std::string s; std::getline(istrm, s);){
            FileAnalyzer* analyzer2 = new FileAnalyzer(str1.toStdString(), s);
            if (analyzer2->getBlocks().size()){
                Graphic* image2 = new Graphic();
                image2->create(analyzer2->getBlocks());
                image2->draw(QString::fromStdString(s + ".png"));
                delete image2;
            }
        }

        delete analyzer;
    }  else {
        QMessageBox::critical(nullptr, "Ошибка", "Недостаточно данных");
    }
}


void MainWindow::on_action_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)){
        QString str = file.readAll();
        ui->plainTextEdit->setPlainText(str);
        file.close();
    } else {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл!");
    }
}


void MainWindow::on_action_2_triggered()
{
    ui->plainTextEdit->clear();
}

