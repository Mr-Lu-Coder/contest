#ifndef __ROUTE_H__
#define __ROUTE_H__
struct Edge{
    int cnt;
    int from, to, w, next;
};

void search_route(int *import_head, Edge *import_edge, int *import_rev_head, Edge *import_rev_edge,
        int import_edgenum, int s, int t, int *import_vv, int import_num);
void dfs(int cur, int t, int curw);
#endif
