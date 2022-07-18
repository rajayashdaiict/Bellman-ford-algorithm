#include <bits/stdc++.h>
using namespace std;
#include <omp.h>
#define NUM_THREADS 4 // change this 1 2 4 8, 1 for serial

#define int long long
#define first ff
#define second ss
const int INF=1e9;

int convert_dimension_2D_1D(int x, int y, int n) 
{
    return x * n + y;
}

void bellman_ford(int n, vector<int>&mat, vector<int>&dist, bool *has_negative_cycle) {

    *has_negative_cycle = false;
    int current_queue = 0;
    int *enqueue_counter;
    std::queue<int> queue;
    bool *in_queue;
    in_queue = (bool *) calloc(sizeof(bool), n+1);
    enqueue_counter = (int *) calloc(n+1, sizeof(int));
    in_queue[1] = true;
    queue.push(1);
    enqueue_counter[1] = 1;
    omp_lock_t writelock;
    omp_init_lock(&writelock);
    chrono::high_resolution_clock::time_point start_t = std::chrono::high_resolution_clock::now();


    while(!queue.empty() && !*has_negative_cycle){
        int u = queue.front(); queue.pop();
        in_queue[u] = false;
        #pragma omp parallel for num_threads(NUM_THREADS) 
            for (int v = 1; v < n; v++) {
                int weight = mat[u * n + v];
                if (weight < INF) {
                    // cout<<weight<<" "<<v<<endl;;
                    int new_dist = weight + dist[u];
                    if (new_dist < dist[v]) {
                        dist[v] = new_dist;
                        enqueue_counter[v]++;
                        if (in_queue[v] == false) {
                            in_queue[v] = true;
                            if (enqueue_counter[v] >= n) {
                                *has_negative_cycle = true;
                            }
                            omp_set_lock(&writelock);
                            {
                               queue.push(v);
                            }
                            omp_unset_lock(&writelock);
                        }
                    }
                }
            }
    }
    
    chrono::high_resolution_clock::time_point end_t = std::chrono::high_resolution_clock::now();
        chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end_t - start_t);
        cout<<"Thread Elapsed time: " << time_span.count() << endl; 
        omp_destroy_lock(&writelock);

    //step 4: free memory (if any)
    free(enqueue_counter);
}
void test_case() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> v(n+1,vector<int>(n+1,INF));
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        v[a][b]=c;
    }
    vector<int> mat;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            // if(v[i][j]==INF)
            //     cout<<"IN"<<" ";
            // else
            // {
            //     cout<<v[i][j]<<" ";
            // }
            mat.push_back(v[i][j]);
        }
        // cout<<endl;
    }
    // for(int i=0;i<mat.size();i++)
    // {
    //     cout<<mat[i]<<endl;
    // }
    vector<int> dis(n+1,INF);
    dis[1]=0;
    bool cycle=false;
    bellman_ford(n+1,mat,dis,&cycle);
    if(cycle)
        {
            cout<<"negative"<<endl;
            return;
        }
    for(int i=1;i<dis.size();i++)
    {
        cout<<dis[i]<<" ";
    }
}

signed main() {
     #ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int T = 1;
    //cin >> T;
    while(T--) test_case();
}