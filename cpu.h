#ifndef CPU_H
#define CPU_H

/**
 *
 * \file CPU.h
 * \brief The CPU class
 */

class CPU
{
public:
    CPU(); //!< Default constructor (not used)
    int *CPUdataArray;
    int callCabo(int rounds);
    int discard(int cardValue);
    int draw(int cardValue);

    int *temp1; //!< Temporary value used between functions
    int *temp2; //!< Temporary value used between functions
};

//7 and 8 are peek
//9 and 10 are spy
//11 and 12 are swap
#endif // CPU_H
