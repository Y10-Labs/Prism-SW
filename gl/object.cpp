#include "object.hpp"

#include <global/panic.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gl
{
    void Object::from_model(Model& model)
    {
        this->model = &model;
    }

    void Object::rotate(glm::vec3 axis, float angle_in_radians)
    {
        this->has_geometry_updated = true;
        this->rotation = glm::rotate(this->rotation, angle_in_radians, axis);
    }
    void Object::set_rotation(glm::vec3 axis, float angle_in_radians)
    {
        this->has_geometry_updated = true;
        this->rotation = glm::rotate(glm::mat4(1.0f), angle_in_radians, axis);
    }
    void Object::euler_update(float deltaTime)
    {
        // reset the total_force and total_impluse
        this->total_force = glm::vec3(0);
        this->total_impluse = glm::vec3(0);

        // if the object is static/not active, no need to update
        if(this->isStatic || !this->isActive) return;

        this->has_geometry_updated = true;

        this->velocity += (this->total_force * deltaTime + this->total_impluse) / this->mass;
        this->currPosition += this->velocity * deltaTime;
    }
    void Object::geometry_update()
    {
        if(!this->has_geometry_updated) return;
        if(!this->model)
        {
            PANIC("No model set for object");
            return;
        }
        this->boundingBox = this->model->bounding_box(this->get_model_matrix());
        this->has_geometry_updated = false;
    }
    void Object::apply_force(glm::vec3 force)
    {
        this->total_force += force;
    }
    void Object::apply_impulse(glm::vec3 impulse)
    {
        this->total_impluse += impulse;
    }
    glm::mat4 Object::get_model_matrix() const
    {
        auto translation = glm::translate(glm::mat4(1.0f), this->position);
        auto scale = glm::scale(glm::mat4(1.0f), this->scale);

        return translation * rotation * scale;
    }
    glm::AABB Object::getBoundingBox() const
    {
        return this->boundingBox;
    }
    void Object::draw() const
    {
        gp::uniform_t uniform;
        uniform.model = this->get_model_matrix();
        uniform.texture_id = 0;

        this->model->draw(uniform);
    }
}
