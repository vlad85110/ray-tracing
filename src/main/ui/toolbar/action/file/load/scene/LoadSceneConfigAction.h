//
// Created by Влад Кирилов on 09.05.2023.
//

#ifndef RAY_TRACING_LOADSCENECONFIGACTION_H
#define RAY_TRACING_LOADSCENECONFIGACTION_H


#include "main/ui/toolbar/action/file/load/LoadFileAction.h"

class LoadSceneConfigAction : public LoadFileAction {
public:
    LoadSceneConfigAction(const QString &iconPath, SceneView &scene);

protected:
    void handleFile(QString fileName) override;

    [[nodiscard]] QString getFileExtensions() const override;

    [[nodiscard]] QString getFileDialogName() const override;
};


#endif //RAY_TRACING_LOADSCENECONFIGACTION_H
