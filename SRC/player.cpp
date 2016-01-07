#include "player.h"

Player::Player()
{
}

Player::~Player()
{
    Resources::TEXTURE()->Delete(Resources::SPRITE()->GetValue(id_sprite)->GetTextureKey());
    Resources::SPRITE()->Delete(id_sprite);
    Resources::TEXTURE()->Delete(4);
    qDebug()<<"Destroy ~Player";
}

QRectF Player::GetBoundBox()
{
    QRectF rect(this->GetPosX(), this->GetPosY(), this->GetScalX(), this->GetScalY());
    return rect;
}

void Player::Init(QHash<QString, QString> property)
{
    this->SetScalX(property.value("scal_x").toFloat());
    this->SetScalY(property.value("scal_y").toFloat());
    this->SetPosX(property.value("pos_x").toFloat());
    this->SetPosY(property.value("pos_y").toFloat());
    id_sprite = property.value("id_sprite").toInt();
    speed_x = property.value("speed_x").toFloat();
    accel_y = property.value("accel_y").toFloat();
    speed_y = 15;
    accel_x = 0;

    direction.setX(0);
    direction.setY(0);
    Status = Down;

    frame = 0;

    font_text.Load("Resources/font.font");
    font_text.SetMeshKey(0);
    font_text.SetShaderKey(0);
    font_text.SetTextureKey(6);
    font_text.SetKerning(5);
    font_text.Create();
}

void Player::Update(float dt)
{
    ///*Движение и проверка коллизии
    this->MoveX((speed_x+accel_x)*dt);
    direction.setX(1);
    QVector3D new_pos = this->GetPos();
    TileMap::getInstance()->CollisionX("Main", new_pos, this->GetBoundBox(), this->direction);
    this->SetPos(new_pos);
    accel_x = 0;

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Escape))
    {
        qDebug()<<"CurrentStatusGame Pause";
        CurrentStatusGame = Pause;
    }

    if (ManagerKeyboard::getInstance()->GetKey(Qt::Key_Space) && Status==OnGround)
    {
        Status = Jump;
        speed_y = 15;
        direction.setY(1);
    }

    if(Status==Jump)
    {
        if (speed_y>0)
        {
            //qDebug()<<"JUMP DO Speed:"<<speed_y<<"Pos:"<<GetPos();
            speed_y-=accel_y;
            direction.setY(1);
            MoveY(speed_y);
            //qDebug()<<"JUMP Speed:"<<speed_y<<"Pos:"<<GetPos();
        }else
        {
            Status = Down;
            direction.setY(-1);
        }
    }
    if (Status==Down)
    {
        //qDebug()<<"DOWN DO Speed:"<<speed_y<<"Pos:"<<GetPos();
        if (speed_y>-30)
        {
            speed_y-=accel_y;
        }
        MoveY(speed_y);
        direction.setY(-1);
        //qDebug()<<"DOWN Speed:"<<speed_y<<"Pos:"<<GetPos();
    }

    new_pos=this->GetPos();

    if(TileMap::getInstance()->CollisionY("Main", new_pos, this->GetBoundBox(), this->direction))
    {
        if (direction.y()==-1)
        {
            Status = OnGround;
            speed_y = 0;
            //qDebug()<<"ONGROUND";
        }
    }else
    {
        if (Status!=Jump)
        {
            Status = Down;
            direction.setY(-1);
        }
    }
    this->SetPos(new_pos);
    //Движение и проверка коллизии*/

    ///*Взаимодействие с объктами
    QVector<Tile> tiles = TileMap::getInstance()->GetTiles("Object", GetBoundBox());
    for (int i=0; i<tiles.size(); i++)
    {
        //Если монета
        if (tiles.at(i).id==13)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                TileMap::getInstance()->GetLayer("Object")->SetValue(tiles.at(i).ij.y(), tiles.at(i).ij.x(), 0);
                PlayProfile::score+=1;
            }
        }
        //Если шип
        if (tiles.at(i).id==16 || tiles.at(i).id==17 || tiles.at(i).id==18)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                speed_x = 0;
                qDebug()<<"DEAD";
            }
        }
        //Если лед
        if (tiles.at(i).id==10)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                accel_x=10;
            }
        }
        //Если жвачка
        if (tiles.at(i).id==7)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                accel_x=-4;
            }
        }
        //Если прунжина
        if (tiles.at(i).id==4)
        {
            if (TileMap::getInstance()->CollisionX("Object", new_pos, GetBoundBox(), direction)==true ||
                    TileMap::getInstance()->CollisionY("Object", new_pos, GetBoundBox(), direction)==true)
            {
                Status = Jump;
                speed_y = 30;
                direction.setY(1);
            }
        }
    }
    //Взаимодействие с объктами*/

    ///*Задание местоположения камеры
    ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetX(GetPosX()-(Setting::GetViewPort().width()/2-GetScalX()/2));
    ManagerCamera::getInstance()->GetCurrentCamera()->SetTargetY(GetPosY()-(Setting::GetViewPort().height()/2-GetScalY()/2));
    //Задание местоположения камеры*/

    ///*Анимация
    frame+=0.08;
    if (frame>3)
        frame = 0;
    //Анимация*/
}

void Player::Draw()
{
    font_text.Draw("Score:"+QString::number(PlayProfile::score), Resources::CAMERA()->GetCurrentCamera()->GetPosX() + 10,
                   Resources::CAMERA()->GetCurrentCamera()->GetPosY() + Setting::GetViewPort().height() - 35);

    ManagerSprite::getInstance()->GetValue(id_sprite)->Bind(this->GetScalX(), this->GetScalY(), qFloor(frame));
    ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->setUniformValue(ManagerSprite::getInstance()->GetValue(id_sprite)->GetShader()->GetNameMatrixPos().toStdString().c_str(),
                                                                                    Setting::GetProjection() *
                                                                                    ManagerCamera::getInstance()->GetCurrentCamera()->GetMatrix() *
                                                                                    this->GetMatrix());
    glDrawArrays(GL_TRIANGLES, 0, ManagerSprite::getInstance()->GetValue(id_sprite)->GetMesh()->GetCountVertex());
    ManagerSprite::getInstance()->GetValue(id_sprite)->UnBind();
}
