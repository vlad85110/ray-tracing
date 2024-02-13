//
// Created by Влад Кирилов on 08.05.2023.
//

#include "RenderingSettingsAction.h"
#include "main/ui/toolbar/action/settings/rendering_settings/form/RenderingForm.h"
#include "main/scene/view/SceneView.h"

RenderingSettingsAction::RenderingSettingsAction(const QString &iconPath, SceneView &scene)
        : SceneAction(iconPath, "Rendering settings", scene) {}

void RenderingSettingsAction::onMouseClicked() {
    ToolbarAction::onMouseClicked();

    RenderingForm form(scene.getConfig());

    auto res = form.exec();
    if (res == QDialog::Rejected) return;

    scene.setConfig(form.getConfig());
}
