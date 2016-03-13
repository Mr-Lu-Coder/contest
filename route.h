#ifndef __ROUTE_H__
#define __ROUTE_H__
struct Edge{
    int cnt;
    int from, to, w, next;
};
void search_route(Edge *edge, int edge_num, int s, int t, int *vv);

#endif
