#include "minestormgame.h"

#include <QColor>
#include <iostream>
#include <math.h>
#include "objects/gameobject.h"

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
    _explosions.clear();
    _currentStyle = Qt::SolidPattern;
    //spaceship
    _spaceShip.setImage(QImage("image/spaceships/0.png"));
    _spaceShip.setLine(QLine(500,280,500,320));
    _spaceShip.setAngle(180);
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
    int id = QFontDatabase::addApplicationFont(":/fonts/Mario256.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Mario(family);
    Mario.setPixelSize(20);
    _font = Mario;
}

void MinestormGame::step() {

}

void MinestormGame::draw(QPainter &painter, QRect &rect)
{
    painter.fillRect(rect, QColor(0,0,0));
    painter.setPen(QColor(255,255,255));
    painter.setFont(_font);
    QBrush brush(QColor(255,255,255),_currentStyle);
    painter.setBrush(brush);
    if(this->isRunning())
    {
        showCinematics(painter,rect);
        if(_health>0)
        {
            //showCinematics(painter,rect);

            //painter.drawImage(rect,QImage("image/background.png"));
            /*show score*/
            drawScore(painter,rect);
            testKeys();
            //drawExplosion(painter);
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
        enemy.setLine(QLine(p2,p1));
        enemy.setAngle(0);
        enemy.setPointSpeed(QPoint(0,0));
        enemy.setSpeed(45);        
        std::stringstream imageAddress;
        imageAddress << "image/spaceships/"<<rand()%12+1<<".png";
        enemy.setImage(QImage(imageAddress.str().c_str()));
        _enemies.push_back(enemy);
        _enemyGenerateTime=rand()%150+40;
    }
    else _enemyGenerateTime--;
}

void MinestormGame::generateMines(int width, int height)
{
    if(_enemyGenerateTime<=0)
    {
        int currentSize = rand()%20+20;
        int xnewb = rand()%width;
        int ynewb = rand()%height;
        QPoint p1(xnewb,ynewb+(currentSize/2));
        QPoint p2(xnewb,ynewb-(currentSize/2));
        //new Mine
        Mine mine;
        mine.setLine(QLine(p2,p1));
        std::stringstream imageAddress;
        imageAddress << "image/mines/"<<rand()%4<<".png";
        mine.setImage(QImage(imageAddress.str().c_str()));
        mine.setMineSize(QSize(currentSize,currentSize));
        _mines.push_back(mine);
        _enemyGenerateTime=rand()%150+40;
    }_enemyGenerateTime--;
}

void MinestormGame::drawSpaceShip(QPainter &painter)
{
    _spaceShip.draw(painter);

    //spaceship movs
    auto x = (_spaceShip.getLine().p1().x()-_spaceShip.getLine().p2().x()) / _spaceShip.getSpeed();
    auto y = (_spaceShip.getLine().p1().y()-_spaceShip.getLine().p2().y()) / _spaceShip.getSpeed();
    _spaceShip.setPointSpeed(QPoint(x,y));
    QLine line(_spaceShip.getLine());
    line.translate(_spaceShip.getPointSpeed());
    _spaceShip.setLine(line);
    //spaceship movs
}

void MinestormGame::drawEnemies(QPainter &painter){
    for(auto i=0u;i<_enemies.size();i++)
    {
        _enemies[i].draw(painter);

        //enemy movs
        //pour avoir l'angle entre 0 et 360
        auto centerSsX = (_spaceShip.getLine().p1().x()+_spaceShip.getLine().p2().x())/2;
        auto centerSsY = (_spaceShip.getLine().p1().y()+_spaceShip.getLine().p2().y())/2;
        auto centerEnemyX = (_enemies[i].getLine().p1().x()+_enemies[i].getLine().p2().x())/2;
        auto centerEnemyY = (_enemies[i].getLine().p1().y()+_enemies[i].getLine().p2().y())/2;

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
        if((_enemies[i].getAngle())%360>=0)
        {
            if(360-((_enemies[i].getAngle())%360)>angleAtourner+5)
            {
                _enemies[i].turnLeft();
            }
            else
                if(360-((_enemies[i].getAngle())%360)<angleAtourner-5)
                {
                    _enemies[i].turnRight();
                }
        }
        else
            if(abs((_enemies[i].getAngle())%360)>angleAtourner+5)
            {
                _enemies[i].turnLeft();
            }
            else
                if(abs((_enemies[i].getAngle())%360)<angleAtourner-5)
                {
                    _enemies[i].turnRight();
                }

        //std::cout<<" | angle : "<<angleAtourner<<"|"<<(_enemies[i].getAngle())%360<<std::endl;
        //painter.drawLine(enemyToSsLine);
        if(_enemyShootIntervalle >= 200){
            addEnemyBullet(_enemies[i].shoot());
            _enemyShootIntervalle=0u;
        }
        else
        {
            _enemyShootIntervalle++;
        }


        auto x = (_enemies[i].getLine().p1().x()-_enemies[i].getLine().p2().x()) / 40;
        auto y = (_enemies[i].getLine().p1().y()-_enemies[i].getLine().p2().y()) / 40;
        _enemies[i].setPointSpeed(QPoint(x,y));
        QLine enemyLine(_enemies[i].getLine());
        enemyLine.translate(_enemies[i].getPointSpeed());
        _enemies[i].setLine(enemyLine);
        //_enemies[i].setAngle(_enemies[i].getAngle());

        //enemy movs
    }
}

void MinestormGame::drawMines(QPainter &painter)
{
    for(auto i=0u;i<_mines.size();i++)
    {
        _mines[i].draw(painter);

        //collision test : remove mine and spaceship _health decrease if collision
        if(_mines[i].collision(_spaceShip))
        {
            _mines[i] = _mines.back();
            _mines.pop_back();
            _health=_health-10;
        }
        //collision test
    }


}

void MinestormGame::drawEnemiesBullets(QPainter &painter, QRect &rect)
{
    for(auto i=0u;i < _enemiesBullets.size();i++) {
        /*if bullet out of screen, destroy bullet*/
        if (_enemiesBullets[i].getLine().p2().x() < 0
                || _enemiesBullets[i].getLine().p2().x() > rect.width()
                || _enemiesBullets[i].getLine().p2().y() < 0
                || _enemiesBullets[i].getLine().p2().y() > rect.height())
        {
            _enemiesBullets[i] = _enemiesBullets.back();
            _enemiesBullets.pop_back();
        }
        /*else draw bullet*/
        else
        {
            _enemiesBullets[i].draw(painter);
            _enemiesBullets[i].bang();
            //collision test : remove bullet if collision
            if(_enemiesBullets[i].collision(_spaceShip))
            {
                _enemiesBullets[i] = _enemiesBullets.back();
                _enemiesBullets.pop_back();
                _health=_health-5;
                //std::cout<<"SpaceShip touché !"<< " Points de vie : " <<_health<<std::endl;
            }
            //collision test
        }
    }
}

void MinestormGame::drawSpaceShipBullets(QPainter &painter, QRect &rect)
{
    for(auto i=0u;i < _spaceShipBullets.size();i++) {
        /*if bullet out of screen, destroy bullet*/
        if (_spaceShipBullets[i].getLine().p2().x() < 0
                || _spaceShipBullets[i].getLine().p2().x() > rect.width()
                || _spaceShipBullets[i].getLine().p2().y() < 0
                || _spaceShipBullets[i].getLine().p2().y() > rect.height())
        {
            _spaceShipBullets[i] = _spaceShipBullets.back();
            _spaceShipBullets.pop_back();
        }
        /*else draw bullet*/
        else
        {
            _spaceShipBullets[i].draw(painter);
            _spaceShipBullets[i].bang();
            //collision test : remove bullets and enemy if collision
            for(auto j=0u;j<_enemies.size();j++)
            {
                if(_spaceShipBullets[i].collision(_enemies[j]))
                {                    
                    _explosions.push_back(_enemies[j].getCenter());
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
                if(_spaceShipBullets[i].collision(_mines[j]))
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
    }
}

void MinestormGame::drawHearth(QPainter &painter, QRect &rect)
{
    painter.setPen(QColor(255,255,255));
    QBrush brush(QColor(255,255,255),_currentStyle);
    painter.setBrush(brush);

    for(auto i=0u;i<_hearths.size();i++)
    {
        painter.drawPoint(QPoint(_hearths[i].x(),_hearths[i].y()));
        painter.drawImage(QRect(QPoint(_hearths[i].x()-15,_hearths[i].y()-15),QSize(30,30)),QImage("image/objects/heart.png"));

        //collision test : remove hearth and spaceship _health +100 if collision
        int distance = 35;
        auto xShip = (_spaceShip.getLine().p1().x()+_spaceShip.getLine().p2().x())/2;
        auto yShip = (_spaceShip.getLine().p1().y()+_spaceShip.getLine().p2().y())/2;
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
    std::stringstream score;
    score << "PV : " << _health<<"\nScore : "<<_score;
    //painter.drawText(QRect(10,10,200,20), Qt::AlignCenter, tr(stream.str().c_str()));
    painter.drawText(QRect(0,0,rect.width(),60),Qt::AlignCenter, tr(score.str().c_str()));
}

void MinestormGame::showCinematics(QPainter &painter, QRect &rect)
{
    painter.fillRect(rect, QColor(0,0,0));
    std::stringstream presentationText;
    presentationText<<"Welcome to Minestorm Vectrex";
    presentationText<<"\nby TN";
    presentationText<<"\n\nS : Shoot";
    presentationText<<"\nR : Restart";
    presentationText<<"\nEnter : Start / Pause / Re-initialize";
    presentationText<<"\n\nBalle : -5 pv";
    presentationText<<"\nMine : -10 pv";
    presentationText<<"\nCoeur : +30 pv";

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
                          ,QImage("image/spaceships/0.png").transformed((QMatrix().rotate(180))));
    }
}

void MinestormGame::drawExplosion(QPainter &painter)
{
    for (auto i=0u; i<_explosions.size();i++)
    {
        painter.drawPoint(_explosions[i]);
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

