//
// Created by Влад Кирилов on 15.05.2023.
//

#ifndef RAY_TRACING_GRID_H
#define RAY_TRACING_GRID_H

#include "main/types.h"
#include "main/model/primitives/Primitive.h"

class Grid {
private:
    Vector<Vector<std::pair<long, ptr<Primitive>>>> grid;
    int cellCnt;

public:
    explicit Grid(const Vector<ptr<Primitive>> &primitives, int cellCnt);

    [[nodiscard]] int getPointCoordIndex(const Point &point, int coordIndex) const;

    [[nodiscard]] int getPointIndex(const Point &point) const;

    [[nodiscard]] int getPointXIndex(const Point &point) const;

    [[nodiscard]] int getPointYIndex(const Point &point) const;

    [[nodiscard]] int getPointZIndex(const Point &point) const;

    [[nodiscard]] const Vector<std::pair<long, ptr<Primitive>>> &operator[](int index) const;

    [[nodiscard]] const Vector<std::pair<long, ptr<Primitive>>> &at(int x, int y, int z) const;

    [[nodiscard]] int getCellCnt() const;

    [[nodiscard]] float getStep(int coordIndex) const;

    [[nodiscard]] static std::pair<float, float> getMinAndMax(int coordIndex);
};


#endif //RAY_TRACING_GRID_H
