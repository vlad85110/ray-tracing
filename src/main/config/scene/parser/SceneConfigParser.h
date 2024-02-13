//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_SCENECONFIGPARSER_H
#define RAY_TRACING_SCENECONFIGPARSER_H

#include <QString>
#include "main/config/scene/SceneConfig.h"
#include "main/config/AbstractParser.h"

class SceneConfigParser : public AbstractParser {
public:
    explicit SceneConfigParser(const QString &fileName);

    [[nodiscard]] Optional<SceneConfig> parse() const;

    static Optional<ScatteredLight> parseScatteredLight(const QString &scatteredLightStr);

    static Optional<LightSource> parseLightSource(const QString &lightSourceStr);

    static Optional<int> parseNL(const QString &NLString);

    [[nodiscard]] Optional<Vector<LightSource>> parseLightSources(int NL) const;

    [[nodiscard]] Optional<Vector<ptr<Primitive>>> parsePrimitives(int startIndex) const;

    [[nodiscard]] Optional<Box> parseBox(int startIndex) const;

    [[nodiscard]] Optional<Triangle> parseTriangle(int startIndex) const;

    static Optional<Primitive> parsePrimitive(const QString &primitiveStr);

    static Optional<Point> parsePoint(const QStringList &stringSpl);

    [[nodiscard]] Optional<Vector<Point>> parsePolygon(int startIndex, int angleCnt) const;

    [[nodiscard]] Optional<Sphere> parseSphere(int startIndex) const;

    [[nodiscard]] Optional<Quadrangle> parseQuadrangle(int startIndex) const;
};


#endif //RAY_TRACING_SCENECONFIGPARSER_H
