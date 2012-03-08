/* 
 * File:   main.cpp
 * Author: ebrjohn
 *
 * Created on 22 de diciembre de 2011, 9:02
 */

#include <cstdlib>
#include <iostream>

#include "MafiaMember.h"
#include "MafiaMembersManager.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    // I hope nobody minds that I use Italian names, Im just stereotyping :)

    // The top boss
    MafiaMember theBigBoss("Antonio", "theBigBoss", 65, MafiaMember::STATUS_NORMAL);

    // His subordinates
    MafiaMember guido("Guido", "TheKneeBreaker", 40, MafiaMember::STATUS_NORMAL);
    MafiaMember luigi("Luigi", "TheHammer", 35, MafiaMember::STATUS_NORMAL);

    // A subordinate of guido, will later send guido to jail and relocate to Luigi
    MafiaMember nicki("Nicki", "Face", 35, MafiaMember::STATUS_NORMAL);

    // Setup the hierarchy
    theBigBoss.addSubordinate(&guido);
    theBigBoss.addSubordinate(&luigi);

    guido.setBoss(&theBigBoss);
    luigi.setBoss(&theBigBoss);

    guido.addSubordinate(&nicki);
    nicki.setBoss(&guido);

    MafiaMembersManager manager;

    manager.setTopBoss(&theBigBoss);

    //
    // Test Sending guido to jail, straight to jail, and do not pass GO
    //
    manager.setMemberInJail(&guido);

    if(nicki.getRelocatedBoss() != &luigi)
    {
      cerr << "Setting guido in jail didnt work :(" << endl;
    }
    else
    {
        // It worked! :)
        cout << nicki.getName() << "'s boss (" << nicki.getBoss()->getName()
             << ") was sent to jail, relocated boss is: " << nicki.getRelocatedBoss()->getName()
             << endl;
    }

    //
    // Test Releasing guido from jail
    //
    manager.setMemberReleasedFromJail(&guido);

    if(nicki.getRelocatedBoss() != NULL)
    {
      cerr << "Releasing guido from jail didnt work :(" << endl;
    }
    else if(nicki.getBoss() != &guido)
    {
      cerr << "Releasing guido from jail didnt work :(" << endl;
    }
    else
    {
        // It worked! :)
        cout << nicki.getName() << "'s boss (" << nicki.getBoss()->getName()
             << ") was released from jail"
             << endl;
    }

    //
    // Test searching for members by name
    //
    MafiaMember *searchedMember = manager.getMemberByName(nicki.getName());
    if(searchedMember != &nicki)
    {
      cerr << "Searching for nicki by name didnt work :(" << endl;
    }
    else
    {
      cerr << "Searching for nicki by name worked!" << endl;
    }

    //
    // Test searching for members by alias
    //
    searchedMember = manager.getMemberByAlias(nicki.getAlias());
    if(searchedMember != &nicki)
    {
      cerr << "Searching for nicki by Alias didnt work :(" << endl;
    }
    else
    {
      cerr << "Searching for nicki by Alias worked!" << endl;
    }

    //
    // Test getting total number of subordinates and if a boss is important
    //
    cout << "TheBigBoss has a total of: " << manager.getNumSubordinates(&theBigBoss)
         << " subordinates"
         << endl;
    cout << "Is TheBigBoss considered important (important limit of 2)? ";
    if(manager.isMemberImportant(&theBigBoss, 2))
    {
      cout << "yes" << endl;
    }
    else
    {
      cout << "no" << endl;
    }

    //
    // Test the member's rank and comparing ranks between members
    //
    cout << "TheBigBoss's rank is: " << manager.getMemberRank(&theBigBoss) << endl;
    cout << "Guido's rank is: "      << manager.getMemberRank(&guido)      << endl;
    cout << "Luigi's rank is: "      << manager.getMemberRank(&luigi)      << endl;
    cout << "Nicki's rank is: "      << manager.getMemberRank(&nicki)      << endl;

    MafiaMember *higherRanked = manager.getHigherRankedMember(&guido, &nicki);
    cout << "Between Guido and Nicki, " << higherRanked->getName() << " has the higher rank" << endl;
    
    return 0;
}

