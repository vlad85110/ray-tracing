//
// Created by Влад Кирилов on 07.05.2023.
//

#include <QList>
#include "SceneConfigParser.h"

SceneConfigParser::SceneConfigParser(const QString &fileName) : AbstractParser(fileName) {}

Optional<SceneConfig> SceneConfigParser::parse() const {
    if (strings.empty()) return std::nullopt;

    auto &scatteredLightString = strings[0];
    auto scatteredLightOpt = parseScatteredLight(scatteredLightString);

    if (!scatteredLightOpt.has_value()) {
        return std::nullopt;
    }

    auto scatteredLight = scatteredLightOpt.value();

    if (strings.size() <= 1) return std::nullopt;

    auto &NLString = strings[1];
    auto NLOpt = parseNL(NLString);

    if (!NLOpt.has_value()) {
        return std::nullopt;
    }

    auto NL = NLOpt.value();

    auto lightSourcesOpt = parseLightSources(NL);

    if (!lightSourcesOpt.has_value()) {
        return std::nullopt;
    }

    auto lightSources = lightSourcesOpt.value();
    auto primitivesOpt = parsePrimitives(2 + NL);


    Vector<ptr<Primitive>> primitives;
    if (!primitivesOpt.has_value()){

    } else {
        primitives = primitivesOpt.value();
    }

    return SceneConfig{scatteredLight, std::move(lightSources), std::move(primitives)};
}

Optional<LightSource> SceneConfigParser::parseLightSource(const QString &lightSourceStr) {
    auto lightSourceStringSpl = lightSourceStr.split(" ");

    if (lightSourceStringSpl.size() != 6) {
        return std::nullopt;
    }

    bool isSuccess;

    auto LXString = lightSourceStringSpl[0];
    auto LX = LXString.toFloat(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto LYString = lightSourceStringSpl[1];
    auto LY = LYString.toFloat(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto LZString = lightSourceStringSpl[2];
    auto LZ = LZString.toFloat(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto LRString = lightSourceStringSpl[3];
    auto LR = LRString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto LGString = lightSourceStringSpl[4];
    auto LG = LGString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto LBString = lightSourceStringSpl[5];
    auto LB = LBString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    return LightSource(Point{LX, LY, LZ}, qRgb(LR, LG, LB));
}

Optional<ScatteredLight> SceneConfigParser::parseScatteredLight(const QString &scatteredLightStr) {
    auto scatteredLightStringSpl = scatteredLightStr.split(" ");

    if (scatteredLightStringSpl.size() != 3) {
        return std::nullopt;
    }

    bool isSuccess;

    auto ArString = scatteredLightStringSpl[0];

    auto Ar = ArString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto AgString = scatteredLightStringSpl[1];

    auto Ag = AgString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    auto AbString = scatteredLightStringSpl[2];

    auto Ab = AbString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    return qRgb(Ar, Ag, Ab);
}

Optional<int> SceneConfigParser::parseNL(const QString &NLString) {
    bool isSuccess;

    auto NL = NLString.toInt(&isSuccess);

    if (!isSuccess) {
        return std::nullopt;
    }

    return NL;
}

Optional<Vector<LightSource>> SceneConfigParser::parseLightSources(int NL) const {
    Vector<LightSource> sources;

    if (strings.size() <= 1 + NL) return std::nullopt;

    for (int i = 0; i < NL; ++i) {
        auto &lightSourceString = strings[2 + i];
        auto lightSourceOpt = parseLightSource(lightSourceString);

        if (!lightSourceOpt.has_value()) {
            return std::nullopt;
        }

        sources.emplace_back(lightSourceOpt.value());
    }

    return sources;
}

Optional<Box> SceneConfigParser::parseBox(int startIndex) const {
    auto &firstStr = strings[startIndex];
    auto firstStrSpl = firstStr.split(" ");

    bool isSuccess;

    auto &minXStr = firstStrSpl[1];
    auto &minYStr = firstStrSpl[2];
    auto &minZStr = firstStrSpl[3];

    auto minX = minXStr.toFloat(&isSuccess);

    if (!isSuccess) return std::nullopt;

    auto minY = minYStr.toFloat(&isSuccess);

    if (!isSuccess) return std::nullopt;

    auto minZ = minZStr.toFloat(&isSuccess);

    if (!isSuccess) return std::nullopt;

    auto &secondStr = strings[startIndex + 1];
    auto secondStrSplit = secondStr.split(" ");

    if (secondStrSplit.size() != 3) return std::nullopt;

    auto &maxXStr = secondStrSplit[0];
    auto &maxYStr = secondStrSplit[1];
    auto &maxZStr = secondStrSplit[2];

    auto maxX = maxXStr.toFloat(&isSuccess);

    if (!isSuccess) return std::nullopt;

    auto maxY = maxYStr.toFloat(&isSuccess);

    if (!isSuccess) return std::nullopt;

    auto maxZ = maxZStr.toFloat(&isSuccess);

    if (!isSuccess) return std::nullopt;

    auto &thirdStr = strings[startIndex + 2];
    auto primitiveOpt = parsePrimitive(thirdStr);

    if (!primitiveOpt.has_value()) return std::nullopt;

    auto primitive = primitiveOpt.value();

    return Box(primitive.getKDr(), primitive.getKDg(), primitive.getKdb(),
               primitive.getKSr(), primitive.getKSg(), primitive.getKsb(),
               primitive.getPower(),
               Point{minX, minY, minZ}, Point{maxX, maxY, maxZ});
}

Optional<Primitive> SceneConfigParser::parsePrimitive(const QString &primitiveStr) {
    auto primitiveStrSpl = primitiveStr.split(" ");
    bool isSuccess;

    if (primitiveStrSpl.size() != 7) return std::nullopt;

    auto &KDrStr = primitiveStrSpl[0];
    auto &KDgStr = primitiveStrSpl[1];
    auto &KDbStr = primitiveStrSpl[2];
    auto &KSrStr = primitiveStrSpl[3];
    auto &KSgStr = primitiveStrSpl[4];
    auto &KSbStr = primitiveStrSpl[5];
    auto &powerStr = primitiveStrSpl[6];

    auto KDr = KDrStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    auto KDg = KDgStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    auto KDb = KDbStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    auto KSr = KSrStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    auto KSg = KSgStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    auto KSb = KSbStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    auto power = powerStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    return Primitive(KDr, KDg, KDb, KSr, KSg, KSb, power);
}

Optional<Point> SceneConfigParser::parsePoint(const QStringList &stringSpl) {
    if (stringSpl.size() != 3) return std::nullopt;

    bool isSuccess;

    auto &xStr = stringSpl[0];
    auto &yStr = stringSpl[1];
    auto &zStr = stringSpl[2];

    auto x = xStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;
    auto y = yStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;
    auto z = zStr.toFloat(&isSuccess);
    if (!isSuccess) return std::nullopt;

    return Point(x, y, z);
}

Optional<Triangle> SceneConfigParser::parseTriangle(int startIndex) const {
    auto pointsOpt = parsePolygon(startIndex, 3);
    if (!pointsOpt.has_value()) return std::nullopt;
    auto points = pointsOpt.value();

    auto primitiveOpt = parsePrimitive(strings[startIndex + 3]);
    if (!primitiveOpt.has_value()) return std::nullopt;
    auto primitive = primitiveOpt.value();

    return Triangle(primitive.getKDr(), primitive.getKDg(), primitive.getKdb(),
                    primitive.getKSr(), primitive.getKSg(), primitive.getKsb(),
                    primitive.getPower(), points[0], points[1], points[2]);
}

Optional<Vector<Point>> SceneConfigParser::parsePolygon(int startIndex, int angleCnt) const {
    Vector<Point> res;

    for (int i = 0; i < angleCnt; ++i) {
        auto pointStr = strings[startIndex + i];
        auto pointStrSpl = pointStr.split(" ");

        if (i == 0) {
            pointStrSpl.erase(pointStrSpl.constBegin());
        }

        auto pointOpt = parsePoint(pointStrSpl);
        if (!pointOpt.has_value()) return std::nullopt;

        auto point = pointOpt.value();
        res.emplace_back(point);
    }

    return res;
}

Optional<Sphere> SceneConfigParser::parseSphere(int startIndex) const {
    auto centerPoints = parsePolygon(startIndex, 1);

    if (!centerPoints.has_value()) return std::nullopt;

    auto &centerPoint = centerPoints.value()[0];
    auto &radiusStr = strings[startIndex + 1];

    bool isSuccess;

    auto radius = radiusStr.toFloat(&isSuccess);
    auto primitiveOpt = parsePrimitive(strings[startIndex + 2]);

    if (!primitiveOpt.has_value()) return std::nullopt;

    auto primitive = primitiveOpt.value();

    return Sphere(primitive.getKDr(), primitive.getKDg(), primitive.getKdb(),
                  primitive.getKSr(), primitive.getKSg(), primitive.getKsb(),
                  primitive.getPower(), centerPoint, radius);
}

Optional<Quadrangle> SceneConfigParser::parseQuadrangle(int startIndex) const {
    auto pointsOpt = parsePolygon(startIndex, 4);
    if (!pointsOpt.has_value()) return std::nullopt;
    auto points = pointsOpt.value();

    auto primitiveOpt = parsePrimitive(strings[startIndex + 4]);
    if (!primitiveOpt.has_value()) return std::nullopt;
    auto primitive = primitiveOpt.value();

    return Quadrangle(primitive.getKDr(), primitive.getKDg(), primitive.getKdb(),
                      primitive.getKSr(), primitive.getKSg(), primitive.getKsb(),
                      primitive.getPower(), points[0], points[1], points[2], points[3]);
}

Optional<Vector<ptr<Primitive>>> SceneConfigParser::parsePrimitives(int startIndex) const {
    Vector<ptr<Primitive>> res;

    auto i = startIndex;

    while (i != strings.size()) {
        auto &string = strings[i];
        auto stringSpl = string.split(" ");

        if (stringSpl.size() != 4) {
            break;
        }

        auto &primitiveName = stringSpl.first();

        if (primitiveName.toLower() == "sphere") {
            if (i + 2 >= strings.size()) break;
            auto sphereOpt = parseSphere(i);
            if (!sphereOpt.has_value()) break;
            auto &sphere = sphereOpt.value();
            res.emplace_back(make_shared<Sphere>(std::move(sphere)));

            i += 3;

        } else if (primitiveName.toLower() == "box") {
            if (i + 2 >= strings.size()) break;
            auto boxOpt = parseBox(i);
            if (!boxOpt.has_value()) break;
            auto &box = boxOpt.value();

            for (auto &q : box.getQuadrangles()) {
                res.emplace_back(make_shared<Quadrangle>(q));
            }

            i += 3;

        } else if (primitiveName.toLower() == "triangle") {
            if (i + 3 >= strings.size()) break;
            auto triangleOpt = parseTriangle(i);
            if (!triangleOpt.has_value()) break;
            auto &triangle = triangleOpt.value();
            res.emplace_back(make_shared<Triangle>(std::move(triangle)));

            i += 4;

        } else if (primitiveName.toLower() == "quadrangle") {
            if (i + 4 >= strings.size()) break;
            auto quadrangleOpt = parseQuadrangle(i);
            if (!quadrangleOpt.has_value()) break;
            auto &quadrangle = quadrangleOpt.value();
            res.emplace_back(make_shared<Quadrangle>(std::move(quadrangle)));

            i += 5;
        } else break;
    }

    return res.empty() ? std::nullopt : std::make_optional(res);
}


