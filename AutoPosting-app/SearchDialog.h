#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

#include "telsearch.h"
#include "telsearch_entry.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
    int get();
    QList<telsearch_entry> adr_list;

public slots:
    void on_search_clicked();
    void get_adr(QList<telsearch_entry> adresses);

signals:
    void selected_adr(telsearch_entry adresse);

private:
    Ui::SearchDialog *ui;
    QStringList List;
};

#endif // SEARCHDIALOG_H
