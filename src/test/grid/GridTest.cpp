//
// Created by Влад Кирилов on 17.05.2023.
//

#include "GridTest.h"
#include "main/render/grid/Grid.h"
#include <QtTest>

void GridTest::test1() {
    Grid grid({}, 10);
    int index;

    index = grid.getPointIndex({-1, -1, 0});
    QCOMPARE(index, 0);

    index = grid.getPointIndex({1, 1, 1});
    QCOMPARE(index, 9 * 10 * 10 + 9 * 10 + 9);

    index = grid.getPointIndex({-0.9, 0.2, 0.5});
    QCOMPARE(index, 0 * 10 * 10 + 6 * 10 + 5);
}

void GridTest::test2() {
    Grid grid({}, 10);
    int index;

    index = grid.getPointXIndex({-1, 0, 0});
    QCOMPARE(index, 0);

    index = grid.getPointXIndex({0, 0, 0});
    QCOMPARE(index, 5);

    index = grid.getPointXIndex({0.3, 0, 0});
    QCOMPARE(index, 6);


    index = grid.getPointYIndex({0, -1, 0});
    QCOMPARE(index, 0);

    index = grid.getPointYIndex({0, 0, 0});
    QCOMPARE(index, 5);

    index = grid.getPointYIndex({0.3, 0.3, 0});
    QCOMPARE(index, 6);


    index = grid.getPointZIndex({0, -1, 0});
    QCOMPARE(index, 0);

    index = grid.getPointZIndex({0, 0, 0.5});
    QCOMPARE(index, 5);

    index = grid.getPointZIndex({0.3, 0.3, 1});
    QCOMPARE(index, 9);
}
