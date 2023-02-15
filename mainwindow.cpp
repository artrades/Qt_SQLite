#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    model = new QSqlTableModel(this, db);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Выбрать базу данных sqlite"),
                               "", tr("Файл базы данных (*.db)"));
        db.setDatabaseName(fileName);
        qDebug() <<  db.database();
        ui->listWidget->clear();
        ui->listWidget->addItems(db.tables());
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    qDebug() <<  index.row();
    model->setTable(ui->listWidget->currentIndex().data().toString());
    ui->tableView->setModel(model);
    model->select();
}

