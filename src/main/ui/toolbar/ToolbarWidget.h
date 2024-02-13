//
// Created by Влад Кирилов on 24.04.2023.
//

#ifndef WIREFRAME_TOOLBARWIDGET_H
#define WIREFRAME_TOOLBARWIDGET_H

#include <QToolBar>

#include "main/ui/toolbar/action/settings/SettingsGroup.h"
#include "main/ui/toolbar/action/rendering/RenderingGroup.h"
#include "main/ui/toolbar/action/file/FileGroup.h"
#include "main/ui/toolbar/action/about/AboutAction.h"
#include "main/types.h"

class ToolbarWidget : public QToolBar {
Q_OBJECT
private:
    ptr<SettingsGroup> settingsGroup;
    ptr<RenderingGroup> renderingGroup;
    ptr<FileGroup> fileGroup;
    ptr<AboutAction> aboutAction;

public:
    explicit ToolbarWidget(QWidget *parent, SceneView &scene);

    [[nodiscard]] SettingsGroup *getSettingsGroup() const;

    [[nodiscard]] RenderingGroup *getRenderGroup() const;

    [[nodiscard]] FileGroup *getFileGroup() const;

    [[nodiscard]] AboutAction *getAboutAction() const;
};


#endif //WIREFRAME_TOOLBARWIDGET_H
