//
// Created by Влад Кирилов on 21.03.2023.
//

#ifndef FILTERS_DOUBLEINPUTWITHERRORLABEL_H
#define FILTERS_DOUBLEINPUTWITHERRORLABEL_H


#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include "DoubleNumSlider.h"
#include "InputWithErrorLabel.h"

struct DoubleInputWithErrorLabel : public InputWithErrorLabel {
Q_OBJECT
private:
    double min;
    double max;

    std::shared_ptr<QLineEdit> input;
    std::shared_ptr<DoubleNumSlider> slider;
    std::shared_ptr<QLabel> label;
    std::shared_ptr<QLabel> errorLabel;

    [[nodiscard]] bool _validate(bool isErrorSet) const;

public:
    DoubleInputWithErrorLabel(double min, double max, double value, QString &&labelText,
                              int accuracy);

    [[nodiscard]] double getValue() const;

    void setValue(double value);

    void clear() override;

    [[nodiscard]] bool verify() const override;

private slots:

    void inputChanged();

    void sliderChanged();
};


#endif //FILTERS_DOUBLEINPUTWITHERRORLABEL_H
