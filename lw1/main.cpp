#include <iostream>
#include <string>
using namespace std;

struct Stack
{
    string stackData;
    Stack *link;
};

struct Queue
{
    string queueName;
    Stack *topStack;
    Queue *next;
};

Queue *front = nullptr;
Queue *rear = nullptr;

bool isEmptyQueue();
void addToQueue();
void deleteFromQueue();
void showFrontQueue();
void displayQueue();

void pushStack(Queue *frontQueue);
void popStack(Queue *frontQueue);
void displayStack(Queue *frontQueue);

int main()
{
    char userCommand;
    do
    {
        cout << "Queue operation:\n\n" 
             << "1. Add element\n"
             << "2. Delete element\n"
             << "3. Display queue\n"
             << "4. Operation with front element of queue\n"
             << "5. Exit\n\n"
             << "Choose command > ";
        cin >> userCommand;
        cout << endl;
        switch (userCommand)
        {
            case '1': 
                addToQueue();
                break;
            case '2': 
                deleteFromQueue();
                break;
            case '3': 
                displayQueue();
                break;
            case '4': 
                if (isEmptyQueue()) cout << "\nQueue is empty\n";
                else
                    {                
                        showFrontQueue();
                        char subMenuCommand;
                        do
                        {
                            cout << "1. Add to stack\n"
                                 << "2. Delete from stack\n"
                                 << "3. Display stack\n"
                                 << "4. Return to main menu\n\n"
                                 << "Choose command > ";
                            cin >> subMenuCommand;
                            cout << endl;
                            switch (subMenuCommand)
                            {
                                case '1':
                                    pushStack(front);
                                    break;
                                case '2':
                                    popStack(front);
                                    break;
                                case '3':
                                    displayStack(front);
                                    break;
                                default:
                                    cout << "\nError command. Try again\n\n";
                                    break;
                            }
                        } while (subMenuCommand != '4');
                    }
                break;
            case '5':
                break;
            default: cout << "\nError command. Try again\n\n";
                break;
        }
    } while (userCommand != '5');
    return 0;
}

bool isEmptyQueue()
{
    if (front == nullptr && rear == nullptr)
    return true;
    else
    return false;
}

void addToQueue()
{
    string value;
    cout << "Name of queue element > ";
    cin >> value;
    Queue *ptr = new Queue();
    ptr -> queueName = value;
    ptr -> topStack = nullptr;
    ptr -> next = nullptr;
    
    if (front == nullptr)
    {
        front = ptr;
        rear = ptr;
    }
    else
    {
        rear -> next = ptr;
        rear = ptr;
    }
    cout << endl;
}

void deleteFromQueue()
{
    if (isEmptyQueue()) cout << "\nQueue is empty\n";
    else
    {
        if (front == rear)
        {
            delete(front);
            front = rear = nullptr;
        }
        else
        {
            Queue *ptr = front;
            front = front -> next;
            delete(ptr);
        }
    }
}

void showFrontQueue()
{
    if (isEmptyQueue()) cout << "\nQueue is empty\n";
    else
        cout << "\nElement at front of queue is: " << front -> queueName << "\n\n";
}

void displayQueue()
{
    if (isEmptyQueue()) cout << "\nQueue is empty\n\n";
    else
    {
        cout << "\nQueue is: ";
        Queue *ptr = front;
        while (ptr != nullptr)
        {
            cout << ptr -> queueName << " ";
            ptr = ptr -> next;
        }
        cout << "\n\n";
    }
}

void pushStack(Queue *frontQueue) 
{
   string value;
   cout << "input stack element > ";
   cin >> value;
    
   Stack *newStack = new Stack();
   newStack -> stackData = value;
   newStack -> link = frontQueue -> topStack;
   frontQueue -> topStack = newStack;
}

void displayStack(Queue *frontQueue) 
{
    if (frontQueue -> topStack == nullptr)
        cout << "Stack is empty\n";
    else {
        Stack* ptr;
        ptr = (frontQueue -> topStack);
        cout << "Stack elements are: ";
        while (ptr != nullptr) 
        {
            cout << ptr -> stackData << " ";
            ptr = ptr -> link;
        }
   }
   cout << endl;
}

void popStack(Queue *frontQueue) 
{
    if (frontQueue -> topStack == nullptr)
        cout << "Stack is empty\n\n";
    else 
    {
        cout << "The popped element is " << frontQueue -> topStack -> stackData << "\n\n";
        Stack *tempStack;
        tempStack = frontQueue -> topStack;
        frontQueue -> topStack = frontQueue -> topStack -> link;
        delete(tempStack);
        tempStack = nullptr;
    }
}