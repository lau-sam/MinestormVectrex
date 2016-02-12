#include "spaceship.h"

SpaceShip::SpaceShip(QLine& shipLine, QImage& shipImage):_shipLine(shipLine),_shipImage(shipImage)
{
}

SpaceShip::SpaceShip()
{
    //std::cout << "Construction space ship vide" << std::endl;
}

SpaceShip::~SpaceShip()
{
    //std::cout<< "Destruction space ship" << std::endl;
}

void SpaceShip::accelerate()
{
    if (_speed > 8 && _speed <= 45)
    {
        _speed--;
    }else _speed = 8;
}

void SpaceShip::breakdown()
{
    if (_speed >= 8 && _speed < 45)
    {
        _speed++;
    }else _speed=45;

    /* recule
    auto x = (_line.p2().x()-_line.p1().x()) / 15;
    auto y = (_line.p2().y()-_line.p1().y()) / 15;
    _speed.setX(x);
    _speed.setY(y);
    _line.translate(_speed);
    std::cout<< "_varSpeed : "<< _varSpeed << endl << x << ";" << y << endl;
*/
}

void SpaceShip::turnLeft()
{
    int angle = -10;
    //p1 rotate, middle of line p1 p2
    QPoint ptRotatedP1 = rotatePoint(angle,
                                   QPoint((_shipLine.p1().x()+_shipLine.p2().x())/2,(_shipLine.p1().y()+_shipLine.p2().y())/2),
                                   _shipLine.p1());

    QPoint ptRotatedP2 = rotatePoint(angle,
                                     QPoint((_shipLine.p1().x()+_shipLine.p2().x())/2,(_shipLine.p1().y()+_shipLine.p2().y())/2),
                                     _shipLine.p2());

    _shipLine.setP1(ptRotatedP1);
    _shipLine.setP2(ptRotatedP2);
    _directionAngle = _directionAngle-angle;
}

void SpaceShip::turnRight()
{
    int angle = 10;
    QPoint ptRotatedP1 = rotatePoint(angle,
                                   QPoint((_shipLine.p1().x()+_shipLine.p2().x())/2,(_shipLine.p1().y()+_shipLine.p2().y())/2),
                                   _shipLine.p1());

    QPoint ptRotatedP2 = rotatePoint(angle,
                                     QPoint((_shipLine.p1().x()+_shipLine.p2().x())/2,(_shipLine.p1().y()+_shipLine.p2().y())/2),
                                     _shipLine.p2());

    _shipLine.setP1(ptRotatedP1);
    _shipLine.setP2(ptRotatedP2);
    _directionAngle = _directionAngle-angle;

}

Bullet SpaceShip::shoot()
{
    QLine line((_shipLine.p1().x() + _shipLine.p2().x())/2
               ,(_shipLine.p1().y() + _shipLine.p2().y())/2
               , _shipLine.p2().x()
               , _shipLine.p2().y());
    QImage image("image/bullet.png");
    Bullet mBullet(line,image);
    mBullet.setBulletImage(mBullet.getBulletImage().transformed(QMatrix().rotate(-_directionAngle)));
    return mBullet;
}

QLine SpaceShip::getShipLine()
{
    return _shipLine;
}

QImage SpaceShip::getShipImage()
{
    return _shipImage;
}

int SpaceShip::getDirectionAngle()
{
    return _directionAngle;
}

int SpaceShip::getSpeed()
{
    return _speed;
}

QPoint SpaceShip::getPointSpeed()
{
    return _pointSpeed;
}

void SpaceShip::setSpeed(int speed)
{
    _speed = speed;
}

void SpaceShip::setShipImage(QImage shipImage)
{
    _shipImage = shipImage;
}

void SpaceShip::setDirectionAngle(int directionAngle)
{
    _directionAngle = directionAngle;
}

void SpaceShip::setShipLine(QLine shipLine)
{
    _shipLine.setLine(shipLine.p1().x(),shipLine.p1().y(),shipLine.p2().x(),shipLine.p2().y());
}

void SpaceShip::setPointSpeed(QPoint pointSpeed)
{
    _pointSpeed.setX(pointSpeed.x());
    _pointSpeed.setY(pointSpeed.y());
}

QPoint SpaceShip::rotatePoint(int degree, QPoint origin, QPoint ptRotate) {
    double radianAngle = (degree * M_PI) / 180.0;
    double sinAngle = sin(radianAngle);
    double cosAngle = cos(radianAngle);

    int px = ptRotate.x() - origin.x();
    int py = ptRotate.y() - origin.y();

    float xnew = px * cosAngle - py * sinAngle;
    float ynew = py * cosAngle + px * sinAngle;

    px = xnew + origin.x();
    py = ynew + origin.y();

    return QPoint(px, py);
}

void SpaceShip::spaceShipOverScreenControle(int width, int height)
{
    int x1 = getShipLine().p1().x();
    int y1 = getShipLine().p1().y();
    int x2 = getShipLine().p2().x();
    int y2 = getShipLine().p2().y();

    //overscreen right
    if(getShipLine().p1().x() > width)
    {
        x1 = x1 - width;
        x2 = x2 - width;
    }
    //overscreen left
    if(getShipLine().p1().x() < 0)
    {
        x1 = x1 + width;
        x2 = x2 + width;
    }
    //overscreen top
    if(getShipLine().p1().y() < 0)
    {
        y1 = y1 + height;
        y2 = y2 + height;
    }
    //overscreen bottom
    if(getShipLine().p1().y() > height)
    {
        y1 = y1 - height;
        y2 = y2 - height;
    }

    QPoint p1(x1,y1);
    QPoint p2(x2,y2);
    setShipLine(QLine(p1,p2));
}

