#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "musicmodel.h"
#include <QCloseEvent>
#include <QLibraryInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MusicModel *model;
public slots:
    void setModified();
    void update_active_actions(QModelIndex index);
private slots:
    void on_actionOpen_triggered();
    bool on_actionSave_triggered();
    void on_actionAdd_Artist_triggered();
    void on_actionAdd_Album_triggered();
    void on_actionAddTrack_triggered();
    void on_actionDelete_triggered();
    void on_actionExit_triggered();
    void on_actionEdit_triggered();
    void on_actionAbout_Programm_triggered();
    void on_actionAbout_Qt_triggered();
};

#endif // MAINWINDOW_H
