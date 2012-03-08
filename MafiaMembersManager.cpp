/* 
 * File:   MafiaMembersManager.cpp
 * Author: ebrjohn
 * 
 * Created on 22 de diciembre de 2011, 9:24
 */

#include <iostream>

#include "MafiaMembersManager.h"

MafiaMembersManager::MafiaMembersManager()
{
}

MafiaMembersManager::MafiaMembersManager(const MafiaMembersManager& orig)
{
}

MafiaMembersManager::~MafiaMembersManager()
{
}


    // Get members by name/alias
MafiaMember *MafiaMembersManager::getMemberByName(const string &memberName)
{
  return getMemberByNameRecursive(topBoss_, memberName);
}

MafiaMember *MafiaMembersManager::getMemberByNameRecursive(MafiaMember *member, const string &memberName)
{
  if(!member->isBoss()) // ends the recursion
  {
    return NULL;
  }

  // First check this member
  MafiaMember *searchedMember = member->findSubordinateByName(memberName);
  if(searchedMember != NULL)
  {
    return searchedMember;
  }

  // Now check each of this member's subordinates
  searchedMember = NULL;
  MafiaMember::MafiaMemberSubordinateType *subordinates = member->getSubordinates();
  MafiaMember::MafiaMemberSubordinateType::iterator iter = subordinates->begin();
  while(iter != subordinates->end() && searchedMember == NULL)
  {
    searchedMember = getMemberByNameRecursive(iter->second, memberName);
    iter++;
  }

  return searchedMember;
}

MafiaMember *MafiaMembersManager::getMemberByAlias(const string &memberAlias)
{
    return getMemberByAliasRecursive(topBoss_, memberAlias);
}

MafiaMember *MafiaMembersManager::getMemberByAliasRecursive(MafiaMember *member, const string &memberAlias)
{
  if(!member->isBoss()) // ends the recursion
  {
    return NULL;
  }

  // First check this member
  MafiaMember *searchedMember = member->findSubordinateByAlias(memberAlias);
  if(searchedMember != NULL)
  {
    return searchedMember;
  }

  // Now check each of this member's subordinates
  searchedMember = NULL;
  MafiaMember::MafiaMemberSubordinateType *subordinates = member->getAliasSubordinates();
  MafiaMember::MafiaMemberSubordinateType::iterator iter = subordinates->begin();
  while(iter != subordinates->end() && searchedMember == NULL)
  {
    searchedMember = getMemberByAliasRecursive(iter->second, memberAlias);
    iter++;
  }

  return searchedMember;
}

void MafiaMembersManager::addMember(MafiaMember *member)
{

}

// For now, removing do the same as set in jail, but make members permanent
void MafiaMembersManager::removeMember(MafiaMember *member)
{

}

// A member is important if he has more than 50 subordinates,
// allow to specify the "important limit"
bool MafiaMembersManager::isMemberImportant(MafiaMember *member, int numSubordinatesLimit /* default = 50*/)
{
    return getNumSubordinates(member) > numSubordinatesLimit ? true : false;
}

unsigned int MafiaMembersManager::getNumSubordinates(MafiaMember *member)
{
  return getNumSubordinatesRecursive(member);
}

unsigned int MafiaMembersManager::getNumSubordinatesRecursive(MafiaMember *member)
{
  if(!member->isBoss()) // ends the recursion
  {
    return NULL;
  }

  int count(member->getNumDirectSubordinates());

  MafiaMember::MafiaMemberSubordinateType *subordinates = member->getSubordinates();
  MafiaMember::MafiaMemberSubordinateType::iterator iter = subordinates->begin();
  while(iter != subordinates->end())
  {
    count += getNumSubordinatesRecursive(iter->second);
    iter++;
  }

  return count;
}

// handles setting members in/out jail
void MafiaMembersManager::setMemberInJail(MafiaMember *member)
{
  member->setStatus(MafiaMember::STATUS_IN_JAIL);
  if(!member->isBoss())
  {
    //cout << "Member is not a boss" << endl;
    // nothing else to be done
    return;
  }

  MafiaMember::MafiaMemberSubordinateType *subordinates = member->getSubordinates();
  MafiaMember *memberBoss = member->getBoss();
  // TODO check if memberBoss is NULL and skip to the subordinate check
  MafiaMember::MafiaMemberSubordinateType *bossSubordinates = memberBoss->getSubordinates();

  // iterate over the member's boss's subordinates to find the one to relocate to

  MafiaMember *bossToRelocateTo(NULL);
  unsigned int oldestCandidateAge(0);
  MafiaMember::MafiaMemberSubordinateType::iterator iter = bossSubordinates->begin();

  while(iter != bossSubordinates->end())
  {
    MafiaMember *candidate = iter->second;
    //cout << "Checking member peer: " << candidate->getName() << ", age " << candidate->getAge() << endl;
    if(candidate->getAge() > oldestCandidateAge && candidate->getStatus() != MafiaMember::STATUS_IN_JAIL)
    {
      oldestCandidateAge = candidate->getAge();
      bossToRelocateTo = candidate;
      //cout << "Checking member peer, found a candidate: " << candidate->getName() << endl;
    }

    iter++;
  }

  if(bossToRelocateTo == NULL)
  {
    // iterate over the subordinates to get the oldest
    oldestCandidateAge = 0;
    iter = subordinates->begin();
    while(iter != subordinates->end())
    {
      MafiaMember *candidate = iter->second;
      //cout << "Checking member subordinate: " << candidate->getName() << endl;
      if(candidate->getAge() > oldestCandidateAge && candidate->getStatus() != MafiaMember::STATUS_IN_JAIL)
      {
        oldestCandidateAge = candidate->getAge();
        bossToRelocateTo = candidate;
      }
      iter++;
    }
  }

  if(bossToRelocateTo != NULL)
  {
    //cout << "Checking member subordinate, setting relocated boss: " << bossToRelocateTo->getName() << endl;
    member->setBossSubordinatesRelocatedTo(bossToRelocateTo);
    bossToRelocateTo->addRelocatedMembers(member, subordinates);

    // set the relocated boss for each subordinate
    iter = subordinates->begin();
    while(iter != subordinates->end())
    {
      MafiaMember *candidate = iter->second;
      candidate->setRelocatedBoss(bossToRelocateTo);
      iter++;
    }
  }
  // else what to do now?
}

void MafiaMembersManager::setMemberReleasedFromJail(MafiaMember *member)
{
  member->setStatus(MafiaMember::STATUS_NORMAL);
  if(!member->isBoss())
  {
    //cout << "Member is not a boss" << endl;
    // nothing else to be done
    return;
  }

  // remove the subordinates from the relocated boss while in jail
  MafiaMember *relocatedBoss = member->getBossSubordinatesRelocatedTo();
  relocatedBoss->removeRelocatedSubordinates(member);

  // clear the relocated boss from each of this member's subordinates
  MafiaMember::MafiaMemberSubordinateType *subordinates = member->getSubordinates();
  MafiaMember::MafiaMemberSubordinateType::iterator iter = subordinates->begin();

  while(iter != subordinates->end())
  {
    MafiaMember *candidate = iter->second;
    candidate->setRelocatedBoss(NULL);
    iter++;
  }
}

// This method is for the Bonus
MafiaMember *MafiaMembersManager::getHigherRankedMember(MafiaMember *m1, MafiaMember *m2)
{
  // The lower the rank, actually the higher up the hierarchy the boss is
  return (getMemberRank(m1) < getMemberRank(m2)) ? m1 : m2;
}

// Gets the depth in the hierarchy
// a return of -1 means the member is not in the hierarchy
int MafiaMembersManager::getMemberRank(MafiaMember *member)
{
    int depth(0);
    bool found  = getMemberRankRecursive(topBoss_, member, depth);

    return found ? depth : -1;
}

bool MafiaMembersManager::getMemberRankRecursive(MafiaMember *root, MafiaMember *searchMember, int &depth)
{
  if(root == searchMember)
  {
    // found the member
    return true;
  }

  if(!root->isBoss()) // ends the recursion
  {
    return false;
  }

  // Now check each of this member's subordinates
  MafiaMember::MafiaMemberSubordinateType *subordinates = root->getSubordinates();
  MafiaMember::MafiaMemberSubordinateType::iterator iter = subordinates->begin();
  bool retval(false);
  depth++;
  while(iter != subordinates->end() && retval == false)
  {
    retval = getMemberRankRecursive(iter->second, searchMember, depth);
    iter++;
  }

  if(!retval)
  {
    depth--;
  }

  return retval;
}
