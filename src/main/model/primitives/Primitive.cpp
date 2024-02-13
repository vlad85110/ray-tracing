//
// Created by Влад Кирилов on 07.05.2023.
//

#include "Primitive.h"
#include <QMatrix4x4>
#include <set>

Primitive::Primitive(float kDr, float kDg, float kdb, float kSr, float kSg, float ksb, float power)
        : KDr(kDr), KDg(kDg), Kdb(kdb), KSr(kSr), KSg(kSg), Ksb(ksb), power(power), originalPoints() {}

void Primitive::handlePoints(const QMatrix4x4 &matrix) {
    for (int i = 0; i < originalPoints.size(); ++i) {
        auto &originalPoint = originalPoints[i];
        auto &handledPoint = handledPoints[i];

        QVector4D vector(originalPoint.x(), originalPoint.y(), originalPoint.z(), 1);
        auto result = matrix * vector;

        handledPoint.setX((float) result[0] / result.w());
        handledPoint.setY((float) result[1] / result.w());
        handledPoint.setZ((float) result[2] / result.w());
    }
}

const Vector<Point> &Primitive::getOriginalPoints() const {
    return originalPoints;
}

const Vector<Point> &Primitive::getHandledPoints() const {
    return handledPoints;
}

Point Primitive::getMin() const {
    std::set<float> xs;
    std::set<float> ys;
    std::set<float> zs;

    for (const auto &p: handledPoints) {
        xs.emplace(p.x());
        ys.emplace(p.y());
        zs.emplace(p.z());
    }

    auto minX = *xs.begin();
    auto minY = *ys.begin();
    auto minZ = *zs.begin();

    return {minX, minY, minZ};
}

Point Primitive::getMax() const {
    std::set<float> xs;
    std::set<float> ys;
    std::set<float> zs;

    for (const auto &p: handledPoints) {
        xs.emplace(p.x());
        ys.emplace(p.y());
        zs.emplace(p.z());
    }

    auto maxX = *xs.rbegin();
    auto maxY = *ys.rbegin();
    auto maxZ = *zs.rbegin();

    return {maxX, maxY, maxZ};
}

float Primitive::getKDr() const {
    return KDr;
}

float Primitive::getKDg() const {
    return KDg;
}

float Primitive::getKdb() const {
    return Kdb;
}

float Primitive::getKSr() const {
    return KSr;
}

float Primitive::getKSg() const {
    return KSg;
}

float Primitive::getKsb() const {
    return Ksb;
}

float Primitive::getPower() const {
    return power;
}

