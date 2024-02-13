//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_FILEGROUP_H
#define RAY_TRACING_FILEGROUP_H

#include "main/types.h"

#include "main/ui/toolbar/action/ActionGroup.h"
#include "main/ui/toolbar/action/file/load/rendering/LoadRenderingConfigAction.h"
#include "main/ui/toolbar/action/file/load/scene/LoadSceneConfigAction.h"
#include "main/ui/toolbar/action/file/save/rendering_config/SaveRenderingConfigAction.h"
#include "main/ui/toolbar/action/file/save/rendering_image/SaveRenderingImageAction.h"
#include "main/Fwd.h"

class FileGroup : public ActionGroup {
public:
    explicit FileGroup(QObject *parent, SceneView &scene);

private:
    ptr<LoadRenderingConfigAction> loadRenderingConfigAction;
    ptr<LoadSceneConfigAction> loadSceneConfigAction;
    ptr<SaveRenderingConfigAction> saveRenderingConfigAction;
    ptr<SaveRenderingImageAction> saveRenderingImageAction;

};


#endif //RAY_TRACING_FILEGROUP_H
