#include "mine.h"


Mine::Mine(){

}

Mine::Mine(QLine &mineLine,QImage &mineImage,QSize &mineSize): GameObject(mineLine,mineImage), _mineSize(mineSize)
{

}

Mine::~Mine()
{

}

void Mine::draw(QPainter &painter)
{
    painter.drawLine(getLine());
    painter.drawImage(QRect(QPoint(((getLine().p1().x()+getLine().p2().x())/2)-(getMineSize().width()/2),
                                    ((getLine().p1().y()+getLine().p2().y())/2)-(getMineSize().height()/2))
                             ,getMineSize()),
                      getImage());
}

QSize Mine::getMineSize()
{
    return _mineSize;
}

void Mine::setMineSize(QSize mineSize)
{
    _mineSize.setWidth(mineSize.width());
    _mineSize.setHeight(mineSize.height());
}
