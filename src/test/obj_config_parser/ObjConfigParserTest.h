//
// Created by Влад Кирилов on 15.05.2023.
//

#ifndef RAY_TRACING_OBJCONFIGPARSERTEST_H
#define RAY_TRACING_OBJCONFIGPARSERTEST_H


#include <QObject>


class ObjConfigParserTest : public QObject {
Q_OBJECT

public:
    explicit ObjConfigParserTest();

private:
    QString pathPrefix;
private slots:

    void test1() const;

    void test2() const;

};


#endif //RAY_TRACING_OBJCONFIGPARSERTEST_H
