/*
@brief	プリプロセッサ
*/
#pragma once

class SpriteComponent;

class TitleUI : public GameObject
{
public:
    TitleUI();
    ~TitleUI() {};

private:
    SpriteComponent* spriteComponent;
};


