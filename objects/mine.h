#ifndef MINE_H
#define MINE_H

#include <QSize>
#include "gameobject.h"

class Mine : public GameObject
{
public:
    Mine();
    Mine(QLine &mineLine,QImage &mineImage,QSize &mineSize);
    ~Mine();
    QSize getMineSize();
    void setMineSize(QSize mineSize);
    void draw(QPainter &painter);
private:
    QSize _mineSize;
};

#endif // MINE_H
