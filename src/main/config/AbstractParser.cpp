//
// Created by Влад Кирилов on 07.05.2023.
//

#include "AbstractParser.h"

#include <utility>
#include <QFile>
#include <QTextStream>

AbstractParser::AbstractParser(QString fileName) : fileName(std::move(fileName)) {
    parseFile();
}

void AbstractParser::parseFile() {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream textStream(&file);

    while (!textStream.atEnd()) {
        auto line = textStream.readLine();

        if (line.isEmpty() || line.isNull()) {
            continue;
        }

        if (line.contains("//")) {
            auto spl = line.split("//");
            if (!spl.first().isEmpty() || !spl.first().isEmpty()) {
                strings.emplace_back(spl.first().trimmed());
            }
        } else {
            strings.emplace_back(line.trimmed());
        }
    }

    file.close();
}
