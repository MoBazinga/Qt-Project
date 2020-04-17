#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&myWatch, &QFileSystemWatcher::directoryChanged, this, &MainWindow::showMessage);
    connect(&myWatch, &QFileSystemWatcher::fileChanged, this, &MainWindow::showMessage);

    //显示当前目录下的所有.h文件
    QDir myDir(QDir::currentPath());
    myDir.setNameFilters(QStringList("*.h"));
    ui->listWidget->addItem(myDir.absolutePath() + tr("目录下的.h文件有："));
    ui->listWidget->addItems(myDir.entryList());

    //创建目录，将其加入监视器中
    myDir.mkdir("mydir");
    myDir.cd("mydir");
    ui->listWidget->addItem(tr("监视器中的目录：") + myDir.absolutePath());
    myWatch.addPath(myDir.absolutePath());

    //创建文件，加入监视器
    QFile file(myDir.absolutePath() + "myfile.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QFileInfo info(file);
        ui->listWidget->addItem(tr("监视的文件：") + info.absoluteFilePath());
        myWatch.addPath(info.absoluteFilePath());
        file.close();
    }

    qDebug() << (QDir::currentPath() + "/mydir");
}

void MainWindow::showMessage(const QString &path)
{
    QDir dir(QDir::currentPath() + "/mydir");

    //如果目录发生了改变
    if (path == dir.absolutePath())
    {
        ui->listWidget->addItem(dir.dirName() + tr("目录发生改变："));
        ui->listWidget->addItems(dir.entryList());
    }
    else //如果是文件发生了改变
    {
        ui->listWidget->addItem(path + tr("文件发生改变！"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
