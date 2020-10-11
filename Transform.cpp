#include "Transform.h"

mat3 Transform::rotate(const float degrees,
    const vec3 & axis) {
    mat3 rotMatrix, I(1.0);
    float x = axis[0], y = axis[1], z = axis[2];
    rotMatrix = cos(degrees * pi / 180.0) * I\ +
        (1 - cos(degrees * pi / 180.0))\ *
        mat3(x * x, x * y, x * z, x * y, y * y, y * z, x * z, y * z, z * z)\ +
        sin(degrees * pi / 180.0)\ *
        mat3(0, z, -y, -z, 0, x, y, -x, 0);
    return rotMatrix;
}

void Transform::left(float degrees, vec3 & eye, vec3 & up) {
    eye = Transform::rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3 & eye, vec3 & up) {
    float eyeLength = sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2));
    float upLength = sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2));
    vec3 eyeCrossUp = glm::normalize(glm::cross(eye, up));
    eye = Transform::rotate(degrees, eyeCrossUp) * eye;
    up = Transform::rotate(degrees, eyeCrossUp) * up;
}

mat4 Transform::lookAt(const vec3 & eye,
    const vec3 & center,
        const vec3 & up) {
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);

    return mat4(u.x, v.x, w.x, 0, \
        u.y, v.y, w.y, 0, \
        u.z, v.z, w.z, 0, \
        -glm::dot(u, eye), \
        -glm::dot(v, eye), \
        -glm::dot(w, eye), 1);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar) {
    mat4 ret;
    float d = cos((fovy * pi / 180) / 2) / sin((fovy * pi / 180) / 2);
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -2 * zFar * zNear / (zFar - zNear);
    ret = mat4(d / aspect, 0, 0, 0, \
        0, d, 0, 0, \
        0, 0, A, -1, \
        0, 0, B, 0);
    return ret;
}

mat4 Transform::scale(const float & sx,
    const float & sy,
        const float & sz) {
    mat4 ret;
    ret = mat4(sx, 0, 0, 0, \
        0, sy, 0, 0, \
        0, 0, sz, 0, \
        0, 0, 0, 1);
    return ret;
}

mat4 Transform::translate(const float & tx,
    const float & ty,
        const float & tz) {
    mat4 ret;
    ret = mat4(1, 0, 0, 0, \
        0, 1, 0, 0, \
        0, 0, 1, 0, \
        tx, ty, tz, 1);
    return ret;
}

vec3 Transform::upvector(const vec3 & up,
    const vec3 & zvec) {
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    vec3 ret = glm::normalize(y);
    return ret;
}

Transform::Transform() {

}

Transform::~Transform() {

}
