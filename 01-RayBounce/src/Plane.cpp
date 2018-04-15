#include "Plane.h"

Plane::Plane(){};

void Plane::setup(glm::vec2 _orig, glm::vec2 _normal){
    orig = _orig;
    normal = _normal;
}

void Plane::updateNormal(glm::vec2 _normal){
    normal = _normal;
}

void Plane::updateOrigin(glm::vec2 _orig){
    orig = _orig;
}

glm::vec2 Plane::getOrigin() const {
    return orig;
}

glm::vec2 Plane::getNormal() const {
    return normal;
}

void Plane::draw(float radius){
    ofPushStyle();
    ofSetColor(0,255,0);
    // draw position of the plane
    ofDrawCircle(orig, radius);

    // draw plane
    auto perpendicularToNormal = glm::normalize(arbitraryOrthogonal(glm::vec2(normal.x, normal.y)));

    // A plane is infinite, be sure that the plane debugging line
    // goes out of the screen
    auto endTop = orig + (perpendicularToNormal * radius * ofGetWidth());
    auto endBottom = orig - ((perpendicularToNormal) * radius * ofGetWidth());
    ofDrawLine(orig,endTop);
    ofDrawLine(orig,endBottom);

    //draw normal
    // draw direction
    ofSetColor(0,0,255);
    ofSetLineWidth(3);
    auto end = orig + (normal * (radius* 4.));
    ofDrawLine(orig,end);
    ofPopStyle();
}

glm::vec3 Plane::arbitraryOrthogonal(const glm::vec3& vec){
    bool b0 = (vec.x <  vec.y) && (vec.x <  vec.z);
    bool b1 = (vec.y <= vec.x) && (vec.y <  vec.z);
    bool b2 = (vec.z <= vec.x) && (vec.z <= vec.y);

    auto d = glm::cross(vec, glm::vec3(int(b0), int(b1), int(b2)));
    cout << d << endl;
    return d;
}

glm::vec2 Plane::arbitraryOrthogonal(const glm::vec2& vec){
    return glm::vec2(vec.y, -vec.x);
}
