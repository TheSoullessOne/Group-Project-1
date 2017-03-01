#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;

// Globals
const double SALES_TAX   =  7.25;

#include "linkedlist.h"
#include "date.h"
#include "item.h"
#include "member.h"
#include "executive.h"
#include "mainwindow.h"
#include <QApplication>


void UpdateDataFromFile(QString fileName);


#endif
