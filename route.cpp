
#include "route.h"
#include "lib_record.h"
#include <stdio.h>


//你要完成的功能总入口

//edge 邻接表数组
//edge_num 边的数量
//s t vv, 起点、终点、要经过的点集

//两点边所在的索引
int index[605][605];
int weight[605][605];
#define WEIGHT_MAX 100
void search_route(Edge *edge, int edge_num, int s, int t, int *vv)
{

    for (int i = 0; i < edge_num; i++)
    {
        printf("%d %d %d %d\n", edge[i].from, edge[i].to, edge[i].w, edge[i].cnt);
    }

    unsigned short result[] = {2, 6, 3};//示例中的一个解
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




    for (int i = 0; i < 3; i++)
        record_result(result[i]);
}
void MainStream(Edge edge[],int maxn,int s,int t)
{

}
void dfs()
{
    static stack<int> rout;
}
