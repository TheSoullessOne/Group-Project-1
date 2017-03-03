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
    void on_pushButton_clicked();

//<<<<<<< HEAD
    void on_Adduser_clicked();

    void on_deleteRec_clicked();

    void on_upgrade_clicked();

    void on_reportsSearch_clicked();

    void on_readInFile_clicked();

//=======
//>>>>>>> 43272280820e008d5101a297129f2adc1d0ff363
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
