#include "Headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>
#include <QDebug>
#include <algorithm>
#include <QVector>
#include <fstream>
#include <QFile>
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

//Function to add a new user
void MainWindow::on_Adduser_clicked()
{
    ui->pages->setCurrentIndex(1);
    //Here we call the function that makes new members
    //Take you to another menu to see what kind of member
}

//Function to delete a user or item
void MainWindow::on_deleteRec_clicked()
{
    ui->pages->setCurrentIndex(2);
    //Link to another menu that will determine what the user
    //wants to delete, whether an item or list
}

//Function to upgrade a user
void MainWindow::on_upgrade_clicked()
{
      ui->pages->setCurrentIndex(6);
    //Link the function that determines whether a user can upgrade
}

//Function to search different types of reports
void MainWindow::on_reportsSearch_clicked()
{
      ui->pages->setCurrentIndex(3);
    //Here we need to link to another menu that helps decide
    //what kind search they want to do
}

//Function to read in a file that has the 5 files of purchases for members
void MainWindow::on_readInFile_clicked()
{
      ui->pages->setCurrentIndex(4);
    //Here we link a function that searched for the user so that
    //way it is stored in the correct member data

}

void MainWindow::on_backButton_6_clicked()
{

}

void MainWindow::on_search_clicked()
{
    // copy_if example
    ui->pages->setCurrentIndex(6);


    //this vector will contain all of the members
    vector<member> memberSearch = {};//add infor for members. This vector holds all the members
    //this vector will contain all of the expired members it is set to be the same size as the member search vector
    vector<member> expiringMember (memberSearch.size());
    //this is the expiring month that we will be getting from the user
    int expiringMonth;

    //auto is for letting the compiler figure out the type. it saves typing, and in case you are going to change the return type.
    //instead of typing vector<member>::iterator auto does it for you
    //it means iterator and we use this in order to resize the expiringMember
    // copy only expiring members
    //this vector reads from beginning to end and enters the struct checkExperation in order to read it into expiringMember.
    auto it = copy_if (memberSearch.begin(), memberSearch.end(),
                       expiringMember.begin(), checkExperation(expiringMonth));
    expiringMember.resize(distance(expiringMember.begin(),it));  // shrink container to new members

    cout << "Expiring members contains:";   // need to replace cout eventually
    //for loop is for showing the contains of expiringMember
    //this for loop looks confusin but all it is doing is looping over the vector.
    for (member x: expiringMember)
    {
     qDebug() << ' ' << x.getName() << endl;
    }

    //this for loop is made in order to tell the member the renewal fee.
    for(int i=0; i < expiringMember.size(); i++ )
    {
        if(expiringMember[i].getType() == false)
        {
          qDebug() <<expiringMember[i].getName() << " your renewal cost is $85.00";
        }
        else
        {
          qDebug() <<expiringMember[i].getName() << " your renewal cost is $95.00";
        }

    }
}

void UpdateDataFromFile(QString fileName, memberStruct myMembers)   {
    ifstream fin;

    fin.open(fileName.toStdString().c_str());



    fin.close();
}

void UpdateMembersFromFile(QString fileName, memberStruct myMembers)    {
    QString tempRank;
    QString tempName;
    int tempId = 0;
    executive *tempExec;
    member *tempMem;

    QFile inputFile(fileName.toStdString().c_str());

    QTextStream fin(&inputFile);

    tempName = fin.readLine();

    fin.readLine(tempId);

    tempRank = fin.readLine();

    if(tempRank == "Executive") {
        tempExec = new executive;
        myMembers.execVec.push_back(tempExec);
        myMembers.execVec[0]->setName(tempName);
        myMembers.execVec[0]->setNum(tempId);
        myMembers.execVec[0]->setRebate(0);

    }
    else    {
        tempMem = new member;
        myMembers.memberVec.push_back(tempMem);
        myMembers.memberVec[0]->setName(tempName);
        myMembers.memberVec[0]->setNum(tempId);
    }


}

void MainWindow::on_backButton_addmen_clicked()
{
 ui->pages->setCurrentIndex(0);
}

void MainWindow::on_backButton_delete_clicked()
{
     ui->pages->setCurrentIndex(0);
}

void MainWindow::on_backButton_reports_clicked()
{
     ui->pages->setCurrentIndex(0);
}

void MainWindow::on_backButton_readfile_clicked()
{
     ui->pages->setCurrentIndex(0);
}

void MainWindow::on_backButton_upgrade_clicked()
{
     ui->pages->setCurrentIndex(0);
}

void MainWindow::on_backButton_search_clicked()
{
     ui->pages->setCurrentIndex(0);
}
