#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <PingenAPI.h>
#include <letter.h>

#include <SearchDialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    price_update();

   // connect(ui->actionSearch_Address, &QAction::triggered, this, &MainWindow::on_actionSearch_Address_triggered);
   // connect(ui->actionSendLetter, &QAction::triggered, this, &MainWindow::on_actionSendLetter_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSearch_Address_triggered()
{
    SearchDialog diag(this);
    diag.exec();

    if(diag.result()){
        int i = diag.get();

        if (i < 0) {
            return;
        }

        if (i < diag.adr_list.count()){
            telsearch_entry entry = diag.adr_list[i];
            ui->name->setText(entry.get_firstname() + " " +entry.get_name());
            ui->street->setText(entry.get_street() + " " + entry.get_streetno());
            ui->town->setText(entry.get_zip() + " " + entry.get_city());
        } else {
            if (i == 0) {
                ui->name->setText("Samuel Dolt");
                ui->street->setText("Les Chéseaux 8");
                ui->town->setText("2607 Cortébert");
            } else {
                ui->name->setText("Christophe Bürki");
                ui->street->setText("Hauptstrasse 2");
                ui->town->setText("3251 Ruppoldsried");
            }
        }
    }
    //telsearch * tel = new telsearch();
    //tel->search(ui->name->text(), ui->town->text());

    //connect(tel, &telsearch::send_adr, this, &MainWindow::get_adr);
}

void MainWindow::get_adr(QList<telsearch_entry> adresses){
    //SearchDialog diag(this);
    //diag.exec();
    //ui->title->setText("Herr");
    //ui->name->setText(adresses[0].get_firstname() + " " +adresses[0].get_name());
    //ui->street->setText(adresses[0].get_street() + " " + adresses[0].get_streetno());
    //ui->town->setText(adresses[0].get_zip() + " " + adresses[0].get_city());
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

    qint8 priority = ui->actionA_Post->isChecked() ? PingenAPI::SPEED_PRIORITY : PingenAPI::SPEED_ECONOMY;
    qint8 color = ui->actionBlack_and_White->isChecked() ? PingenAPI::COLOR_BW : PingenAPI::COLOR_COLOR;
    response += api.sendLetter(l1.getId(), priority, color );
    api.deleteLetter(l1.getId());

    ui->statusBar->showMessage(response);
}

void MainWindow::on_actionA_Post_triggered()
{
    price_update();
}

void MainWindow::on_actionBlack_and_White_triggered()
{
    price_update();
}

void MainWindow::price_update(){
    if(ui->actionA_Post->isChecked() && ui->actionBlack_and_White->isChecked()) {
        ui->statusBar->showMessage("Letter price: 1.35CHF");
    };

    if(ui->actionA_Post->isChecked() && !ui->actionBlack_and_White->isChecked()) {
        ui->statusBar->showMessage("Letter price: 1.40CHF");
    };

    if(!ui->actionA_Post->isChecked() && !ui->actionBlack_and_White->isChecked()) {
        ui->statusBar->showMessage("Letter price: 1.30CHF");
    };

    if(!ui->actionA_Post->isChecked() && ui->actionBlack_and_White->isChecked()) {
        ui->statusBar->showMessage("Letter price: 1.20CHF");
    };
}
