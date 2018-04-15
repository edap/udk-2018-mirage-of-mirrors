#pragma once
#include "ofMain.h"
#include "Plane.h"

class Ray {
public:
    Ray(){};
    Ray(glm::vec2 origin, glm::vec2 direction);

    glm::vec2 getOrigin() const;
    glm::vec2 getDirection() const;
    void setDirection(glm::vec2 direction);
    void draw(float radius = 20.);

//    float distanceToPlane(Plane plane) const;
//    bool intersectsPlane(Plane plane) const;
    void intersectsPlane(Plane plane, glm::vec2& intersection, bool& intersects);
    void intersectsSegment(glm::vec2 a, glm::vec2 b, glm::vec2& intersection, bool& intersects);
    void intersectsPolyline(ofPolyline pol, glm::vec2& intersection, bool& intersects);

private:
    glm::vec2 origin;
    glm::vec2 direction;
};
