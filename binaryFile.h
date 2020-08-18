#ifndef __BINARYFILE__H__
#define __BINARYFILE__H__

#include "customErrorClass.h"
#include <fstream>
#include <string>
#include <algorithm>

typedef enum department
{
    ACCOUNTING,
    BUSINESS,
    HUMAN_RESOURCES,
    SALES,
    PRODUCTION
} e_DEPT;

typedef struct employee
{
    int deptNumber;
    int employeeID;
    string employeeName;
} s_EMPLOYEE;

class binaryFile
{
public:
    binaryFile();
    ~binaryFile();
    int countLines(string);
    void populateData(s_EMPLOYEE *, string, int);
    void makeBinary(s_EMPLOYEE *, string, int);
    bool updateName(s_EMPLOYEE);
    void readandSort(int arraysz, string filename);
    bool Linear_search(int deptnumber, int employeeID);
    void mergesort(s_EMPLOYEE *arr, int l, int r);
    void merge(s_EMPLOYEE *arr, int l, int m, int r);
    bool compare(s_EMPLOYEE l, s_EMPLOYEE r);
    s_EMPLOYEE* return_employee(int dept, int id);

private:
    int arraysize;    
    int *indexArray;
    
    int p_CountLines(string);
    void p_PopulateData(s_EMPLOYEE *, string, int);
    void p_MakeBinary(s_EMPLOYEE *, string, int);
    bool p_UpdateName(s_EMPLOYEE);
    int p_partition(s_EMPLOYEE *arr, int low, int high);
    int p_Linear_search(s_EMPLOYEE *arr, int size, int employeeid, int deptnum);
    int *p_generateBinaryIndex(s_EMPLOYEE *dataArray, int arraySize, string filename, int modvalue);
    s_EMPLOYEE* p_return_employee(int dept, int id);
};

#endif