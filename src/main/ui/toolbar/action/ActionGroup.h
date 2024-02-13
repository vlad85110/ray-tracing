//
// Created by Влад Кирилов on 26.03.2023.
//

#ifndef FILTERS_ABSTRACTACTIONGROUP_H
#define FILTERS_ABSTRACTACTIONGROUP_H

#include <QMenu>
#include <QActionGroup>

class ActionGroup : public QActionGroup {
Q_OBJECT
public:
    [[nodiscard]] QMenu *getMenu() const;

    QString name;

protected:
     ActionGroup(QObject *parent, QString name);
};


#endif //FILTERS_ABSTRACTACTIONGROUP_H
