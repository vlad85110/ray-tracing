//
// Created by Влад Кирилов on 24.05.2023.
//

#ifndef RAY_TRACING_SCENEACTION_H
#define RAY_TRACING_SCENEACTION_H


#include "ToolbarAction.h"
#include "main/Fwd.h"

class SceneAction : public ToolbarAction {
protected:
    SceneView& scene;

public:
    SceneAction(const QString &iconPath, const QString &name, SceneView &scene);
};


#endif //RAY_TRACING_SCENEACTION_H
