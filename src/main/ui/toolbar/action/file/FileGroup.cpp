//
// Created by Влад Кирилов on 08.05.2023.
//

#include "FileGroup.h"
#include "main/scene/view/SceneView.h"

FileGroup::FileGroup(QObject *parent, SceneView &scene) : ActionGroup(parent, "File") {
    QString iconPathPrefix = "/Users/vladkirilov/CLionProjects/ray tracing/resources/icons/";

    loadRenderingConfigAction = make_shared<LoadRenderingConfigAction>(iconPathPrefix
                                                                         + "loadRenderConfig.png", scene);

    loadSceneConfigAction = make_shared<LoadSceneConfigAction>(iconPathPrefix
                                                               + "loadSceneConfig.png", scene);

    saveRenderingConfigAction = make_shared<SaveRenderingConfigAction>(iconPathPrefix
                                                                       + "saveRenderConfig.png", scene);

    saveRenderingImageAction = make_shared<SaveRenderingImageAction>(iconPathPrefix + "saveRenderingImage", scene);

    addAction(loadSceneConfigAction.get());
    addAction(loadRenderingConfigAction.get());
    addAction(saveRenderingImageAction.get());
    addAction(saveRenderingConfigAction.get());
}
