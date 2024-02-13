//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_RENDERINGSETTINGSACTION_H
#define RAY_TRACING_RENDERINGSETTINGSACTION_H


#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/SceneAction.h"

class RenderingSettingsAction : public SceneAction {
public:
    RenderingSettingsAction(const QString &iconPath, SceneView &scene);

    void onMouseClicked() override;

};


#endif //RAY_TRACING_RENDERINGSETTINGSACTION_H
