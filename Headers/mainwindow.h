#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "executive.h"
#include <QVector>
#include <QMessageBox>
using namespace std;

struct memberStruct {
    QVector<member*>    memberVec;
    QVector<executive*> execVec;
};

//This struct is a functor which is a struct that has the function call operator
struct checkExperation
{
    int theMonth;
    //this is the struct constuctor. it construct the struct and blew my mind. literaly.
    checkExperation(int theMonth){this->theMonth = theMonth;}
    //this is the function call operator that turns the struct into a funtion. this also blew my MIND!!!
    //operator() is what overloads the function call operator in order to be able to turn the struct into a function.
    bool operator()(member m)
    {
    //this is going into the member class retriving the date then going into the date class and retriving the month.
    //then it is comparing month from date class to theMonth in the struct returning a true or false.
        return m.getExpiry().getMonth() == theMonth;
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void UpdateDataFromFile(QString);

    bool UpdateMembersFromFile(QString);

    void SaveToFile(QString);

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

    void on_lineEdit_returnPressed();

    void on_readInButton_clicked();

    void on_purchases_rep_clicked();

    void on_sales_rep_clicked();

    void on_quantity_rep_clicked();

    void on_rebate_rep_clicked();

    void on_expiring_rep_clicked();

    void on_delete_user_clicked();

    void on_delete_item_clicked();

    void on_add_user_clicked();

    void on_add_purchase_clicked();

    void on_enterPassword_returnPressed();

//    void on_pushButton_clicked();

    void on_back_to_login_clicked();

    void on_Admin_Login_Button_clicked();

private:
    Ui::MainWindow *ui;
    memberStruct myMembers;
    QVector<int> memberIds;
};

#endif // MAINWINDOW_H
