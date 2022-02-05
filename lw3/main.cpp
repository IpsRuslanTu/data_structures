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
void DFS(vector<vector<int>> graphMatrix, int maxLengthOfGraph, vector<int> &path, int &start);

int main()
{
  system("cls");

  vector<int> truePath;                     // для хранения пути
  vector<Point> arrOfPoints;                // хранение координат точек
  readPointsfromFile(arrOfPoints);
  int numberOfPoints = arrOfPoints.size();  // количество элементов

  vector<vector<int>> graph(numberOfPoints, vector<int>(numberOfPoints, 0));
  vector<int> distance(numberOfPoints, 0);

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
    intervalX = arrOfPoints[startPoint].x - arrOfPoints[endPoint].x;
    intervalY = arrOfPoints[startPoint].y - arrOfPoints[endPoint].y;
    intervalMain = sqrt(pow(intervalX, 2) + pow(intervalY, 2));

    // Ввод данных в матрицу смежности
    graph[startPoint][endPoint] = intervalMain;
    graph[endPoint][startPoint] = intervalMain;

    // Поиск элемента, имеющего наибольшую суммарную длину связей с другими элементами
    distance[startPoint] += intervalMain;
    distance[endPoint] += intervalMain;
  }
  fileCurves.close();

  int maxDistance = 0;
  int mainPoint;

  for (int i = 0; i < distance.size(); i++)
    if (distance[i] > maxDistance)
    {
      mainPoint = i;
      maxDistance = distance[i];
    }
  cout << "Point with a long path length: " << mainPoint << endl;

  // Печать матрицы смежности
  for (int i = 0; i < numberOfPoints; i++)
  {
    for (int j = 0; j < numberOfPoints; j++)
      printf("%4d", graph[i][j]);
    cout << endl;
  }

  truePath.push_back(mainPoint);
  DFS(graph, numberOfPoints, truePath, mainPoint);

  for (int i = 0; i < truePath.size(); i++)
    cout << truePath[i] << " - ";

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

void DFS(vector<vector<int>> graphMatrix, int maxLengthOfGraph, vector<int> &path, int &start)
{
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
    path.push_back(newStart);
    DFS(graphMatrix, maxLengthOfGraph, path, newStart);
  }
}