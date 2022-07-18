#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define NUM_THREADS 4 // change this 1 2 4 8, 1 for serial

#define int long long
// #define first ff
// #define second ss
int v=0; 
const int INF = 1e15;
vector<vector<pair<int, int>>> adj;
 
bool spfa(int s, vector<int>& d) {
    int n = adj.size();
    d.assign(n, INF);
    vector<int> cnt(n, 0);
    vector<bool> inqueue(n, false);
    queue<int> q;
    omp_lock_t writelock;
     omp_init_lock(&writelock);
    chrono::high_resolution_clock::time_point start_t = std::chrono::high_resolution_clock::now();
    d[s] = 0;
    q.push(s);
    inqueue[s] = true;
    while (!q.empty()) {
        v = q.front();
        
        q.pop();
        if(v>n)
          return false;
        inqueue[v] = false;
        
        #pragma omp parallel for num_threads(NUM_THREADS)
        for(int i = 0; i < adj[v].size(); i++) 
        {
            int to = adj[v][i].first;
            int len = adj[v][i].second;
 
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                if (!inqueue[to]) {
                    omp_set_lock(&writelock);
                    q.push(to);
                    omp_unset_lock(&writelock);
                    inqueue[to] = true;
                    cnt[to]++;
                }
            }
        }
        
    }
    chrono::high_resolution_clock::time_point end_t = std::chrono::high_resolution_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end_t - start_t);
        cout<<"Thread Elapsed time: " << time_span.count() << endl; 
        omp_destroy_lock(&writelock);
    return true;
}
 
void test_case() {
  int n, m;
  cin >> n >> m;
  adj.resize(n+1);
  for(int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    adj[a].push_back({b, w});
    // adj[b].push_back({a, w});
  }
  vector<int> d;
  spfa(1, d);
 
  for(int i = 1; i <= n; i++) cout << d[i] << ' ';
}
 
signed main() {
     #ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int T = 1;
    // cin >> T;
    while(T--) test_case();
}