//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_LIGHTSOURCE_H
#define RAY_TRACING_LIGHTSOURCE_H

#include <QRgb>
#include "main/types.h"
#include "main/model/primitives/Primitive.h"

class LightSource : public Primitive {
private:
    QRgb color;

public:
    LightSource(const Point &point, QRgb color);

    [[nodiscard]] const Point &getPoint() const;

    [[nodiscard]] QRgb getColor() const;

    void setColor(QRgb color);
};




#endif //RAY_TRACING_LIGHTSOURCE_H
