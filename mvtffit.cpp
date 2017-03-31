#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int size, num;
}p;

struct Block
{
    int size, occu, start;
}b;

vector<Process> waiting;
vector<Block> block;
vector<Process> job;

int main()
{
    int i, mem, numBlock = 0, numProcess = 0, flag, num, choice, cnt = 0;
    cout<<"Enter user memory:";
    cin>>mem;
    b.start = 0;
    b.size = mem;
    b.occu = 0;
    block.push_back(b);
    while(1)
    {
        cout<<"Memory space --> ";
        for (i=0;i<block.size();i++)
        {
            if (block[i].occu != 0)
                cout<<block[i].occu<<"("<<block[i].start<<" to "<<block[i].size + block[i].start - 1<<")"<<" | ";
            else
                cout<<"Vacant block("<<block[i].start<<" to "<<block[i].size + block[i].start - 1<<")"<<" | ";
        }
        cout<<endl<<endl;
        cout<<"waiting list (Process numbers) --> ";
        for (i=0;i<waiting.size();i++)
            cout<<waiting[i].num<<" ";
        cout<<endl<<endl;
        cout<<"1. Add Process.\n2. Remove Process.\n3. Stop Simulation.\nEnter choice:";
        cin>>choice;
        switch(choice)
        {
            case 1: cout<<"Size required:";
                    cin>>p.size;
                    p.num = numProcess + 1;
                    numProcess++;
                    flag = 0;
                    for (i=0;i<block.size();i++)            //checking the existing blocks
                    {
                        if (block[i].occu == 0 && block[i].size >= p.size)
                        {
                            block[i].occu = p.num;
                            if (block[i].size != p.size)
                            {
                                b.occu = 0;
                                b.size = block[i].size - p.size;
                                b.start = block[i].start + p.size;
                                block.insert(block.begin() + i + 1, b);
                                //have to insert new block
                            }
                            block[i].size = p.size;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)              //checking the un-partitioned memory
                    {
                        if (p.size <= mem - block.back().start - block.back().size)
                        {
                            b.size = p.size;
                            b.start = block.back().start + block.back().size;
                            b.occu = p.num;
                            block.push_back(b);
                        }
                        else            //process put in waiting since size is too big
                        {
                             cout<<"Process added to waiting list.\n";
                             waiting.push_back(p);
                        }
                    }
                    break;
            case 2: cout<<"Enter process number to remove:";
                    cin>>num;
                    for (i=0;i<block.size();i++)            //checking the existing blocks
                        if (block[i].occu == num)
                            block[i].occu = 0;
                    //merge blocks
                    cnt = 0;
                    while (cnt<block.size()-1)
                    {
                        if (block[cnt].occu == 0 && block[cnt + 1].occu == 0)
                        {
                            block[cnt].size += block[cnt + 1].size;
                            block.erase(block.begin() + cnt + 1);
                        }
                        else
                            cnt++;
                    }
                    //allot waiting list processes if possible
                    cnt = 0;
                    while(cnt < waiting.size())
                    {
                        p = waiting[cnt];
                        flag = 0;
                        for (i=0;i<block.size();i++)            //checking the existing blocks
                        {
                            if (block[i].occu == 0 && block[i].size >= p.size)
                            {
                                block[i].occu = p.num;
                                if (block[i].size != p.size)
                                {
                                    b.occu = 0;
                                    b.size = block[i].size - p.size;
                                    b.start = block[i].start + p.size;
                                    block.insert(block.begin() + i + 1, b);
                                    //have to insert new block
                                }
                                block[i].size = p.size;
                                waiting.erase(waiting.begin() + cnt);
                                flag = 1;
                                break;
                            }
                        }
                        if (flag == 0)
                            cnt++;
                    }
                    break;
            case 3: exit(0);
            default: cout<<"Enter valid option.\n";
        }
    }
    return 0;
}
