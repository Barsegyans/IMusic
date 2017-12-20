#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "albumdialog.h"
#include "artistdialog.h"
#include "ratingdelegate.h"

#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->treeView);

    model = new MusicModel();
    ui->treeView->setModel(model);

    const int RatingColumn = 2; // возможно в вашей модели это будет
    // другой номер колонки
    RatingDelegate *delegate = new RatingDelegate(ui->treeView);
    ui->treeView->setItemDelegateForColumn(RatingColumn, delegate);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->actionEdit->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->actionAdd_Album->setEnabled(false);
    ui->actionAddTrack->setEnabled(false);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(setModified()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(update_active_actions(QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open"),tr("/"), tr("*.mus"));
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream in(&file);
            delete model->m_root;
            setWindowModified(false);
            model->m_root = new Item();
            ui->treeView->reset();
            in >> *(model->m_root);
            file.close();
            ui->actionEdit->setEnabled(false);
            ui->actionDelete->setEnabled(false);
            ui->actionAdd_Album->setEnabled(false);
            ui->actionAddTrack->setEnabled(false);
        }

    }
    ui->treeView->reset();
}


void MainWindow::on_actionAdd_Artist_triggered()
{
    ArtistDialog *dialog = new ArtistDialog();
    dialog->addArtist(model, QModelIndex());
    setModified();
}

void MainWindow::on_actionAdd_Album_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    AlbumDialog *album= new AlbumDialog();
    album->addAlbum(model, cur_index);
    setModified();
}

void MainWindow::on_actionAddTrack_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();


    int row = model->rowCount(cur_index);
    model->insertRow(row, cur_index);

    setModified();
}

void MainWindow::on_actionDelete_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    model->removeRow(cur_index.row(), cur_index.parent());

    update_active_actions(ui->treeView->selectionModel()->currentIndex());
    setModified();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionEdit_triggered()
{
    Item *cur_item=static_cast<Item*>(ui->treeView->selectionModel()->currentIndex().internalPointer());
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    QModelIndex parent = ui->treeView->selectionModel()->currentIndex().parent();

    if(cur_item->toAlbum())
    {
            AlbumDialog *album = new AlbumDialog();
            album->setModel(model);
            album->setModelIndex(cur_index);
            album->show();
    }
    else
    if(cur_item->toArtist())
    {
            ArtistDialog *artist = new ArtistDialog();
            artist->setModel(model);
            artist->setModelIndex(cur_index);
            artist->show();
    }
    else
    if(cur_item->toTrack()) return;
}

bool MainWindow::on_actionSave_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save"), tr("/"), tr("*.mus"));
    if (fileName.isEmpty()) return false;
    else
    {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream out(&file);
            out << *(model->m_root);
            file.close();
            setWindowModified(false);
            return true;
        }

    }
    return false;
}

void MainWindow::setModified()
{
    setWindowModified(true);
}

void MainWindow::update_active_actions(QModelIndex index)
{
    Item *cur_item=static_cast<Item*>(index.internalPointer());
    if(!cur_item or !index.isValid())
    {
        ui->actionEdit->setEnabled(false);
        ui->actionDelete->setEnabled(false);
        ui->actionAdd_Album->setEnabled(false);
        ui->actionAddTrack->setEnabled(false);
        return;
    }
    if(cur_item->toAlbum())
    {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionAdd_Album->setEnabled(false);
        ui->actionAddTrack->setEnabled(true);
    }
    if(cur_item->toTrack())
    {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionAdd_Album->setEnabled(false);
        ui->actionAddTrack->setEnabled(true);
    }
    if(cur_item->toArtist())
    {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        ui->actionAdd_Album->setEnabled(true);
        ui->actionAddTrack->setEnabled(false);
    }


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(isWindowModified())
    {
        QMessageBox::StandardButton choose = QMessageBox::warning(this, tr("Save"), tr("There is some changes. Do you want to save them?"),
                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        switch (choose)
        {
          case QMessageBox::Yes:
              if(!this->on_actionSave_triggered())
              {
                  event->ignore();
                  return;
              }
              event->accept();
              return;
          case QMessageBox::No:
              event->accept();
              return;
          case QMessageBox::Cancel:
              event->ignore();
              return;
        }
    }
    event->accept();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}


void MainWindow::on_actionAbout_Programm_triggered()
{

    QFile f(QString(":/about.txt"));
    if(!f.open(QIODevice::ReadOnly))
    {
        qFatal("Couldn't open file ");
    }
    QTextStream in(&f);
    QMessageBox::about(this, "Title", in.readAll());
    f.close();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
     QMessageBox::aboutQt(this, "Title About Qt");
}
