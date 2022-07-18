/*#include<bits/stdc++.h>
#include <omp.h>
using namespace std;
struct node {
    int u;
    int v;
    int wt; 
    node(int first, int second, int weight) {
        u = first;
        v = second;
        wt = weight;
    }
};
#define CHUNKSIZE 1 

/*
/defines the chunk size as 1 contiguous iteration/
#define CHUNKSIZE 1 
/forks off the threads/
#pragma omp parallel private(i) {
/Starts the work sharing construct/
#pragma omp for schedule(dynamic, CHUNKSIZE)
        list<list_node>::iterator i;
        for (int u = 0; u < V - 1; u++) {
            if (dist[u] != INT_MAX) {
                for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                    if (dist[i->get_vertex()] > dist[u] + i->get_weight()) {
                        dist[i->get_vertex()] = dist[u] + i->get_weight();
                        pre[i->get_vertex()] = u;
                    }
                }
            }
        }
    }*/
    /*
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("outputP.txt", "w", stdout);
    #endif  
    int N,m;
    cin >> N >> m;
    vector<node> edges; 
    for(int i = 0;i<m;i++) {
        int u, v, wt;
        cin >> u >> v >> wt; 
        edges.push_back(node(u, v, wt)); 
    }

    int src=0;
    cin >> src; 


    int inf = 10000000; 
    vector<int> dist(N, inf); 

    dist[src] = 0; 
    
    omp_set_num_threads(4);
    int j;
    clock_t start, end;
    double wallTime = 0;
    start = clock();
    //#pragma omp parallel for  {
    {
      //int j;
        for(int i = 1;i<=N-1;i++) {
            //#pragma omp parallel for
             {
            for (j=0; j<m; j++)
            {
                //#pragma omp critical
                if(dist[edges[j].u] + edges[j].wt < dist[edges[j].v]) {
                    dist[edges[j].v] = dist[edges[j].u] + edges[j].wt; 
                }
            }
        }
      }
    }
    end = clock();
    wallTime = (end - start)/((double)CLOCKS_PER_SEC);
    
        cout<<wallTime<<" <-wallTime"<<endl;
    for(int i = 0;i<N;i++) {
       cout << i << " " << dist[i] << endl;
    }
    


    return 0;
}
*/
/*#include<bits/stdc++.h>
#include <time.h>
using namespace std;
 
#define fast_io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0) 	
#define int long long
#define ff first
#define ss second
const int INF = 1000000000;



struct edge
{
    int v1,v2,cost;
};

void test_case()
{
    int n,m,source=1;
    cin>>n>>m;
    std::vector<edge> e;
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        edge temp={a,b,c};
        e.push_back(temp);
    }
    
    vector<int> dis(n+1,INF);
    
    dis[source]=0;           //distance of the source is 0 
    for (int i=0; i<n-1; i++)
    {
        bool check = false;
        for (int j=0; j<m; j++)
        {
            if (dis[e[j].v1] < INF)
            {
                dis[e[j].v2] = min (dis[e[j].v2], dis[e[j].v1] + e[j].cost);
                check=true;
            }
        }
        if(!check)
            break;
    }

    int flag=0;
    for (int i=0; i<n-1; i++)
    {
        bool check = false;
        for (int j=0; j<m; j++)
        {
            if (dis[e[j].v1] == INF)
            {
                dis[e[j].v2]=INF;
                check=true;
                
            }
            else
            {
                if(dis[e[i].v1]+e[i].cost<dis[e[i].v2])
                {
                    dis[e[j].v2]=INF;
                    check=true;
                }
            }
                
        }
        if(!check)
            break;
    }


    for(int i=1;i<=n;i++)
    {
       cout<<i<<" "<<dis[i]<<" "<<endl;     //here infinite indicates nagetive cycle 
    }
}

signed main()
{               
	#ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif     
    fast_io;
    clock_t start, end;
    double wallTime = 0;
    int T=1;
    start = clock();
	test_case();
	end = clock();
	wallTime = (end - start)/((double)CLOCKS_PER_SEC);
     /* Avg throughput */
        /*double throughput = ((double)sizeof(double) * 10 * 1)/wallTime;
        double mthro = ((double)sizeof(double) * 10 * 2)/wallTime;
        printf(" %lf, %lf, %lf\n",  throughput,mthro,wallTime);
}*/
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <chrono>

#define NUM_THREADS 8

using namespace std;

struct edge {
  int start;
  int end;
  int weight;
};

const int imax = std::numeric_limits<int>::max();


void bf(int N, int e_cnt, int start_v, vector<edge> gr) {

    //vector<int> d(N, imax);
    int inf = 10000000; 
    vector<int> d(N); 
    //vector<int> p(N, -1);
    
    d[start_v] = 0;

    //chrono::high_resolution_clock::time_point start_t = std::chrono::high_resolution_clock::now();
    double wallTime = 0;
      //int T=1;
    clock_t start, end;
     start = clock();
     #pragma omp parallel for num_threads(4)
     for(int i=0;i<N;i++)
     d[i]=inf;
     
    for (int i = 0; i < N - 1; i++) 
      {
        #pragma omp parallel for num_threads(4)
        for (int j = 0; j < e_cnt; j++)
             
            if (d[ gr[j].start ] < inf) 
              {
                if (d[ gr[j].end ] > d[ gr[j].start ] + gr[j].weight) 
                  {
                    //#pragma omp critical
                    d[ gr[j].end ] = d[ gr[j].start ] + gr[j].weight;
                    //p[ gr[j].end ] = gr[j].start;
                  }
              }
      }
      
	   //test_case();
	   end = clock();
 	  wallTime = (end - start)/((double)CLOCKS_PER_SEC);
     cout<<wallTime<<" <-wallTime"<<endl;
  //chrono::high_resolution_clock::time_point end_t = std::chrono::high_resolution_clock::now();

  //chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(end_t - start_t);
  //cout << /*"Elapsed time: " << */time_span.count() << endl; 

  for(int i = 0;i<N;i++) {
       cout << i << " " << d[i] << endl;
    }

}

int main() {

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("outputPavan.txt", "w", stdout);
    #endif  
    int N,m;
    cin >> N >> m;
    vector<edge> edges; 
    for(int i = 0;i<m;i++) {
        int u, v, wt;
        cin >> u >> v >> wt; 
        edges.push_back({u, v, wt}); 
    }
    bf(N, m, 0, edges);

  /*if (argc < 2)
    cout << "Specify input file" << endl;

  ifstream inp;
  inp.open(argv[1], ios::out);

  int v_cnt, e_cnt, start_v, end_v;
  int start, end, weight;

  inp >> v_cnt >> e_cnt >> start_v >> end_v;

  vector<edge> gr;

  for (int i = 0; i < e_cnt; ++i)
    {
      inp >> start >> end >> weight;
      gr.push_back({start, end, weight});
    }
  inp.close();*/


  //bf(v_cnt, e_cnt, start_v, end_v, gr);

  return 0;
}