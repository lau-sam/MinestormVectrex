#include "mine.h"


Mine::Mine(){

}

Mine::Mine(QLine &mineLine,QImage &mineImage,QSize &mineSize): _mineLine(mineLine), _mineImage(mineImage), _mineSize(mineSize)
{

}

Mine::~Mine()
{

}

bool Mine::collideWithSpaceShip(QLine spaceShipLine)
{
    int distance = (_mineSize.width()/2)+10;
    bool collide = false;
    auto xShip = (spaceShipLine.p1().x()+spaceShipLine.p2().x())/2;
    auto yShip = (spaceShipLine.p1().y()+spaceShipLine.p2().y())/2;
    auto xMine = (_mineLine.p1().x()+_mineLine.p2().x())/2;
    auto yMine = (_mineLine.p1().y()+_mineLine.p2().y())/2;
    if(abs(xShip-xMine) < distance && abs(yShip-yMine) < distance)
    {
        collide = true;
    }
    return collide;
}

QLine Mine::getMineLine()
{
    return _mineLine;
}

QImage Mine::getMineImage()
{
    return _mineImage;
}

QSize Mine::getMineSize()
{
    return _mineSize;
}

void Mine::setMineLine(QLine mineLine)
{
    _mineLine.setLine(mineLine.p1().x(),mineLine.p1().y(),mineLine.p2().x(),mineLine.p2().y());
}

void Mine::setMineImage(QImage mineImage)
{
   _mineImage=mineImage;
}

void Mine::setMineSize(QSize mineSize)
{
    _mineSize.setWidth(mineSize.width());
    _mineSize.setHeight(mineSize.height());
}
