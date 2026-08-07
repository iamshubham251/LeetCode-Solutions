class Solution {
public:
    string smallestNumber(string s, long long t) {
        int e[4]={},p[]={2,3,5,7},v[10][4]={{},{},{1},{0,1},{2},{0,0,1},{1,1},{0,0,0,1},{3},{0,2}};
        for(int i=0;i<4;i++) while(t%p[i]==0)e[i]++,t/=p[i];
        if(t>1)return "-1";

        auto need=[&](array<int,4>a){
            int z=100;
            for(int k=0;k<=min(a[0],a[1]);k++)
                z=min(z,k+(a[0]-k+2)/3+(a[1]-k+1)/2);
            return z+a[2]+a[3];
        };

        int n=s.size();
        vector<array<int,4>> pre(n+1);
        vector<int> ok(n+1,1);

        for(int i=0;i<n;i++){
            pre[i+1]=pre[i]; ok[i+1]=ok[i]&&s[i]!='0';
            if(s[i]!='0')for(int j=0;j<4;j++)pre[i+1][j]+=v[s[i]-'0'][j];
        }

        if(ok[n]){
            bool yes=1;
            for(int j=0;j<4;j++)yes&=pre[n][j]>=e[j];
            if(yes)return s;
        }

        auto sub=[&](array<int,4>a,int d){
            for(int j=0;j<4;j++)a[j]=max(0,a[j]-v[d][j]);
            return a;
        };

        auto build=[&](int L,array<int,4>r){
            string x;
            while(L--)for(int d=1;d<=9;d++){
                auto q=sub(r,d);
                if(need(q)<=L){x+=char('0'+d);r=q;break;}
            }
            return x;
        };

        for(int i=n-1;i>=0;i--)if(ok[i])
            for(int d=max(1,s[i]-'0'+1);d<=9;d++){
                array<int,4> r;
                for(int j=0;j<4;j++)r[j]=max(0,e[j]-pre[i][j]-v[d][j]);
                if(need(r)<=n-i-1)
                    return s.substr(0,i)+char('0'+d)+build(n-i-1,r);
            }

        array<int,4> r={e[0],e[1],e[2],e[3]};
        int L=max(n+1,need(r));
        return build(L,r);
    }
};
