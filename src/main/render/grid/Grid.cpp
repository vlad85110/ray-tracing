//
// Created by Влад Кирилов on 15.05.2023.
//

#include "Grid.h"


Grid::Grid(const Vector<ptr<Primitive>> &primitives, int cellCnt)
        : cellCnt(cellCnt), grid(cellCnt * cellCnt * cellCnt) {

    auto id = 0L;
    for (const auto &primitive: primitives) {
        auto max = primitive->getMax();
        auto min = primitive->getMin();

        auto minXIndex = getPointXIndex(min);
        auto minYIndex = getPointYIndex(min);
        auto minZIndex = getPointZIndex(min);

        auto maxXIndex = getPointXIndex(max);
        auto maxYIndex = getPointYIndex(max);
        auto maxZIndex = getPointZIndex(max);

        for (int i = minXIndex; i <= maxXIndex; ++i) {
            for (int j = minYIndex; j <= maxYIndex; ++j) {
                for (int k = minZIndex; k <= maxZIndex; ++k) {
                    if (!(i < 0 || i > cellCnt - 1 || j < 0 || j > cellCnt - 1 || k < 0 || k > cellCnt - 1)) {
                        grid.at(i * cellCnt * cellCnt + j * cellCnt + k).emplace_back(id, primitive);
                    }
                }
            }
        }

        id++;
    }
}

int Grid::getPointIndex(const Point &point) const {
    auto xIndex = getPointXIndex(point);
    if (xIndex < 0 || xIndex >= cellCnt) return -1;
    auto yIndex = getPointYIndex(point);
    if (yIndex < 0 || yIndex >= cellCnt) return -1;
    auto zIndex = getPointZIndex(point);
    if (zIndex < 0 || zIndex >= cellCnt) return -1;
    return xIndex * cellCnt * cellCnt + yIndex * cellCnt + zIndex;
}

int Grid::getPointXIndex(const Point &point) const {
    auto cellCntF = static_cast<float>(cellCnt);
    auto xIndex = static_cast<int>((point.x() + 1.f) * cellCntF / 2.f);
    if (point.x() == 1) xIndex--;
    return xIndex;
}

int Grid::getPointYIndex(const Point &point) const {
    auto cellCntF = static_cast<float>(cellCnt);
    auto yIndex = static_cast<int>((point.y() + 1.f) * cellCntF / 2.f);
    if (point.y() == 1) yIndex--;
    return yIndex;
}

int Grid::getPointZIndex(const Point &point) const {
    auto cellCntF = static_cast<float>(cellCnt);
    auto zIndex = static_cast<int>(point.z() * cellCntF);
    if (point.z() == 1) zIndex--;
    return zIndex;
}

const Vector<std::pair<long, ptr<Primitive>>> &Grid::operator[](int index) const {
    return grid[index];
}

int Grid::getCellCnt() const {
    return cellCnt;
}

const Vector<std::pair<long, ptr<Primitive>>> &Grid::at(int x, int y, int z) const {
    return grid.at(x * cellCnt * cellCnt + y * cellCnt + z);
}

int Grid::getPointCoordIndex(const Point &point, int coordIndex) const {
    switch (coordIndex) {
        case 0:
            return getPointXIndex(point);
        case 1:
            return getPointYIndex(point);
        case 2:
            return getPointZIndex(point);
        default:
            return -1;
    }
}

float Grid::getStep(int coordIndex) const {
    auto cellCntF = static_cast<float>(cellCnt);

    switch (coordIndex) {
        case 0:
        case 1:
            return 2.f / cellCntF;
        case 2:
            return 1.f /  cellCntF;
        default:
            return -1;
    }
}

std::pair<float, float> Grid::getMinAndMax(int coordIndex) {
    switch (coordIndex) {
        case 0:
        case 1:
            return {-1, 1};
        case 2:
            return {0, 1};
        default:
            return {};
    }
}

