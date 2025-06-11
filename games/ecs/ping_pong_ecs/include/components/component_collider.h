#ifndef COMPONENT_COLLIDER_H
#define COMPONENT_COLLIDER_H

typedef enum {
    COLLIDE_TYPE_AABB,
    COLLIDE_TYPE_CIRCLE,
    COLLIDE_TYPE_POLYGON,
} shape_type_e;

typedef struct {
    shape_type_e shape_type;
    // ?
} collider_c;

#endif //COMPONENT_COLLIDER_H
