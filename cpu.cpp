#include "cpu.h"
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

/**
 * \file cpu.cpp
 * \brief Contains cpu class definition
 *
 * CPU class used to store data and evaluate CPU opponent decisions
 */


/**
 * @brief CPU::CPU
 *
 * CPU class constructor
 */

CPU::CPU()
{
    CPUdataArray = new int[12];
    temp1=new int();
    *temp1=0;
    temp2=new int();
    *temp2=0;

    for(int i=0;i<12;i++)
    {
        CPUdataArray[i]=99;
    }

    srand(time(0));
}

// 0 : do not call cabo
// 1 : call cabo

/**
 * @brief CPU::callCabo
 * @param rounds first argument, give the amount of rounds who passed for the function to decide an output
 * @return Returns an integer that says whether the CPU wants to call CABO or not (0: do not call cabo, 1: call cabo)
 *
 * Check if the CPU should call CABO
 */

int CPU::callCabo(int rounds)
{
    // If we have already did more than 10 rounds, 20% chance of calling cabo
    if(rounds>=10)
    {
        int temp=rand()%10;

        if(temp==4||temp==5)
        {
            //Call cabo
            return 1;
        }
    }

    // Check if the CPU knows 3 of his own cards , and their sum is 15 or less. If yes, call cabo
    int sum=0;
    int disc=0;
    for(int x=0;x<4;x++)
    {
        if(CPUdataArray[x]!=99)
        {
            disc=disc+1;
            sum=sum+CPUdataArray[x];
        }
    }

    if (disc>=3&&sum<=15)
    {
        return 1;
    }

    return 0;
}

// 0 : do not take from discard
// 1 : take from discard / pos1
// 2 : take from discard / pos2
// 3 : take from discard / pos3
// 4 : take from discard / pos4

/**
 * @brief CPU::discard
 * @param cardValue first argument, give card value
 * @return Returns an integer that says whether the CPU wants to select a card from the discard pile or not (0: do not select card from discard pile, or else 1-2-3-4 select a card and replace at a specific position)
 *
 * Check if CPU should pick a card from the discard pile
 */

int CPU::discard(int cardValue)
{
    if(cardValue>=8)
    {
    return 0;
    }


    for(int x=0;x<4;x++)
    {
        if(CPUdataArray[x]!=99)
        {
            if(CPUdataArray[x]>cardValue)
            {
                CPUdataArray[x]=cardValue;
                return x+1;
            }
        }
    }

    for(int x=0;x<4;x++)
    {
        if(CPUdataArray[x]==99)
        {
                CPUdataArray[x]=cardValue;
                return x+1;
        }
    }

    //Replace no card if alt not found
    return 0;


}

// 0 : do not take from draw and put in discard pile
// 1 : take from draw / pos1
// 2 : take from draw / pos2
// 3 : take from draw / pos3
// 4 : take from draw / pos4
// 5 : peek - val1 and put in discard pile
// 6 : spy - val1 and put in discard pile
// 7 : swap- val1 / val2 and put in discard pile

/**
 * @brief CPU::draw
 * @param cardValue first argument, give card value
 * @return Returns an integer that says whether the CPU wants to select a card from the draw or not, and also handle any special card picked (0: put picked card to discard pile, or else 1-2-3-4 select a card and replace at a specific position, or else 5-6-7 handle special action)
 *
 * Check if CPU should pick a card from the draw pile, and handle any special action
 */

int CPU::draw(int cardValue)
{

    //get card 13
    if(cardValue==13 )
    {
        return 0;
    }

    //Peek
    else if(cardValue==7 || cardValue==8 )
    {
        for(int x=0;x<4;x++)
        {
            if(CPUdataArray[x]==99)
            {
                *temp1=x+1;
                return 5;
            }
        }

        *temp1=1;
        return 5;


    }

    //Spy
    else if(cardValue==9 || cardValue==10 )
    {
        for(int x=4;x<12;x++)
        {
            if(CPUdataArray[x]==99)
            {
                *temp1=x+1;
                return 6;
            }
        }

        *temp1=1;
        return 6;
    }

    //Swap
    else if(cardValue==11 || cardValue==12 )
    {
        bool selected=false;
        for(int x=0;x<4;x++)
        {
            if(CPUdataArray[x]>=8&& CPUdataArray[x]!=99)
            {
                *temp1=x+1;
                selected=true;

            }
        }

        if(selected==false)
        {
            for(int x=0;x<4;x++)
            {
                if(CPUdataArray[x]==99)
                {
                    *temp1=x+1;
                    selected=true;
                }
            }


        }

        if (selected==false)
        {
             *temp1=1;
        }

        selected=false;

        for(int x=4;x<12;x++)
        {
            if(CPUdataArray[x]<=8)
            {
                *temp2=x+1;
                selected=true;

            }
        }

        if(selected==false)
        {
            for(int x=4;x<12;x++)
            {
                if(CPUdataArray[x]==99)
                {
                    *temp2=x+1;
                    selected=true;
                }
            }


        }

        if (selected==false)
        {
             *temp2=1;
        }

       return 7;


    }

    else
    {
        for(int x=0;x<4;x++)
        {
            if(CPUdataArray[x]!=99)
            {
                if(CPUdataArray[x]>cardValue)
                {
                    CPUdataArray[x]=cardValue;
                    return x+1;
                }
            }
        }

        for(int x=0;x<4;x++)
        {
            if(CPUdataArray[x]==99)
            {
                    CPUdataArray[x]=cardValue;
                    return x+1;
            }
        }

        //Replace no card if alt not found
        return 0;
    }




}
