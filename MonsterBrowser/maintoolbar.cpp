#include "maintoolbar.h"
#include "serveractions.h"
#include <QHBoxLayout>


MainToolBar::MainToolBar(QWidget* parent) : QToolBar(parent)
{
    setMovable(false);

    QAction* action = addAction("Check for new");
    connect(action, &QAction::triggered, serverActions,
            &ServerActions::checkForNew);
    action = addAction("Refresh all");
    connect(action, &QAction::triggered, serverActions,
            &ServerActions::refreshAll);
    action = addAction("Add...");
    action = addAction("Settings");

    // Add some space after the buttons.
    QWidget* spacer = new QWidget(this);
    spacer->setMinimumWidth(40);
    addWidget(spacer);

    filterBar_ = new QGroupBox("Filters and game selection", this);
    QHBoxLayout* filterLayout = new QHBoxLayout();

    QCheckBox* notEmptyButton = new QCheckBox("Not empty", filterBar_);
    filterLayout->addWidget(notEmptyButton);

    QCheckBox* hasHumansButton = new QCheckBox("Has humans", filterBar_);
    filterLayout->addWidget(hasHumansButton);

    QComboBox* gamesCombo = new QComboBox(filterBar_);
    gamesCombo->addItem("Smokin' Guns");
    gamesCombo->addItem("World of Padman");
    gamesCombo->addItem("baseq3");
    filterLayout->addWidget(gamesCombo);

    filterBar_->setLayout(filterLayout);
    addWidget(filterBar_);
}
