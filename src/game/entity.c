#include "game/entity.h"
#include "core/arena.h"

Entity_Pool entity_pool_create(u64 capacity) {
    Entity_Pool pool = {
        .pool = pool_create_type(capacity, Entity),
        .next_entity_id = 0,
    };

    return pool;
}

void entity_pool_free(Entity_Pool *pool) {
    pool_free(&pool->pool);
    ZERO_STRUCT(pool);
}

Entity *entity_create(Entity_Pool *entity_pool, Entity_Flags flags, vec3 position, vec3 rotation,
                      vec3 scale, vec3 color, RND_Mesh *mesh) {

    Entity *entity = pool_alloc(&entity_pool->pool);

    *entity = (Entity){
        .id = entity_pool->next_entity_id,
        .flags = flags,
        .position = position,
        .rotation = rotation,
        .scale = scale,
        .color = color,
        .mesh = mesh,
    };

    // and increment the id
    entity_pool->next_entity_id += 1;

    return entity;
}

mat4 entity_model_transform(Entity *entity) {
    // mat4 transform = mat4_mul(mat4_translation(entity->position),
    //                           mat4_mul(mat4_rotation_y(entity->rotation.y),
    //                                    mat4_mul(mat4_rotation_x(entity->rotation.x),
    //                                             mat4_mul(mat4_rotation_z(entity->rotation.z),
    //                                                      mat4_scale(entity->scale)))));

    // Taken algebra from Brendan Galea, couldn't be bothered, tait bryan angles, Y, X, Z
    f32 sinx = sinf(entity->rotation.x);
    f32 cosx = cosf(entity->rotation.x);
    f32 siny = sinf(entity->rotation.y);
    f32 cosy = cosf(entity->rotation.y);
    f32 sinz = sinf(entity->rotation.z);
    f32 cosz = cosf(entity->rotation.z);

    // We can algebraically simplify the above like so, throwing it into godbolt,
    // it turned ~500 ASM instructions into ~100, simulating just his transform for 10,000
    // entities
    // this is faster on my computer by about 20 fps
    mat4 transform = {.cols = {
                          {
                              .x = entity->scale.x * (cosy * cosz + siny * sinx * sinz),
                              .y = entity->scale.x * (cosx * sinz),
                              .z = entity->scale.x * (cosy * sinx * sinz - cosz * siny),
                              .w = 0.0f,
                          },
                          {
                              .x = entity->scale.y * (cosz * siny * sinx - cosy * sinz),
                              .y = entity->scale.y * (cosx * cosz),
                              .z = entity->scale.y * (cosy * cosz * sinx + siny * sinz),
                              .w = 0.0f,
                          },
                          {
                              .x = entity->scale.z * (cosx * siny),
                              .y = entity->scale.z * (-sinx),
                              .z = entity->scale.z * (cosy * cosx),
                              .w = 0.0f,
                          },
                          {
                              .xyz = entity->position,
                              .w = 1.0f,
                          },
                      }};
    return transform;
}

void entity_free(Entity_Pool *entity_pool, Entity *entity) { pool_pop(&entity_pool->pool, entity); }
