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

    void on_Adduser_clicked();

    void on_deleteRec_clicked();

    void on_upgrade_clicked();

    void on_reportsSearch_clicked();

    void on_readInFile_clicked();

    void on_backButton_6_clicked();

    void on_backButton_addmen_clicked();

    void on_backButton_delete_clicked();

    void on_backButton_reports_clicked();

    void on_backButton_readfile_clicked();

    void on_backButton_upgrade_clicked();

    void on_backButton_search_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
