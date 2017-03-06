#include "header.h"
#include "member.h"
#include "executive.h"
#include <Qvector>
#include <QDebug>

void InitializeVectors() {
    static QVector<member>      memberVec;
    static QVector<executive>   execVec;
    member newMem;

    memberVec.push_back(newMem);

    qInfo() << "Test: " << memberVec[0].getNum();
}
