//
// Created by Влад Кирилов on 08.05.2023.
//

#ifndef RAY_TRACING_SETTINGSGROUP_H
#define RAY_TRACING_SETTINGSGROUP_H

#include <memory>
#include "main/ui/toolbar/action/settings/init/InitAction.h"
#include "main/ui/toolbar/action/settings/rendering_settings/RenderingSettingsAction.h"
#include "main/ui/toolbar/action/ActionGroup.h"
#include "main/types.h"

class SettingsGroup : public ActionGroup {
private:
    ptr<InitAction> initAction;
    ptr<RenderingSettingsAction> renderingSettingsAction;

public:
    explicit SettingsGroup(QObject *parent, SceneView &scene);

    [[nodiscard]] const InitAction &getInitAction() const;

    [[nodiscard]] const RenderingSettingsAction &getRenderingSettingsAction() const;
};


#endif //RAY_TRACING_SETTINGSGROUP_H
