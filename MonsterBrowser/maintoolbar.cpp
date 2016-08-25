#include "maintoolbar.h"
#include "serveractions.h"
#include <QHBoxLayout>


MainToolBar::MainToolBar(QWidget* parent) : QToolBar(parent)
{
    setMovable(false);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setIconSize(QSize(48, 32));

    QAction* action = addAction(QIcon(":/icons/box_download_32.png"),
                                "Check for new");
    connect(action, &QAction::triggered, serverActions,
            &ServerActions::checkForNew);
    action = addAction(QIcon(":/icons/refresh_32.png"), "Refresh all");
    connect(action, &QAction::triggered, serverActions,
            &ServerActions::refreshAll);
    action = addAction(QIcon(":/icons/add_32.png"), "Add...");
    action = addAction(QIcon(":/icons/spanner_32.png"), "Settings");

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
