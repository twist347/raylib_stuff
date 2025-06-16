#pragma once

#include <stdbool.h>

#include <config.h>

typedef unsigned long long entity_t;
typedef unsigned long long component_mask_t;

// 64 components max
#define COMPONENT_TRANSFORM    (1ull << 0)
#define COMPONENT_INPUT        (1ull << 1)
#define COMPONENT_PHYS         (1ull << 2)
#define COMPONENT_RENDER       (1ull << 2)

typedef struct {
    bool alive[MAX_ENTITIES];
    unsigned long long entity_count;
    component_mask_t component_mask[MAX_ENTITIES];


} world_t;