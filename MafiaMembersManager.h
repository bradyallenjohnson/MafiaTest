/* 
 * File:   MafiaMembersManager.h
 * Author: ebrjohn
 *
 * Created on 22 de diciembre de 2011, 9:24
 * 
 * - Manages the mafia members and related actions such
 *   as member relocation when a boss goes to jail
 * - Putting the member management in a seperate class to try
 *   and keep a higher cohesion for the MafiaMember class
 */

#ifndef MAFIAMEMBERSMANAGER_H
#define	MAFIAMEMBERSMANAGER_H

#include <string>

#include <MafiaMember.h>

using namespace std;

class MafiaMembersManager {
public:
    MafiaMembersManager();
    MafiaMembersManager(const MafiaMembersManager& orig);
    virtual ~MafiaMembersManager();

    // Get members by name/alias
    MafiaMember *getMemberByName(const string &memberName);
    MafiaMember *getMemberByAlias(const string &memberAlias);

    void addMember(MafiaMember *member);
    // For now, removing do the same as set in jail, but make members permanent
    void removeMember(MafiaMember *member);

    inline void setTopBoss(MafiaMember *boss) { topBoss_ = boss; }

    // A member is important if he has more than 50 subordinates,
    // allow to specify the "important limit"
    bool isMemberImportant(MafiaMember *member, int numSubordinatesLimit = 50);
    unsigned int getNumSubordinates(MafiaMember *member);

    int getMemberRank(MafiaMember *member);
    bool getMemberRankRecursive(MafiaMember *root, MafiaMember *member, int &count);

    // handles setting members in/out jail
    void setMemberInJail(MafiaMember *member);
    void setMemberReleasedFromJail(MafiaMember *member);

    // This method is for the Bonus
    MafiaMember *getHigherRankedMember(MafiaMember *m1, MafiaMember *m2);

private:
    // TODO change this to a map of mafia org name to its topBoss_
    MafiaMember *topBoss_;

    MafiaMember *getMemberByNameRecursive(MafiaMember *member, const string &memberName);
    MafiaMember *getMemberByAliasRecursive(MafiaMember *member, const string &memberName);
    unsigned int getNumSubordinatesRecursive(MafiaMember *member);
};

#endif	/* MAFIAMEMBERSMANAGER_H */

