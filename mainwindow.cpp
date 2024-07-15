#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
#include<fstream>
#include<QString>
#include<QDebug>
#include<QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    auto fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Application"), "/home/");
    ui->app->setText(fileName);
};



void MainWindow::on_pushButton_2_pressed()
{
    auto fileName = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.svg)"));
    ui->icon->setText(fileName);
}


void MainWindow::on_pushButton_3_pressed()
{
    if(ui->app_name->text().length()<=0)
    {
        ui->debug_label->setText("Error : App Name must be set before adding desktop entry!");
        return;
    };

    if(ui->app->text().length()<=0)
    {
        ui->debug_label->setText("Error : Please first select and Application");
        return;
    };

    if(ui->icon->text().length()<=0)
    {
        ui->debug_label->setText("Error ; Please Select icon for dekstop entry!");
        return;
    }
    QString path= *QStandardPaths::standardLocations(QStandardPaths::HomeLocation).begin();
    path.append("/.local/share/applications/");
    const QString app_name{ui->app_name->text()};
    path.append(app_name);
    path.append(".desktop");
    QString to_write{R"(
[Desktop Entry]
Version=1.0
Name=appName
Comment=None
Exec=applicationPath
Icon=iconPath
Terminal=false
Type=Application
Categories=Game;Development;
Keywords=game;engine;development;IDE;
)"};

    std::fstream file{};
    file.open(path.toStdString().c_str(),std::ios::out);
    if(!file.is_open())
    {
        qDebug()<<"Failed to create file "<<path<<"\n";
        return;
    }
    to_write.replace("applicationPath",ui->app->text());
    to_write.replace("iconPath",ui->icon->text());
    to_write.replace("appName",app_name);
    qDebug()<<path<<"\n";
    qDebug()<<to_write<<"\n";
    file<<to_write.toStdString();
    file.close();
    ui->debug_label->setText("Success : desktop entry has been added");
}

