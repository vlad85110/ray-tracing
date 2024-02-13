//
// Created by Влад Кирилов on 07.05.2023.
//

#include "SceneConfigParserTest.h"
#include "main/config/scene/parser/SceneConfigParser.h"
#include <QTest>

SceneConfigParserTest::SceneConfigParserTest() {
    pathPrefix = "/Users/vladkirilov/CLionProjects/"
                 "ray tracing/src/test/scene_config_parser/";
}

void SceneConfigParserTest::test1() const {
    SceneConfigParser parser(pathPrefix + "test1.txt");

    auto resOpt = parser.parse();

    QCOMPARE(resOpt.has_value(), true);
    auto res = resOpt.value();

    QCOMPARE(res.scatteredLight, qRgb(1, 2, 3));
    QCOMPARE(res.lightSources.size(), 3);

    auto &firstLightSource = res.lightSources[0];
    QCOMPARE(firstLightSource.getColor(), qRgb(1, 2, 3));
    QCOMPARE(firstLightSource.getPoint(), Point(1, 2, 3));

    QCOMPARE(res.primitives.size(), 1);

    auto primitive = res.primitives[0];
    auto sphere = std::dynamic_pointer_cast<Sphere>(primitive);

    QCOMPARE(sphere != nullptr, true);
    QCOMPARE(sphere->getCenter(), Point(1, 2, 3));
    QCOMPARE(sphere->getRadius(), 3);
}

void SceneConfigParserTest::test2() const {
    SceneConfigParser parser(pathPrefix + "test2.txt");

    auto resOpt = parser.parse();

    QCOMPARE(resOpt.has_value(), true);
    auto res = resOpt.value();
    QCOMPARE(res.primitives.size(), 8);
}


