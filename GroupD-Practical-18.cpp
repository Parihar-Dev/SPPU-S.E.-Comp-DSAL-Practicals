/*
Given sequence k = k1<k2<.....<kn of n sorted keys, with a search probility pi for each key ki. Build the Binary Search Tree that has the least
search cost given the access probability for each key?
*/

#include<iostream>
using namespace std;

void const_obj(void);
void print(int,int);
float p[20],q[20],wt[20][20],c[20][20];
int r[20][20],n;

int main()
{
    cout<<"\nPROGRAM FOR OBST : ";
    cout<<"\nEnter the total number of nodes : ";
    cin>>n;

    cout<<"\nEnter the probability for successfull search : ";
    for (int i = 1 ; i<=n ; i++)
    {
        cout<<"p["<<i<<"] : ";
        cin>>p[i];
    }

    cout<<"\nEnter the probability for unsuccessfull search : ";
    for (int i = 0 ; i<=n ; i++)
    {
        cout<<"q["<<i<<"] : ";
        cin>>q[i];
    }
    const_obj();
    print(0,n);
    cout<<endl;
}

void const_obj(void)
{
    int i,j,k;

    for(i = 0 ; i < n ;i++)
    {
        c[i][i] = 0.0;
        r[i][i] = 0;
        wt[i][i] = q[i];
        wt[i][i+1] = q[i] + q[i+1] + p[i+1];
        c[i][i+1] = q[i] + q[i+1] + p[i+1];
        r[i][i+1] = i + 1;
    }
    c[n][n] = 0.0;
    r[n][n] = 0;
    wt[n][n] = q[n];

    for (i = 2 ; i<=n ; i++)
    {
        for (j = 0 ; j<=n-i ; j++)
        {
            wt[j][j+i] = p[j+i] + q[j+i] + wt[j][j+i-1];
            c[j][j+i] = 9999;
            for (k = j+1 ; k<= j+i ; k++)
            {
                if (c[j][j+i] > (c[j][k-1] + c[k][j+i]))
                {
                    c[j][j+i] = (c[j][k-1] + c[k][j+i]);
                    r[j][j+i] = k;
                }
            }
            c[j][j+i] += wt[j][j+i];
        }
        cout<<endl;
    }
    cout<<"\nOptimal BST : ";
    cout<<"\nwt[0]["<<n<<"] : "<<wt[0][n];
    cout<<"\nc[0]["<<n<<"] : "<<c[0][n];
    cout<<"\nr[0]["<<n<<"] : "<<r[0][n];
}

void print(int a, int b)
{
    if (a>=b)
        return;
    if (r[a][r[a][b]-1] != 0)
        cout<<"\nLeft child of "<<r[a][b]<<": "<<r[a][r[a][b]-1];
    if (r[r[a][b]][b] != 0)
        cout<<"\nRight Child of "<<r[a][b]<<" : "<<r[r[a][b]][b];
    print(a,r[a][b]-1);
    print(r[a][b],b);
    return;
}
