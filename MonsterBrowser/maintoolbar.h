#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QToolBar>


class MainToolBar : public QToolBar
{
public:
    MainToolBar(QWidget* parent);

private:
    QGroupBox* filterBar_;
};

#endif // MAINTOOLBAR_H
