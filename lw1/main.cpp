#include <iostream>
#include <string>
using namespace std;

struct Stack
{
    string stack_data;
    Stack *link;
};

struct Queue_node
{
    string queueName;
    Stack *topStack;
    Queue_node *next;
};

Queue_node *front = nullptr;
Queue_node *rear = nullptr;

bool isEmptyQueue(); 
void addToQueue();
void deleteFromQueue();
void showFrontQueue();
void displayQueue();

void pushStack(Queue_node *FrontEl);
void popStack(Queue_node *FrontEl);
void displayStack(Queue_node *FrontEl);

int main()
{
    char userCommand;
    do
    {
        cout << "Queue operation:\n\n1. Add element\n2. Delete element\n3. Display queue\n"
            "4. Operation with front element of queue\n5. Exit\n\nChoose command > ";
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
                            cout << "1. Add to stack\n2. Delete from stack\n3. Display stack\n"
                                "4. Return to main menu\n\nChoose command > ";
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
    Queue_node *ptr = new Queue_node();
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
            if( front == rear)
            {
                delete(front);
                front = rear = nullptr;
            }
            else
            {
                Queue_node *ptr = front;
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
        Queue_node *ptr = front;
        while (ptr != nullptr)
        {
            cout << ptr -> queueName << " ";
            ptr = ptr -> next;
        }
        cout << "\n\n";
    }
}

void pushStack(Queue_node *FrontEl) 
{
   string value;
   cout << "input stack element > ";
   cin >> value;
    
   struct Stack* newStack = new Stack();
   newStack -> stack_data = value;
   newStack -> link = FrontEl -> topStack;
   FrontEl -> topStack = newStack;
}

void displayStack(Queue_node *FrontEl) 
{
    if (FrontEl -> topStack == nullptr)
        cout << "Stack is empty\n";
    else {
        Stack* ptr;
        ptr = (FrontEl -> topStack);
        cout << "Stack elements are: ";
        while (ptr != nullptr) 
        {
            cout << ptr -> stack_data << " ";
            ptr = ptr -> link;
        }
   }
   cout << endl;
}

void popStack(Queue_node *FrontEl) 
    {
        if (FrontEl -> topStack == nullptr)
            cout << "Stack is empty\n\n";
        else 
        {
            cout << "The popped element is " << FrontEl -> topStack -> stack_data << "\n\n";
            Stack *tempStack;
            tempStack = FrontEl -> topStack;
            (FrontEl -> topStack) = (FrontEl -> topStack -> link);
            delete(tempStack);
            tempStack = nullptr;
        }
}