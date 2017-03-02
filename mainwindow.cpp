#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <algorithm>
#include <vector>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

<<<<<<< HEAD
//Function to add a new user
void MainWindow::on_Adduser_clicked()
{
    //Here we call the function that makes new members
    //Take you to another menu to see what kind of member
}

//Function to delete a user or item
void MainWindow::on_deleteRec_clicked()
{
    //Link to another menu that will determine what the user
    //wants to delete, whether an item or list
}

//Function to upgrade a user
void MainWindow::on_upgrade_clicked()
{
    //Link the function that determines whether a user can upgrade
}

//Function to search different types of reports
void MainWindow::on_reportsSearch_clicked()
{
    //Here we need to link to another menu that helps decide
    //what kind search they want to do
}

//Function to read in a file that has the 5 files of purchases for members
void MainWindow::on_readInFile_clicked()
{
    //Here we link a function that searched for the user so that
    //way it is stored in the correct member data
=======

void MainWindow::on_pushButton_clicked()
{
    // copy_if example

    bool is_positive(int i);

    vector<int> memberSearch = {};//add infor for members. This vector holds all the members
    vector<int> expiringMember (memberSearch.size());

    // copy only expiring members
    auto it = copy_if (memberSearch.begin(), memberSearch.end(), expiringMember.begin(),  is_positive);
    expiringMember.resize(distance(expiringMember.begin(),it));  // shrink container to new members

    cout << "Expiring members contains:";   // need to replace cout eventually
    for (int& x: expiringMember)
    {
     cout << ' ' << x;
     cout << '\n';
    }
}

bool is_positive(int i)
{
    return !(i<0);
>>>>>>> 43272280820e008d5101a297129f2adc1d0ff363
}
