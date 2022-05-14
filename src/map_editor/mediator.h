#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QObject>

class QAction;
class QGraphicsScene;
class QLayout;
class QGraphicsItem;
class EditorView;
class MainWindow;
class EditorData;
class CellGrid;

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
signals:

private:
    void ResetSceneBackGround();

private:
    MainWindow& main_window_;

    CellGrid* cell_grid_;

    EditorView* editor_view_;
    QGraphicsScene* editor_scene_;
    EditorData* editor_data_;
};

#endif // MEDIATOR_H
