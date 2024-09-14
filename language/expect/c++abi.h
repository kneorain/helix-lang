// Part of: Expect
// Used in: Helix Programming Language
#ifndef __C_PLUS_PLUS_ABI_H__
#define __C_PLUS_PLUS_ABI_H__

#include <helix/stdc.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
class Point {
#else
typedef struct Point {
#endif
int x;
int y;
#ifdef __cplusplus
public:
Point(int x, int y);
float distance(Point other);
float distance_from_origin();
void translate(int dx, int dy);
};
#else
} Point;
#endif
#ifndef __cplusplus
Point* Point_new(int x, int y);
float Point_distance(Point* self, Point* other);
float Point_distance_from_origin(Point* self);
void Point_translate(Point* self, int dx, int dy);
#endif
#ifdef __cplusplus
int add(int a, int b);
Point add_Point(Point a, Point b);
#else
int add(int a, int b);
Point* add(Point* a, Point* b);
#endif
#ifdef __cplusplus
}
#endif

#endif // __C_PLUS_PLUS_ABI_H__