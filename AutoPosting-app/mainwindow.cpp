#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <PingenAPI.h>
#include <letter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionSearch_Address, &QAction::triggered, this, &MainWindow::on_actionSearch_Address_triggered);
    connect(ui->actionSendLetter, &QAction::triggered, this, &MainWindow::on_actionSendLetter_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSearch_Address_triggered()
{
    telsearch * tel = new telsearch();
    tel->search(ui->name->text(), ui->town->text());

    connect(tel, &telsearch::send_adr, this, &MainWindow::get_adr);
}

void MainWindow::get_adr(QList<telsearch_entry> adresses){
    //ui->title->setText("Herr");
    ui->name->setText(adresses[0].get_firstname() + " " +adresses[0].get_name());
    ui->street->setText(adresses[0].get_street() + " " + adresses[0].get_streetno());
    ui->town->setText(adresses[0].get_zip() + " " + adresses[0].get_city());
}

void MainWindow::on_actionSendLetter_triggered()
{
    Letter l1(ui->title->text(),
              ui->name->text(),
              ui->street->text(),
              ui->town->text(),
              ui->content->toPlainText()
              );

    PingenAPI api("9ec907a72c823617ea27b894b45d2d6b");
    QString response = api.addLetter(l1) + " ";
    response += api.sendLetter(l1.getId(), PingenAPI::SPEED_PRIORITY, PingenAPI::COLOR_COLOR );
    api.deleteLetter(l1.getId());
}
