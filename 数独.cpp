#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 16*16*16+10;   
const int MAXM = 16*16*4+10;   
const int MAXNODE = MAXN*4+MAXM;

struct DancingLink {
	int n,s,ansd;	// 列数 节点总数
	int S[MAXM],A[MAXN],H[MAXN];	// S[]该列节点总数  A[]答案  H[]行首指针
	int L[MAXNODE],R[MAXNODE],U[MAXNODE],D[MAXNODE];	// L[],R[],U[],D[] 上下左右
	int X[MAXNODE],C[MAXNODE];	// X[] C[] 行列编号
    void init(int n){	// 初始化 
        this->n = n;
        for(int i=0; i<=n; i++)
            U[i]=i, D[i]=i, L[i]=i-1, R[i]=i+1;
        R[n]=0, L[0]=n; s=n+1;
		memset(S, 0, sizeof(S));
		memset(H, -1, sizeof(H));
    }
    void DelCol(int c){	// 删除列 
        L[R[c]]=L[c]; R[L[c]]=R[c];
        for(int i=D[c]; i!=c; i=D[i])
            for(int j=R[i]; j!=i; j=R[j])
                U[D[j]]=U[j], D[U[j]]=D[j], --S[C[j]];
    }
    void ResCol(int c){	// 恢复列 
        for(int i=U[c]; i!=c; i=U[i])
            for(int j=L[i]; j!=i; j=L[j])
                ++S[C[j]], U[D[j]]=j, D[U[j]]=j;
        L[R[c]]=c, R[L[c]]=c;
    }
    void AddNode(int r,int c){	// 添加节点 
        ++S[c], C[++s]=c, X[s]=r;
        D[s]=D[c], U[D[c]]=s, U[s]=c, D[c]=s;
        if(H[r]<0) H[r]=L[s]=R[s]=s;	// 行首节点
        else R[s]=R[H[r]], L[R[H[r]]]=s, L[s]=H[r], R[H[r]]=s;
    }
    bool dfs(int d){	// 深度，深搜遍历 
        if(!R[0]) { ansd=d; return true; }
        int c=R[0];
        for(int i=R[0]; i; i=R[i]) if(S[i]<S[c]) c=i;
        DelCol(c);
        for(int i=D[c]; i!=c; i=D[i]){
            A[d]=X[i];
            for(int j=R[i]; j!=i; j=R[j]) DelCol(C[j]);
            if(dfs(d+1)) return true;
            for(int j=L[i]; j!=i; j=L[j]) ResCol(C[j]);
        }
        ResCol(c); return false;
    }
} dlx; 

int encode(int a,int b,int c)   {
	return a*256+b*16+c+1;
}
void decode(int code,int &a,int &b,int &c)   {
	code--;
	c=code%16;
	code/=16;
	b=code%16;
	code/=16;
	a=code;
}
int main() {
	char s[20][20];
	bool first=true;
	while(scanf("%s",s[0])!=EOF) {
		if(first)first=false;
		else printf("\n");
		for(int i=1; i<16; i++)
			scanf("%s",s[i]);
		dlx.init(16*16*4);
		for(int r=0; r<16; r++)
			for(int c=0; c<16; c++)
				for(int v=0; v<16; v++)
					if(s[r][c]=='-'||s[r][c]=='A'+v) {
						int row=encode(r,c,v);
						dlx.AddNode(row,encode(0,r,c));
						dlx.AddNode(row,encode(1,r,v));
						dlx.AddNode(row,encode(2,c,v));
						dlx.AddNode(row,encode(3,(r/4)*4+c/4,v));
					}
		dlx.dfs(0);
		for(int i=0; i<dlx.ansd; i++) {
			int r,c,v;
			decode(dlx.A[i],r,c,v);
			s[r][c]='A'+v;
		}
		for(int i=0; i<16; i++)
			printf("%s\n",s[i]);
	}
}