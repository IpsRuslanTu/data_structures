/*                          Тухватуллин Р. Р.  ИПС - 21
                            VS Code - 1.63.2
Лабораторная работа № 4
Задание 4. 
    В текстовом файле задана последовательность целых чисел.
    Отсортировать файл методом простого слияния с 4 лентами (8). */

#include <fstream>
#include <iostream>

bool isFile(int numberOfParams, char *inputFile);
int countingNumbers(char *inputFile);
void mergeSort(char *inputFile);
void CopyFile(const char *FileIn, const char *FileOut);

int main(int argc, char *argv[])
{
  if (isFile(argc, argv[1]))
    mergeSort(argv[1]);
  else
    return 1;
}

//----------------------------- Проверка входного файла ---------------------------------------

bool isFile(int numberOfParams, char *inputFile)
{
  if (numberOfParams != 2)
  {
    printf("\nThere should be 2 parameters, e.g. : main.exe input.txt");
    return false;
  }
  if (fopen(inputFile, "r") == NULL)
  {
    printf("\nThe sourse file cannot be read...");
    return false;
  }
  return true;
}

//-------------------------------- Подсчет чисел ----------------------------------------

int countingNumbers(char *inputFile)
{
  FILE *input;
  int oneNumber;
  int counter = 0;
  input = fopen(inputFile, "r");
  while (!feof(input))
  {
    fscanf(input, "%d", &oneNumber);
    counter++;
  }
  fclose(input);
  return counter;
}

//--------------------------- Сортировка простым однофазным слиянием ---------------------------
void mergeSort(char *inputFile)
{
  int quantityNums = countingNumbers(inputFile);
  int a, b; // Переменные для чтения чисел из файлов
  int seriesLength, i, j;
  FILE *f1, *f2, *f3, *f4;
// Делим входной файл на 2 файла 
  f1 = fopen(inputFile, "r");
  f2 = fopen("temp_2", "w");
  f3 = fopen("temp_3", "w");
  bool toggle = true;
  if (!feof(f1))
    fscanf(f1, "%d", &a);
  while (!feof(f1))
  {
    if (toggle == true)
      fprintf(f2, "%d ", a);
    else
      fprintf(f3, "%d ", a);
    toggle = !toggle;
    fscanf(f1, "%d", &a);
  }
  fclose(f3);
  fclose(f2);
  fclose(f1);
// Сортировка простым однофазным слиянием
  seriesLength = 1;
  toggle = true;
  FILE *fileForRead1, *fileForRead2, *fileForWrite;

  while (seriesLength < quantityNums)
  {
    if (toggle == true)
    {
      f2 = fopen("temp_2", "r");
      f3 = fopen("temp_3", "r");
      f1 = fopen(inputFile, "w");
      f4 = fopen("temp_4", "w");
    }
    else
    {
      f2 = fopen("temp_2", "w");
      f3 = fopen("temp_3", "w");
      f1 = fopen(inputFile, "r");
      f4 = fopen("temp_4", "r");
    }

    (fileForRead1 != f2) ? fileForRead1 = f2 : fileForRead1 = f1;
    (fileForRead2 != f3) ? fileForRead2 = f3 : fileForRead2 = f4;
    if (fileForRead1 == f2 && fileForRead2 == f3) fileForWrite = f1;
    if (fileForRead1 == f1 && fileForRead2 == f4) fileForWrite = f2;
    if (!feof(fileForRead1)) fscanf(fileForRead1, "%d", &a);
    if (!feof(fileForRead2)) fscanf(fileForRead2, "%d", &b);

    while (!feof(fileForRead1) && !feof(fileForRead2))
    {
      i = 0;
      j = 0;
      while (i < seriesLength && j < seriesLength && !feof(fileForRead1) && !feof(fileForRead2))
      {
        if (a < b)
        {
          fprintf(fileForWrite, "%d ", a);
          fscanf(fileForRead1, "%d", &a);
          i++;
        }
        else
        {
          fprintf(fileForWrite, "%d ", b);
          fscanf(fileForRead2, "%d", &b);
          j++;
        }
      }
      while (i < seriesLength && !feof(fileForRead1))
      {
        fprintf(fileForWrite, "%d ", a);
        fscanf(fileForRead1, "%d", &a);
        i++;
      }
      while (j < seriesLength && !feof(fileForRead2))
      {
        fprintf(fileForWrite, "%d ", b);
        fscanf(fileForRead2, "%d", &b);
        j++;
      }

      if (toggle == true)
        (fileForWrite == f1) ? fileForWrite = f4 : fileForWrite = f1;
      else
        (fileForWrite == f2) ? fileForWrite = f3 : fileForWrite = f2;
    }

    while (!feof(fileForRead1))
    {
      fprintf(fileForWrite, "%d ", a);
      fscanf(fileForRead1, "%d", &a);
    }
    while (!feof(fileForRead2))
    {
      fprintf(fileForWrite, "%d ", b);
      fscanf(fileForRead2, "%d", &b);
    }

    fclose(f4);
    fclose(f3);
    fclose(f2);
    fclose(f1);

    toggle = !toggle;
    seriesLength *= 2;
  }
  
  if (toggle == true) CopyFile("temp_2", inputFile);
  
  remove("temp_2");
  remove("temp_3");
  remove("temp_4");
}

void CopyFile(const char *FileIn, const char *FileOut) 
{
  FILE *FIn, *FOut;
  int a;
  FIn = fopen(FileIn, "r");
  FOut = fopen(FileOut, "w");
  if (!feof(FIn))
    fscanf(FIn, "%d", &a);
  while (!feof(FIn))
  {
    fprintf(FOut, "%d ", a);
    fscanf(FIn, "%d", &a);
  }
  fclose(FIn);
  fclose(FOut);
}