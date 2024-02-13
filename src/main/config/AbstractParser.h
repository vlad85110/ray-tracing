//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_ABSTRACTPARSER_H
#define RAY_TRACING_ABSTRACTPARSER_H

#include <QString>

#include "main/types.h"


class AbstractParser {
protected:
    QString fileName;
    Vector<QString> strings;

    void parseFile();

public:
    explicit AbstractParser(QString fileName);

};

#endif //RAY_TRACING_ABSTRACTPARSER_H
