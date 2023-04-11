#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail,
    int row, int col,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& numShifts
);

bool isValid(const AvailabilityMatrix& avail,
    int row,
    int col,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int numDays,
    std::vector<size_t>& numShifts,
    int pos
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if (avail.empty() || avail[0].empty()) {
        return false;
    }
    if (dailyNeed > avail.size()) {
        return false;
    }
    sched.clear();

    //setting every element to invalid for initialization
    sched = DailySchedule(avail.size(), std::vector<Worker_T>(avail[0].size(), INVALID_ID));

    std::vector<size_t> numShifts(avail[0].size(), 0);

    return scheduleHelper(avail, 0, 0, dailyNeed, maxShifts, sched, numShifts);
}


bool scheduleHelper(const AvailabilityMatrix& avail,
                    int row,
                    int col,
                    const size_t dailyNeed,
                    const size_t maxShifts,
                    DailySchedule& sched,
                    std::vector<size_t>& numShifts)
{
    if(col == sched[0].size()){
        return scheduleHelper(avail,row+1,0,dailyNeed,maxShifts,sched, numShifts);
    }
    if (row == sched.size()) {
        return true;
    }
    

    if (sched[row][col] == INVALID_ID) {
        for (int i = 0; i < avail[0].size(); ++i) {
            if (isValid(avail, row, col, dailyNeed, maxShifts, sched, i, numShifts, i)) {
                sched[row][col] = i;
                numShifts[i] = numShifts[i] + 1;

                if (scheduleHelper(avail, row, col + 1, dailyNeed, maxShifts, sched, numShifts)) {
                    return true;
                }

                sched[row][col] = INVALID_ID;
                numShifts[i] = numShifts[i]-1;
            }
        }
    }

    return false;
}








bool isValid(const AvailabilityMatrix& avail,
    int row,
    int col,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int numDays,
    std::vector<size_t>& numShifts,
    int workerIndex
)
{
    int counter = 0;
    for(int i =0; i<sched[row].size(); ++i){
        if(sched[row][i]==workerIndex){
            ++counter;
        }
    }
    if(counter>1){
        return false;
    }

    // Check if worker has exceeded maximum shifts
    if (numShifts[workerIndex] >= maxShifts) {
        return false;
    }

    // Check if worker is available
    if (avail[row][col] == 0) {
        return false;
    }

    return true;



    // if(avail[row][col]){
    //     if(numShifts[workerIndex] < maxShifts){
    //         return true;
    //     } 
    // }
    // return false;

    //return isValid(avail, row, col, dailyNeed, maxShifts, sched, 0, numShifts,workerIndex+1 );
   // return true;
}