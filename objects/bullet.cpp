#include "bullet.h"

Bullet::Bullet(QLine& bulletLine, QImage& bulletImage):_bulletLine(bulletLine),_bulletImage(bulletImage)
{
}

Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}

bool Bullet::collideWithSpaceShip(QLine spaceShipLine)
{
    int distance = 40;
    bool collide = false;
    auto xShip = (spaceShipLine.p1().x()+spaceShipLine.p2().x())/2;
    auto yShip = (spaceShipLine.p1().y()+spaceShipLine.p2().y())/2;
    auto xBullet = (_bulletLine.p1().x()+_bulletLine.p2().x())/2;
    auto yBullet = (_bulletLine.p1().y()+_bulletLine.p2().y())/2;
    if(abs(xShip-xBullet) < distance && abs(yShip-yBullet) < distance)
    {
        collide = true;
    }
    return collide;
}

QLine Bullet::getBulletLine()
{
    return _bulletLine;
}

QImage Bullet::getBulletImage()
{
    return _bulletImage;
}

void Bullet::setBulletLine(QLine bulletLine)
{
    _bulletLine.setLine(bulletLine.p1().x(),bulletLine.p1().y(),bulletLine.p2().x(),bulletLine.p2().y());
}

void Bullet::setBulletImage(QImage bulletImage)
{
    _bulletImage = bulletImage;
}
