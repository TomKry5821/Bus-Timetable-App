#include <iostream>
#include <string>
#include<fstream>

using namespace std;

/*
* Structure representanting a bus stop
*/
struct BusStop
{
    int lineNumber;
    string arrivalTime;
    string name;
    BusStop* pNext;
};

/*
* Structure representanting a bus line
*/
struct BusLine
{
    string name;
    int number;
    BusLine* pNext;
};

/*
* Function that removes duplicates from bus stops list
*/
void removeDuplicates(BusStop*& head)
{
    BusStop* p, * pc, * r;
    pc = head;
    while (pc)
    {
        p = pc;
        while (p->pNext)
            if (p->pNext->name == pc->name and p->pNext->lineNumber == pc->lineNumber)
            {
                r = p->pNext;
                p->pNext = r->pNext;
                delete r;
            }
            else p = p->pNext;
        pc = pc->pNext;
    }
}

/*
* Function that loads data(bus stops and lines) from file to lists 
* @param fileName name of the input file
* @param pBusStopHead head of the bus stops list
* @param pBusLinesHead head of the bus lines list
*/
void loadDataFromFile(string fileName, BusStop*& pBusStopsHead, BusLine*& pBusLineshead)
{
    fstream file;
    file.open(fileName);
    if (!file.good())
    {
        cout << " blad! Pliku nie mozna otworzyc! " << endl;
        return;
    }
    else
    {
        if (!pBusLineshead)
        {
            BusLine* newBusLine = new BusLine;
            file >> newBusLine->name >> newBusLine->number;
            newBusLine->pNext = nullptr;
            pBusLineshead = newBusLine;
            while (!file.eof())
            {
                if (!pBusStopsHead)
                {
                    BusStop* newBusStop = new BusStop;
                    file >> newBusStop->arrivalTime >> newBusStop->name;
                    newBusStop->lineNumber = pBusLineshead->number;
                    newBusStop->pNext = nullptr;
                    pBusStopsHead = newBusStop;
                }
                else
                {
                    BusStop* tmp = pBusStopsHead;
                    BusStop* newBusStop = new BusStop;
                    file >> newBusStop->arrivalTime >> newBusStop->name;
                    newBusStop->lineNumber = pBusLineshead->number;
                    while (pBusStopsHead->pNext)
                    {
                        pBusStopsHead = pBusStopsHead->pNext;
                    }
                    pBusStopsHead->pNext = newBusStop;
                    newBusStop->pNext = nullptr;
                    pBusStopsHead = tmp;
                }
            }

        }
        else
        {
            BusLine* tmp = pBusLineshead;
            BusLine* newBusLine = new BusLine;
            file >> newBusLine->name >> newBusLine->number;
            while (pBusLineshead->pNext)
            {
                pBusLineshead = pBusLineshead->pNext;
            }
            newBusLine->pNext = nullptr;
            pBusLineshead->pNext = newBusLine;
            while (!file.eof())
            {
                if (!pBusStopsHead)
                {
                    BusStop* newBusStop = new BusStop;
                    file >> newBusStop->arrivalTime >> newBusStop->name;
                    newBusStop->lineNumber = pBusLineshead->number;
                    newBusStop->pNext = nullptr;
                    pBusStopsHead = newBusStop;
                }
                else
                {
                    BusStop* tmp = pBusStopsHead;
                    BusStop* newBustStop = new BusStop;
                    file >> newBustStop->arrivalTime >> newBustStop->name;
                    auto p = pBusLineshead;
                    while (pBusLineshead->pNext)
                    {
                        pBusLineshead = pBusLineshead->pNext;
                    }
                    newBustStop->lineNumber = pBusLineshead->number;
                    pBusLineshead = p;
                    while (pBusStopsHead->pNext)
                    {
                        pBusStopsHead = pBusStopsHead->pNext;
                    }
                    pBusStopsHead->pNext = newBustStop;
                    newBustStop->pNext = nullptr;
                    pBusStopsHead = tmp;
                }
            }
            pBusLineshead = tmp;
        }
        file.close();
    }
}

/*
* Function that prints all bus lines at the console output
* @param head of the bus lines list
*/
void printLines(BusLine* pHead)
{
    while (pHead)
    {
        cout << pHead->name << " " << pHead->number << endl;

        pHead = pHead->pNext;
    }

}

/*
* Function that prints all bus stops at the console output
* @param head of the bus stops list
*/
void printBusStops(BusStop* pHead)
{
    while (pHead)
    {
        cout << pHead->arrivalTime << endl;
        cout << pHead->name << "     " << pHead->lineNumber << endl;
        cout << "nastepny element " << endl;
        pHead = pHead->pNext;
    }
}

/*
* Function that prints bus stops with lines at the console output
* @param head of the bus stops list
*/
void printBusStopsWithLines(BusStop* pHead)
{
    while (pHead)
    {
        cout << pHead->name << endl;
        cout << pHead->arrivalTime << endl;
        cout << pHead->lineNumber << endl;
        cout << " nastepnt element " << endl;
        pHead = pHead->pNext;
    }
}

/*
* Function that loads data from first to second bus stops list
* @param pHeadpom head of the bus stops list
* @param pHeadp head of the new bus stops list
*/
void loadToTmpList(BusStop* pHeadp, BusStop*& pHeadpom)
{
    auto begin = pHeadp;
    auto p = pHeadp;
    auto z = pHeadp;
    while (pHeadp)
    {
        if (pHeadp->name == z->name)
        {
            if (!pHeadpom)
            {
                BusStop* newBusStop = new BusStop;
                newBusStop->name = pHeadp->name;
                newBusStop->lineNumber = pHeadp->lineNumber;
                while (p)
                {
                    if (p->name == pHeadp->name and p->lineNumber == pHeadp->lineNumber)
                    {
                        newBusStop->arrivalTime += p->arrivalTime + " ";
                    }
                    p = p->pNext;
                }
                p = begin;
                newBusStop->pNext = nullptr;
                pHeadpom = newBusStop;
                z = z->pNext;
            }
            else
            {
                auto begin2 = pHeadpom;
                BusStop* newBusStop = new BusStop;
                newBusStop->name = pHeadp->name;
                newBusStop->lineNumber = pHeadp->lineNumber;
                while (p)
                {
                    if (p->name == pHeadp->name and p->lineNumber == pHeadp->lineNumber)
                    {
                        newBusStop->arrivalTime += p->arrivalTime + " ";
                    }
                    p = p->pNext;
                }
                p = begin;
                while (pHeadpom->pNext)
                {
                    pHeadpom = pHeadpom->pNext;
                }
                pHeadpom->pNext = newBusStop;
                newBusStop->pNext = nullptr;
                pHeadpom = begin2;
                z = z->pNext;

            }
        }
        pHeadp = pHeadp->pNext;
    }
    pHeadp = begin;
    z = begin;
    while (pHeadp)
    {
        if (pHeadp->lineNumber != pHeadpom->lineNumber)
        {
            auto begin2 = pHeadpom;
            BusStop* newBustStop = new BusStop;
            newBustStop->name = pHeadp->name;
            newBustStop->lineNumber = pHeadp->lineNumber;
            while (p)
            {
                if (p->name == pHeadp->name and p->lineNumber != pHeadp->lineNumber)
                {
                    newBustStop->arrivalTime += p->arrivalTime + " ";
                }
                p = p->pNext;
            }
            p = begin;
            while (pHeadpom->pNext)
            {
                pHeadpom = pHeadpom->pNext;
            }
            pHeadpom->pNext = newBustStop;
            newBustStop->pNext = nullptr;
            pHeadpom = begin2;

        }
        pHeadp = pHeadp->pNext;
    }
}

/*
* Function that saves data about bus stops to file
* @param head of the bus stops list
*/
void saveDataToFile(BusStop*& pHead)
{
    auto begin = pHead;
    auto p = pHead->pNext;
    auto x = pHead;
    while (pHead)
    {
        if (pHead->name == p->name)
        {
            fstream file;
            file.open(pHead->name + ".txt", ios::out);
            file << pHead->name << endl;
            file << "=======" << endl;
            file << "LINIA " << pHead->lineNumber << endl;
            file << endl;
            file << pHead->arrivalTime << endl;
            file << endl;
            auto q = begin;
            while (q)
            {
                if (q->name == pHead->name and q->lineNumber != pHead->lineNumber)
                {
                    file << "LINIA " << q->lineNumber << endl;
                    file << endl;
                    file << q->arrivalTime << endl;
                    file << endl;
                }
                q = q->pNext;
            }
            p = p->pNext;
        }
        pHead = pHead->pNext;
    }
}

/*
* Function that deletes bus lines list
* @param head of the bus lines list
*/
void deleteLinesList(BusLine*& pHead)
{
    if (pHead)
    {
        auto p = pHead->pNext;
        delete pHead;
        pHead = nullptr;
        pHead = p;
        deleteLinesList(p);
    }
}

/*
* Function that deletes bus lines list
* @param head of the bus stops list
*/
void deleteBusStopsList(BusStop*& pHead)
{
    if (pHead)
    {
        auto p = pHead->pNext;
        delete pHead;
        pHead = nullptr;
        pHead = p;
        deleteBusStopsList(p);
    }
}

/*
* Function that load the arguments from the shell
*/
bool loadArgs(int count, char** args, string& inputFile)


{
    const string ETYKIETA_INPUT("-i");               ///> tworzymy string etykieta_input -i
    bool inOK = false;                               ///> tworzymy zmienna logiczna inok i przypisujemy wartosc false


    for (int i = 0; i < count - 1; i++)
    {
        string arg(args[i]);
        if (arg == ETYKIETA_INPUT)
        {
            inputFile = args[i + 1];
            inOK = true;
        }
    }
    return inOK;
}

/*
* Function that loads data(bus stops and lines) from file to lists
* @param fileName name of the input file
* @param pBusStopHead head of the bus stops list
* @param pBusLinesHead head of the bus lines list
*/
void loadDataFromFile(string fileName, BusStop*& pBusStopsHead, BusLine*& pBusLineshead)
{
    fstream file;
    file.open(fileName);
    if (!file.good())
    {
        cout << " blad! Pliku nie mozna otworzyc! " << endl;
        return;
    }
    else
    {
        if (!pBusLineshead)
        {
            BusLine* newBusLine = new BusLine;
            file >> newBusLine->name >> newBusLine->number;
            newBusLine->pNext = nullptr;
            pBusLineshead = newBusLine;
            while (!file.eof())
            {
                if (!pBusStopsHead)
                {
                    BusStop* newBusStop = new BusStop;
                    file >> newBusStop->arrivalTime >> newBusStop->name;
                    newBusStop->lineNumber = pBusLineshead->number;
                    newBusStop->pNext = nullptr;
                    pBusStopsHead = newBusStop;
                }
                else
                {
                    BusStop* tmp = pBusStopsHead;
                    BusStop* newBusStop = new BusStop;
                    file >> newBusStop->arrivalTime >> newBusStop->name;
                    newBusStop->lineNumber = pBusLineshead->number;
                    while (pBusStopsHead->pNext)
                    {
                        pBusStopsHead = pBusStopsHead->pNext;
                    }
                    pBusStopsHead->pNext = newBusStop;
                    newBusStop->pNext = nullptr;
                    pBusStopsHead = tmp;
                }
            }

        }
        else
        {
            BusLine* tmp = pBusLineshead;
            BusLine* newBusLine = new BusLine;
            file >> newBusLine->name >> newBusLine->number;
            while (pBusLineshead->pNext)
            {
                pBusLineshead = pBusLineshead->pNext;
            }
            newBusLine->pNext = nullptr;
            pBusLineshead->pNext = newBusLine;
            while (!file.eof())
            {
                if (!pBusStopsHead)
                {
                    BusStop* newBusStop = new BusStop;
                    file >> newBusStop->arrivalTime >> newBusStop->name;
                    newBusStop->lineNumber = pBusLineshead->number;
                    newBusStop->pNext = nullptr;
                    pBusStopsHead = newBusStop;
                }
                else
                {
                    BusStop* tmp = pBusStopsHead;
                    BusStop* newBustStop = new BusStop;
                    file >> newBustStop->arrivalTime >> newBustStop->name;
                    auto p = pBusLineshead;
                    while (pBusLineshead->pNext)
                    {
                        pBusLineshead = pBusLineshead->pNext;
                    }
                    newBustStop->lineNumber = pBusLineshead->number;
                    pBusLineshead = p;
                    while (pBusStopsHead->pNext)
                    {
                        pBusStopsHead = pBusStopsHead->pNext;
                    }
                    pBusStopsHead->pNext = newBustStop;
                    newBustStop->pNext = nullptr;
                    pBusStopsHead = tmp;
                }
            }
            pBusLineshead = tmp;
        }
        file.close();
    }
}

/*
* Function that load the arguments from the shell
*/
bool loadArgs(int count, char** args, string& inputFile)


{
    const string ETYKIETA_INPUT("-i");               ///> tworzymy string etykieta_input -i
    bool inOK = false;                               ///> tworzymy zmienna logiczna inok i przypisujemy wartosc false


    for (int i = 0; i < count - 1; i++)
    {
        string arg(args[i]);
        if (arg == ETYKIETA_INPUT)
        {
            inputFile = args[i + 1];
            inOK = true;
        }
    }
    return inOK;
}