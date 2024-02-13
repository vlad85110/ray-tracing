//
// Created by Влад Кирилов on 13.05.2023.
//

#include "PrimitiveTest.h"
#include "main/model/primitives/box/Box.h"
#include <QtTest>

void PrimitiveTest::test1() {
    Box box({-1, -1, -1}, {1, 1, 1});

    auto lines = box.getLines();

    QCOMPARE(lines.size(), 12);

    QCOMPARE(lines[0].first.x(), -1);
    QCOMPARE(lines[0].first.y(), -1);
    QCOMPARE(lines[0].first.z(), -1);
    QCOMPARE(lines[0].second.x(), -1);
    QCOMPARE(lines[0].second.y(), -1);
    QCOMPARE(lines[0].second.z(), 1);

    QCOMPARE(lines[1].first.x(), -1);
    QCOMPARE(lines[1].first.y(), -1);
    QCOMPARE(lines[1].first.z(), -1);
    QCOMPARE(lines[1].second.x(), -1);
    QCOMPARE(lines[1].second.y(), -1);
    QCOMPARE(lines[1].second.z(), 1);
}

void PrimitiveTest::test2() {

}


