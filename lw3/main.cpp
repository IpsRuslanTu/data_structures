#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
  int nameNum;
  int x;
  int y;
};

void readPointsfromFile(vector<Point> &arr);
void createMatrix(vector<Point> arrOfCoords, vector<vector<int>> &arrGraph);
void DFS(vector<vector<int>> graphMatrix, int maxLengthOfGraph, vector<int> &path, int &start);
int findElemWithMaxPaths(vector<vector<int>> graphMatrix, int numOfPoints);
void printMatrix(vector<vector<int>> graphMatrix, int numOfPoints);
void printPath(vector<int> arrPath);

int main()
{
  system("cls");

  vector<int> truePath;      // для хранения пути
  vector<Point> arrOfPoints; // хранение координат точек
  readPointsfromFile(arrOfPoints);
  int numberOfPoints = arrOfPoints.size(); // количество элементов
  vector<vector<int>> graph(numberOfPoints, vector<int>(numberOfPoints, 0));
  createMatrix(arrOfPoints, graph);
  int startElement = findElemWithMaxPaths(graph, numberOfPoints);
  printMatrix(graph, numberOfPoints);
  DFS(graph, numberOfPoints, truePath, startElement);
  printPath(truePath);

  return 0;
}

void readPointsfromFile(vector<Point> &arr)
{
  string nameFilePoints;

  cout << "Enter file name with points of scheme: ";
  cin >> nameFilePoints;
  ifstream filePoints(nameFilePoints);
  int index;
  int coordX;
  int coordY;

  Point point;

  while (!filePoints.eof())
  {
    filePoints >> index >> coordX >> coordY;

    point.nameNum = index;
    point.x = coordX;
    point.y = coordY;

    arr.push_back(point);
  }
  filePoints.close();
}

void createMatrix(vector<Point> arrOfCoords, vector<vector<int>> &arrGraph)
{
  string nameFileCurves;
  cout << "Enter file name with curves around of points: ";
  cin >> nameFileCurves;

  ifstream fileCurves(nameFileCurves);
  int startPoint;
  int endPoint;

  int intervalX;
  int intervalY;
  int intervalMain;

  while (!fileCurves.eof())
  {
    fileCurves >> startPoint >> endPoint;

    // Вычисление расстояния между точками
    intervalX = arrOfCoords[startPoint].x - arrOfCoords[endPoint].x;
    intervalY = arrOfCoords[startPoint].y - arrOfCoords[endPoint].y;
    intervalMain = sqrt(pow(intervalX, 2) + pow(intervalY, 2));

    // Ввод данных в матрицу смежности
    arrGraph[startPoint][endPoint] = intervalMain;
    arrGraph[endPoint][startPoint] = intervalMain;
  }
  fileCurves.close();
}

int findElemWithMaxPaths(vector<vector<int>> graphMatrix, int numOfPoints)
{
  int maxDistance = 0;
  int mainPoint;

  for (int i = 0; i < numOfPoints; i++)
  {
    int tempMaxDistance = 0;
    for (int j = 0; j < numOfPoints; j++)
    {
      tempMaxDistance += graphMatrix[i][j];
    }
    if (tempMaxDistance > maxDistance)
    {
      maxDistance = tempMaxDistance;
      mainPoint = i;
    }
  }
  cout << "Element " << mainPoint << " has max length of paths = " << maxDistance << endl;
  return mainPoint;
}

void printMatrix(vector<vector<int>> graphMatrix, int numOfPoints)
{
  string print;
  cout << "Do you want to print the matrix? y/n : ";
  cin >> print;

  if (print == "y" || print == "Y")
  {
    for (int i = 0; i < numOfPoints; i++)
    {
      for (int j = 0; j < numOfPoints; j++)
        printf("%4d", graphMatrix[i][j]);
      cout << endl;
    }
  }
}

void printPath(vector<int> arrPath)
{
  cout << "The path from the point " << arrPath[0] << ", along the shortest paths, without cycles: " << endl;
  for (int i = 0; i < arrPath.size(); i++)
    cout << arrPath[i] << " - ";
}

void DFS(vector<vector<int>> graphMatrix, int maxLengthOfGraph, vector<int> &path, int &start)
{

  path.push_back(start);

  int minDistance = INT_MAX;
  int newStart;

  for (int i = 0; i < maxLengthOfGraph; i++)
  {
    if (graphMatrix[i][start] != 0 && !(find(path.begin(), path.end(), i) != path.end()) &&
        graphMatrix[i][start] < minDistance)
    {
      minDistance = graphMatrix[i][start];
      newStart = i;
    }
  }

  if (minDistance != INT_MAX)
  {
    DFS(graphMatrix, maxLengthOfGraph, path, newStart);
  }
}