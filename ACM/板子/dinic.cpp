struct edge{int to,cap,rev;};
vector<edge>g[maxn];
int level[maxn];
int iter[maxn];   //当前弧
void add(int from, int to, int cap)
{
	g[from].push_back(edge{to,cap,(int)g[to].size()});
	g[to].push_back(edge{from, 0, (int)g[from].size() - 1});
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int>que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front();que.pop();
        for(int i=0;i<g[v].size();i++)
        {
            edge &e=g[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f)
{
    if(v==t) return f;
    for(int &i=iter[v];i<g[v].size();i++)
    {
        edge &e=g[v][i];
        if(e.cap>0&&level[v]<level[e.to])
        {	//debug(v),debug(e.to);
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                g[e.to][e.rev].cap+=d;
                return d;
            }
            
        }

    }
    if(!f) level[v]=-1; 
    return 0;
}
int maxflow(int s,int t)
{
    int flow=0;
    while(1)
    {
        bfs(s);
        if(level[t]<0) return flow;
        set0(iter);
        int f;
        while(f=dfs(s,t,inf))
            flow+=f;

    }
    return flow;
}