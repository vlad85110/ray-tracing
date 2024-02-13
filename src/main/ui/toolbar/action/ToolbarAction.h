//
// Created by Влад Кирилов on 15.03.2023.
//

#ifndef FILTERS_TOOLBARACTION_H
#define FILTERS_TOOLBARACTION_H

#include <QPushButton>
#include <QMenu>
#include <QAction>


class ToolbarAction : public QAction {
Q_OBJECT
protected:
    QString name;

public:
    ToolbarAction(const QString &iconPath, const QString &name);
    virtual void onMouseClicked(){};
    ~ToolbarAction() override;

public slots:
    virtual void onTrigger();
};


#endif //FILTERS_TOOLBARACTION_H
