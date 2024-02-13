//
// Created by Влад Кирилов on 24.05.2023.
//

#include <QDialogButtonBox>
#include <QFormLayout>
#include "RenderingForm.h"

RenderingForm::RenderingForm(const RenderConfig &config) : config(config) {
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setCenterButtons(true);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &RenderingForm::onOkClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto layout = new QFormLayout();

    bRInput = std::make_shared<DoubleInputWithErrorLabel>(1, 255, config.bR,
                                                             QString("Ambient R"), 0);
    layout->addWidget(bRInput.get());

    bGInput = std::make_shared<DoubleInputWithErrorLabel>(1, 255, config.bG,
                                                          QString("Ambient G"), 0);
    layout->addWidget(bGInput.get());

    bBInput = std::make_shared<DoubleInputWithErrorLabel>(1, 255, config.bB,
                                                          QString("Ambient B"), 0);
    layout->addWidget(bBInput.get());

    gammaInput = std::make_shared<DoubleInputWithErrorLabel>(0.1, 10, config.gamma,
                                                             QString("Gamma"), 2);
    layout->addWidget(gammaInput.get());

    depthInput = std::make_shared<DoubleInputWithErrorLabel>(1, 10, config.depth,
                                                          QString("Depth"), 0);
    layout->addWidget(depthInput.get());

    layout->addRow(buttonBox);
    setLayout(layout);
}

void RenderingForm::onOkClicked() {
    auto isValid = true;

    isValid &= bRInput->verify();
    isValid &= bGInput->verify();
    isValid &= bBInput->verify();
    isValid &= gammaInput->verify();
    isValid &= depthInput->verify();

    if (!isValid) return;

    config.bR = static_cast<int>(bRInput->getValue());
    config.bG = static_cast<int>(bGInput->getValue());
    config.bB = static_cast<int>(bBInput->getValue());

    config.gamma = static_cast<float>(gammaInput->getValue());
    config.depth = static_cast<int>(depthInput->getValue());

    accept();
}

const RenderConfig &RenderingForm::getConfig() const {
    return config;
}
