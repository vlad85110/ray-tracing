//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_TYPES_H
#define RAY_TRACING_TYPES_H

#include <vector>
#include <iostream>
#include <QVector3D>
#include <qrgb.h>

template<typename T>
using Vector = std::vector<T>;

using std::cout;
using std::endl;
template<typename T>
using Optional = std::optional<T>;

using Point = QVector3D;
template<typename T>
using ptr = std::shared_ptr<T>;
using std::make_shared;

using Line = std::pair<QVector3D, QVector3D>;

using ScatteredLight = QRgb;

#endif //RAY_TRACING_TYPES_H
