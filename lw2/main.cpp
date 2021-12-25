#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Tree 
{
    string name;
    int urov;
    Tree *father;               // отец в исходном дереве
    vector<Tree*> sons;         // указатели на сыновей
};

int read_from_file(ifstream &F, Tree *&r);          // чтение из файла, формирование дерева
void free_tree(Tree *&p);                           // очистка дерева
void findLevelPersons(Tree *&p, Tree *&newPerson, int level, string human);
void LCA(Tree *u, Tree *v);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "\nNumber parameters is wrong, use main.exe <input>";
		getchar();
		return 1;
	}
	ifstream Fin(argv[1]);      // ifstream Fin("input.txt");
	if (!Fin)
	{
		cout << "\nCan not open file " << argv[1];
		getchar();
		return 1;
	}
    Tree *root = 0;

    read_from_file(Fin, root);
	Fin.close();

    cout << "Tree is built in OP" << endl;
	getchar();

    char replay = 'y';

    do {
        string human1, human2;
        cout << "\nEnter the first person to search for ancestor: ";
        cin >> human1;
        cout << "\nEnter the second person to search for ancestor: ";
        cin >> human2;

        Tree *Person1, *Person2;

        findLevelPersons(root, Person1, 0, human1);
        findLevelPersons(root, Person2, 0, human2);

        LCA(Person1, Person2);

        Person1 = 0; Person2 = 0;

        cout << "Find out an ancestor for other people? y/n: ";
        cin >> replay;

    } while (replay == 'y' || replay == 'Y');

    free_tree(root);
	cout << "Dynamic memory is released" << endl;
	getchar();

	return 0;
}

int read_from_file(ifstream &F, Tree *&r)
{
    string buf;
    int i, j, k, m, len;
    Tree *p, *q, *t;            // *root = 0 
    m = -1;                     // уровень предыдущей вершины
    t = 0;                      // указатель на предыдущую вершину
    while (!F.eof())
    {
        getline(F, buf);
        len = buf.length();
        if (len == 0) continue;         // если конец файла в следующей строке или пустая строка
        k = 0;
        while (buf[k] == '.') k++;      // k-уровень вершины
        p = new Tree;
        i = 0;
        j = k;
        while (j < len) j++;
        p -> name = buf.substr(k, j - k);
        p -> urov = k;
        if (k == 0)                     // корень
        {
            r = p;
            t = r;
            m = 0;
            continue;
        }
        if (k > m)                      // переход на следующий уровень
        {
            t -> sons.push_back(p);
            p -> father = t;
        }
        else if (k == m)                // тот же уровень
        {
            q = t -> father;
            q -> sons.push_back(p);
            p -> father = q;
        }
        else                            // подъем по дереву на m-k+1 уровней
        {
            q = t;
            for (i = 0; i <= m - k; i++) q = q -> father;
            // q - отец вводимой вершины p
            q -> sons.push_back(p);
            p -> father = q;
        }
        m = k;      // текущий уровень
        t = p;      // текущая вершина
    }
    F.close();
    return 0;
}

void free_tree(Tree *&p)
{
	if (p -> sons.size())
		for (int i = 0; i < p -> sons.size(); i++) free_tree(p -> sons[i]);
	delete p;
	p = 0;
}

void LCA(Tree *u, Tree *v)
{
    string nameU = u -> name;
    string nameV = v -> name;
    while (u -> urov != v -> urov)
        if (u -> urov > v -> urov)
        {
            u = u -> father;
            if (u -> name == v -> name) 
            {
                cout << nameV << " is ancestor of " << nameU << endl;
                return;
            }
        } 
        else 
        {
            v = v -> father; 
            if (u -> name == v -> name)
            {
                cout << nameU << " is ancestor of " << nameV << endl;
                return;
            }
        }
    while (u != v)
    {
        u = u -> father;
        v = v -> father;
    }
    cout << "Common ancestor is " << u -> name << endl;
}

void findLevelPersons(Tree *&p, Tree *&newPerson, int level, string human)
{
    if (p -> name == human) newPerson = p;

    if (p -> sons.size())
        for (int i = 0; i < p -> sons.size(); i++) 
            findLevelPersons(p -> sons[i], newPerson, level + 1, human);
}