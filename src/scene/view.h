#ifndef BATTLEVIEW_H
#define BATTLEVIEW_H

#include <QGraphicsView>

class PathGrid;
class Gui;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget* parent = nullptr);
    ~View() override;

    void ShowWidget(PathGrid* cell_grid, int w, int h);

    QPoint GetCenterCamPos() const;
    void SetCenterCamPos(QPointF position);

    void AddGui(Gui* gui);

Q_SIGNALS:
    void SgnMousePress();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    void UpdateGuiPositions();

private:
    // 网格数据
    PathGrid* path_grid_;

    bool drag_cam_;
    QPoint drag_cam_mouse_pos_;
    QPoint drag_cam_center_pos_;

    double cam_rect_[2];
    double cam_pos_max_[2];

    QGraphicsRectItem* lay_gui_;
    QTimer* gui_update_timer_;
};

#endif // BATTLEVIEW_H
