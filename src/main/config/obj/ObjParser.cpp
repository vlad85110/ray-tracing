//
// Created by Влад Кирилов on 13.05.2023.
//

#include <QList>
#include "ObjParser.h"
#include "main/config/scene/parser/SceneConfigParser.h"

ObjParser::ObjParser(const QString &fileName) : AbstractParser(fileName) {}

Optional<SceneConfig> ObjParser::parse() {
    Vector<ptr<Primitive>> primitives;

    for (const auto &string: strings) {
        auto stringSpl = string.split(" ");

        if (stringSpl[0] == "f") {
            if (stringSpl.size() == 5) {
                auto pair = parseQuadrangle(stringSpl).value();
                primitives.emplace_back(make_shared<Triangle>(std::move(pair.first)));
                primitives.emplace_back(make_shared<Triangle>(std::move(pair.second)));
            } else if (stringSpl.size() == 4) {
                auto triOpt = parseTriangle(stringSpl);
                primitives.emplace_back(make_shared<Triangle>(std::move(triOpt.value())));
            }
        } else if (stringSpl[0] == "v") {
            auto pointOpt = parsePoint(stringSpl);
            points.emplace_back(pointOpt.value());
        } else if (stringSpl[0] == "usemtl") {
            stringSpl.removeFirst();
            stringSpl.removeFirst();

            auto primitiveOpt = SceneConfigParser::parsePrimitive(stringSpl.join(" "));

            if (primitiveOpt.has_value()) {
                currentPrimitive = make_shared<Primitive>(std::move(primitiveOpt.value()));
            }
        }
    }

    return SceneConfig{qRgb(265, 23, 23), {}, primitives};
}

Optional<Point> ObjParser::parsePoint(const QStringList &stringSpl) {
    float x = stringSpl[1].toFloat();
    float y = stringSpl[2].toFloat();
    float z = stringSpl[3].toFloat();
    return std::make_optional<Point>(x, y, z);
}

Optional<std::pair<Triangle, Triangle>> ObjParser::parseQuadrangle(const QStringList &stringSpl) {
    Vector<int> indices;

    for (int i = 1; i < stringSpl.size(); ++i) {
        auto spl = stringSpl[i].split("/");
        indices.emplace_back(spl.first().toInt());
    }

    if (currentPrimitive != nullptr) {
        return std::make_pair(Triangle(*currentPrimitive,
                                       points[indices[0] - 1],
                                       points[indices[1] - 1],
                                       points[indices[2] - 1]),
                              Triangle(*currentPrimitive,
                                       points[indices[0] - 1],
                                       points[indices[2] - 1],
                                       points[indices[3] - 1]));
    } else {
        return std::make_pair(Triangle(
                                      points[indices[0] - 1],
                                      points[indices[1] - 1],
                                      points[indices[2] - 1]),
                              Triangle(
                                      points[indices[0] - 1],
                                      points[indices[2] - 1],
                                      points[indices[3] - 1]));
    }
}

Optional<Triangle> ObjParser::parseTriangle(const QStringList &stringSpl) {
    Vector<int> indices;

    for (int i = 1; i < stringSpl.size(); ++i) {
        auto spl = stringSpl[i].split("/");
        indices.emplace_back(spl.first().toInt());
    }

    if (currentPrimitive != nullptr) {
        return std::make_optional<Triangle>(*currentPrimitive, points[indices[0] - 1],
                                            points[indices[1] - 1],
                                            points[indices[2] - 1]);
    } else {
        return std::make_optional<Triangle>(points[indices[0] - 1],
                                            points[indices[1] - 1],
                                            points[indices[2] - 1]);
    }
}
