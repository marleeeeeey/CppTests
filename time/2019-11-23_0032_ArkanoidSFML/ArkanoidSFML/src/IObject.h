#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Collision.h"
#include <optional>
#include <functional>

class IObjectFactory;

class IObject : public std::enable_shared_from_this<IObject>
{
public:
    virtual ~IObject() = default;
    virtual void checkBumping(std::vector<std::shared_ptr<IObject>>& objects) = 0;
    virtual void onBumping(std::vector<Collision>& collisions) = 0;
    virtual void setOnBumpingCallBack(std::function<void(std::vector<Collision>& collisions)> cb) = 0;
    virtual void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual State& state() = 0;
};
