#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataWidgetMapper>
#include <musicmodel.h>

namespace Ui {
class AlbumDialog;
}

class AlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumDialog(QWidget *parent = 0);
    void setModel(MusicModel*model);
    void accept();
    bool addAlbum(MusicModel *model, const QModelIndex &parent);
    ~AlbumDialog(); 
    void setModelIndex(QModelIndex &index);
private slots:
    void on_brouse_button_clicked();

private:
    Ui::AlbumDialog *ui;
    QDataWidgetMapper m_mapper;
    QPixmap image;
    QModelIndex index;
    Item *item;
};

#endif // ALBUMDIALOG_H
