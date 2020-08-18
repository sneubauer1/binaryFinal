#include <iostream>
#include "binaryFile.h"
#include "customErrorClass.h"

int main(int argc, char *argv[])
{

    binaryFile myBinaryFile;

    s_EMPLOYEE *dataArray = NULL;
    string filename = "testLarge.txt";
    bool result;
    bool update;
    //string filename = "mediumOutput.txt";
    //string filename = "largeOutput.txt";
    int lineCount;
    
    try
    {
        lineCount = myBinaryFile.countLines(filename);
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }
    try
    {
        dataArray = new s_EMPLOYEE[lineCount];
    }
    catch (bad_alloc &exc)
    {
        string excString = string("Main: Allocation issue") + exc.what();
        throw myException(excString, SYSTEM_FAILURE);
    }
    try
    {
        myBinaryFile.populateData(dataArray, filename, lineCount);
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }

    string binFileName = "binary_File.txt";
    try
    {
        myBinaryFile.makeBinary(dataArray, binFileName, lineCount);
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }

    try
    {
        myBinaryFile.readandSort(lineCount, binFileName);
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }

    

    int dept_array[] = {0, 1, 2, 3, 4};
    //Small Input Operations
    //int id_array[] = {45731, 37503, 58509, 58510, 44258, 18738, 63006, 757, 68263, 65898};
    //Medium Input Operations
    // int id_array[] = {243013, 135016, 15013, 105013, 297008, 138708, 250506, 206998, 6011, 243119};
    //Large Input Operations
     int id_array[] = {205009, 25013, 189715, 155012, 430017, 205508, 335014, 430013, 5014, 433415};
    int counter = 0;

    for (int i = 0; i < 10; i++)
    {
        if (counter == 5)
        {
            counter = 0;
        }
        cout << dept_array[counter] << " : " << id_array[i] << " : ";
        result = myBinaryFile.Linear_search(dept_array[counter], id_array[i]);
        if (result)
        {
            cout << "employee found" << endl;
        }
        else
        {
            cout << "employee not found" << endl;
        }
        counter++;
    }

    s_EMPLOYEE *person = NULL;
    try
    {
        person = new s_EMPLOYEE;
    }
    catch (bad_alloc &exc)
    {
        string excString = string("Main: Allocation issue") + exc.what();
        throw myException(excString, SYSTEM_FAILURE);
    }

    counter = 0;

    for (int i = 0; i < 10; i++)
    {
        if (counter == 5)
        {
            counter = 0;
        }
        person = myBinaryFile.return_employee(dept_array[counter], id_array[i]);
        if (person != NULL)
        {
            cout << person->employeeName << " " << person->deptNumber << " " << person->employeeID << endl;
        }
        else
        {
            cout << "employee not found" << endl;
        }
        counter++;
    }
    /* s_EMPLOYEE temp_employee = {
        0,
        45731,
        "Leona",
    };
    update = myBinaryFile.updateName(temp_employee);
    if (update == true)
    {
        cout << "Employee updated" << endl;
    }
    else
    {
        cout << "Employee not updated" << endl;
    }
    */
    

    delete[] dataArray;

    return 0;
}