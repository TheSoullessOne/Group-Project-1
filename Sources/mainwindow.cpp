#include "Headers\mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <algorithm>
#include <QFile>
#include <QList>
#include <QSortFilterProxyModel>
#include <QStringList>
#include <QStandardItemModel>
#include "Headers/salesreport.h"
#include <QtGlobal>
#include <time.h>
#include <QDate>
using namespace std;

/**
 * @brief The PAGES enum
 */
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
    ADD_MEMBER,         //12
    ADD_ITEM            //13

};
/**
 * @brief The REPORT_PAGES enum
 */
enum REPORT_PAGES{
    MAIN_REPORT_PAGE,     //0
    PRODUCT_REPORT_PAGE,  //1
    SALES_REPORT,         //2
    QUANTITY_REPORT       //3
};

//----------------------------------------------------------------------
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
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
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
    SaveToFile("Texts\\warehouse shoppers.txt");
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to add a new user
/**
 * @brief MainWindow::on_Adduser_clicked
 */
void MainWindow::on_Adduser_clicked()
{
    ui->pages->setCurrentIndex(ADD_MENU);
    // Here we call the function that makes new members
    // Take you to another menu to see what kind of member
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to delete a user or item
/**
 * @brief MainWindow::on_deleteRec_clicked
 */
void MainWindow::on_deleteRec_clicked()
{
    ui->pages->setCurrentIndex(DELETE);
    // Link to another menu that will determine what the user
    // wants to delete, whether an item or list
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to upgrade a user
/**
 * @brief MainWindow::on_upgrade_clicked
 */
void MainWindow::on_upgrade_clicked()
{
    ui->pages->setCurrentIndex(UPGRADE);
    //Link the function that determines whether a user can upgrade
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to search different types of reports
/**
 * @brief MainWindow::on_reportsSearch_clicked
 */
void MainWindow::on_reportsSearch_clicked()
{
    ui->pages->setCurrentIndex(REPORTS);
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
    // Here we need to link to another menu that helps decide
    // what kind search they want to do
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
//Function to read in a file that has the 5 files of purchases for members
/**
 * @brief MainWindow::on_readInFile_clicked
 */
void MainWindow::on_readInFile_clicked()
{
    ui->pages->setCurrentIndex(READ_FILE);
    // Here we link a function that searched for the user so that
    // way it is stored in the correct member data

}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_search_line_edit_returnPressed
 */
void MainWindow::on_search_line_edit_returnPressed()
{
    // copy_if example
    //ui->pages->setCurrentIndex(UPGRADE);


    //this vector will contain all of the members
    vector<member*> memberSearch;//add info for members

    for(int i = 0; i < myMembers.memberVec.size(); i++)
    {
        memberSearch.push_back(myMembers.memberVec[i]);
    }
    for(int j = 0; j < myMembers.execVec.size(); j++)
    {
        memberSearch.push_back(myMembers.execVec[j]);
    }

    //this vector will contain all of the expired members it is set to
    //be the same size as the member search vector
    vector<member*> expiringMember (memberSearch.size());

    //this is the expiring month that we will be getting from the user
    QString tempMonth= ui->search_line_edit->text();
    int expiringMonth = tempMonth.toInt();

    //auto is for letting the compiler figure out the type. it saves typing,
    //and in case you are going to change the return type.
    //instead of typing vector<member>::iterator auto does it for you
    //it means iterator and we use this in order to resize the expiringMember
    // copy only expiring members
    //this vector reads from beginning to end and enters the struct checkExperation
    //in order to read it into expiringMember.
    auto it = copy_if (memberSearch.begin(), memberSearch.end(),
                       expiringMember.begin(), checkExperation(expiringMonth));

    // shrink container to new members
    expiringMember.resize(distance(expiringMember.begin(),it));

    // need to replace cout eventually
    ui->Output_ExpiredMembers->setText("Expiring members contains:\n" );

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
            ui->Output_ExpiredMembers->append(expiringMember[i]->getName()
                                           + " your renewal cost is $85.00");
        }
        else
        {
            ui->Output_ExpiredMembers->append(expiringMember[i]->getName()
                                           + " your renewal cost is $95.00");
        }
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::UpdateDataFromFile
 * @param fileName
 * @return
 */
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
                myMembers.execVec[i]->setTotal(this->myMembers.execVec[i]->getTotal()
                                            + (tempPrice.toDouble() * tempAmt.toDouble()));
                myMembers.execVec[i]->setRebate(this->myMembers.execVec[i]->getRebate()
                                            + (0.0325 * tempPrice.toDouble() * tempAmt.toDouble()));
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
                myMembers.memberVec[i]->setTotal(this->myMembers.memberVec[i]->getTotal()
                                              + (tempPrice.toDouble() * tempAmt.toDouble()));
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
                if(execBool)    {
                    myMembers.sales.push_back(new salesReport(tempItem, myMembers.execVec[i],
                                                              tempItem->getItemPrice(),
                                                              tempItem->getShopDate()));
                }
                else
                {
                    myMembers.sales.push_back(new salesReport(tempItem, myMembers.memberVec[i],
                                                              tempItem->getItemPrice(),
                                                              tempItem->getShopDate()));
                }
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
/**
 * @brief MainWindow::UpdateMembersFromFile
 * @param fileName
 * @return
 */
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
            tempId   = fin.readLine().toInt();
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
        std::sort(memberIds.begin(), memberIds.end());
        return true;
    }
    return false;
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::SaveToFile
 * @param fileName
 */
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
/**
 * @brief MainWindow::on_purchases_rep_clicked
 */
void MainWindow::on_purchases_rep_clicked()
{
    ui->pages->setCurrentIndex(REPORTS);
    ui->REPORTS_PAGES->setCurrentIndex(PRODUCT_REPORT_PAGE);
    ui->productReportDisplay->setText("DISPLAYING PURCHASE REPORT SORTED BY MEMBER ID");


    bool exec;
    bool found = false;
    int index =0;

    //This will sort the member id vector from greatest to smallest
    std::sort(memberIds.begin(),memberIds.end());

    // This for loop will keep track of all of the members and make sure we
    //don't go out of searching bounds
    for(int idIndex = 0; idIndex < memberIds.size(); ++idIndex) {

        ui->productReportDisplay->append("\n\n"); //Just outputs some empty lines

        int i = 0;     //sets the index counter to 0
        found = false; //sets the bool to false
        index = 0;     //sets index that will be used to store the index for
                       //the current member id

        //This loop will search for an ID match in the regular member vector
        while(!found && i < myMembers.memberVec.size()){
            if(memberIds[idIndex] == myMembers.memberVec[i]->getNum()){
                found = true;
                index = i;
                exec = false;
            }
            else {
                ++i;
            }
        }
        if(!found)  {
            i = 0;
        }
        //This loop will search for an ID match in the executive member vector
        while(!found && i < myMembers.execVec.size())   {
            if(memberIds[idIndex] == myMembers.execVec[i]->getNum()){
                found = true;
                index = i;
                exec = true;
            }
            else{
                ++i;
            }
        }
        // So these if -statments will execute depending on the value of the exec bool
        // These loops will take care of displaying the data to window
        if(exec){
            ui->productReportDisplay->append(QString::number(memberIds[idIndex])
                                  + " - " + myMembers.execVec[index]->getName());

            for(int k = 0; k < myMembers.execVec[index]->getReceipt().size();k++){
                ui->productReportDisplay->append(myMembers.execVec[index]->getReceipt()[k]->getItemName() + " "
                       + "$ " + QString::number(myMembers.execVec[index]->getReceipt()[k]->getItemPrice())+ " "
                       + " " +  QString::number(myMembers.execVec[index]->getReceipt()[k]->getAmtBought())+ " ");
            }
            ui->productReportDisplay->append(" TOTAL: $ " +
                          QString::number(myMembers.execVec[index]->getTotal()));
        }
        else if(!exec){
            ui->productReportDisplay->append(QString::number(memberIds[idIndex])
                                + " - " + myMembers.memberVec[index]->getName());

            for(int k = 0; k < myMembers.memberVec[index]->getReceipt().size();k++){

                ui->productReportDisplay->append(myMembers.memberVec[index]->getReceipt()[k]->getItemName() + " "
                       + "$ " + QString::number(myMembers.memberVec[index]->getReceipt()[k]->getItemPrice())+ " "
                       + " " +  QString::number(myMembers.memberVec[index]->getReceipt()[k]->getAmtBought())+ " ");

            }
            ui->productReportDisplay->append(" TOTAL: $ " +
                         QString::number(myMembers.memberVec[index]->getTotal()));
        }
        else
        {
            ui->productReportDisplay->append("Nothing to display");
        }
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_sales_rep_clicked
 */
void MainWindow::on_sales_rep_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(SALES_REPORT);

    double totalRevenue = 0;
    bool   found;
    int    execCounter  = 0;
    int    memCounter   = 0;



    QVector<std::string> sortedItems = {"08/01/2015" , "08/02/2015",
                                        "08/03/2015", "08/04/2015",
                                        "08/06/2015"};

        ui->salesReport_display->setText("DISPLAYING FULL SALES REPORT\n\n");

        for(int i = 0; i < sortedItems.size(); ++i) {
            totalRevenue = 0;
            execCounter  = 0;
            memCounter   = 0;

            ui->salesReport_display->append("\n\n"+QString::fromStdString(sortedItems[i]));

            for(int j = 0; j < myMembers.execVec.size(); ++j){

                found  =false;

                for(int k = 0; k < myMembers.execVec[j]->getReceipt().size(); ++k){

                    if(myMembers.execVec[j]->getReceipt()[k]->getShopDate().printDate() ==
                            QString::fromStdString(sortedItems[i])){

                        found = true;
                        totalRevenue += (myMembers.execVec[j]->getReceipt()[k]->getAmtBought() *
                                         myMembers.execVec[j]->getReceipt()[k]->getItemPrice());

                        ui->salesReport_display->append(myMembers.execVec[j]->
                                                        getReceipt()[k]->getItemName()
                            + " X " + QString::number(myMembers.execVec[j]->
                                                        getReceipt()[k]->getAmtBought()));
                    }
                }
                if(found){
                    ui->salesReport_display->append(myMembers.execVec[j]->getName()
                                                    + " shopped here this day!");
                    ++execCounter;
                }
            }
            for(int j = 0; j < myMembers.memberVec.size(); ++j){
                for(int k = 0; k < myMembers.memberVec[j]->getReceipt().size(); ++k)  {
                    found = false;
                    if(myMembers.memberVec[j]->getReceipt()[k]->getShopDate().printDate() ==
                       QString::fromStdString(sortedItems[i]))
                    {
                        found  =true;
                        totalRevenue += (myMembers.memberVec[j]->getReceipt()[k]->getAmtBought() *
                                         myMembers.memberVec[j]->getReceipt()[k]->getItemPrice());

                        ui->salesReport_display->append(myMembers.memberVec[j]->getReceipt()[k]->getItemName()
                            +" X " + QString::number(myMembers.memberVec[j]->getReceipt()[k]->getAmtBought()));
                    }

                }
                if(found)   {
                    ui->salesReport_display->append(myMembers.memberVec[j]->getName()
                                                    + " shopped here this day!");
                    ++memCounter; //regular member counter
                }
            }

            ui->salesReport_display->append("Total for this day: $" + QString::number(totalRevenue));
            ui->salesReport_display->append("We had " + QString::number(execCounter)
                                            + " executive members come through.");
            ui->salesReport_display->append("We had " + QString::number(memCounter)
                                            + " regular members come through.");
        }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_quantity_rep_clicked
 */
void MainWindow::on_quantity_rep_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(QUANTITY_REPORT);

    int    totalSold;
    double price;
    QVector<std::string> sortedItems;

    for(int i =0; i<myMembers.ourStock.size();i++){
        sortedItems.push_back(myMembers.ourStock[i]->getItemName().toStdString());
    }

    std::sort(sortedItems.begin(), sortedItems.end());

    ui->quantityReportDisplay->setText("DISPLAYING QUANTITY REPORT SORTED BY ITEM NAME\n\n");

    for(int i =0; i< sortedItems.size();i++){
        totalSold = 0;
        for(int j = 0; j < myMembers.ourStock.size(); ++j)  {
            if(QString::fromStdString(sortedItems[i]) == myMembers.ourStock[j]->getItemName()){
                totalSold += myMembers.ourStock[j]->getAmtBought();
                price = myMembers.ourStock[j]->getItemPrice();
            }
        }
        ui->quantityReportDisplay->append(QString::fromStdString(sortedItems[i]) + " X "
                                        + QString::number(totalSold)+ " @ "
                                        + QString::number(price) + " ea.  Total of $"
                                        + QString::number(price * double(totalSold)) );
    }
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_enterPassword_returnPressed
 */
void MainWindow::on_enterPassword_returnPressed()
{
    // Stores the info that the user passed into the user Id line
    QString username = ui->enterUserName->text();

    // Converts the string to an int to be able to be searched
    int tempId = username.toInt();

    // Stores the info that the user passed into the password line
    QString password = ui->enterPassword->text();

    // Creates a found boolean and sets it to false
    bool found   = false;
    bool deleted = false;
    bool exec    = false;
    int  index   = 0;
    QString date;
    QString name;
    QString typeString;
    int num;
    double total;



    // Clears the display browsers on the member info page
    ui->Member_Info_Receipt->clear();
    ui->Member_Info_Name->clear();
    ui->Member_Info_Id->clear();
    ui->Member_Info_Spent->clear();
    ui->Member_Info_Expiration->clear();
    ui->Member_Info_Type->clear();

    // Searches for the member id and sees if its an executive or not
    while(!found && index < myMembers.execVec.size()){
        if(tempId == myMembers.execVec[index]->getNum()){
            exec = true;
            found = true;
        }
        else
        {
            ++index;
        }
    }
    if(!found)  {
        index = 0;
    }
    while(!found && index < myMembers.memberVec.size()){
        if(tempId == myMembers.memberVec[index]->getNum()){
            exec = false;
            found = true;
        }
        else
        {
            ++index;
        }
    }

    // checks to see if the user has been deleted
    for(int i = 0; i < myMembers.deletedMemberIds.size(); ++i)   {
        if(tempId == myMembers.deletedMemberIds[i]) {
            deleted = true;
        }
    }


    // if user is NOT deleted, and FOUND, and password is
    // "member, change the displays
    // and change page to member info page
    if(!deleted && found && password == "member"){
        // Jump to member info page if password and id are correct
        if(exec)    {
            // Sets predefined variables
            name  = myMembers.execVec[index]->getName();
            num   = myMembers.execVec[index]->getNum();
            total = myMembers.execVec[index]->getTotal();
            date  = myMembers.execVec[index]->getExpiry().printDate();
            typeString = "Executive Member";

            // This sets the receipt display browser, i first hardcode
            //the first line, then append all the others
            if(myMembers.execVec[index]->getReceipt().size() > 0){
                ui->Member_Info_Receipt->setText(myMembers.execVec[index]->getReceipt()[0]->
                                                 getShopDate().printDate());

                for(int i = 0; i < myMembers.execVec[index]->getReceipt().size(); ++i){

                    ui->Member_Info_Receipt->append(myMembers.execVec[index]->
                                                    getReceipt()[i]->getItemName());
                    ui->Member_Info_Receipt->append( QString::number(myMembers.execVec[index]->
                                                     getReceipt()[i]->getAmtBought())+ " @ " + "$"
                                                     + QString::number(myMembers.execVec[index]->
                                                     getReceipt()[i]->getItemPrice())+ " ea. ");

                    ui->Member_Info_Receipt->append("\n");

                    if(i < myMembers.execVec[index]->getReceipt().size() - 1)
                       ui->Member_Info_Receipt->append(myMembers.execVec[index]->
                                                getReceipt()[i + 1]->getShopDate().printDate());

                }
            }
            else{
                ui->Member_Info_Receipt->setText("No Recent Purchases");
            }
        }
        else
        {
            // Sets predefined variables
            typeString = "Regular Member";
            name       = myMembers.memberVec[index]->getName();
            num        = myMembers.memberVec[index]->getNum();
            total      = myMembers.memberVec[index]->getTotal();
            date       = myMembers.memberVec[index]->getExpiry().printDate();


            // This sets the receipt display browser,
            //i first hardcode the first line, then append all the others
            if(myMembers.execVec[index]->getReceipt().size() > 0){

                ui->Member_Info_Receipt->setText(myMembers.memberVec[index]->
                                                 getReceipt()[0]->getShopDate().printDate());

                for(int i = 0; i < myMembers.memberVec[index]->getReceipt().size(); ++i){

                    ui->Member_Info_Receipt->append(myMembers.memberVec[index]->
                                                    getReceipt()[i]->getItemName());
                    ui->Member_Info_Receipt->append(QString::number(myMembers.memberVec[index]->getReceipt()[i]->
                                                    getAmtBought())+ " @ " + "$"
                                                    + QString::number(myMembers.memberVec[index]->
                                                    getReceipt()[i]->getItemPrice())+ " ea. ");

                    ui->Member_Info_Receipt->append("\n");
                    if(i < myMembers.memberVec[index]->getReceipt().size() - 1)
                        ui->Member_Info_Receipt->append(myMembers.memberVec[index]->
                                                        getReceipt()[i + 1]->getShopDate().printDate());
                }
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

        // Changes the page to member info page and resets the
        // lines the user typed in info to login
        ui->pages->setCurrentIndex(MEMBER_INFO);
        ui->enterUserName->clear();
        ui->enterPassword->clear();
    }
    // If the member is deleted, clear the member info
    // browsers to not receive a runtime error
    // And then displays error
    else if(deleted)
    {
        QMessageBox::critical(this, "User Deleted", "That user has been deleted.");
    }
    else
    {
        // If the password is incorrect, clear the member info browsers to
        // not receive a runtime error And then displays error
        QMessageBox::critical(this, "Login Error", "Incorrect Password");
    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_Admin_Login_Button_clicked
 */
void MainWindow::on_Admin_Login_Button_clicked()
{
    // go to admin login page to get to menu choices
    ui->pages->setCurrentIndex(ADMIN_LOGIN);
    ui->enterUserName->clear();
    ui->enterPassword->clear();
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_admin_login_clicked
 */
void MainWindow::on_backButton_admin_login_clicked()
{
    ui->pages->setCurrentIndex(LOGIN_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_Admin_Password_line_edit_returnPressed
 */
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
/**
 * @brief MainWindow::on_read_file_line_edit_returnPressed
 */
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
/**
 * @brief MainWindow::deleteItemOrName
 * @param searchItem
 * @return
 */
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
            found = true;
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

//-----------------------------------------------------------------------

void MainWindow::on_id_enter_button_clicked()
{
    /******************************************************************
     * This portion of code will determine if it is more money savy to
     * either upgrade or downgrade their membership. It will also
     * show their total amount due for the year. This includes
     * the annual membership fee (based on member status i.e.
     * regular/executive) and the rebate if they are an executive
     * member (based off of their total spending for the year)
     *****************************************************************/
    QString idTempString = ui->id_enter_box->text();
    bool executive = false;
    bool reg_found = false;
    bool exec_found = false;
    double rebate = 0;
    double total = 0;
    double annualTotal = 0;
    int exec_index = 0;
    int reg_index = 0;

    const int EXEC_ANNUAL_FEE = 95;
    const int REG_ANNUAL_FEE = 85;
    const int PRICE_DIFFERENCE = 10; //the difference in price between
    //a regular member and an executive
    const float REBATE_RATE = .0325;

    int idTemp = idTempString.toInt();

    while(!reg_found && reg_index < myMembers.memberVec.size()){
        if(idTemp == myMembers.memberVec[reg_index]->getNum()){
            reg_found = true;
            executive = false;
            total = myMembers.memberVec[reg_index]->getTotal();
        }
        else{
            reg_index++;
        }
    }

    while(!exec_found && exec_index < myMembers.execVec.size()){
        if(idTemp == myMembers.execVec[exec_index]->getNum()){
            exec_found = true;
            executive = true;
            total = myMembers.execVec[exec_index]->getTotal();
        }
        else{
            exec_index++;
        }
    }


    rebate = memberRebate(idTemp);

    if(executive){
        annualTotal = (EXEC_ANNUAL_FEE - rebate);

        //output to the member their total for the year
        QString memberTotal = "The rebate you received was ";
        ui->total_rebate_display->setText("Your annual total dues is ");
        ui->total_rebate_display->append(QString::number(annualTotal));
        ui->total_rebate_display->append("\n");
        ui->total_rebate_display->append(memberTotal);
        ui->total_rebate_display->append(QString::number(rebate));

        if(rebate < PRICE_DIFFERENCE){
            //  the member should downgrade to save money
            ui->total_rebate_display->append("\nTo save money, you should downgrade");
        }
        else{
            //  the member should remain an executive
            ui->total_rebate_display->append("\nTo save money, you should remain the same");
        }
    }
    else{   //this would be for regular members
        annualTotal = REG_ANNUAL_FEE;
        //output to the member their total for the year
        ui->total_rebate_display->setText("Your annual total dues is ");
        ui->total_rebate_display->append(QString::number(annualTotal));
        ui->total_rebate_display->append("\n");

        if(total > (PRICE_DIFFERENCE/REBATE_RATE)){
            //  the member should upgrade to executive to
            //  save money
            ui->total_rebate_display->append("\nTo save money, you should upgrade");
        }
        else{
            //  the member should remain a regular member
            ui->total_rebate_display->append("\nTo save money, you should remain the same");
        }
    }
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
void MainWindow::on_upgrade_downgrade_button_clicked()
{

    /******************************************************************
     * This portion of code will determine if it is more money savy to
     * either upgrade or downgrade their membership. It will also
     * show their total amount due for the year. This includes
     * the annual membership fee (based on member status i.e.
     * regular/executive) and the rebate if they are an executive
     * member (based off of their total spending for the year)
     *****************************************************************/
    bool upgrade = ui->upgrade_checkBox_2->isChecked();
    bool downgrade = ui->downgrade_checkBox_3->isChecked();
    bool executive_yes = false;
    bool exec_found = false;
    bool reg_found = false;
    int exec_index = 0;
    int reg_index = 0;

    QString idTempString = ui->id_enter_box->text();

    int idTemp = idTempString.toInt();

    //search for regular member
    while(!reg_found && reg_index < myMembers.memberVec.size()){
        if(idTemp == myMembers.memberVec[reg_index]->getNum()){
            reg_found = true;
            executive_yes = false;
        }
        else{
            reg_index++;
        }
    }

    //search for executive member
    while(!exec_found && exec_index < myMembers.execVec.size()){
        if(idTemp == myMembers.execVec[exec_index]->getNum()){
            exec_found = true;
            executive_yes = true;
        }
        else{
            exec_index++;
        }
    }
    qDebug() << "reg index " + QString::number(reg_index);
    qDebug() << "exec index " + QString::number(exec_index);

    //if the user chooses to upgrade, all of their information will be
    //added to the executive vector and deleted from the regular vector
    if(upgrade && !executive_yes){
        executive *tempExec;
        QString tempName = myMembers.memberVec[reg_index]->getName();
        int tempId = myMembers.memberVec[reg_index]->getNum();
        double tempTotal = myMembers.memberVec[reg_index]->getTotal();
        double tempAnnualDues = myMembers.memberVec[reg_index]->getAnnual();
        int index0;
        item* tempItem;

        QDate      today;  // to retrieve today's date
        int        year;   // to translate QDate to date
        int        month;  //
        int        day;    //

        tempExec = new executive;

        // Push it to the Back
        myMembers.execVec.push_back(tempExec);

        // Initialize ind0 to Working Index
        index0 = myMembers.execVec.size() - 1;

        myMembers.execVec[index0]->setName(tempName);
        myMembers.execVec[index0]->setNum(tempId);
        myMembers.execVec[index0]->setType(true);
        myMembers.execVec[index0]->setTotal(tempTotal);
        myMembers.execVec[index0]->setAnnual(tempAnnualDues);
        for(int i = 0; i < myMembers.memberVec[reg_index]->getReceipt().size(); ++i){
            tempItem = myMembers.memberVec[reg_index]->getReceipt()[i];
            myMembers.execVec[index0]->setReceipt(tempItem);
        }

        // Set Expiry
        today = QDate::currentDate();
        today = today.addYears(1);
        day   = today.day();
        month = today.month();
        year  = today.year();

        myMembers.execVec[index0]->setExpiry(day, month, year);

        myMembers.memberVec.removeAt(reg_index);
    }

    //if the user chooses to downgrade, all of their information will be
    //added to the regular vector and deleted from the executive vector
    if(downgrade && executive_yes){
        member *tempMember;
        QString tempName = myMembers.execVec[exec_index]->getName();
        int tempId = myMembers.execVec[exec_index]->getNum();
        double tempTotal = myMembers.execVec[exec_index]->getTotal();
        double tempAnnualDues = myMembers.execVec[exec_index]->getAnnual();
        int index1;
        item* tempItem;

        QDate      today;  // to retrieve today's date
        int        year;   // to translate QDate to date
        int        month;  //
        int        day;    //

        tempMember = new member;

        // Push it to the Back
        myMembers.memberVec.push_back(tempMember);

        // Initialize ind1 to Working Index
        index1 = myMembers.memberVec.size() - 1;

        myMembers.memberVec[index1]->setName(tempName);
        myMembers.memberVec[index1]->setNum(tempId);
        myMembers.memberVec[index1]->setType(false);
        myMembers.memberVec[index1]->setTotal(tempTotal);
        myMembers.memberVec[index1]->setAnnual(tempAnnualDues);
        for(int i = 0; i < myMembers.execVec[exec_index]->getReceipt().size(); ++i){
            tempItem = myMembers.execVec[exec_index]->getReceipt()[i];
            myMembers.memberVec[index1]->setReceipt(tempItem);
        }


        // Set Expiry
        today = QDate::currentDate();
        today = today.addYears(1);
        day   = today.day();
        month = today.month();
        year  = today.year();

        myMembers.memberVec[index1]->setExpiry(day, month, year);

        myMembers.execVec.removeAt(exec_index);

    }

    ui->id_enter_box->clear();
    ui->total_rebate_display->clear();
    ui->upgrade_checkBox_2->setChecked( false );
    ui->downgrade_checkBox_3->setChecked(false);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButtonForAddItem_clicked
 */
void MainWindow::on_backButtonForAddItem_clicked()
{
    ui->pages->setCurrentIndex(ADD_MENU);
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------
void MainWindow::on_pushButton_2_clicked()
{
    /*ints that are gathering information from the calender widget
     * acting as a user input*/
    int day = ui->dateEdit->date().day();
    int month = ui->dateEdit->date().month();
    int year = ui->dateEdit->date().year();

    /*this is the master vector behold and tremble
       its the vector that holds the sales report*/
    vector<salesReport*> report (myMembers.sales.size());
    /*degub testing*/
    qDebug() << "There are " << myMembers.sales.size() << " sales records";
    /* auto in order to copy the vector into a new vector and the resize to slim it down
      because its chuby, but really in order to make the vector the size its suppose to be*/
    auto it = copy_if (myMembers.sales.begin(), myMembers.sales.end(),
                       report.begin(), salesCheck(day,month,year));
    report.resize(distance(report.begin(),it));

    qDebug() << "On " << month << "/" << day << "/" << year
             << " there were " << report.size() << " sales";

    /* magical code used to creat the table*/
    QStandardItemModel *m = new QStandardItemModel();
    ui->SalesReportTable->setModel(m);
    /* this is how to use a QT table I honestly really disliked it because
     * it took me a stupid amount of time to learn, and even thought I spent
     * time trying to learn I am still uterly confused.*/
    m->setColumnCount(4);
    m->setHorizontalHeaderItem(0, new QStandardItem("Member Name"));
    m->setHorizontalHeaderItem(1, new QStandardItem("Date"));
    m->setHorizontalHeaderItem(2, new QStandardItem("Item"));
    m->setHorizontalHeaderItem(3, new QStandardItem("Price"));

    m->setRowCount(report.size());
    /*for loop in order to print out the table*/
    for (unsigned int i = 0; i < report.size(); i++)
    {
        salesReport* x = report[i];
        m->setItem(i, 0, new QStandardItem(x->getTheMember()->getName()));
        m->setItem(i, 1, new QStandardItem(
                       QString("%1/%2/%3")
                       .arg(x->getDate().getMonth())
                       .arg(x->getDate().getDay())
                       .arg( x->getDate().getYear())));
        m->setItem(i, 2, new QStandardItem(x->getTheItem()->getItemName()));
        m->setItem(i, 3, new QStandardItem(QString("%1").arg(x->getThePrice())));


    }
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_enterButtonForAddMember_clicked
 */
void MainWindow::on_enterButtonForAddMember_clicked()
{
    /***   Declarations   ***/
    QString    strQ;
    bool       check;  // check checkbox, check R#G
    int        rando;  // R#

    QDate      today;  // to retrieve today's date
    int        year;   // to translate QDate to date
    int        month;  // ditto ^
    int        day;    // ditto ^^

    executive *tempE;
    int        ind0;

    member    *tempM;
    int        ind1;

    /***************************************************************/
    // Initialize
    srand(time(NULL));

    // Receive Input
    strQ  = ui->nameInputLine->text();
    check = ui->executive_checkBox->isChecked();

    if(check)
    {
        /***   Handle Vector   ****/
        // Create New Exec
        tempE = new executive;

        // Push it to the Back
        myMembers.execVec.push_back(tempE);

        // Initialize ind0 to Working Index
        ind0 = myMembers.execVec.size() - 1;

        /***   Handle Information   ***/
        // Set Member Name
        myMembers.execVec[ind0]->setName(strQ);

        // Set ID Number
        do
        {
            rando = rand() % 99999 + 10000;

            check = false;

            // Use Range-Based For-Loop to Ensure Unique ID #
            for(executive *eTemp : myMembers.execVec)
            {
                if(eTemp->getNum() == rando)
                {
                    check = true;
                }
            }

            for(member *mTemp : myMembers.memberVec)
            {
                if(mTemp->getNum() == rando)
                {
                    check = true;
                }
            }

        }while(check);

        myMembers.execVec[ind0]->setNum(rando);
        memberIds.push_back(rando);

        // Set type
        myMembers.execVec[ind0]->setType(true);

        // Set Expiry
        today = QDate::currentDate();
        today = today.addYears(1);
        day   = today.day();
        month = today.month();
        year  = today.year();

        myMembers.execVec[ind0]->setExpiry(day, month, year);

        // Set Annual Dues
        myMembers.memberVec[ind0]->setAnnual(95.00);

        // Inform User of New ID #
        ui->informUserID->setText(QString::number(myMembers.execVec[ind0]->getNum()));

    }
    else
    {
        /***   Handle Vector   ****/
        // Create New Member
        tempM = new member;

        // Push it to the Back
        myMembers.memberVec.push_back(tempM);

        // Initialize ind0 to Working Index
        ind1 = myMembers.memberVec.size() - 1;

        /***   Handle Information   ***/
        // Set Member Name
        myMembers.memberVec[ind1]->setName(strQ);

        // Set ID Number
        do
        {
            rando = rand() % 99999 + 10000;

            check = false;

            // Use Range-Based For-Loop to Ensure Unique ID #
            for(executive *eTemp : myMembers.execVec)
            {
                if(eTemp->getNum() == rando)
                {
                    check = true;
                }
            }

            for(member *mTemp : myMembers.memberVec)
            {
                if(mTemp->getNum() == rando)
                {
                    check = true;
                }
            }

        }while(check);

        myMembers.memberVec[ind1]->setNum(rando);
        memberIds.push_back(rando);

        // Set type
        myMembers.memberVec[ind1]->setType(false);

        // Set Expiry
        today = QDate::currentDate();
        today = today.addYears(1);
        day   = today.day();
        month = today.month();
        year  = today.year();

        myMembers.memberVec[ind1]->setExpiry(day, month, year);

        // Set Annual Dues
        myMembers.memberVec[ind1]->setAnnual(95.00);

        // Inform User of New ID #
        ui->informUserID->setText(QString::number(myMembers.memberVec[ind1]->getNum()));



    }
    //    for(int i = 0; i < memberIds.size(); ++i)   {
    //    }
    ui->nameInputLine->clear();
    ui->executive_checkBox->setChecked(false);
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------

/**
 * @brief MainWindow::on_enterButtonAddItem_clicked
 */
void MainWindow::on_enterButtonAddItem_clicked()
{
    QString newItemName = ui->ItemNameInputLine->text();
    QString newItemPrice = ui->itemPriceInputLine->text();
    item* tempItem = new item;

    tempItem->setItemName(newItemName);
    tempItem->setItemPrice(newItemPrice.toDouble());

    myMembers.ourStock.push_back(tempItem);

    QMessageBox::information(this, "Item Added", "Congratulations, your item has been added.");
    ui->ItemNameInputLine->clear();
    ui->itemPriceInputLine->clear();
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_Delete_line_edit_returnPressed
 */
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
/**
 * @brief MainWindow::on_Member_info_back_button_clicked
 */
void MainWindow::on_Member_info_back_button_clicked()
{
    ui->pages->setCurrentIndex(LOGIN_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_searchButtonBrians_clicked
 */
void MainWindow::on_searchButtonBrians_clicked()
{
    ui->pages->setCurrentIndex(SEARCH);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_Search_back_button_clicked
 */
void MainWindow::on_Search_back_button_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_expiredMembers_clicked
 */
void MainWindow::on_backButton_expiredMembers_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_addMember_clicked
 */
void MainWindow::on_backButton_addMember_clicked()
{
    ui->pages->setCurrentIndex(ADD_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_add_member_button_clicked
 */
void MainWindow::on_add_member_button_clicked()
{
    ui->pages->setCurrentIndex(ADD_MEMBER);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_deleteInput_clicked
 */
void MainWindow::on_backButton_deleteInput_clicked()
{
    ui->pages->setCurrentIndex(DELETE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_reports_3_clicked
 */
void MainWindow::on_backButton_reports_3_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_reports_2_clicked
 */
void MainWindow::on_backButton_reports_2_clicked()
{

    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_addmen_clicked
 */
void MainWindow::on_backButton_addmen_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_delete_clicked
 */
void MainWindow::on_backButton_delete_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_reports_clicked
 */
void MainWindow::on_backButton_reports_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_readfile_clicked
 */
void MainWindow::on_backButton_readfile_clicked()
{
    ui->pages->setCurrentIndex(MAIN_MENU);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_upgrade_clicked
 */
void MainWindow::on_backButton_upgrade_clicked()
{
    ui->pages->setCurrentIndex(REPORTS);
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_backButton_search_clicked
 */
void MainWindow::on_backButton_search_clicked()
{
    ui->pages->setCurrentIndex(REPORTS);
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_back_to_login_clicked
 */
void MainWindow::on_back_to_login_clicked()
{
    ui->pages->setCurrentIndex(LOGIN_PAGE);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_rebate_rep_clicked
 */
void MainWindow::on_rebate_rep_clicked()
{
    ui->pages->setCurrentIndex(UPGRADE);
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_expiring_rep_clicked
 */
void MainWindow::on_expiring_rep_clicked()
{
    ui->pages->setCurrentIndex(SEARCH_EXPIRED);
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_delete_user_clicked
 */
void MainWindow::on_delete_user_clicked()
{
    ui->pages->setCurrentIndex(MEMBER_INFO);
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_delete_item_clicked
 */
void MainWindow::on_delete_item_clicked()
{
    ui->pages->setCurrentIndex(MEMBER_INFO);
}
//----------------------------------------------------------------------

//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_add_user_clicked
 */
void MainWindow::on_add_user_clicked()
{
    ui->pages->setCurrentIndex(ADD_MEMBER);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_add_purchase_clicked
 */
void MainWindow::on_add_purchase_clicked()
{
    ui->pages->setCurrentIndex(ADD_ITEM);
}//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_searchByMonth_clicked
 */
void MainWindow::on_searchByMonth_clicked()
{
    ui->pages->setCurrentIndex(SEARCH_EXPIRED);
}
//----------------------------------------------------------------------


//----------------------------------------------------------------------
/**
 * @brief MainWindow::on_lineEdit_2_returnPressed
 */
void MainWindow::on_lineEdit_2_returnPressed()
{

}
//----------------------------------------------------------------------


//----------------------------------------------------------------------

void MainWindow::on_backButton_reports_4_clicked()
{

    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);

}

//----------------------------------------------------------------------


//----------------------------------------------------------------------

void MainWindow::on_backButton_reports_5_clicked()
{
    ui->REPORTS_PAGES->setCurrentIndex(MAIN_REPORT_PAGE);
}

//----------------------------------------------------------------------


//----------------------------------------------------------------------



void MainWindow::on_searchItemEnterButton_clicked()
{
    QString searchString = ui->enterItemNameBox->text();

    double totalRevenue = 0;
    int    totalSold = 0;
    int    index;
    int    i = 0;
    bool   found = false;

    ui->itemInfoDisplayBox->setText("DISPLAYING INFO FOR ENTERED ITEM\n\n");

    while(!found && i<myMembers.ourStock.size()){
       if(searchString == myMembers.ourStock[i]->getItemName()){
           found = true;
           index =i;
       }else{
          ++i;
       }
    }
    for(int i = 0; i < myMembers.memberVec.size(); ++i) {
        for(int j = 0; j < myMembers.memberVec[i]->getReceipt().size(); ++j)    {
            totalSold += myMembers.memberVec[i]->getReceipt()[j]->getAmtBought();
            qDebug() << QString::number(totalSold);
            totalRevenue += (myMembers.memberVec[i]->getReceipt()[j]->getAmtBought() *
                             myMembers.memberVec[i]->getReceipt()[j]->getItemPrice());
            qDebug() << QString::number(totalRevenue);
        }
    }
    for(int i = 0; i < myMembers.execVec.size(); ++i) {
        for(int j = 0; j < myMembers.execVec[i]->getReceipt().size(); ++j)    {
            totalSold += myMembers.execVec[i]->getReceipt()[j]->getAmtBought();
            qDebug() << QString::number(totalSold);
            totalRevenue += (myMembers.execVec[i]->getReceipt()[j]->getAmtBought() *
                             myMembers.execVec[i]->getReceipt()[j]->getItemPrice());
            qDebug() << QString::number(totalRevenue);
        }
    }

    if(found){

        ui->itemInfoDisplayBox->append(searchString);

//        totalPrice = myMembers.ourStock[index]->getItemPrice()*myMembers.ourStock[index]->getAmtBought();

        ui->itemInfoDisplayBox->append("Amount Bought: " + QString::number(totalSold));
        ui->itemInfoDisplayBox->append("Price: $ " + QString::number(myMembers.ourStock[index]->getItemPrice()));

        ui->itemInfoDisplayBox->append("TOTAL REVENUE: $ " + QString::number(totalRevenue));


    }
    else
    {
        QMessageBox::critical(this, "Not Found", "Item not found!");
    }
}
