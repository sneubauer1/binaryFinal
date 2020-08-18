#include "binaryFile.h"

/**************************** PUBLIC: Constructor ****************************/
binaryFile::binaryFile(void)
{
    this->indexArray = NULL;
    this->arraysize = 0;
}
/**************************** PUBLIC: Destructor ****************************/
binaryFile::~binaryFile(void)
{
    delete []this->indexArray;
    this->arraysize = 0;
}


/**************************** PUBLIC: countLines ****************************/
int binaryFile::countLines(string filename)
{

    try
    {
        return this->p_CountLines(filename);
    }
    catch (myException &exc)
    {
        string excString = string("Lines could not be counted (countLines): ") + exc.what();
        throw myException(excString, ERROR);
    }
}


/**************************** PUBLIC: populateData ****************************/
void binaryFile::populateData(s_EMPLOYEE *dataArray, string filename, int arraySize)
{
    try
    {
        this->p_PopulateData(dataArray, filename, arraySize);
    }
    catch (myException &exc)
    {
        string excString = string("Data could not be populated (populateData): ") + exc.what();
        throw myException(excString, ERROR);
    }
}


/**************************** PUBLIC: makeBinary ****************************/
void binaryFile::makeBinary(s_EMPLOYEE *dataArray, string binFileName, int lineCount)
{
    try
    {
        this->p_MakeBinary(dataArray, binFileName, lineCount);
    }
    catch (myException &exc)
    {
        string excString = string("Data could not be converted into binary from text (makeBinary): ") + exc.what();
        throw myException(excString, ERROR);
    }
}


/**************************** PUBLIC: updateName****************************/
bool binaryFile::updateName(s_EMPLOYEE updateEmp)
{

    bool update = false;
    try
    {
        update = this->p_UpdateName(updateEmp);
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }

    if (update == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}


/**************************** PUBLIC: readandSort ****************************/
void binaryFile::readandSort(int arraysz, string filename)
{
    fstream dataFile;
    s_EMPLOYEE *temp;
    int num;
    int *dataArray;
    int i = 0;
    try
    {
        temp = new s_EMPLOYEE[arraysz];
        dataArray = new int[arraysz];
    }
    catch (bad_alloc &exc)
    {
        string excString = string("readandSort: Allocation issue") + exc.what();
        throw myException(excString, SYSTEM_FAILURE);
    }

    dataFile.open(filename, ios::binary | ios::in);

    if (dataFile.is_open())
    {
        try
        {
            dataFile.read((char *)temp, sizeof(s_EMPLOYEE) * arraysz);
            dataFile.close();
            mergesort(temp, 0, arraysz);
        }
        catch (exception &exc)
        {
            string excString = string("readandSort: General issue") + exc.what();
            throw myException(excString, SYSTEM_FAILURE);
        }
        try
        {
            indexArray = p_generateBinaryIndex(temp, arraysz, filename, 4);
        }
        catch (myException &exc)
        {
            string excString = string("readandSort: ") + exc.what();
            throw myException(excString, SYSTEM_FAILURE);
        }
    }
    else
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
    }
}


/**************************** PUBLIC: Linear_search ****************************/
bool binaryFile::Linear_search(int deptnumber, int employeeID)
{
    try
    {

        s_EMPLOYEE *arr;
        int result;
        //int arraysz = 75000;

        arr = new s_EMPLOYEE[arraysize];
        fstream datafile;
        s_EMPLOYEE test;

        result = p_Linear_search(arr, arraysize, employeeID, deptnumber);

        if (result == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }
}


/**************************** PUBLIC: mergesort ****************************/
void binaryFile::mergesort(s_EMPLOYEE *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergesort(arr, l, m);
        mergesort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


/**************************** PUBLIC: merge ****************************/
void binaryFile::merge(s_EMPLOYEE *arr, int l, int m, int r)
{
    int i, j, k;

    int n1 = m - l + 1;
    int n2 = r - m;

    s_EMPLOYEE *L, *R;
    L = new s_EMPLOYEE[n1];
    R = new s_EMPLOYEE[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    { 
        if (L[i].deptNumber <= R[j].deptNumber && L[i].employeeID < R[j].employeeID)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


/**************************** PUBLIC: compare ****************************/
bool binaryFile::compare(s_EMPLOYEE l, s_EMPLOYEE r)
{
    if (l.deptNumber <= r.deptNumber)
    {
        return true;
    }
    if (l.employeeID <= r.employeeID)
    {
        return true;
    }
}


/**************************** PUBLIC: return_employee ****************************/
s_EMPLOYEE *binaryFile::return_employee(int dept, int id)
{
    s_EMPLOYEE *person = NULL;
    person = new s_EMPLOYEE;
    try
    {
        person = p_return_employee(dept, id);
    }
    catch (myException &exc)
    {
        cout << exc.what() << endl;
    }

    return person;
}


/*************************************PRIVATE***********************************************************************************/
/******************************************************************************************************************************/



/**************************** PRIVATE: p_CountLines ****************************/
int binaryFile::p_CountLines(string filename)
{

    ifstream inputData;
    string dataFromFile;
    int lineCount = 0;
    inputData.open(filename);
    if (!inputData.is_open())
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
        exit;
    }
    else
    {

        while (getline(inputData, dataFromFile))
        {
            lineCount++;
        }
        return lineCount;

        inputData.close();
    }
}


/**************************** PRIVATE: p_PopulateData ****************************/
void binaryFile::p_PopulateData(s_EMPLOYEE *dataArray, string filename, int arraySize)
{

    int commaArray[3] = {0};
    int temp;
    int i = 0;
    ifstream inputData;
    string dataFromFile;

    inputData.open(filename);

    if (inputData.is_open())
    {
        while (getline(inputData, dataFromFile) && i < arraySize)
        {
            commaArray[0] = dataFromFile.find(",");
            commaArray[1] = dataFromFile.find(",", commaArray[0] + 1);
            commaArray[2] = dataFromFile.length() - commaArray[1] + 1;

            dataArray[i].deptNumber = (e_DEPT)atoi(dataFromFile.substr(0, commaArray[0] + 1).c_str());
            dataArray[i].employeeID = atoi(dataFromFile.substr(commaArray[0] + 1, commaArray[1] - 1).c_str());
            dataArray[i].employeeName = dataFromFile.substr(commaArray[1] + 1, commaArray[2] - 1);
            if (dataArray[i].employeeName.length() > 30)
            {
                string excString = string("Bad Input: Employee name is too many characters ");
                throw myException(excString, ERROR);
            }
            else if (dataArray[i].deptNumber > 4 || dataArray[i].deptNumber < 0)
            {
                string excString = string("Bad Input: Department is out of standard bounds ");
                throw myException(excString, ERROR);
            }
            ++i;
        }
    }
    else
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
        exit;
    }
    inputData.close();
}


/**************************** PRIVATE: p_MakeBinary ****************************/
void binaryFile::p_MakeBinary(s_EMPLOYEE *dataArray, string binFileName, int lineCount)
{

    fstream outputData;
    this->arraysize = lineCount;

    outputData.open(binFileName, ios::out | ios::binary);
    if (outputData.is_open())
    {
        try
        {
            outputData.write((char *)dataArray, sizeof(s_EMPLOYEE) * lineCount);
        }
        catch (exception &exc)
        {
            string excString = string("Text could not be converted into binary file ");
            throw myException(excString, ERROR);
        }

        outputData.close();
    }
    else
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
        exit;
    }
}


/**************************** PRIVATE: p_UpdateName****************************/
bool binaryFile::p_UpdateName(s_EMPLOYEE updateEmp)
{

    fstream overwrite;
    s_EMPLOYEE *dataArray;
    dataArray = new s_EMPLOYEE[this->arraysize];
    int department = 0;
    long pos = 0;
    bool update = 0;

    department = updateEmp.deptNumber;

    string replace = "Jebediah";

    overwrite.open("binary_File.txt", ios::in | ios::out | ios::binary);

    if (overwrite.is_open())
    {
        overwrite.seekg(indexArray[department], ios::beg);

        for (int i = 0; i < this->arraysize; i++)
        {
            overwrite.read((char *)&dataArray[i], sizeof(s_EMPLOYEE));

            if (dataArray[i].deptNumber == department && dataArray[i].employeeID == updateEmp.employeeID)
            {
                overwrite.seekg(0, ios::cur);
                dataArray[i].employeeName = replace;
                long pos = overwrite.tellg();
                overwrite.seekp(pos - sizeof(s_EMPLOYEE));

                overwrite.write((char *)&dataArray[i], sizeof(s_EMPLOYEE));

                overwrite.close();
                cout << dataArray[i].employeeName << endl;
                return update = true;
            }
        }
        overwrite.close();
        return update = false;
    }
    else
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
        return update = false;
    }
}


/**************************** PRIVATE: p_partition ****************************/
int binaryFile::p_partition(s_EMPLOYEE *arr, int low, int high)
{
    int pivot = 0, i = 0, j = 0;
    pivot = arr[high].deptNumber;
    int pivot2 = 0;
    pivot2 = arr[high].employeeID;

    i = (low - 1);

    for (j = low; j <= high - 1; j++)
    {
        if ((arr[j].deptNumber < pivot) || (arr[j].deptNumber == pivot && arr[j].employeeID < pivot2))
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);

    return (i + 1);
}


/**************************** PRIVATE: p_Linear_search ****************************/
int binaryFile::p_Linear_search(s_EMPLOYEE *arr, int size, int employeeid, int deptnum)
{
    fstream datafile;
    int returndat;
    datafile.open("binary_File.txt", ios::in | ios::binary);
    datafile.seekg(indexArray[deptnum], ios::beg);
    if (datafile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            datafile.read((char *)&arr[i], sizeof(s_EMPLOYEE));

            if (arr[i].deptNumber == deptnum && arr[i].employeeID == employeeid)
            {
                returndat = datafile.tellp();
                datafile.close();
                return returndat;
            }
        }
    }
    else
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
    }

    datafile.close();
    return -1;
}


/**************************** PRIVATE: p_generateBinaryIndex ****************************/
int *binaryFile::p_generateBinaryIndex(s_EMPLOYEE *dataArray, int arraySize, string filename, int modvalue)
{
    fstream outFile;
    int *indexArray;
    int indexSize, indexLocation = 0;
    int checkSize = 0;
    int i = 0;

    if (0 == (modvalue % 1))
    {
        indexSize = modvalue / 1 + 1;
        indexArray = new int[indexSize];
    }
    else
    {
        throw logic_error("mod value not divisible by 4");
    }
    outFile.open("binary_File.txt", ios::out | ios::binary);

    if (outFile.is_open())
    {
        for (i = 0; i < arraySize; ++i)
        {

            if (checkSize <= dataArray[i].deptNumber && indexLocation < indexSize)
            {

                indexArray[indexLocation] = outFile.tellp();
                checkSize++;
                indexLocation++;
            }
            outFile.write((char *)&dataArray[i], sizeof(s_EMPLOYEE));
        }
        outFile.close();

        outFile.open(filename, ios::in | ios::binary);
    }
    else
    {
        throw logic_error("couldn't open file.");
    }
    return indexArray;
}


/**************************** PRIVATE: p_return_employee ****************************/
s_EMPLOYEE *binaryFile::p_return_employee(int dept, int id)
{
    fstream datafile;
    s_EMPLOYEE *arr = new s_EMPLOYEE[arraysize];
    s_EMPLOYEE *person = new s_EMPLOYEE;
    int returndat;
    datafile.open("binary_File.txt", ios::in | ios::binary);
    datafile.seekg(indexArray[dept], ios::beg);
    if (datafile.is_open())
    {
        for (int i = 0; i < arraysize; i++)
        {
            datafile.read((char *)&arr[i], sizeof(s_EMPLOYEE));

            if (arr[i].deptNumber == dept && arr[i].employeeID == id)
            {
                person->deptNumber = arr[i].deptNumber;
                person->employeeID = arr[i].employeeID;
                person->employeeName = arr[i].employeeName;
                returndat = datafile.tellp();
                return person;
                datafile.close();
            }
        }
        return NULL;
        datafile.close();
    }
    else
    {
        string excString = string("File could not be opened or does not exist. ");
        throw myException(excString, ERROR);
    }
}