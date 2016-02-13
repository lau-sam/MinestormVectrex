#include "spaceship.h"

SpaceShip::SpaceShip(QLine& shipLine, QImage& shipImage): GameObject(shipLine,shipImage)
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

void SpaceShip::draw(QPainter &painter)
{
    painter.drawLine(getLine());
    painter.drawImage(QRect(QPoint(((getLine().p1().x()+getLine().p2().x())/2)-20,
                                   ((getLine().p1().y()+getLine().p2().y())/2)-20),QSize(40,40)),
                      getImage().transformed(QMatrix().rotate(-getAngle())));
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
    QPoint ptRotatedP1 = GameObject::rotatePoint(angle,
                                   QPoint((_line.p1().x()+_line.p2().x())/2,(_line.p1().y()+_line.p2().y())/2),
                                   _line.p1());

    QPoint ptRotatedP2 = GameObject::rotatePoint(angle,
                                     QPoint((_line.p1().x()+_line.p2().x())/2,(_line.p1().y()+_line.p2().y())/2),
                                     _line.p2());

    _line.setP1(ptRotatedP1);
    _line.setP2(ptRotatedP2);
    _angle = _angle-angle;
}

void SpaceShip::turnRight()
{
    int angle = 10;
    QPoint ptRotatedP1 = GameObject::rotatePoint(angle,
                                   QPoint((_line.p1().x()+_line.p2().x())/2,(_line.p1().y()+_line.p2().y())/2),
                                   _line.p1());

    QPoint ptRotatedP2 = GameObject::rotatePoint(angle,
                                     QPoint((_line.p1().x()+_line.p2().x())/2,(_line.p1().y()+_line.p2().y())/2),
                                     _line.p2());
    _line.setP1(ptRotatedP1);
    _line.setP2(ptRotatedP2);
    _angle = _angle-angle;

}

Bullet SpaceShip::shoot()
{
    QLine line((_line.p1().x() + _line.p2().x())/2
               ,(_line.p1().y() + _line.p2().y())/2
               , _line.p2().x()
               , _line.p2().y());
    QImage image("image/bullet.png");
    Bullet mBullet(line,image);
    mBullet.setImage(mBullet.getImage().transformed(QMatrix().rotate(-_angle)));
    return mBullet;
}

int SpaceShip::getAngle()
{
    return _angle;
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

void SpaceShip::setAngle(int angle)
{
    _angle = angle;
}

void SpaceShip::setPointSpeed(QPoint pointSpeed)
{
    _pointSpeed.setX(pointSpeed.x());
    _pointSpeed.setY(pointSpeed.y());
}

void SpaceShip::spaceShipOverScreenControle(int width, int height)
{
    int x1 = getLine().p1().x();
    int y1 = getLine().p1().y();
    int x2 = getLine().p2().x();
    int y2 = getLine().p2().y();

    //overscreen right
    if(getLine().p1().x() > width)
    {
        x1 = x1 - width;
        x2 = x2 - width;
    }
    //overscreen left
    if(getLine().p1().x() < 0)
    {
        x1 = x1 + width;
        x2 = x2 + width;
    }
    //overscreen top
    if(getLine().p1().y() < 0)
    {
        y1 = y1 + height;
        y2 = y2 + height;
    }
    //overscreen bottom
    if(getLine().p1().y() > height)
    {
        y1 = y1 - height;
        y2 = y2 - height;
    }

    QPoint p1(x1,y1);
    QPoint p2(x2,y2);
    setLine(QLine(p1,p2));
}

