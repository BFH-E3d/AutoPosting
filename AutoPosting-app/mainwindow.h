#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "telsearch.h"
#include "telsearch_entry.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionSearch_Address_triggered();

    void on_actionSendLetter_triggered();

    void get_adr(QList<telsearch_entry> adresses);

private slots:
    void on_actionA_Post_triggered();

    void on_actionBlack_and_White_triggered();

private:
    Ui::MainWindow *ui;
    void price_update();
};

#endif // MAINWINDOW_H
