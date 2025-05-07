#include <iostream>
#include <algorithm>
using namespace std;

// --------- Selection Sort using Greedy Approach ---------
void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// --------- Job Scheduling using Greedy Approach ---------
struct Job {
    char id;
    int deadline;
    int profit;
};

void sortJobs(Job jobs[], int m) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

void jobScheduling(Job jobs[], int m) {
    sortJobs(jobs, m);
    int maxDeadline = 0;
    for(int i = 0; i < m; i++) {
        if(jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    char result[101];
    bool slot[101] = { false };

    for(int i = 1; i <= maxDeadline; i++)
        result[i] = '-';

    for(int i = 0; i < m; i++) {
        for(int j = jobs[i].deadline; j > 0; j--) {
            if(!slot[j]) {
                slot[j] = true;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    cout << "Scheduled Jobs: ";
    for(int i = 1; i <= maxDeadline; i++) {
        if(result[i] != '-')
            cout << result[i] << " ";
    }
    cout << endl;
}

// --------- Kruskal's Algorithm for MST ---------
struct Edge {
    int src, dest, weight;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

int find(int parent[], int i) {
    if(parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if(rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if(rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

void kruskalMST(Edge edges[], int V, int E) {
    sort(edges, edges + E, compareEdges);

    int parent[100], rank[100] = {0};

    for(int i = 0; i < V; i++)
        parent[i] = i;

    Edge result[100];
    int e = 0, i = 0;

    while(e < V - 1 && i < E) {
        Edge next = edges[i++];

        int x = find(parent, next.src);
        int y = find(parent, next.dest);

        if(x != y) {
            result[e++] = next;
            unionSets(parent, rank, x, y);
        }
    }

    cout << "Edges in Minimum Spanning Tree:\n";
    for(int i = 0; i < e; i++)
        cout << result[i].src << " - " << result[i].dest << " : " << result[i].weight << endl;
}

// -------------------- Main Function ---------------------
int main() {
    // ----------- Selection Sort Input & Output -----------
    int n;
    cout << "Enter number of elements for Selection Sort: ";
    cin >> n;
    int arr[100];
    cout << "Enter " << n << " elements:\n";
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    selectionSort(arr, n);
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    // ----------- Job Scheduling Input & Output -----------
    int m;
    cout << "\nEnter number of jobs: ";
    cin >> m;
    Job jobs[100];
    cout << "Enter job id (char), deadline (int), and profit (int):\n";
    for(int i = 0; i < m; i++) {
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    jobScheduling(jobs, m);

    // ----------- MST (Kruskal's Algorithm) -----------
    int V, E;
    cout << "\nEnter number of vertices and edges for MST: ";
    cin >> V >> E;
    Edge edges[100];
    cout << "Enter source, destination and weight for each edge:\n";
    for(int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    kruskalMST(edges, V, E);

    return 0;
}
