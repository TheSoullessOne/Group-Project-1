#include "Headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>
#include <QFile>
#include <QStringList>
using namespace std;

enum PAGES{
    LOGIN_PAGE,         //0
    MAIN_MENU,          //1
    ADD_MENU,           //2
    DELETE,             //3
    REPORTS,            //4
    READ_FILE,          //5
    UPGRADE,            //6
    ADMIN_LOGIN,        //7
    SEARCH,             //8
    MEMBER_INFO,        //9
    ENTER_DELETE_INFO,  //10
    SEARCH_EXPIRED,     //11
    ADD_MEMBER          //12

};
enum REPORT_PAGES{
    MAIN_REPORT_PAGE,   //0
    FILTER_PAGE,        //1
    REPORT_DISPLAY_PAGE //2
};

//----------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->File_error_message_label->setHidden(true);
    if(!UpdateMembersFromFile("Texts\\warehouse shoppers.txt")){
        QMessageBox::critical(this, "Error with File", "Warehouse Shoppers did not load properly.\nPlease try again.");
    }
    if(!UpdateDataFromFile("Texts\\day1.txt"))   {
        QMessageBox::critical(this, "Error with File", "day1.txt did not load properly.\nPlease try again.");
    }
    if(!UpdateDataFromFile("Texts\\day2.txt"))   {
        QMessageBox::critical(this, "Error with File", "day2.txt did not load properly.\nPlease try again.");
    }
    if(!UpdateDataFromFile("Texts\\day3.txt"))   {
        QMessageBox::critical(this, "Error with File", "day3.txt did not load properly.\nPlease try again.");
    }
    if(!UpdateDataFromFile("Texts\\day4.txt"))   {
        QMessageBox::critical(this, "Error with File", "day4.txt did not load properly.\nPlease try again.");
    }
    if(!UpdateDataFromFile("Texts\\day5.txt"))   {
        QMessageBox::critical(this, "Error with File", "day5.txt did not load properly.\nPlease try again.");
    }


}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
    SaveToFile("Texts\\warehouse shoppers.txt");
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to add a new user
void MainWindow::on_Adduser_clicked()
{
    ui->pages->setCurrentIndex(ADD_MENU);
    //Here we call the function that makes new members
    //Take you to another menu to see what kind of member
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to delete a user or item
void MainWindow::on_deleteRec_clicked()
{
    ui->pages->setCurrentIndex(DELETE);
    //Link to another menu that will determine what the user
    //wants to delete, whether an item or list
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to upgrade a user
void MainWindow::on_upgrade_clicked()
{
    ui->pages->setCurrentIndex(UPGRADE);
    //Link the function that determines whether a user can upgrade
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to search different types of reports
void MainWindow::on_reportsSearch_clicked()
{
    ui->pages->setCurrentIndex(REPORTS);
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
    //Here we need to link to another menu that helps decide
    //what kind search they want to do
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to read in a file that has the 5 files of purchases for members
void MainWindow::on_readInFile_clicked()
{
    ui->pages->setCurrentIndex(READ_FILE);
    //Here we link a function that searched for the user so that
    //way it is stored in the correct member data

}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_search_line_edit_returnPressed()
{
    // copy_if example
    //ui->pages->setCurrentIndex(UPGRADE);


    //this vector will contain all of the members
    vector<member*> memberSearch;//add infor for members. This vector holds all the members
    for(int i = 0; i < myMembers.memberVec.size(); i++)
    {
        memberSearch.push_back(myMembers.memberVec[i]);
    }
    for(int j = 0; j < myMembers.execVec.size(); j++)
    {
        memberSearch.push_back(myMembers.execVec[j]);
    }
    //this vector will contain all of the expired members it is set to be the same size as the member search vector
    vector<member*> expiringMember (memberSearch.size());
    //this is the expiring month that we will be getting from the user
    QString tempMonth= ui->search_line_edit->text();
    int expiringMonth = tempMonth.toInt();
    //auto is for letting the compiler figure out the type. it saves typing, and in case you are going to change the return type.
    //instead of typing vector<member>::iterator auto does it for you
    //it means iterator and we use this in order to resize the expiringMember
    // copy only expiring members
    //this vector reads from beginning to end and enters the struct checkExperation in order to read it into expiringMember.
    auto it = copy_if (memberSearch.begin(), memberSearch.end(),
                       expiringMember.begin(), checkExperation(expiringMonth));
    expiringMember.resize(distance(expiringMember.begin(),it));  // shrink container to new members

    ui->Output_ExpiredMembers->setText("Expiring members contains:\n" );   // need to replace cout eventually
    //for loop is for showing the contains of expiringMember
    //this for loop looks confusin but all it is doing is looping over the vector.
    for (member* x: expiringMember)
    {
        ui->Output_ExpiredMembers->append(x->getName() +"\n");

    }

    //this for loop is made in order to tell the member the renewal fee.
    for(unsigned int i=0; i < expiringMember.size(); i++ )
    {
        if(expiringMember[i]->getType() == false)
        {
            ui->Output_ExpiredMembers->append(expiringMember[i]->getName() + " your renewal cost is $85.00");
        }
        else
        {
            ui->Output_ExpiredMembers->append(expiringMember[i]->getName() + " your renewal cost is $95.00");
        }
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
bool MainWindow::UpdateDataFromFile(QString fileName)   {

    // Creates an object of QFile type
    QFile inputFile(fileName.toStdString().c_str());

    // Opens the file if it exists and makes it read Only
    if(inputFile.open(QFile::ReadOnly)) {


        QString tempPriceAndAmt;
        QString tempPrice;
        QString tempAmt;
        QString tempName;
        QString tempDate;
        int tempId;
        item *tempItem;
        bool found;
        bool execBool;
        bool otherFound = false;

        // My textStream variables "fstream"
        QTextStream fin(&inputFile);

        // While !eof
        while(!fin.atEnd())  {
            found = false;
            tempDate = fin.readLine();
            tempId = fin.readLine().toInt();
            tempName = fin.readLine();
            tempPriceAndAmt = fin.readLine();

            // A string List can seperate QString into an array and the first parameter is what
            // Defines where to seperate it. So in the day1-5 text files there are tabs between
            // The Item price and amount bought
            QStringList strList = tempPriceAndAmt.split('\t', QString::SkipEmptyParts);
            tempPrice = strList[0];
            tempAmt = strList[1];

            // i is just an incrementer to access the index
            int i = 0;

            // While loop to search through the executive Vector
            while(!found && i < myMembers.execVec.size())   {
                if(myMembers.execVec[i]->getNum() == tempId)    {
                    found = true;
                    execBool = true;
                }
                else
                {
                    ++i;
                }
            }
            // if the item wasnt found in the member Vec it resets i
            if(!found)  {
                i = 0;
            }
            // Searches through the member vector
            while(!found && i < myMembers.memberVec.size())   {
                if(tempId == myMembers.memberVec[i]->getNum())  {
                    found = true;
                    execBool = false;
                }
                else    {
                    ++i;
                }
            }
            // Is it an executive? If so...
            if(execBool) {
                tempItem = new item;
                tempItem->setShopDate(tempDate.left(2).toInt(),
                                      tempDate.mid(3,2).toInt(),
                                      tempDate.right(4).toInt());
                tempItem->setItemName(tempName);
                tempItem->setItemPrice(tempPrice.toDouble());
                tempItem->setAmtBought(tempAmt.toDouble());
                myMembers.execVec[i]->setReceipt(tempItem);
                myMembers.execVec[i]->setTotal(this->myMembers.execVec[i]->getTotal() + (tempPrice.toDouble() * tempAmt.toDouble()));
                myMembers.execVec[i]->setRebate(this->myMembers.execVec[i]->getRebate() + (0.0325 * tempPrice.toDouble() * tempAmt.toDouble()));
            }
            else    // if not an executive do this...
            {
                tempItem = new item;
                tempItem->setShopDate(tempDate.left(2).toInt(),
                                      tempDate.mid(3,2).toInt(),
                                      tempDate.right(4).toInt());
                tempItem->setItemName(tempName);
                tempItem->setItemPrice(tempPrice.toDouble());
                tempItem->setAmtBought(tempAmt.toDouble());
                myMembers.memberVec[i]->setReceipt(tempItem);
                myMembers.memberVec[i]->setTotal(this->myMembers.memberVec[i]->getTotal() + (tempPrice.toDouble() * tempAmt.toDouble()));
            }
            // This for loop checks to see if the item name is already in the ourStock vector.
            // If it isn't...
            for(int j = 0; j < myMembers.ourStock.size(); ++j)  {
                if(tempName == myMembers.ourStock[j]->getItemName())    {
                    otherFound = true;
                }
            }
            // Then it will create the item and push it to the back fo the vector
            if(!otherFound)  {
                myMembers.ourStock.push_back(tempItem);
            }
        }
        // it returns true because the function is called in an if-statement
        // Pretty much saying, it returns true if the function worked
        if(fileName != "Texts\\warehouse shoppers.txt" &&
           fileName != "Texts\\day1.txt" &&
           fileName != "Texts\\day2.txt" &&
           fileName != "Texts\\day3.txt" &&
           fileName != "Texts\\day4.txt" &&
           fileName != "Texts\\day5.txt")
        QMessageBox::information(this, "It Worked!", "The file has successfully loaded!");
        return true;
    }
    // Returns false if the function did not work, meaning the file didnt exist
    return false;
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
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

            memberIds.push_back(tempId);

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
                myMembers.execVec[index]->setType(true);
                myMembers.execVec[index]->setTotal(0);
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
                myMembers.memberVec[index]->setTotal(0);
                myMembers.memberVec[index]->setType(false);
            }
        }
        return true;
    }
    return false;
}


//----------------------------------------------------------------------
void MainWindow::SaveToFile(QString fileName)   {
    // Creates our QFile variable
    QFile outputFile(fileName);
    // If the file exists and is able to written to:
    if(outputFile.open(QFile::WriteOnly))   {
        // Creates our "fstream" variable
        QTextStream fout(&outputFile);

        // Outputs the executives first
        for(int i = 0; i < myMembers.execVec.size(); ++i)   {
            fout << myMembers.execVec[i]->getName() << endl;
            fout << myMembers.execVec[i]->getNum() << endl;
            fout << "Executive" << endl;
            fout << myMembers.execVec[i]->getExpiry().printDate() << endl;
        }
        // Then it outputs the members
        for(int j = 0; j < myMembers.memberVec.size(); ++j) {
            fout << myMembers.memberVec[j]->getName() << endl;
            fout << myMembers.memberVec[j]->getNum() << endl;
            fout << "Regular" << endl;
            fout << myMembers.memberVec[j]->getExpiry().printDate();
            if(j != myMembers.memberVec.size() - 1) {
                fout << endl;
            }
        }
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//void MainWindow::on_readInButton_clicked()
//{
//    //This is for the first way of reading in file
//}
//----------------------------------------------------------------------


//----------------------------------------------------------------------DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY
void MainWindow::on_purchases_rep_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(FILTER_PAGE); //takes you to page to input the string
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY
void MainWindow::on_sales_rep_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(FILTER_PAGE);//takes you to page to input the string
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY
void MainWindow::on_quantity_rep_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(FILTER_PAGE);//takes you to page to input the string
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY
void MainWindow::on_rebate_rep_clicked()
{
    ui->pages->setCurrentIndex(UPGRADE);//takes you to page to input the string
}
//----------------------------------------------------------------------DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY

//----------------------------------------------------------------------
void MainWindow::on_expiring_rep_clicked()
{
    ui->pages->setCurrentIndex(SEARCH_EXPIRED);//takes you to page to input the string
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------****************************************************************************************DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY
void MainWindow::on_create_report_button_clicked()
{


//    ui->REPORTS_PAGES->setCurrentIndex(REPORT_DISPLAY_PAGE);

//    QCheckBox id_search       = ui->ID_CB->isChecked();
//    QCheckBox userName_search = ui->USERNAME_CB->isChecked();
//    QCheckBox date_search     = ui->DATE_CB->isChecked();
//    QCheckBox itemName_search = ui->PRODUCT_CB->isChecked();



//    QString search_string = ui->SEARCH_INPUT_LINE->text();

//    if(id_search ){
//        //searching by id

//    }else if(userName_search == true){
//        //searching by userName

//    }else if(date_search == true){
//        //searching by date

//    }else {
//        //searching by itemName
//    }




    //this vector will contain all of the members
    vector<member*> memberSearch;//add infor for members. This vector holds all the members
    for(int i = 0; i < myMembers.memberVec.size(); i++)
    {
        memberSearch.push_back(myMembers.memberVec[i]);
    }
    for(int j = 0; j < myMembers.execVec.size(); j++)
    {
        memberSearch.push_back(myMembers.execVec[j]);
    }
    //this vector will contain all of the expired members it is set to be the same size as the member search vector
    vector<member*> expiringMember (memberSearch.size());

    //this is the expiring month that we will be getting from the user
    QString tempMonth= ui->search_line_edit->text();
    int expiringMonth = tempMonth.toInt();

    auto it = copy_if (memberSearch.begin(), memberSearch.end(),
                       expiringMember.begin(), checkExperation(expiringMonth));

    expiringMember.resize(distance(expiringMember.begin(),it));  // shrink container to new members

    ui->Output_ExpiredMembers->setText("Expiring members contains:\n" );   // need to replace cout eventually
    //for loop is for showing the contains of expiringMember
    //this for loop looks confusin but all it is doing is looping over the vector.
    for (member* x: expiringMember)
    {
        ui->Output_ExpiredMembers->append(x->getName() +"\n");

    }

}
//----------------------------------------------------------------------*******************************************************************************************DESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERYDESSERY


//----------------------------------------------------------------------CARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAA
void MainWindow::on_delete_user_clicked()
{
    ui->pages->setCurrentIndex(MEMBER_INFO);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------CARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAA
void MainWindow::on_delete_item_clicked()
{
    ui->pages->setCurrentIndex(MEMBER_INFO);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------CARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAAVCARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAA
void MainWindow::on_add_user_clicked()
{
    ui->pages->setCurrentIndex(SEARCH);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_add_purchase_clicked()
{
    ui->pages->setCurrentIndex(SEARCH);
}
//----------------------------------------------------------------------CARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAACARISSAAAAAACARISSSAAA


//----------------------------------------------------------------------
void MainWindow::on_enterPassword_returnPressed()
{
    // Stores the info that the user passed into the user Id line
    QString username = ui->enterUserName->text();
    // Converts the string to an int to be able to be searched
    int tempId = username.toInt();
    // Stores the info that the user passed into the password line
    QString password = ui->enterPassword->text();
    // Creates a found boolean and sets it to false
    bool found = false;
    bool deleted = false;
    bool exec = false;
    int  index = 0;
    QString date;
    QString name;
    QString typeString;
    int num;
    double total;

    ui->Member_Info_Receipt->clear();
    ui->Member_Info_Name->clear();
    ui->Member_Info_Id->clear();
    ui->Member_Info_Spent->clear();
    ui->Member_Info_Expiration->clear();
    ui->Member_Info_Type->clear();

    while(!exec && index < myMembers.execVec.size())    {
        if(tempId == myMembers.execVec[index]->getNum())  {
            exec = true;
        }
        else
        {
            ++index;
        }
    }
    if(!exec)   {
        index = 0;
        for(int i = 0; i < myMembers.memberVec.size(); ++i) {
            if(tempId == myMembers.memberVec[i]->getNum())  {
                index = i;
            }
        }
    }


    // checks to see if the user was found
    for(int i = 0; i < memberIds.size(); ++i)   {
        if(tempId == memberIds[i])  {
            found = true;
            index = i;
        }
    }

    if(!exec)   {
        index -= myMembers.execVec.size();
    }
    // checks to see if the user has been deleted
    for(int i = 0; i < myMembers.deletedMemberIds.size(); ++i)   {
        if(tempId == myMembers.deletedMemberIds[i]) {
            deleted = true;
        }
    }

    // if user is NOT deleted, and FOUND, and password is "member, change the displays
    // and change page to member info page
    if(!deleted && found && password == "member")  {
        ui->Member_Info_Receipt->clear();
        ui->Member_Info_Name->clear();
        ui->Member_Info_Id->clear();
        ui->Member_Info_Spent->clear();
        ui->Member_Info_Expiration->clear();
        ui->Member_Info_Type->clear();
        // Jump to member info page if password and id are correct
        if(exec)    {
            // Sets predefined variables
            name  = myMembers.execVec[index]->getName();
            num   = myMembers.execVec[index]->getNum();
            total = myMembers.execVec[index]->getTotal();
            date  = myMembers.execVec[index]->getExpiry().printDate();
            typeString = "Executive Member";

            // This sets the receipt display browser, i first hardcode the first line, then append all the others
   if(myMembers.execVec[index]->getReceipt().size() > 0){
                ui->Member_Info_Receipt->setText(myMembers.execVec[index]->getReceipt()[0]->getShopDate().printDate());
                for(int i = 0; i < myMembers.execVec[index]->getReceipt().size(); ++i)  {
                    ui->Member_Info_Receipt->append(myMembers.execVec[index]->getReceipt()[i]->getItemName());
                    ui->Member_Info_Receipt->append( QString::number(myMembers.execVec[index]->getReceipt()[i]->getAmtBought())
                                                     + " @ " + "$" +QString::number(myMembers.execVec[index]->getReceipt()[i]->getItemPrice())
                                                     + " ea. ");\
                    ui->Member_Info_Receipt->append("\n");
                    if(i < myMembers.execVec[index]->getReceipt().size() - 1)
                        ui->Member_Info_Receipt->append(myMembers.execVec[index]->getReceipt()[i + 1]->getShopDate().printDate());

                }   // end-for(int i
            }
            else    {
                ui->Member_Info_Receipt->setText("No Recent Purchases");
            }
        }
        else
        {
            // Sets predefined variables
            name  = myMembers.memberVec[index]->getName();
            num   = myMembers.memberVec[index]->getNum();
            total = myMembers.memberVec[index]->getTotal();
            date  = myMembers.memberVec[index]->getExpiry().printDate();
            typeString = "Regular Member";

            // This sets the receipt display browser, i first hardcode the first line, then append all the others
            if(myMembers.execVec[index]->getReceipt().size() > 0){
                ui->Member_Info_Receipt->setText(myMembers.memberVec[index]->getReceipt()[0]->getShopDate().printDate());
                for(int i = 0; i < myMembers.memberVec[index]->getReceipt().size(); ++i)  {
                    ui->Member_Info_Receipt->append(myMembers.memberVec[index]->getReceipt()[i]->getItemName());
                    ui->Member_Info_Receipt->append( QString::number(myMembers.memberVec[index]->getReceipt()[i]->getAmtBought())
                                                     + " @ " + "$" +QString::number(myMembers.memberVec[index]->getReceipt()[i]->getItemPrice())
                                                     + " ea. ");\
                    ui->Member_Info_Receipt->append("\n");
                    if(i < myMembers.memberVec[index]->getReceipt().size() - 1)
                        ui->Member_Info_Receipt->append(myMembers.memberVec[index]->getReceipt()[i + 1]->getShopDate().printDate());

                }   // end-for(int i
            }
            else    {
                ui->Member_Info_Receipt->setText("No Recent Purchases");
            }
        }
        // Sets the remainder of the display browsers with values received
        ui->Member_Info_Name->setText(name);
        ui->Member_Info_Id->setText(QString::number(num));
        ui->Member_Info_Spent->setText(QString::number(total));
        ui->Member_Info_Expiration->setText(date);
        ui->Member_Info_Type->setText(typeString);

        // Changes the page to member info page and resets the lines the user typed in info to login
        ui->pages->setCurrentIndex(MEMBER_INFO);
        ui->enterUserName->clear();
        ui->enterPassword->clear();
    }
    // If the member is deleted, clear the member info browsers to not receive a runtime error
    // And then displays error
    else if(deleted)
    {
        ui->Member_Info_Receipt->clear();
        ui->Member_Info_Name->clear();
        ui->Member_Info_Id->clear();
        ui->Member_Info_Spent->clear();
        ui->Member_Info_Expiration->clear();
        ui->Member_Info_Type->clear();
        QMessageBox::critical(this, "User Deleted", "That user has been deleted.");
    }
    else
    {
        // If the password is incorrect, clear the member info browsers to not receive a runtime error
        // And then displays error
        ui->Member_Info_Receipt->clear();
        ui->Member_Info_Name->clear();
        ui->Member_Info_Id->clear();
        ui->Member_Info_Spent->clear();
        ui->Member_Info_Expiration->clear();
        ui->Member_Info_Type->clear();
        QMessageBox::critical(this, "Login Error", "Incorrect Password");
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_Admin_Login_Button_clicked()
{
    // go to admin login page to get to menu choices
    ui->pages->setCurrentIndex(ADMIN_LOGIN);
    ui->enterUserName->clear();
    ui->enterPassword->clear();
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_admin_login_clicked()
{
    ui->pages->setCurrentIndex(LOGIN_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_Admin_Password_line_edit_returnPressed()
{
    QString username = ui->Admin_Username_line_edit->text();
    QString password = ui->Admin_Password_line_edit->text();

    username = username.toLower();
    password = password.toLower();

    if(username == "admin"  &&
            password == "password")  {
        ui->pages->setCurrentIndex(MAIN_MENU);
        ui->Admin_Username_line_edit->clear();
        ui->Admin_Password_line_edit->clear();
    }
    else
    {
        // Jump to member info page if password and id are correct
        QMessageBox::critical(this, "Login Error", "Incorrect Password Or Username");
    }
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
void MainWindow::on_read_file_line_edit_returnPressed()
{
    ui->File_error_message_label->setHidden(true);

    QString fileName = ui->read_file_line_edit->text();

    if(!fileName.endsWith(".txt"))
        fileName += ".txt";

    fileName = "Texts\\" + fileName;

    if(!UpdateDataFromFile(fileName))  {
        // Error message prompt for input again
        ui->File_error_message_label->setHidden(false);
    }
    ui->read_file_line_edit->clear();
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
bool MainWindow::deleteItemOrName(QString searchItem)  {
    bool found = false;
    int i = 0;

    while(!found && i < myMembers.execVec.size())    {
        if(searchItem == myMembers.execVec[i]->getName())   {
            found = true;
            myMembers.deletedMemberIds.push_back(this->myMembers.execVec[i]->getNum());
        }
        else
        {
            ++i;
        }
    }
    if(!found)  {
        i = 0;
    }
    while(!found && i < myMembers.memberVec.size()) {
        if(searchItem == myMembers.memberVec[i]->getName())    {
            found = true;
            myMembers.deletedMemberIds.push_back(this->myMembers.memberVec[i]->getNum());
        }
        else
        {
            ++i;
        }
    }
    if(!found)  {
        i = 0;
    }
    while(!found && i < myMembers.ourStock.size())    {
        if(searchItem == myMembers.ourStock[i]->getItemName()) {
            found == true;
            myMembers.deletedItemNames.push_back(myMembers.ourStock[i]->getItemName());
        }
        else
        {
            ++i;
        }
    }
    if(!found)  {
        return found;
    }
    return true;
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_searchByMonth_clicked()
{
    ui->pages->setCurrentIndex(SEARCH_EXPIRED);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_lineEdit_2_returnPressed()
{

}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_Delete_line_edit_returnPressed()
{
    QString searchItem = ui->Delete_line_edit->text();
    if(!deleteItemOrName(searchItem))    {
        QMessageBox::critical(this, "Name not found",
                              "I'm sorry, that name was not found.");
    }
    else    {
        ui->Delete_line_edit->clear();
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_Member_info_back_button_clicked()
{
    ui->pages->setCurrentIndex(LOGIN_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_searchButtonBrians_clicked()
{
    ui->pages->setCurrentIndex(SEARCH);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_Search_back_button_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_expiredMembers_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------

void MainWindow::on_backButton_addMember_clicked()
{
    ui->pages->setCurrentIndex(ADD_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------

void MainWindow::on_add_member_button_clicked()
{
    ui->pages->setCurrentIndex(ADD_MEMBER);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------

void MainWindow::on_backButton_deleteInput_clicked()
{
    ui->pages->setCurrentIndex(DELETE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_reports_3_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------

void MainWindow::on_backButton_reports_2_clicked()
{

    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_addmen_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_delete_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_reports_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_readfile_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_upgrade_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_backButton_search_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_back_to_login_clicked()
{
    ui->pages->setCurrentIndex(LOGIN_PAGE);
}
