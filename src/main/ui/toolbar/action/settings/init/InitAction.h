//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_INITACTION_H
#define RAY_TRACING_INITACTION_H


#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/SceneAction.h"

class InitAction : public SceneAction {
public:
    InitAction(const QString &iconPath, SceneView &scene);

    void onMouseClicked() override;
};


#endif //RAY_TRACING_INITACTION_H
