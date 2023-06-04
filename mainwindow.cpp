#include <QMessageBox>
#include <fstream>
#include <QWidget>
#include <QDateTime>
#include <sstream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "lab6.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MyApp");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString text = ui->textEdit1->toPlainText();
    QStringList words = text.split(" ");

    QStringList replacedWords;
    for (const QString& word : words) {
        std::string result = findRandomSynonym(word.toStdString(), glossary);
        replacedWords.append(QString::fromStdString(result));
    }

    QString replacedText = replacedWords.join(" ");
    ui->textEdit1->setPlainText(replacedText);

    std::ofstream fout("result");
    fout << replacedText.toStdString();
    fout.close();

    std::ofstream out(logName, std::ios_base::app);
    auto now = QDateTime::currentDateTime();
    auto s = now.toString("d MMMM hh:mm:ss");
    out << s.toStdString() << "  " << "MEDIUM" << "    " << "Получен очередной результат!" << std::endl;
    out.close();
}


void MainWindow::on_pushButton_2_clicked()
{
    auto s = ui->fileEdit->text();
    std::ifstream fin(s.toStdString(), std::ios_base::in);
    if(!fin.good()) {
        QMessageBox msg;
        msg.setText(QString::fromStdString("Такого файла не существует!"));
        msg.exec();

        std::ofstream out(logName, std::ios_base::app);
        auto now = QDateTime::currentDateTime();
        auto s = now.toString("d MMMM hh:mm:ss");
        out << s.toStdString() << "    " << "HIGH" << "    " << "Попытка открыть несуществующий файл!" << std::endl;
        out.close();
        return;
    }
    int k = 1;
    while (fin.good()) {
        while(fin.good()) {
            std::string w;
            fin >> w;
            if(w == "*") {
                k++;
                break;
            }
            if(w == "") {
                continue;
            }
            glossary.push_back(std::make_pair(w, k));
        }
    }
    std::sort(glossary.begin(), glossary.end());

    std::ofstream out(logName, std::ios_base::app);
    auto now = QDateTime::currentDateTime();
    auto s2 = now.toString("d MMMM hh:mm:ss");
    out << s2.toStdString() << "    " << "HIGH" << "    " << "Сформировали список синонимов!" << std::endl;
    out.close();

    string res;
    for(size_t k = 0; k < glossary.size(); k++) {
        res += glossary[k].first + ":" + std::to_string(glossary[k].second) + "\n";
    }

    QMessageBox msg;

    msg.setText(QString::fromStdString(res));
    msg.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    auto s = ui->fileEdit2->text();
    std::ifstream fin(s.toStdString(), std::ios_base::in);
    if(!fin.good()) {
        QMessageBox msg;
        msg.setText(QString::fromStdString("Такого файла не существует!"));
        msg.exec();
        return;
    }
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string file_contents = buffer.str();

    QString result = QString::fromStdString(file_contents);
    ui->textEdit1->setPlainText(result);
}

