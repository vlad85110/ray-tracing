//
// Created by Влад Кирилов on 20.05.2023.
//

#ifndef RAY_TRACING_GEOMETRY_H
#define RAY_TRACING_GEOMETRY_H

#include "main/types.h"
#include "main/render/ray/Ray.h"

int sgn(float number);

int getVectorDominantCoordIndex(const QVector3D &vector3D);

Optional<Point> getPlaneIntersectionPoint(const QVector3D &normal, const Ray &ray, const Point &pointOnPlane);

QVector3D getReflectionVector(const Ray &ray, const QVector3D &normal);

Point getPointOnSphere(float angleY, float angleZ, float radius, const Point &center);

QVector3D getH(const QVector3D& eye, const QVector3D &lightRay);

#endif //RAY_TRACING_GEOMETRY_H
