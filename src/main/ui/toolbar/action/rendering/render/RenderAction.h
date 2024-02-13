//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_RENDERACTION_H
#define RAY_TRACING_RENDERACTION_H


#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/SceneAction.h"

class RenderAction : public SceneAction {
public:
    RenderAction(const QString &iconPath, SceneView &scene);

    void onMouseClicked() override;

};


#endif //RAY_TRACING_RENDERACTION_H
