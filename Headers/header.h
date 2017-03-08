#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;

// Globals
const double SALES_TAX   =  7.25;


#include <QApplication>

void InitializeVectors();

void UpdateDataFromFile(QString fileName);

void UpdateMembersFromFile(QString fileName);

void memberRebate(QString id);


#endif
