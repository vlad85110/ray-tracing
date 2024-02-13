//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_RENDERINGGROUP_H
#define RAY_TRACING_RENDERINGGROUP_H

#include "main/types.h"

#include "main/ui/toolbar/action/rendering/select_view/SelectViewAction.h"
#include "main/ui/toolbar/action/rendering/render/RenderAction.h"
#include "main/ui/toolbar/action/ActionGroup.h"

class RenderingGroup : public ActionGroup {
    ptr<SelectViewAction> selectViewAction;
    ptr<RenderAction> renderAction;

public:
    explicit RenderingGroup(QObject *parent, SceneView &scene);

};


#endif //RAY_TRACING_RENDERINGGROUP_H
