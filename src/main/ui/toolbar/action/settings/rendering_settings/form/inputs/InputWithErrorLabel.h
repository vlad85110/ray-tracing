//
// Created by Влад Кирилов on 01.04.2023.
//

#ifndef FILTERS_INPUTWITHERRORLABEL_H
#define FILTERS_INPUTWITHERRORLABEL_H


#include <QWidget>

class InputWithErrorLabel : public QWidget {
public:
    virtual void clear() = 0;
    [[nodiscard]] virtual bool verify() const = 0;
};


#endif //FILTERS_INPUTWITHERRORLABEL_H
