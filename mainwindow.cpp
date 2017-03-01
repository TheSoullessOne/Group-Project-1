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


void MainWindow::on_pushButton_clicked()
{
    // copy_if example

    bool is_positive(int i);

    vector<int> memberSearch = {};//add infor for members.
    vector<int> expiringMember (memberSearch.size());

    // copy only expiring members
    auto it = copy_if (memberSearch.begin(), memberSearch.end(), expiringMember.begin(),  is_positive);
    expiringMember.resize(distance(expiringMember.begin(),it));  // shrink container to new members

    cout << "Expiring members contains:";
    for (int& x: expiringMember)
    {
     cout << ' ' << x;
     cout << '\n';
    }


}

bool is_positive(int i)
{
    return !(i<0);
}
