#include "route.h"
#include "lib_io.h"
#include "lib_time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
using namespace std;
const int maxn_edge = 4800;
const int maxn_node = 605;
int inhead[maxn_node];

Edge inedge[maxn_edge];
int rev_inhead[maxn_node];
Edge rev_inedge[maxn_edge];

int inedge_num = 0;
void add_edge(int num, int x, int y, int w)
{
    //正图
    inedge[inedge_num].next = inhead[x];
    inedge[inedge_num].from = x;
    inedge[inedge_num].to = y;
    inedge[inedge_num].cnt = num;
    inedge[inedge_num].w = w;
    inhead[x] = inedge_num;

    //反图
    rev_inedge[inedge_num].next = rev_inhead[y];
    rev_inedge[inedge_num].from = y;
    rev_inedge[inedge_num].to = x;
    rev_inedge[inedge_num].cnt = num;
    rev_inedge[inedge_num].w = w;
    rev_inhead[y] = inedge_num++;

}
int main(int argc, char *argv[])
{
    print_time("Begin");

    int demand_num;


    for (int i = 0; i < maxn_node; i++)
    {
        inhead[i] = rev_inhead[i] = -1;
    }
    //topo.csv;
    char topo_file[50] = "G:\\my c\\huawei\\test-cases\\case3\\topo.csv";
    FILE *fp = fopen(topo_file, "r");
    if (fp == NULL)
    {
        printf("Fail to open file %s, %s.\n", topo_file, strerror(errno));
        return -1;
    }
    while (!feof(fp))
    {
        int num, s, t, w;
        fscanf(fp, "%d,%d,%d,%d", &num, &s, &t, &w);
        add_edge(num, s, t, w);
    }
    fclose(fp);
    printf("There are %d lines in file %s.\n", inedge_num, topo_file);
    if (inedge_num == 0)
    {
        printf("Please input valid topo file.\n");
        return -1;
    }



    //demand.csv
    char demand_file[50] = "G:\\my c\\huawei\\test-cases\\case3\\demand.csv";
    demand_num = 1;
    int vv[55];
    int s, t;
    fp = fopen(demand_file, "r");
    if (fp == NULL)
    {
        printf("Fail to open file %s, %s.\n", topo_file, strerror(errno));
        return -1;
    }

    int re = fscanf(fp, "%d,%d,%d", &s, &t, &vv[demand_num++]);
    if (re == -1) {
        printf("Please input valid demand file.\n");
    }
    while(!feof(fp)) {
        fscanf(fp, "|%d", &vv[demand_num++]);
        //printf("***%d\n", vv[demand_num-1]);
    }



    search_route(inhead, inedge, rev_inhead, rev_inedge,
                 inedge_num, s, t, vv, demand_num-1);

    char result_file[50] = "G:\\my c\\huawei\\test-cases\\case3\\sample_result.csv";
    write_result(result_file);

    print_time("End");

	return 0;
}

