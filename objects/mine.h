#ifndef MINE_H
#define MINE_H

#include <QPoint>
#include <QImage>
#include <iostream>
#include <QLine>
#include <QSize>

class Mine
{
public:
    Mine();
    Mine(QLine &mineLine,QImage &mineImage,QSize &mineSize);
    ~Mine();
    bool collideWithSpaceShip(QLine spaceShipLine);

    QLine getMineLine();
    QImage getMineImage();
    QSize getMineSize();

    void setMineLine(QLine mineLine);
    void setMineImage(QImage mineImage);
    void setMineSize(QSize mineSize);
private:
    QLine _mineLine;
    QImage _mineImage;
    QSize _mineSize;
};

#endif // MINE_H
