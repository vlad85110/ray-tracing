//
// Created by Влад Кирилов on 08.05.2023.
//

#include "SettingsGroup.h"

SettingsGroup::SettingsGroup(QObject *parent, SceneView &scene) : ActionGroup(parent, "Settings") {
    QString iconPathPrefix = "/Users/vladkirilov/CLionProjects/ray tracing/resources/icons/";

    initAction = make_shared<InitAction>(iconPathPrefix + "init.png", scene);
    renderingSettingsAction = make_shared<RenderingSettingsAction>(iconPathPrefix + "settings.png", scene);

    addAction(initAction.get());
    addAction(renderingSettingsAction.get());
}

const InitAction &SettingsGroup::getInitAction() const {
    return *initAction;
}

const RenderingSettingsAction &SettingsGroup::getRenderingSettingsAction() const {
    return *renderingSettingsAction;
}
