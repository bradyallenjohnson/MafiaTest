/* 
 * File:   MafiaMember.cpp
 * Author: ebrjohn
 * 
 * Created on 22 de diciembre de 2011, 9:16
 */

#include <iostream>

#include "MafiaMember.h"

MafiaMember::MafiaMember(const MafiaMember& orig)
{
    setName(orig.getName());
    setAlias(orig.getAlias());
    setAge(orig.getAge());
    setStatus(orig.getStatus());
    setBoss(orig.getBoss());

    // dont copy subordinates nor relocatedSubordinates
}

MafiaMember::MafiaMember(const string &name, const string &alias, int age, int status) :
    name_(name),
    alias_(alias),
    age_(age),
    status_(status),
    boss_(NULL),
    relocatedBoss_(NULL),
    bossSubordinatesRelocatedTo_(NULL)
{
}

MafiaMember::~MafiaMember()
{
    subordinatesByName_.clear();
    subordinatesByAlias_.clear();
    relocatedSubordinates_.clear();
}

void MafiaMember::addSubordinate(MafiaMember *member)
{
  if(member != NULL)
  {
    subordinatesByName_.insert(make_pair(member->getName(), member));
    subordinatesByAlias_.insert(make_pair(member->getAlias(), member));
  }
}

MafiaMember *MafiaMember::findSubordinateByName(const string &name)
{
  MafiaMemberSubordinateType::iterator iter = subordinatesByName_.find(name);

  if(iter == subordinatesByName_.end())
  {
      return NULL;
  }

  return iter->second;
}

MafiaMember *MafiaMember::findRelocatedSubordinateByName(const string &name)
{
  // Iterate over the relocated subordinates list and search each map
  // This is not the most efficient way, but a member probably wont
  // have several relocated subordinate lists

/* TODO finish this, has lower priority right now
  MafiaMemberSubordinateType::iterator iter = subordinatesByName_.find(name);

  if(iter == subordinatesByName_.end())
  {
      return NULL;
  }

  return iter->second;
*/
    return NULL;
}

MafiaMember *MafiaMember::findSubordinateByAlias(const string &name)
{
  //cout << "Looking for alias: " << name << ", in member: " << getName() << endl;

  MafiaMemberSubordinateType::iterator iter = subordinatesByAlias_.find(name);

  if(iter == subordinatesByAlias_.end())
  {
      return NULL;
  }

  return iter->second;
}

MafiaMember *MafiaMember::findRelocatedSubordinateByAlias(const string &name)
{
    // TODO need to create a way to search by alias as well, this has lower priority
    return NULL;
}

void MafiaMember::addRelocatedMembers(MafiaMember *boss, MafiaMemberSubordinateType *subordinates)
{
  if(boss != NULL)
  {
    relocatedSubordinates_.insert(make_pair(boss, subordinates));
  }
}

void MafiaMember::removeRelocatedSubordinates(MafiaMember *boss)
{
  if(boss != NULL)
  {
    relocatedSubordinates_.erase(boss);
  }
}