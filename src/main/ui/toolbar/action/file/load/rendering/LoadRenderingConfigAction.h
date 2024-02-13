//
// Created by Влад Кирилов on 09.05.2023.
//

#ifndef RAY_TRACING_LOADRENDERINGCONFIGACTION_H
#define RAY_TRACING_LOADRENDERINGCONFIGACTION_H


#include "main/ui/toolbar/action/file/load/LoadFileAction.h"

class LoadRenderingConfigAction : public LoadFileAction {
public:
    LoadRenderingConfigAction(const QString &iconPath, SceneView &scene);

protected:
    void handleFile(QString fileName) override;

    [[nodiscard]] QString getFileExtensions() const override;

    [[nodiscard]] QString getFileDialogName() const override;
};


#endif //RAY_TRACING_LOADRENDERINGCONFIGACTION_H
