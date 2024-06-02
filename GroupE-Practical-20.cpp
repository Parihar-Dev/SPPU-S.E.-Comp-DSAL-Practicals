/*
Consider a scenario for hospital to cater services to different kinds of patients as Serious (top priority) b)Non-Serious
(Medium Priority) c) General Checkup (Least Priority). Implement the priority queue to cater services to the patients.
*/

#include<iostream>
using namespace std;

struct Patient
{
    string name;
    int priority;
};

class Priority_Queue
{
    private:
        Patient arr[100];
        int rear;
    public:
        Priority_Queue()
        {
            rear = -1;
        }
        bool isEmpty()
        {
            return (rear == -1);
        }
        bool isFull()
        {
            return (rear == 99);
        }
        void enque(Patient p)
        {
            if (isFull())
            {
                cout<<"\nQueue Overflow";
                return;
            }
            int i;
            for(i = rear; i>=0; i--)
            {
                if(arr[i].priority > p.priority)
                    arr[i+1] = arr[i];
                else
                    break;
            }
            arr[i+1] = p;
            rear++;
        }
        Patient dequeue()
        {
            if (isEmpty())
            {
                cout<<"Queue Underflow\n";
                return {"",-1};
            }
            Patient frontPatient = arr[rear];
            rear--;
            return frontPatient;
        }
};

int main()
{
    Priority_Queue pq;
    int n;
    cout<<"Enter the number of patients : ";
    cin>>n;

    for (int i = 0 ; i < n ; i++)
    {
        Patient p;
        cout<<"Enter the name of the patient : ";
        cin>>p.name;
        cout<<"Enter the priority of patient (1-General Check Up,2-Non-Serious,3-Serious) : ";
        cin>>p.priority;
        pq.enque(p);
    }

    cout<<"Serving Patients : ";

    Patient patients[100];
    int index = 0;

    while (!pq.isEmpty())
    {
        patients[index++] = pq.dequeue();
    }

    for (int i = 0 ; i<n ; i++)
    {
        Patient p = patients[i];
        cout<<"\nPatient Name : "<<p.name<<", Priority : ";
        if (p.priority == 1)
            cout<<"General Check-Up";
        else if (p.priority == 2)
            cout<<"Non-Serious";
        else if (p.priority == 3)
            cout<<"Serious";
    }
    return 0;
}

