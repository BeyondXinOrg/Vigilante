#ifndef BATTLEVIEW_H
#define BATTLEVIEW_H

#include <QGraphicsView>

class BattleView : public QGraphicsView
{
    Q_OBJECT
public:
    BattleView(QWidget* parent = nullptr);
    ~BattleView() override;
};

#endif // BATTLEVIEW_H
