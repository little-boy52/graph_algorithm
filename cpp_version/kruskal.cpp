#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Elemtype
{
    int u, v, w;
    Elemtype(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
    bool operator<(const Elemtype &rhs) const
    {
        return w < rhs.w;
    }
};

class Graph
{
private:
    const int V;
    list<Elemtype> graph;
public:
    Graph(int v): V(v) {}
    void add_edge(int u, int v, int w)
    {
        graph.push_back({u, v, w});
    }

    int root(vector<int> &parent, int i)
    {
        while (i != parent[i])
        {
            parent[i] = parent[parent[i]];
            i = parent[i];
        }

        return i;
    }

    void unite(vector<int> &parent, vector<int> &ranks, int i, int j)
    {
        int i_root = root(parent, i);
        int j_root = root(parent, j);

        if (ranks[i_root] < ranks[j_root])
        {
            parent[i_root] = j_root;
        }
        else
        {
            parent[j_root] = i_root;
            if (ranks[i_root] == ranks[j_root])
            {
                ranks[i_root] += ranks[j_root];
            }
        }
    }

    void kruskal_algo()
    {
        list<Elemtype> result;
        vector<int> parent(V);
        for (int i = 0; i < V; ++i)
        {
            parent[i] = i;

        }
        vector<int> ranks(V, 0);
        graph.sort();
        //for (auto i: graph)
        //{
        //cout << i.content.w << " ";
        //}
        //cout << endl;


        auto i = graph.begin();
        for (int no_edge = 0; no_edge < V - 1; ++i)
        {
            int u, v, w;
            u = i->u;
            v = i->v;
            w = i->w;

            if (root(parent, u) != root(parent, v))
            {
                ++no_edge;
                unite(parent, ranks, u, v);
                result.push_back({u, v, w});
            }
        }
        cout << "Edge   |   Weight" << endl;
        for_each(result.begin(), result.end(), [](Elemtype & i)
        {
            cout << i.u << " - " << i.v << " : " << i.w << endl;
        });
    }

};

int main(void)
{
    Graph g(6);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 4);
    g.add_edge(1, 2, 2);
    g.add_edge(1, 0, 4);
    g.add_edge(2, 0, 4);
    g.add_edge(2, 1, 2);
    g.add_edge(2, 3, 3);
    g.add_edge(2, 5, 2);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 2, 3);
    g.add_edge(3, 4, 3);
    g.add_edge(4, 2, 4);
    g.add_edge(4, 3, 3);
    g.add_edge(5, 2, 2);
    g.add_edge(5, 4, 3);
    g.kruskal_algo();

    return 0;
}
