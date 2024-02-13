//
// Created by Влад Кирилов on 21.03.2023.
//

#include <QFormLayout>
#include <iostream>
#include "DoubleInputWithErrorLabel.h"

DoubleInputWithErrorLabel::DoubleInputWithErrorLabel(double min, double max, double value, QString &&labelText,
                                                     int accuracy) {
    this->min = min;
    this->max = max;

    slider = std::make_shared<DoubleNumSlider>(accuracy, min, max);
    label = std::make_shared<QLabel>(std::move(labelText));
    input = std::make_shared<QLineEdit>(QString::number(value));

    slider->setValue(value);

    errorLabel = std::make_shared<QLabel>();
    errorLabel->setStyleSheet("QLabel { color : red; }");

    auto layout = new QFormLayout();
    layout->addRow(label.get(), input.get());
    layout->addRow(slider.get());
    layout->addRow(errorLabel.get());
    setLayout(layout);

    connect(input.get(), &QLineEdit::textChanged, this,
            &DoubleInputWithErrorLabel::inputChanged);
    connect(slider.get(), &QSlider::valueChanged, this,
            &DoubleInputWithErrorLabel::sliderChanged);
}

bool DoubleInputWithErrorLabel::_validate(bool isErrorSet) const {
    auto text = input->text();
    auto value = text.toDouble();

    auto error = QString("Значение должно быть числом от ") + QString::number(min)
                 + " до " + QString::number(max);

    if (value == 0) {
        double stdVal;
        try {
            stdVal = std::stod(text.toStdString());
        }
        catch (std::exception &e) {
            if (isErrorSet) errorLabel->setText(error);
            return false;
        }

        if (stdVal != 0) {
            if (isErrorSet) errorLabel->setText(error);
            return false;
        }
    }

    if (value < min || value > max) {
        if (isErrorSet) errorLabel->setText(error);
        return false;
    }

    if (isErrorSet) errorLabel->setText("");
    return true;
}

double DoubleInputWithErrorLabel::getValue() const {
    return input->text().toDouble();
}

void DoubleInputWithErrorLabel::clear() {
    errorLabel->clear();
    input->clear();
}

void DoubleInputWithErrorLabel::inputChanged() {
    if (_validate(false)) {
        slider->setValue(input->text().toDouble());
    }
}

void DoubleInputWithErrorLabel::sliderChanged() {
    input->setText(QString::number(slider->getValue()));
}

void DoubleInputWithErrorLabel::setValue(double value) {
    input->setText(QString::number(value));
}

bool DoubleInputWithErrorLabel::verify() const {
    return _validate(true);
}


