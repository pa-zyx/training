#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

const int MAXN = 10000;
const int MAXM = 100000;
const int INF = 0x3f3f3f3f;
struct Edge {
  int to, next, cap, flow, cost;
} edge[MAXM];
int head[MAXN], tol;
int pre[MAXN], dis[MAXN];
bool vis[MAXN];
int N;  //节点总个数，节点编号从 0∼N-1
void init(int n) {
  N = n;
  tol = 0;
  memset(head, -1, sizeof(head));
}
void addedge(int u, int v, int cap, int cost) {
  edge[tol].to = v;
  edge[tol].cap = cap;
  edge[tol].cost = cost;
  edge[tol].flow = 0;
  edge[tol].next = head[u];
  head[u] = tol++;
  edge[tol].to = u;
  edge[tol].cap = 0;
  edge[tol].cost = -cost;
  edge[tol].flow = 0;
  edge[tol].next = head[v];
  head[v] = tol++;
}
bool spfa(int s, int t) {
  queue<int> q;
  for (int i = 0; i < N; i++) {
    dis[i] = INF;
    vis[i] = false;
    pre[i] = -1;
  }
  dis[s] = 0;
  vis[s] = true;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = false;
    for (int i = head[u]; i != -1; i = edge[i].next) {
      int v = edge[i].to;
      if (edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost) {
        dis[v] = dis[u] + edge[i].cost;
        pre[v] = i;
        if (!vis[v]) {
          vis[v] = true;
          q.push(v);
        }
      }
    }
  }
  if (pre[t] == -1)
    return false;
  else
    return true;
}
//返回的是最大流，cost 存的是最小费用
int minCostMaxflow(int s, int t, int &cost) {
  int flow = 0;
  cost = 0;
  while (spfa(s, t)) {
    int Min = INF;
    for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
      if (Min > edge[i].cap - edge[i].flow) Min = edge[i].cap - edge[i].flow;
    }
    for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
      edge[i].flow += Min;
      edge[i ^ 1].flow -= Min;
      cost += edge[i].cost * Min;
    }
    flow += Min;
  }
  return flow;
}

int main() {
  int m, n;
  cin >> m >> n;
  int S = 0, T = n * m + 20 + n;
  init(n * m * 3 + 100);
  for (int i = 1; i <= m * n; i++) {
    addedge(S, i, 1, 0);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int x;
      cin >> x;
      for (int k = 1; k <= n; k++) {
        addedge((j - 1) * n + k, i + m * n, 1, x * k);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    addedge(i + m * n, T, 1, 0);
  }
  int costs;
  int ans = minCostMaxflow(S, T, costs);
  printf("%.2lf\n", (double)costs / (double)n);
  // cout << (double)costs / (double)n << endl;
  return 0;
}