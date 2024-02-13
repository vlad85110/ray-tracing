//
// Created by Влад Кирилов on 13.05.2023.
//

#ifndef RAY_TRACING_OBJPARSER_H
#define RAY_TRACING_OBJPARSER_H


#include "main/config/AbstractParser.h"
#include "main/config/scene/SceneConfig.h"

class ObjParser : public AbstractParser {
private:
    static Optional<Point> parsePoint(const QStringList &stringSpl);

    Optional<std::pair<Triangle, Triangle>> parseQuadrangle(const QStringList &stringSpl);

    Optional<Triangle> parseTriangle(const QStringList &stringSpl);

    Vector<Point> points;

    ptr<Primitive> currentPrimitive;

public:
    explicit ObjParser(const QString &fileName);

    [[nodiscard]] Optional<SceneConfig> parse();
};


#endif //RAY_TRACING_OBJPARSER_H
