#include <iostream>
#include <string.h>
#include "tool.h"
#include <map>
#include <queue>
#include <math.h>
#include <QDebug>

using namespace std;

const int maxn = 1000000 + 100;
const int SIGMA_SIZE = 26;
const int maxnode = 1000000 + 100;
int n,ans;
bool vis[maxn];
map<string,int> ms;
int ch[maxnode][SIGMA_SIZE + 5];
int val[maxnode];
int idx(char c){return c - 'a';}
struct Trie{
    int sz;
    Trie(){sz = 1;memset(ch[0],0,sizeof(ch[0]));memset(vis,0,sizeof(vis));}
    void insert(char * s){
        int u = 0,n = strlen(s);
        for(int i = 0;i < n;i++){
            int c = idx(s[i]);
            if(!ch[u][c]){
                memset(ch[sz],0,sizeof (ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u]++;
    }
};
int last[maxn],f[maxn];
void print(int j) {
 if(j&&!vis[j]){
     ans += val[j];vis[j] = 1;
     print(last[j]);
 }
}
void getFail(){
  queue<int>q;
  f[0] = 0;
  for(int c = 0;c<SIGMA_SIZE;c++){
       int u = ch[0][c];
       if(u){f[u] = 0;q.push(u);last[u]=0;}
  }
  while(!q.empty()){
        int r = q.front();q.pop();
        for(int c = 0;c<SIGMA_SIZE;c++){
            int u = ch[r][c];
            if(!u){
                ch[r][c] = ch[f[r]][c];
                continue;
            }
        q.push(u);
        int v = f[r];
        while(v&&!ch[v][c])v = f[v];
        f[u] = ch[v][c];
        last[u] = val[f[u]]?f[u] : last[f[u]];
        }
  }
}

void find_T(char* T) {
    int n = strlen(T);
    int j = 0;
    for(int i = 0;i<n;i++) {
        int c = idx(T[i]);
        j = ch[j][c];
        if(val[j])print(j);
        else if(last[j])print(last[j]);
    }
}

int ACforString(char *keyword1,char *keyword2,char *keyword3,char *keyword4,char *keyword5,char *keyword6,char *text){
    Trie trie;
    ans = 0;
    trie.insert(keyword1);
    trie.insert(keyword2);
    trie.insert(keyword3);
    trie.insert(keyword4);
    trie.insert(keyword5);
    trie.insert(keyword6);
    getFail();
    find_T(text);
    qDebug()<<ans;
    return ans;
}
