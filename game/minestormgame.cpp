#include "minestormgame.h"

#include <QColor>
#include <iostream>
#include <math.h>

MinestormGame::MinestormGame(const QSize &size,QObject *parent):Game(size,parent), _currentStyle(Qt::SolidPattern) {
    initialize();
}

void MinestormGame::initialize() {
    //clear list : _mines, _spaceShipBullets, _enemiesBullets, _enemies, _hearths
    _spaceShipBullets.clear();
    _enemiesBullets.clear();
    _enemies.clear();
    _mines.clear();
    _hearths.clear();
    _currentStyle = Qt::SolidPattern;
    //spaceship
    _spaceShip.setShipImage(QImage("image/mario.png"));
    _spaceShip.setShipLine(QLine(500,320,500,280));
    _spaceShip.setDirectionAngle(180);
    _spaceShip.setPointSpeed(QPoint(0,0));
    _spaceShip.setSpeed(45);
    //spaceship
    _spaceShipShootControl = 20;
    _enemyShootIntervalle = 0u;
    _score=0;
    _health = 30;
    _enemyGenerateTime=rand()%150+40;
    _hearthGenerateTime=500;
    _keyDown = false;
    _keyLeft = false;
    _keyR = false;
    _keyRight = false;
    _keyS = false;
    _keyUp = false;
    _gamePaused = false;
}

void MinestormGame::step() {

}

void MinestormGame::draw(QPainter &painter, QRect &rect)
{    
    painter.fillRect(rect, QColor(0,0,0));
    painter.setPen(QColor(255,255,255));
    QBrush brush(QColor(255,255,255),_currentStyle);
    painter.setBrush(brush);
    if(this->isRunning())
    {
        showCinematics(painter,rect);
        if(_health>0)
        {
            //showCinematics(painter,rect);

            painter.drawImage(rect,QImage("image/background.png"));
            /*show score*/
            drawScore(painter,rect);
            testKeys();
            drawSpaceShip(painter);
            drawEnemies(painter);
            drawEnemiesBullets(painter,rect);
            drawSpaceShipBullets(painter,rect);
            drawMines(painter);
            drawHearth(painter,rect);
            /*overScreenControle*/
            _spaceShip.spaceShipOverScreenControle(rect.width(),rect.height());
            /*generate new enemy*/
            if(_enemies.size()<5)
            {
                generateEnemy(rect.width(),rect.height());
            }

            if(_mines.size()<10)
            {
                generateMines(rect.width(),rect.height());
            }
        }
        else
        {
            showCinematics(painter,rect);
        }
    }
    else
    {
        showCinematics(painter,rect);
    }
}

const char * MinestormGame::boolToString(bool b)
{
    return b ? "true" : "false";
}

void MinestormGame::addSpaceShipBullet(Bullet bullet)
{
    _spaceShipBullets.push_back(bullet);
}

void MinestormGame::addEnemyBullet(Bullet bullet)
{
    _enemiesBullets.push_back(bullet);
}

void MinestormGame::generateEnemy(int width, int height)
{
    if(_enemyGenerateTime<=0)
    {
        int xnewb = rand()%width;
        int ynewb = rand()%height;
        QPoint p1(xnewb,ynewb+20);
        QPoint p2(xnewb,ynewb-20);
        //new enemy
        SpaceShip enemy;
        enemy.setShipLine(QLine(p2,p1));
        enemy.setDirectionAngle(0);
        enemy.setPointSpeed(QPoint(0,0));
        enemy.setSpeed(45);        
        std::stringstream imageAddress;
        imageAddress << "image/enemy/"<<rand()%4<<".png";
        enemy.setShipImage(QImage(imageAddress.str().c_str()));
        _enemies.push_back(enemy);
        _enemyGenerateTime=rand()%150+40;
    }
    else _enemyGenerateTime--;
}

void MinestormGame::generateMines(int width, int height)
{
    if(_enemyGenerateTime<=0)
    {
        int currentSize = rand()%60+20;
        int xnewb = rand()%width;
        int ynewb = rand()%height;
        QPoint p1(xnewb,ynewb+(currentSize/2));
        QPoint p2(xnewb,ynewb-(currentSize/2));
        //new Mine
        Mine mine;
        mine.setMineLine(QLine(p2,p1));
        mine.setMineImage(QImage("image/enemy/bomb.png"));
        mine.setMineSize(QSize(currentSize,currentSize));
        _mines.push_back(mine);
        _enemyGenerateTime=rand()%150+40;
    }_enemyGenerateTime--;
}

void MinestormGame::drawSpaceShip(QPainter &painter)
{
    //painter.drawLine(_spaceShip.getShipLine());
    painter.drawImage(QRect(QPoint(((_spaceShip.getShipLine().p1().x()+_spaceShip.getShipLine().p2().x())/2)-20,
                                   ((_spaceShip.getShipLine().p1().y()+_spaceShip.getShipLine().p2().y())/2)-20),QSize(40,40)),
                      _spaceShip.getShipImage().transformed(QMatrix().rotate(-_spaceShip.getDirectionAngle())));

    //spaceship movs
    auto x = (_spaceShip.getShipLine().p1().x()-_spaceShip.getShipLine().p2().x()) / _spaceShip.getSpeed();
    auto y = (_spaceShip.getShipLine().p1().y()-_spaceShip.getShipLine().p2().y()) / _spaceShip.getSpeed();
    _spaceShip.setPointSpeed(QPoint(x,y));
    QLine line(_spaceShip.getShipLine());
    line.translate(_spaceShip.getPointSpeed());
    _spaceShip.setShipLine(line);
    //spaceship movs
}

void MinestormGame::drawEnemies(QPainter &painter){
    for(auto i=0u;i<_enemies.size();i++)
    {
        //painter.drawLine(_enemies[i].getShipLine());
        painter.drawImage(QRect(QPoint(((_enemies[i].getShipLine().p1().x()+_enemies[i].getShipLine().p2().x())/2)-20,
                                       ((_enemies[i].getShipLine().p1().y()+_enemies[i].getShipLine().p2().y())/2)-20),QSize(40,40)),
                          _enemies[i].getShipImage().transformed(QMatrix().rotate(-_enemies[i].getDirectionAngle())));

        //enemy movs
        //pour avoir l'angle entre 0 et 360
        auto centerSsX = (_spaceShip.getShipLine().p1().x()+_spaceShip.getShipLine().p2().x())/2;
        auto centerSsY = (_spaceShip.getShipLine().p1().y()+_spaceShip.getShipLine().p2().y())/2;
        auto centerEnemyX = (_enemies[i].getShipLine().p1().x()+_enemies[i].getShipLine().p2().x())/2;
        auto centerEnemyY = (_enemies[i].getShipLine().p1().y()+_enemies[i].getShipLine().p2().y())/2;

        QLine enemyToSsLine(QPoint(centerEnemyX,centerEnemyY),QPoint(centerSsX,centerSsY));
        double angleRadian=atan(double(abs(enemyToSsLine.dx()))/double(abs(enemyToSsLine.dy())));
        int angleAtourner = 0;
        if(enemyToSsLine.dx()<=0 && enemyToSsLine.dy() <=0)
        {
            angleAtourner = 270+(90-(angleRadian*180.0/M_PI));
        }else
            if(enemyToSsLine.dx() <=0 && enemyToSsLine.dy()>0)
            {
                angleAtourner = 180+(angleRadian*180.0/M_PI);
            }
            else
                if(enemyToSsLine.dx() > 0 && enemyToSsLine.dy() >0)
                {
                    angleAtourner = 90+(90-(angleRadian*180.0/M_PI));
                }
                else
                {
                    angleAtourner = angleRadian*180/M_PI;
                }
        //pour avoir l'angle entre 0 et 360
        //
        if((_enemies[i].getDirectionAngle())%360>=0)
        {
            if(360-((_enemies[i].getDirectionAngle())%360)>angleAtourner+5)
            {
                _enemies[i].turnLeft();
            }
            else
                if(360-((_enemies[i].getDirectionAngle())%360)<angleAtourner-5)
                {
                    _enemies[i].turnRight();
                }
        }
        else
            if(abs((_enemies[i].getDirectionAngle())%360)>angleAtourner+5)
            {
                _enemies[i].turnLeft();
            }
            else
                if(abs((_enemies[i].getDirectionAngle())%360)<angleAtourner-5)
                {
                    _enemies[i].turnRight();
                }

        //std::cout<<" | angle : "<<angleAtourner<<"|"<<(_enemies[i].getDirectionAngle())%360<<std::endl;
        //painter.drawLine(enemyToSsLine);
        if(_enemyShootIntervalle >= 200){
            addEnemyBullet(_enemies[i].shoot());
            _enemyShootIntervalle=0u;
        }
        else
        {
            _enemyShootIntervalle++;
        }
        //enemy movs
    }

    //enemies movs
    for(auto i=0u; i<_enemies.size();i++)
    {
        auto x = (_enemies[i].getShipLine().p1().x()-_enemies[i].getShipLine().p2().x()) / 40;
        auto y = (_enemies[i].getShipLine().p1().y()-_enemies[i].getShipLine().p2().y()) / 40;
        _enemies[i].setPointSpeed(QPoint(x,y));
        QLine enemyLine(_enemies[i].getShipLine());
        enemyLine.translate(_enemies[i].getPointSpeed());
        _enemies[i].setShipLine(enemyLine);
        //_enemies[i].setDirectionAngle(_enemies[i].getDirectionAngle());

    }

    //enemies movs
}

void MinestormGame::drawMines(QPainter &painter)
{
    for(auto i=0u;i<_mines.size();i++)
    {
        //painter.drawLine(_mines[i].getMineLine());
        painter.drawImage(QRect(QPoint(((_mines[i].getMineLine().p1().x()+_mines[i].getMineLine().p2().x())/2)-(_mines[i].getMineSize().width()/2),
                                        ((_mines[i].getMineLine().p1().y()+_mines[i].getMineLine().p2().y())/2)-(_mines[i].getMineSize().height()/2))
                                 ,_mines[i].getMineSize()),
                          _mines[i].getMineImage());

        //collision test : remove mine and spaceship _health decrease if collision
        if(_mines[i].collideWithSpaceShip(_spaceShip.getShipLine()))
        {
            _mines[i] = _mines.back();
            _mines.pop_back();
            _health=_health-10;
            //std::cout<<"SpaceShip collide with mine"<<std::endl;
        }
        //collision test
    }


}

void MinestormGame::drawEnemiesBullets(QPainter &painter, QRect &rect)
{
    for(auto i=0u;i < _enemiesBullets.size();i++) {
        /*if bullet out of screen, destroy bullet*/
        if (_enemiesBullets[i].getBulletLine().p2().x() < 0
                || _enemiesBullets[i].getBulletLine().p2().x() > rect.width()
                || _enemiesBullets[i].getBulletLine().p2().y() < 0
                || _enemiesBullets[i].getBulletLine().p2().y() > rect.height())
        {
            _enemiesBullets[i] = _enemiesBullets.back();
            _enemiesBullets.pop_back();
        }
        /*else draw bullet*/
        else
        {
            //painter.drawLine(_spaceShipBullets[i].getBulletLine());
            painter.drawImage(QRect(QPoint(((_enemiesBullets[i].getBulletLine().p1().x()+_enemiesBullets[i].getBulletLine().p2().x())/2)-5,
                                           ((_enemiesBullets[i].getBulletLine().p1().y()+_enemiesBullets[i].getBulletLine().p2().y())/2)-5),
                                    QSize(10,10)),
                              _enemiesBullets[i].getBulletImage());
        }
    }

    //_enemiesBullets movs
    for(auto i=0u;i < _enemiesBullets.size();i++) {
        auto x = (_enemiesBullets[i].getBulletLine().p1().x()-_enemiesBullets[i].getBulletLine().p2().x()) / 2;
        auto y = (_enemiesBullets[i].getBulletLine().p1().y()-_enemiesBullets[i].getBulletLine().p2().y()) / 2;
        QLine bulletLine(_enemiesBullets[i].getBulletLine());
        bulletLine.translate(QPoint(x,y));
        _enemiesBullets[i].setBulletLine(bulletLine);

        //collision test : remove bullet if collision
        if(_enemiesBullets[i].collideWithSpaceShip(_spaceShip.getShipLine()))
        {
            _enemiesBullets[i] = _enemiesBullets.back();
            _enemiesBullets.pop_back();
            _health=_health-5;
            //std::cout<<"SpaceShip touché !"<< " Points de vie : " <<_health<<std::endl;
        }
        //collision test
    }
    //_enemiesBullets movs
}

void MinestormGame::drawSpaceShipBullets(QPainter &painter, QRect &rect)
{
    for(auto i=0u;i < _spaceShipBullets.size();i++) {
        /*if bullet out of screen, destroy bullet*/
        if (_spaceShipBullets[i].getBulletLine().p2().x() < 0
                || _spaceShipBullets[i].getBulletLine().p2().x() > rect.width()
                || _spaceShipBullets[i].getBulletLine().p2().y() < 0
                || _spaceShipBullets[i].getBulletLine().p2().y() > rect.height())
        {
            _spaceShipBullets[i] = _spaceShipBullets.back();
            _spaceShipBullets.pop_back();
        }
        /*else draw bullet*/
        else
        {
            //painter.drawLine(_spaceShipBullets[i].getBulletLine());
            painter.drawImage(QRect(QPoint(((_spaceShipBullets[i].getBulletLine().p1().x()+_spaceShipBullets[i].getBulletLine().p2().x())/2)-5,
                                           ((_spaceShipBullets[i].getBulletLine().p1().y()+_spaceShipBullets[i].getBulletLine().p2().y())/2)-5),
                                    QSize(10,10)),
                              _spaceShipBullets[i].getBulletImage());
        }
    }

    //_spaceShipBullets movs
    for(auto i=0u;i < _spaceShipBullets.size();i++) {
        auto x = (_spaceShipBullets[i].getBulletLine().p1().x()-_spaceShipBullets[i].getBulletLine().p2().x()) / 2;
        auto y = (_spaceShipBullets[i].getBulletLine().p1().y()-_spaceShipBullets[i].getBulletLine().p2().y()) / 2;
        QLine bulletLine(_spaceShipBullets[i].getBulletLine());
        bulletLine.translate(QPoint(x,y));
        _spaceShipBullets[i].setBulletLine(bulletLine);

        //collision test : remove bullets and enemy if collision
        for(auto j=0u;j<_enemies.size();j++)
        {
            if(_spaceShipBullets[i].collideWithSpaceShip(_enemies[j].getShipLine()))
            {
                _spaceShipBullets[i] = _spaceShipBullets.back();
                _spaceShipBullets.pop_back();
                _enemies[j] = _enemies.back();
                _enemies.pop_back();
                j=_enemies.size();

                _score+=50;
            }
        }
        //collision test


        //collision test : remove bullet and mine if collision
        for(auto j=0u;j<_mines.size();j++)
        {
            if(_spaceShipBullets[i].collideWithSpaceShip(_mines[j].getMineLine()))
            {
                _spaceShipBullets[i] = _spaceShipBullets.back();
                _spaceShipBullets.pop_back();
                _mines[j] = _mines.back();
                _mines.pop_back();
                j=_mines.size();
                _score+=30;
            }
        }
        //collision test

    }
    //_spaceShipBullets movs
}

void MinestormGame::drawHearth(QPainter &painter, QRect &rect)
{
    painter.setPen(QColor(255,255,255));
    QBrush brush(QColor(255,255,255),_currentStyle);
    painter.setBrush(brush);

    for(auto i=0u;i<_hearths.size();i++)
    {
        painter.drawPoint(QPoint(_hearths[i].x(),_hearths[i].y()));
        painter.drawImage(QRect(QPoint(_hearths[i].x()-15,_hearths[i].y()-15),QSize(30,30)),QImage("image/hearth.png"));

        //collision test : remove hearth and spaceship _health +100 if collision
        int distance = 35;
        auto xShip = (_spaceShip.getShipLine().p1().x()+_spaceShip.getShipLine().p2().x())/2;
        auto yShip = (_spaceShip.getShipLine().p1().y()+_spaceShip.getShipLine().p2().y())/2;
        auto xHearth = _hearths[i].x();
        auto yHearth = _hearths[i].y();

        if(abs(xShip-xHearth) < distance && abs(yShip-yHearth) < distance)
        {
            _hearths[i] = _hearths.back();
            _hearths.pop_back();
            _health += 30;
            //std::cout<<"SpaceShip collide with hearth"<<std::endl;
        }
        //collision test : remove hearth and spaceship _health +100 if collision
    }

    if(_hearths.size()<5 && _score >= _hearthGenerateTime)
    {
        QPoint hearth(rand()%rect.width(),rand()%rect.height());
        _hearths.push_back(hearth);
        _hearthGenerateTime += 500;
    }
}

void MinestormGame::drawScore(QPainter &painter, QRect &rect)
{

    painter.setPen(QColor(0,0,0));
    QBrush brush(QColor(0,0,0),_currentStyle);
    painter.setBrush(brush);
    std::stringstream score;
    score << "PV : " << _health<<"\nScore : "<<_score;
    //painter.drawText(QRect(10,10,200,20), Qt::AlignCenter, tr(stream.str().c_str()));
    painter.drawText(QRect(0,0,rect.width(),60),Qt::AlignCenter, tr(score.str().c_str()));
}

void MinestormGame::showCinematics(QPainter &painter, QRect &rect)
{
    painter.fillRect(rect, QColor(0,0,0));
    std::stringstream presentationText;
    presentationText<<"Welcome to Minestorm Vectrex game original version";
    presentationText<<"\nby TN";
    presentationText<<"\n\nS : Shoot | Enter : Start / Pause / Re-initialize | R : Restart";
    presentationText<<"\n\nSe prendre une balle : -5 pv";
    presentationText<<"\nSe prendre une mine : -10 pv";
    presentationText<<"\nCoeur pris : +30 pv";
    presentationText<<"\n\nEnemy tué : 50 pts";
    presentationText<<"\nMine touchée : 30 pts";

    painter.setFont(QFont("default", 15, -1, false));
    if(_health<=0)
    {
        std::stringstream score;
        score << "GAME OVER\n\n"<<"\nScore final : "<<_score;
        painter.drawText(QRect((rect.width()/2)-100,rect.height()/2,200,100), Qt::AlignCenter, tr(score.str().c_str()));
    }

    if(_gamePaused)
    {
        painter.drawText(QRect((rect.width()/2)-50,rect.height()/2,100,40), Qt::AlignCenter, tr("PAUSE"));
    }
    else if(!this->isRunning())
    {
        painter.drawText(QRect(0,rect.height()/5,rect.width(),rect.height()), Qt::AlignHCenter, tr(presentationText.str().c_str()));
        painter.drawImage(QRect(QPoint((rect.width()/5)*2.2,(rect.height()/5)*3.5),QSize((rect.height()/5),(rect.height()/5)))
                          ,QImage("image/mario.png").transformed((QMatrix().rotate(180))));
    }
}

void MinestormGame::testKeys()
{
    if (_keyLeft)
        _spaceShip.turnLeft();
    if (_keyRight)
        _spaceShip.turnRight();
    if (_keyUp)
        _spaceShip.accelerate();
    if (_keyDown)
        _spaceShip.breakdown();

    if (_keyS && _spaceShipShootControl<0)
    {
        addSpaceShipBullet(_spaceShip.shoot());
        _spaceShipShootControl = 20;
    }else _spaceShipShootControl--;
}

void MinestormGame::keyPressed( int key ) {
    switch(key) {
    case Qt::Key_1: _currentStyle = Qt::SolidPattern;
        break;
    case Qt::Key_2: _currentStyle = Qt::CrossPattern;
        break;
    case Qt::Key_3: _currentStyle = Qt::VerPattern;
        break;
    case Qt::Key_4: _currentStyle = Qt::HorPattern;
        break;
    case Qt::Key_R: initialize();
        break;
    case Qt::Key_Up: _keyUp=true;
        break;
    case Qt::Key_Down:_keyDown=true;
        break;
    case Qt::Key_Left: _keyLeft=true;
        break;
    case Qt::Key_Right: _keyRight=true;
        break;
    case Qt::Key_S: _keyS=true;
        break;
    case Qt::Key_Return :
        if (_health<=0)
        {
            initialize();
            _gamePaused = false;
        } else if (this->isRunning())
        {
            this->pause();
            _gamePaused = true;
        } else
        {
            this->start();
            _gamePaused = false;
        }
        break;
    }
    emit changed();
}

void MinestormGame::keyReleased( int key ) {
    switch(key) {
    //space ship movs
    case Qt::Key_Up: _keyUp=false;
        break;
    case Qt::Key_Down:_keyDown=false;
        break;
    case Qt::Key_Left: _keyLeft=false;
        break;
    case Qt::Key_Right: _keyRight=false;
        break;
        //space ship shoot
    case Qt::Key_S: _keyS=false;
        break;
    }
    emit changed();
}

void MinestormGame::mousePressed( int /*x*/, int /*y*/) {
}
void MinestormGame::mouseReleased( int /* x */, int /* y */) {
}
void MinestormGame::mouseMoved(int /* x */, int /* y */) {

}

