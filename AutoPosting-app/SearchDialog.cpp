#include "SearchDialog.h"
#include "ui_SearchDialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);


    ui->list->setSelectionBehavior( QAbstractItemView::SelectItems );
    ui->list->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );



    connect(ui->search, &QPushButton::clicked, this, &SearchDialog::on_search_clicked);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}


void SearchDialog::on_search_clicked(){
    telsearch * tel = new telsearch();
    tel->search(ui->what->text(), ui->who->text());

    connect(tel, &telsearch::send_adr, this, &SearchDialog::get_adr);


}

void SearchDialog::get_adr(QList<telsearch_entry> adresses){
    adr_list = adresses;
    QListIterator<telsearch_entry> i(adresses);

    List.clear();

    if(!i.hasNext()){
        List.append("Samuel Dolt\n Les Chéseaux 8\n2607 Cortébert");
        List.append("Christophe Bürki\n Hauptstrasse 29\n 3251 Ruppoldsried");
    }

    while (i.hasNext()){
        telsearch_entry adr = i.next();
        QString adrstr = "";
        adrstr += adr.get_firstname() + " " +adr.get_name() + "\n";
        adrstr += adr.get_street() + " " + adr.get_streetno() + "\n";
        adrstr += adr.get_zip() + " " + adr.get_city() + "\n";
        List.append(adrstr);
    }

    QStringListModel *model = new QStringListModel(this);;
    model->setStringList(List);
    ui->list->setModel(model);
    if(List.count() > 0){
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( true );
        ui->list->setCurrentIndex(model->index(0, 0));
    } else {
        ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
    }
}

int SearchDialog::get(){
     QList<QModelIndex> indexes = ui->list->selectionModel()->selectedIndexes();

     if (indexes.isEmpty()) {
         return -1;
     }
     if (0 < indexes.count()){
        QModelIndex index = indexes[0];
        return index.row();
     } else {
         return -1;
     }
}
