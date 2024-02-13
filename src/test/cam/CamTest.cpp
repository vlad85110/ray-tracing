//
// Created by Влад Кирилов on 11.05.2023.
//

#include "CamTest.h"

#include <QMatrix4x4>
#include <QTest>

void CamTest::test1() {
    QMatrix4x4 matrix4X4(
            0, 1, 0, 0,
            0, 0, 1, 0,
            -1, 0, 0, 5,
            0, 0, 0, 1
    );

    auto res = matrix4X4 * QVector4D(0, 1, 0, 1);
    QCOMPARE(res.x(), 1);
}

void CamTest::test2() {
//    auto angle = 45 * (float) M_PI / 180;
//
//    QMatrix4x4 rotation (
//
//            );
}
