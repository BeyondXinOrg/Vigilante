#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMouseEvent>
#include <QObject>

class QAction;
class QGraphicsScene;
class QLayout;
class QGraphicsItem;
class EditorView;
class MainWindow;
class EditorData;
class CellGrid;
class ToolWidget;
class QGraphicsRectItem;

/*! 充当主窗口和编辑器组件之间的通信通道：
 *  - MainWindow <-> Mediator <-> QGraphicsScene / EditorView / EditorData
 *  - EditorView <-> Mediator <-> EditorData
 */
class Mediator : public QObject
{
    Q_OBJECT
public:
    explicit Mediator(MainWindow& mainWindow);
    void InitScene();
    void CreateNewMap();
    void AddTileTypeItem(QGraphicsItem* item);

public:
    void MousePress(QMouseEvent* event);
    void MouseMove(QMouseEvent* event);
    void MouseRelease(QMouseEvent* event);

signals:

private:
    void ResetSceneBackGround();
    void MoveBgLayout(const QPointF& delta);

private:
    MainWindow& main_window_;
    ToolWidget* tool_wid_;

    CellGrid* cell_grid_;

    EditorView* editor_view_;
    QGraphicsScene* editor_scene_;
    EditorData* editor_data_;
    QGraphicsRectItem* lay_bg_;

    QPointF prev_mid_mouse_pos_;
};

#endif // MEDIATOR_H
