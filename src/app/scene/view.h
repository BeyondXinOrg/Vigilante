#ifndef BATTLEVIEW_H
#define BATTLEVIEW_H

#include <QGraphicsView>

class PathGrid;
class SceneManager;
class Gui;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget* parent = nullptr);
    ~View() override;
    void SetSceneManager(SceneManager* scene_mgr);

    void ShowWidget(int w, int h);

    QPoint GetCenterCamPos() const;
    void SetCenterCamPos(QPointF position);

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
    SceneManager* scene_mgr_;

    bool drag_cam_;
    QPoint press_pos_;
    QPoint cam_center_pos_;

    double cam_rect_[2];
    double cam_pos_max_[2];

    QTimer* gui_update_timer_;
};

#endif // BATTLEVIEW_H
