#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>

class Mediator;

class EditorView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit EditorView(Mediator* mediator, QWidget* parent = nullptr);
    ~EditorView() override;

    void ScaleScene(const double& new_scale);
    void ScaleSceneByPoint(const double& new_scale, const QPointF& point);

    void UpdateSceneRect();

Q_SIGNALS:

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void wheelEvent(QWheelEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

private:
    double current_scale_, max_scale_, min_scale_;

    Mediator* mediator_;
};

#endif // EDITORVIEW_H
