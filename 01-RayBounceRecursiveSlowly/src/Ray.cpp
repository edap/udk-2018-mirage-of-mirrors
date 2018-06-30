#include "Ray.h"

void Ray::init(glm::vec2 _o, glm::vec2 _d, const int _maxBounces){
    this->setup(_o, _d);
    this->startingOrig = _o;
    this->startingDir = _d;
    this->maxBounces = _maxBounces;
}

void Ray::reset(){
    this->setOrigin(this->startingOrig);
    this->setDirection(this->startingDir);
    this->currentBounces = 0;
};

void Ray::bounce(vector<Segment> segments, ofParameter<float> velocity){
    float eps = 0.00001;
    if (this->currentBounces < this->maxBounces) {
        float distance = std::numeric_limits<float>::infinity();
        float tmpDistance;
        bool intersection = false;
        Segment tmpSegment;
        // find the closest segment that intersect with the ray
        // save it into tmpSegment, and save the distance too.
        for (auto s:segments) {
            if (this->intersectsSegment(s.a, s.b, tmpDistance)) {
                if (intersection == false) { intersection = true;};
                if (tmpDistance < distance){
                    distance = tmpDistance;
                    tmpSegment = s;
                }
            }
        }

        if (intersection) {
            auto intersectionPoint = this->getOrigin() + this->getDirection() * distance;
            auto distance = glm::distance(this->getOrigin(), intersectionPoint);
            if (distance <= this->radius) {
                ofLog() << this->currentBounces;
                this->currentBounces += 1;
                // change direction and bounce
                // the direction of the ray will be the direction of the reflected light
                auto segmentDir = tmpSegment.a - tmpSegment.b;
                auto segmentSurfaceNormal = glm::vec2(segmentDir.y, -segmentDir.x);
                auto reflectDir =
                glm::normalize(glm::reflect(this->getDirection(),segmentSurfaceNormal));

                // the origin of the new ray is the intersection point moved a bit along the
                // reflected direction. This is to avoid to have a new ray that intersect with the segment
                // on which its origin lays.

                this->setup(intersectionPoint +reflectDir*(eps+this->radius),reflectDir);
                this->draw();
                //this->drawBouncing(limit, segments, velocity);
            }else{
                // move towards the interscetion
                auto dir = glm::normalize(intersectionPoint - this->getOrigin());
                this->setOrigin(this->getOrigin() + dir * velocity.get());
            }
        }
        else {
            // no bounce, go back to the origin
            this->reset();
        }
    }
}


void Ray::drawRayControls(){

};



