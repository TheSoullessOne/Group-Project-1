#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_search_clicked();

<<<<<<< HEAD
//<<<<<<< HEAD
=======
>>>>>>> 6e8a67cf476172d09012fc049c5b8d1183f67986
    void on_Adduser_clicked();

    void on_deleteRec_clicked();

    void on_upgrade_clicked();

    void on_reportsSearch_clicked();

    void on_readInFile_clicked();

<<<<<<< HEAD
<<<<<<< HEAD
//=======
//>>>>>>> 43272280820e008d5101a297129f2adc1d0ff363
=======
>>>>>>> 6e8a67cf476172d09012fc049c5b8d1183f67986
=======
    void on_backButton_6_clicked();

    void on_backButton_addmen_clicked();

    void on_backButton_delete_clicked();

    void on_backButton_reports_clicked();

    void on_backButton_readfile_clicked();

    void on_backButton_upgrade_clicked();

    void on_backButton_search_clicked();

>>>>>>> d0b5a8857acb7452d0a0c5ae6dd4999efcbaee28
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
