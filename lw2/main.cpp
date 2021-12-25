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
void findPersonInTree(Tree *&p, Tree *&newPerson, int level, int numberHuman, string humanName);
void LCA(Tree *u, Tree *v);
void enterNamePerson(Tree *&root, Tree *&Person, int level, int numberHuman);

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
        Tree *Person1 = 0, *Person2 = 0;
        enterNamePerson(root, Person1, 0, 1);
        enterNamePerson(root, Person2, 0, 2);

        LCA(Person1, Person2);

        Person1 = 0; Person2 = 0;

        cout << "Enter 'Y' for the next search: ";
        cin >> replay;

    } while (replay == 'y' || replay == 'Y');

    free_tree(root);
	cout << "\nDynamic memory is released" << endl;
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

void findPersonInTree(Tree *&p, Tree *&newPerson, int level, int numberHuman, string humanName)
{
    cout << p -> name << endl;
    if (p -> name == humanName) newPerson = p;
    else if (p -> sons.size())
        for (int i = 0; i < p -> sons.size(); i++) 
            findPersonInTree(p -> sons[i], newPerson, level + 1, numberHuman, humanName);
}

void enterNamePerson(Tree *&root, Tree *&Person, int level, int numberHuman)
{
    do 
    {
        string humanName;
        cout << "\nEnter name of " << numberHuman << " person to search for ancestor: ";
        cin >> humanName;
        findPersonInTree(root, Person, 0, numberHuman, humanName);
        if (!Person) cout << "\nPerson does not exist in the tree, try again\n";
    } while (Person == 0);
}

void LCA(Tree *u, Tree *v)
{
    cout << endl;
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
    cout << "Common ancestor of " << nameU << " and " << nameV << " is " << u -> name << endl;
    cout << endl;
}