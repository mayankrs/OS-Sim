#include <iostream>
//#include <windows.h>
using namespace std;

struct pro
{
    int pn, a, bt, si;
}p[100], temp, q[100];

struct block
{
    int size, bn, start, occu;
}b[100];

int f = -1, r = -1;

int findpro(int pn, int n)
{
    int in, i;
    for (i=0;i<n;i++)
        if (pn == p[i].pn)
            in = i;
    return in;
}

void split(int i, int m)
{
    int j;
    for (j=m-1;j>i;j--)
    {
        b[j+1] = b[j];
        b[j+1].bn = b[j].bn + 1;
    }
    b[i+1].bn = b[i].bn + 1;
}

void Enqueue(pro a)
{
    if (f == -1)
        f++;
    q[++r] = a;
}

void Stuff(pro a)
{
    q[--f] = a;
}

int Empty()
{
    if (f == -1)
        return 1;
    else
        return 0;
}

pro Dequeue()
{
    pro m = q[f++];
    if (f == r+1)
    {
        f = -1;
        r = -1;
    }
    return m;
}

int main()
{
    int n, i, j, memsize, osmem, usermem, cnt, to = 0, numblcks = 0, in, diff, flag = 0, rem, f;
    cout<<"Enter number of process:";
    cin>>n;
    cout<<"Total memory space:";
    cin>>memsize;
    cout<<"OS space:";
    cin>>osmem;
    for (i=0;i<n;i++)
    {
        cin>>p[i].a>>p[i].bt>>p[i].si;
        p[i].pn = i+1;
    }

    for (i=0;i<n-1;i++)
        for (j=0;j<n-1-i;j++)
        {
            if (p[j].a > p[j+1].a)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    usermem = memsize - osmem;
    int m = n;
    j = 0;
    int g = 5;
    while (g--)
    {
        //Sleep(1000);
        while (p[j].a<=to && j<m)
            Enqueue(p[j++]);
        cout<<"test\n";
        if (!Empty())
        {
            cout<<"test2\n";
            temp = Dequeue();
            //cout<<"test2\n";
            in = findpro(temp.pn, m);
            //cout<<"test2\n";
            if (numblcks == 0)
            {
                cout<<"test4\n";
                b[numblcks].bn = 1;
                b[numblcks].size = p[in].si;
                b[numblcks].start = 0;
                b[numblcks].occu = p[in].pn;
                cout<<"Process: "<<p[in].pn<<" to block "<<b[numblcks].bn<<" from "<<b[numblcks].start<<endl;
                numblcks++;
            }
            else
            {
                for (i=0;i<numblcks;i++)
                {
                    if (b[i].occu != 0)
                    {
                        f = findpro(b[i].occu, m);
                        p[f].bt--;
                    }
                    if (b[i].occu == 0 && b[i].size >= p[in].si)
                    {
                        b[i].occu = p[in].pn;
                        diff = b[i].size - p[in].si;
                        if (diff > 0)
                        {
                            split(i, numblcks);
                            numblcks++;
                            b[i+1].occu = 0;
                            b[i+1].size = diff;
                            b[i+1].start = b[i].start + b[i].size;
                            n--;
                        }
                        b[i].size = p[in].si;
                        flag = 1;
                        n--;
                        cout<<"Process: "<<p[in].pn<<" to block "<<b[i].bn<<" from "<<b[i].start<<endl;
                    }
                }
                if (flag == 1)
                    continue;
                rem = usermem - b[numblcks - 1].size + b[numblcks - 1].start;
                if (rem > 0 && rem >= p[in].si)
                {
                    b[numblcks].start = usermem - rem;
                    b[numblcks].size = p[in].si;
                    b[numblcks].occu = p[in].pn;
                    b[numblcks].bn = b[numblcks - 1].bn + 1;
                    numblcks++;
                    rem -= p[in].si;
                    if (rem != 0)
                    {
                        b[numblcks].bn = b[numblcks - 1].bn + 1;
                        b[numblcks].size = rem;
                        b[numblcks].occu = 0;
                        b[numblcks].start = b[numblcks - 1].start + b[numblcks - 1].size;
                    }
                    n--;
                }
                else
                    Stuff(p[in]);
            }
        }
        else
        {
            cout<<"test3\n";
            to++;
        }
    }
    /*for (i=0;i<n;i++)
    {
        cout<<p[i].pn<<" "<<p[i].a<<" "<<p[i].bt<<" "<<p[i].si<<endl;
    }*/
    return 0;
}
