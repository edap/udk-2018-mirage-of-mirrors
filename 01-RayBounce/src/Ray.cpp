#include "Ray.h"

Ray::Ray(glm::vec2 _orig, glm::vec2 _dir){
    origin = _orig;
    direction = glm::normalize(_dir);
}

void Ray::setDirection(glm::vec2 _direction){
    direction = _direction;
};

glm::vec2 Ray::getOrigin() const {
    return origin;
};

glm::vec2 Ray::getDirection() const{
    return direction;
};

void Ray::draw(float radius){
    ofPushStyle();
    // draw origin
    ofSetColor(255, 0, 0);
    ofDrawSphere(origin.x, origin.y, radius);

    // draw direction
    ofSetColor(0,0,255);
    auto end = origin + (direction * (radius*4.));
    ofSetLineWidth(3);
    ofDrawLine(origin,end);
    ofSetLineWidth(1);
    ofPopStyle();
}


void Ray::intersectsPlane(Plane plane, glm::vec2& intersection, bool& intersects){
    float distance;
    intersects = glm::intersectRayPlane(origin, direction,
                                        plane.getOrigin(), plane.getNormal(),
                                        distance);
    if (intersects) {
        intersection = origin + direction*distance;
    }
};

//float Ray::distanceToPlane(Plane plane) const{
//    float distance;
//    auto inter = glm::intersectRayPlane(origin, direction,
//                                        plane.getOrigin(), plane.getNormal(),
//                                        distance);
//    return distance;
//};
//
//bool Ray::intersectsPlane(Plane plane) const{
//    float distance;
//    return glm::intersectRayPlane(origin, direction,
//                                  plane.getOrigin(), plane.getNormal(),distance);
//};
