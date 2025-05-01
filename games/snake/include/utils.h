#ifndef UTILS_H
#define UTILS_H

#define VEC2_SPLIT(v) ((v).x), ((v).y)

#define VEC2_PTR_SPLIT(p) ((p)->x), ((p)->y)

#define VEC2_MAKE(x, y) ((Vector2){(x), (y)})

char *str_concat(const char *s1, const char *s2);

#endif //UTILS_H
