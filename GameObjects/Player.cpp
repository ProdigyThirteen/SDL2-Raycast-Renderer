#include "Player.h"
#include "../Globals/DeltaTime.h"
#include "../Core/InputManager.h"
#include "../Rendering/RenderInstanceManager.h"
#include <cmath>

Player::Player()
{
    InputManager::instance().BindKey(SDL_SCANCODE_W, InputManager::KeypressType::KEYHELD, std::bind(&Player::MoveForward, this));
    InputManager::instance().BindKey(SDL_SCANCODE_S, InputManager::KeypressType::KEYHELD, std::bind(&Player::MoveBackward, this));
    InputManager::instance().BindKey(SDL_SCANCODE_A, InputManager::KeypressType::KEYHELD, std::bind(&Player::MoveLeft, this));
    InputManager::instance().BindKey(SDL_SCANCODE_D, InputManager::KeypressType::KEYHELD, std::bind(&Player::MoveRight, this));

    InputManager::instance().BindKey(SDL_SCANCODE_LEFT, InputManager::KeypressType::KEYHELD, std::bind(&Player::RotateLeft, this));
    InputManager::instance().BindKey(SDL_SCANCODE_RIGHT, InputManager::KeypressType::KEYHELD, std::bind(&Player::RotateRight, this));

    //DAN
    //auto rim = RenderInstanceManager::instance();
    auto r = RenderInstanceManager::instance().GetRenderer("main");
    Camera* c = RenderInstanceManager::instance().GetRenderer("main")->GetCamera();
    //DAN

    _camera = RenderInstanceManager::instance().GetRenderer("main")->GetCamera();
}

Player::~Player()
{}

void Player::Init()
{}

void Player::MoveForward()
{
    double moveSpeed = DeltaTime::GetDeltaTime() * 5.0; //the constant value is in squares/second
    _pos.X += _dir.X * moveSpeed;
    _pos.Y += _dir.Y * moveSpeed;
}

void Player::MoveBackward()
{
    double moveSpeed = DeltaTime::GetDeltaTime() * 5.0; //the constant value is in squares/second
    _pos.X -= _dir.X * moveSpeed;
    _pos.Y -= _dir.Y * moveSpeed;
}

void Player::MoveLeft()
{
    double moveSpeed = DeltaTime::GetDeltaTime() * 5.0; //the constant value is in squares/second
    _pos.X -= _plane.X * moveSpeed;
    _pos.Y -= _plane.Y * moveSpeed;
}

void Player::MoveRight()
{
    double moveSpeed = DeltaTime::GetDeltaTime() * 5.0; //the constant value is in squares/second
    _pos.X += _plane.X * moveSpeed;
    _pos.Y += _plane.Y * moveSpeed;
}

void Player::RotateLeft()
{
    double rotSpeed = DeltaTime::GetDeltaTime() * 3.0; //the constant value is in radians/second
    double oldDirX = _dir.X;
    _dir.X = _dir.X * cos(rotSpeed) - _dir.Y * sin(rotSpeed);
    _dir.Y = oldDirX * sin(rotSpeed) + _dir.Y * cos(rotSpeed);
    double oldPlaneX = _plane.X;
    _plane.X = _plane.X * cos(rotSpeed) - _plane.Y * sin(rotSpeed);
    _plane.Y = oldPlaneX * sin(rotSpeed) + _plane.Y * cos(rotSpeed);
}

void Player::RotateRight()
{
    double rotSpeed = DeltaTime::GetDeltaTime() * 3.0; //the constant value is in radians/second
    double oldDirX = _dir.X;
    _dir.X = _dir.X * cos(-rotSpeed) - _dir.Y * sin(-rotSpeed);
    _dir.Y = oldDirX * sin(-rotSpeed) + _dir.Y * cos(-rotSpeed);
    double oldPlaneX = _plane.X;
    _plane.X = _plane.X * cos(-rotSpeed) - _plane.Y * sin(-rotSpeed);
    _plane.Y = oldPlaneX * sin(-rotSpeed) + _plane.Y * cos(-rotSpeed);
}

void Player::Update()
{
    _camera->SetPosition(_pos.X, _pos.Y);
    _camera->SetDirection(_dir.X, _dir.Y);
    _camera->SetPlane(_plane.X, _plane.Y);
}
