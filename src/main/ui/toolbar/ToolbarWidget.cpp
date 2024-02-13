//
// Created by Влад Кирилов on 24.04.2023.
//

#include "ToolbarWidget.h"

ToolbarWidget::ToolbarWidget(QWidget *parent, SceneView &scene) : QToolBar(parent) {
    setFixedHeight(25);

    setMovable(false);

    auto iconPrefix = QString("/Users/vladkirilov/CLionProjects/ray tracing/resources/icons/");

    fileGroup = make_shared<FileGroup>(this, scene);
//    addActions(fileGroup->actions());
    addSeparator();

    renderingGroup = make_shared<RenderingGroup>(this, scene);
    addActions(renderingGroup->actions());
    addSeparator();

    settingsGroup = make_shared<SettingsGroup>(this, scene);
    addActions(settingsGroup->actions());
    addSeparator();

    aboutAction = make_shared<AboutAction>(iconPrefix + "about.png");
    addAction(aboutAction.get());
}

SettingsGroup *ToolbarWidget::getSettingsGroup() const {
    return settingsGroup.get();
}

RenderingGroup *ToolbarWidget::getRenderGroup() const {
    return renderingGroup.get();
}

FileGroup *ToolbarWidget::getFileGroup() const {
    return fileGroup.get();
}

AboutAction *ToolbarWidget::getAboutAction() const {
    return aboutAction.get();
}
