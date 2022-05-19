#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QIcon>
#include <QWidget>

class ToolAction : public QObject
{
    Q_OBJECT
public:
    ToolAction(QObject* parent = nullptr);
    ToolAction(const QIcon& icon, const QString& text, QObject* parent = nullptr);
    ToolAction(const ToolAction& action);
    ~ToolAction();

private:
    QString data_;
    QIcon icon_;
};

class ToolWidget : public QWidget
{
public:
    ToolWidget(QWidget* parent = nullptr);
    ~ToolWidget() override;

Q_SIGNALS:

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void moveEvent(QMoveEvent* event) override;

private:
    QList<ToolAction> actions_;

    int hover_id_;
    int select_id_;

    QSize size_;
    int btns_col_;
    int btns_row_;
    int space_;
};

#endif // TOOLWIDGET_H
