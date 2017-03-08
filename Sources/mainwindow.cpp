#include "Headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>
#include <QFile>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateMembersFromFile("Texts\\warehouse shoppers.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Function to add a new user
void MainWindow::on_Adduser_clicked()
{
    ui->pages->setCurrentIndex(2);
    //Here we call the function that makes new members
    //Take you to another menu to see what kind of member
}

//Function to delete a user or item
void MainWindow::on_deleteRec_clicked()
{
    ui->pages->setCurrentIndex(3);
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
    ui->pages->setCurrentIndex(4);
    //Here we need to link to another menu that helps decide
    //what kind search they want to do
}

//Function to read in a file that has the 5 files of purchases for members
void MainWindow::on_readInFile_clicked()
{
    ui->pages->setCurrentIndex(5);
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

    qDebug() << "Expiring members contains:";   // need to replace cout eventually
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

void MainWindow::UpdateDataFromFile(QString fileName)   {
    QString tempDate;
    QString itemName;
    int tempId = 0;     // SEARCH FUNCTION
    double itemPrice = 0;
    int itemQuan = 0;

    QFile inputFile(fileName.toStdString().c_str());

    QTextStream fin(&inputFile);

    tempDate = fin.readLine();
    fin.readLine(tempId);
    itemName = fin.readLine();
    fin.readLine(itemPrice);
    fin.readLine(itemQuan);
}

bool MainWindow::UpdateMembersFromFile(QString fileName)    {
    // Creates an object of QFile type
    QFile inputFile(fileName.toStdString().c_str());
    // Opens the file if it exists and makes it read Only
    if(inputFile.open(QFile::ReadOnly)) {

        QString tempRank;
        QString tempName;
        QString tempDate;
        int tempId;
        int index;
        executive *tempExec;
        member *tempMem;

        // My textStream variables "fstream"
        QTextStream fin(&inputFile);

        // While !eof
        while(!fin.atEnd())  {

            // Reads in the 4 lines that belong to 1 member
            tempName = fin.readLine();
            tempId = fin.readLine().toInt();
            tempRank = fin.readLine();
            tempDate = fin.readLine();

            // Creates exec mem, and initializes
            if(tempRank == "Executive") {
                tempExec = new executive;                       // Creates new exec
                myMembers.execVec.push_back(tempExec);          // Pushes it to the back of the vector
                index = myMembers.execVec.size() - 1;
                myMembers.execVec[index]->setName(tempName);    // Sets the name of that obj
                myMembers.execVec[index]->setNum(tempId);       // Sets the id of that obj
                myMembers.execVec[index]->setExpiry(tempDate.mid(3,2).toInt(),
                                                    tempDate.left(2).toInt(),
                                                    tempDate.right(4).toInt());
                myMembers.execVec[index]->setAnnual(95);        // Sets the annual due to 95
                myMembers.execVec[index]->setRebate(0);         // Sets rebate to 0 just for it to start
            }
            else    // creates member mem and initializes
            {
                tempMem = new member;                           // Creates new member
                myMembers.memberVec.push_back(tempMem);         // Pushes it to the back of the vector
                index = myMembers.memberVec.size() - 1;
                myMembers.memberVec[index]->setName(tempName);  // Sets the member's name
                myMembers.memberVec[index]->setNum(tempId);     // Sets the member's ID
                myMembers.memberVec[index]->setExpiry(tempDate.mid(3,2).toInt(),
                                                      tempDate.left(2).toInt(),
                                                      tempDate.right(4).toInt());
                myMembers.memberVec[index]->setAnnual(85);      // Sets the annual dues to 85
            }
        }
        return true;
    }
    return false;
}

void MainWindow::on_backButton_addmen_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::on_backButton_delete_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::on_backButton_reports_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::on_backButton_readfile_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::on_backButton_upgrade_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::on_backButton_search_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString fileName = ui->lineEdit->text();

    if(!fileName.endsWith(".txt"))
        fileName += ".txt";

    fileName = "Texts\\" + fileName;

    if(UpdateMembersFromFile(fileName))  {
        //Change the page, let user know it worked
        qDebug()    << "success";
    }
    else
    {
        // Error message prompt for input again
        qDebug()    << "Failure.";
    }


}


void MainWindow::SaveToFile(QString)   {
    QFile outputFile("Texts\test.txt");
    if(outputFile.open(QFile::WriteOnly))   {

    }
}

void MainWindow::on_readInButton_clicked()
{
    //This is for the first way of readding in file
}

void MainWindow::on_purchases_rep_clicked()
{
    ui->pages->setCurrentIndex(7); //takes you to page to input the string
}

void MainWindow::on_sales_rep_clicked()
{
    ui->pages->setCurrentIndex(7);//takes you to page to input the string
}

void MainWindow::on_quantity_rep_clicked()
{
    ui->pages->setCurrentIndex(7);//takes you to page to input the string
}

void MainWindow::on_rebate_rep_clicked()
{
    ui->pages->setCurrentIndex(7);//takes you to page to input the string
}

void MainWindow::on_expiring_rep_clicked()
{
    ui->pages->setCurrentIndex(7);//takes you to page to input the string
}

void MainWindow::on_delete_user_clicked()
{
    ui->pages->setCurrentIndex(9);
}

void MainWindow::on_delete_item_clicked()
{
    ui->pages->setCurrentIndex(9);
}

void MainWindow::on_add_user_clicked()
{
    ui->pages->setCurrentIndex(8);
}

void MainWindow::on_add_purchase_clicked()
{
    ui->pages->setCurrentIndex(8);
}


void MainWindow::on_enterPassword_returnPressed()
{
    QString username = ui->enterUserName->text();
    int tempId = username.toInt();
    QString password = ui->enterPassword->text();
    bool found = false;

    for(int i = 0; i < myMembers.execVec.size(); ++i)   {
        memberIds.push_back(myMembers.execVec[i]->getNum());
    }
    for(int j = 0; j < myMembers.memberVec.size(); ++j) {
        memberIds.push_back(myMembers.memberVec[j]->getNum());
    }

    for(int i = 0; i < memberIds.size(); ++i)   {
        if(tempId == memberIds[i])  {
            found = true;
        }
    }

    if(password != "member")  {
        QMessageBox::critical(this, "Login Error", "Incorrect Password");
    }
    else if(found)
    {
        // Jump to member info page if password and id are correct
        ui->pages->setCurrentIndex(9);
    }
}


void MainWindow::on_back_to_login_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_Admin_Login_Button_clicked()
{
    // go to admin login page to get to menu choices
    ui->pages->setCurrentIndex(7);
}

void MainWindow::on_backButton_admin_login_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_Admin_Password_line_edit_returnPressed()
{
    QString username = ui->Admin_Username_line_edit->text();
    QString password = ui->Admin_Password_line_edit->text();

    username = username.toLower();
    password = password.toLower();

    if(username == "admin"  &&
       password == "password")  {
        ui->pages->setCurrentIndex(1);
    }
    else
    {
        // Jump to member info page if password and id are correct
        QMessageBox::critical(this, "Login Error", "Incorrect Password Or Username");
    }
}

void MainWindow::on_Member_info_back_button_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_searchButtonBrians_clicked()
{
    ui->pages->setCurrentIndex(8);
}

void MainWindow::on_Search_back_button_clicked()
{
    ui->pages->setCurrentIndex(1);
}
