#ifndef BATTLEVIEW_H
#define BATTLEVIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget* parent = nullptr);
    ~View() override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // BATTLEVIEW_H
