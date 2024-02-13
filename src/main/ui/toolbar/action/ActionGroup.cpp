//
// Created by Влад Кирилов on 26.03.2023.
//

#include "ActionGroup.h"

#include <utility>

ActionGroup::ActionGroup(QObject *parent, QString name) :
        QActionGroup(parent), name(std::move(name)) {}

QMenu *ActionGroup::getMenu() const {
    auto res = new QMenu(name);
    res->addActions(actions());
    return res;
}

