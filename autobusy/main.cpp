#include "DataStructures_and_functions.h"



int main(int argsCount, char** args)
{
        BusStop* pBusStopHead = nullptr;
        BusLine* pBusLineHead = nullptr;
        BusStop* pTmpBusStopHead = nullptr;

        string test1 = "test.txt";
        string test2 = "test2.txt";
        string test3 = "test3.txt";
        string test4 = "test4.txt";

        loadDataFromFile(test1, pTmpBusStopHead, pBusLineHead);
        loadDataFromFile(test2, pTmpBusStopHead, pBusLineHead);
        loadDataFromFile(test3, pTmpBusStopHead, pBusLineHead);
        loadDataFromFile(test4, pTmpBusStopHead, pBusLineHead);

        loadToTmpList(pTmpBusStopHead, pBusStopHead);
        removeDuplicates(pBusStopHead);
        saveDataToFile(pBusStopHead);
        deleteLinesList(pBusLineHead);
        deleteBusStopsList(pTmpBusStopHead);
        deleteBusStopsList(pBusStopHead);
        return 0;
}