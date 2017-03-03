#ifndef ADDRECWINDOW_H
#define ADDRECWINDOW_H

#include <QMainWindow>

namespace Ui {
class addRecWindow;
}

class addRecWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit addRecWindow(QWidget *parent = 0);
    ~addRecWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addRecWindow *ui;
};

#endif // ADDRECWINDOW_H
