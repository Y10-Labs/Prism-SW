#pragma once
#include <string>
#include<iostream>
#include<vector>
class Component {
public:
    virtual ~Component() = default;
};

class Collision : public virtual Component {
public:
    virtual void OnCollision(Component* other) = 0;
};

class Event : public virtual Component {
public:
    virtual void HandleEvents(const std::string& event) = 0;
};

struct AABB {
    float minX, minY, maxX, maxY; //the boundaries of the box...
};

class Hitbox : public virtual Component {
public:
    virtual AABB GetHitbox() const = 0;
    virtual void SetHitbox(const AABB& box) = 0;
};

class Player : public virtual Collision, public virtual Event, public virtual Hitbox {
public:
    AABB hitbox;

    Player(const AABB& box) : hitbox(box) {}

    void OnCollision(Component* other) override {}

    void HandleEvents(const std::string& event) override {}

    AABB GetHitbox() const override {
        return hitbox;
    }

    void SetHitbox(const AABB& box) override {
        hitbox = box;
    }
};
