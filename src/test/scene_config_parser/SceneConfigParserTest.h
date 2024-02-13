//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_SCENECONFIGPARSERTEST_H
#define RAY_TRACING_SCENECONFIGPARSERTEST_H

#include <QObject>
#include <QtTest>

class SceneConfigParserTest : public QObject {
Q_OBJECT
public:
    SceneConfigParserTest();

private:
    QString pathPrefix;
private slots:

    void test1() const;

    void test2() const;

};


#endif //RAY_TRACING_SCENECONFIGPARSERTEST_H
