#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->newAction,&QAction::triggered,this, &MainWindow::newActionSlot);
    connect(ui->openAction,&QAction::triggered,this,&MainWindow::openActionSlot);
    connect(ui->saveAction,&QAction::triggered,this,&MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot()
{
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档.txt");
}

void MainWindow::openActionSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开文件"),QCoreApplication::applicationFilePath(),tr("Text files(*.txt)"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "错误", "无法打开文件");
            return;
        }
        QTextStream in(&file);
        QString content = in.readAll();
        // while(!in.atEnd()){
        //     content+=in.readLine()+"\n";
        // }
        // qDebug()<<content;
        ui->textEdit->setPlainText(content);
        file.close();
    }
}

void MainWindow::saveActionSlot()
{
    QString defaultFileName = "新建文本文件";
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存文件")
                                                    ,QDir(QCoreApplication::applicationFilePath()).filePath(defaultFileName)
                                                    ,tr("Text files(*.txt)"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "错误", "无法打开文件");
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        file.close();
    }
}
