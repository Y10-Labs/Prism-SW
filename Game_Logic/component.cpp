#pragma once
#include<iostream>
#include<string>
#include"collision.h"
#include"event.h"
#include"Hitbox.h"
class Player : public collision, public event, public Hitbox {
public:
AABB hitbox;
AABB GetHitbox() const override {
        return hitbox;
    }


Player(const AABB& box) : hitbox(box) {}
void OnCollision(Component* other) override {
    }
void HandleEvents(const std::string& event) override {
    }
void SetHitbox(const AABB& box) override {
        hitbox = box;
    }
};
