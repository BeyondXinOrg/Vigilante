#include "tool_widget.h"

ToolAction::ToolAction(QObject* parent)
  : QObject(parent)
{
}

ToolAction::ToolAction(const QIcon& icon,
                       const QString& text, QObject* parent)
  : ToolAction(parent)
{
    icon_ = icon;
    data_ = text;
}

ToolAction::ToolAction(const ToolAction& action)
  : QObject(nullptr)
{
    icon_ = action.icon_;
    data_ = action.data_;
}

ToolAction::~ToolAction()
{
}

ToolWidget::ToolWidget(QWidget* parent)
{
    qRegisterMetaType<ToolAction>("ToolAction&");
    qRegisterMetaType<ToolAction>("ToolAction");
}

ToolWidget::~ToolWidget()
{
}

void ToolWidget::paintEvent(QPaintEvent* event)
{
}

void ToolWidget::mousePressEvent(QMouseEvent* event)
{
}

void ToolWidget::moveEvent(QMoveEvent* event)
{
}
