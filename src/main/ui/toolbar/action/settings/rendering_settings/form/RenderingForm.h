//
// Created by Влад Кирилов on 24.05.2023.
//

#ifndef RAY_TRACING_RENDERINGFORM_H
#define RAY_TRACING_RENDERINGFORM_H


#include <QDialog>
#include "main/config/render/RenderConfig.h"
#include "inputs/DoubleInputWithErrorLabel.h"
#include "main/types.h"

class RenderingForm : public QDialog {
Q_OBJECT

private:
    RenderConfig config;

    ptr<DoubleInputWithErrorLabel> bRInput;
    ptr<DoubleInputWithErrorLabel> bGInput;
    ptr<DoubleInputWithErrorLabel> bBInput;
    ptr<DoubleInputWithErrorLabel> gammaInput;
    ptr<DoubleInputWithErrorLabel> depthInput;

public:
    explicit RenderingForm(const RenderConfig &config);

    [[nodiscard]] const RenderConfig &getConfig() const;

private slots:

    void onOkClicked();
};


#endif //RAY_TRACING_RENDERINGFORM_H
