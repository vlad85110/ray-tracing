//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_SELECTVIEWACTION_H
#define RAY_TRACING_SELECTVIEWACTION_H


#include "main/ui/toolbar/action/ToolbarAction.h"
#include "main/ui/toolbar/action/SceneAction.h"

class SelectViewAction : public SceneAction {
public:
    SelectViewAction(const QString &iconPath, SceneView &scene);

    void onMouseClicked() override;

};


#endif //RAY_TRACING_SELECTVIEWACTION_H
