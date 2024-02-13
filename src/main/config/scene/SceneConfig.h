//
// Created by Влад Кирилов on 07.05.2023.
//

#ifndef RAY_TRACING_SCENECONFIG_H
#define RAY_TRACING_SCENECONFIG_H

#include "main/types.h"
#include "main/model/light/ScatteredLight.h"
#include "main/model/light/LightSource.h"
#include "main/model/primitives/box/Box.h"
#include "main/model/primitives/triangle/Triangle.h"
#include "main/model/primitives/sphere/Sphere.h"
#include "main/model/primitives/quadrangle/Quadrangle.h"

struct SceneConfig {
    ScatteredLight scatteredLight;
    Vector<LightSource> lightSources;
    Vector<ptr<Primitive>> primitives;
};


#endif //RAY_TRACING_SCENECONFIG_H
