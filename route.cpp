#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
const int MAX_INT = 0x7fffffff;
const int maxn_edge = 4800;
const int maxn_node = 605;
#define WEIGHT_MAX 100
//你要完成的功能总入口

//edge 邻接表数组
//edge_num 边的数量
//s t vv, 起点、终点、要经过的点集

//两点边所在的索引



//因为在这个函数里要用所以我把所有的有定义成全局变量，
//把future_net.cpp里的给赋值过来了
int head[maxn_node];
Edge edge[maxn_edge];
int rev_head[maxn_node];
Edge rev_edge[maxn_edge];

int index[maxn_node][maxn_node];
int weight[maxn_node][maxn_node];
int pre[maxn_node];
int tmp_pre[maxn_node];
int is_find;
int vv[55];
int ans[maxn_node];
int ans_num;
int edge_num;
int vv_num;
int mmin = MAX_INT;


bool vis[maxn_node];


void Init()
{
    is_find = 0;
    mmin = MAX_INT;
    for (int i = 0; i < maxn_node; i++)
    {
        pre[i] = tmp_pre[i] = -1;
    }
    memset(vis, 0, sizeof(vis));
    ans_num = 0;
}

bool contain_allvv(int *pre)
{

    for (int i = 1; i <= vv_num; i++)
    {
        int flag = 0;
        for (int j = 0; j < maxn_node; j++)
        {
            //cout << vv[i] << " " << pre[j] << endl;
            if (pre[j] == vv[i])
            {
                flag = 1;
                break;
            }
        }
        if (!flag) return false;
    }
    return true;
}

void output(int s, int cur)
{
    if (cur != s && cur != -1) output(s, pre[cur]);

        cout << cur << " ";
        ans[ans_num++] = cur;

}
void search_route(int *import_head, Edge *import_edge, int *import_rev_head, Edge *import_rev_edge,
        int import_edgenum, int s, int t, int *import_vv, int import_num)
{
    memcpy(head, import_head, sizeof(head));
    memcpy(edge, import_edge, sizeof(edge));
    memcpy(rev_head, import_rev_head, sizeof(rev_head));
    memcpy(rev_edge, import_rev_edge, sizeof(rev_edge));
    memcpy(vv, import_vv, sizeof(vv));
    vv_num = import_num;
    edge_num = import_edgenum;
    //for (int i = 0; i < edge_num; i++)
    //{
    //    printf("%d %d %d %d\n", edge[i].from, edge[i].to, edge[i].w, edge[i].cnt);
    //}
    //printf("%d %d\n", s, t);
    //for (int i = 1; i <= vv_num; i++)
    //    printf("%d ", vv[i]);
    //printf("\n");
    //weight 初始化为最大值
    for (int i = 0; i <= 600; i++)
        for (int j = 0; j <= 600; j++) weight[i][j] = WEIGHT_MAX;
    //得到任意两点间权值最小的索引
    for (int i = 0; i < edge_num; i++) {
        int x = edge[i].from;
        int y = edge[i].to;
        if (edge[i].w < weight[x][y])
        {
            index[x][y] = edge[i].cnt;
            weight[x][y] = edge[i].w;
        }
    }

    printf("mmin Init: %d\n", mmin);

    Init();

    dfs(s, t, 0);
    cout << is_find << " " << mmin<< endl;
    output(s, t);
    cout << endl;
    for (int i = 0; i < ans_num-1; i++)
    {
        cout << index[ans[i]][ans[i+1]] << " ";
        record_result(index[ans[i]][ans[i+1]]);
    }
    cout << endl;

}


void dfs(int cur, int t, int curw)
{
    //printf("in %d %d %d\n", cur, t, curw);
    if (cur == t){
        //output();
        if  (curw < mmin)
        {
            if (contain_allvv(tmp_pre)) {
                is_find = 1;
                mmin = curw;
                memcpy(pre, tmp_pre, sizeof(pre));
            }

        }
    }
    else {
        for (int i = head[cur]; i != -1; i = edge[i].next)
        {
            //和cur相连的所有的点可以先排个序，优先选择vv里的
            int to = edge[i].to;
            if (!vis[to]) {
                vis[to] = 1;
                tmp_pre[to] = cur;
                dfs(to, t, curw+edge[i].w);
                tmp_pre[to] = -1;
                vis[to] = 0;
            }
        }
    }
}
