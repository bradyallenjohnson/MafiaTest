/* 
 * File:   MafiaMember.h
 * Author: ebrjohn
 *
 * Created on 22 de diciembre de 2011, 9:16
 * 
 * Class to store a MafiaMember, to be used as a Composite Design Pattern
 * 
 */

#ifndef MAFIAMEMBER_H
#define	MAFIAMEMBER_H

#include <string>
#include <map>
#include <list>

using namespace std;

class MafiaMember {
public:
    MafiaMember(const MafiaMember& orig);
    MafiaMember(const string &name,
                const string &alias,
                int age,
                int status);
    virtual ~MafiaMember();

    // TODO make the operator=()

    typedef map<string, MafiaMember*> MafiaMemberSubordinateType;
    typedef map<MafiaMember*, MafiaMemberSubordinateType*> MafiaMemberRelocatedSubordinateType;

    enum
    {
        STATUS_NORMAL = 0,
        STATUS_IN_JAIL
    };

    //
    // Setters and Getters
    //
    inline void setName(string name) { this->name_ = name; }
    inline string getName() const { return name_; }

    inline void setAlias(string alias) { this->alias_ = alias; }
    inline string getAlias() const { return alias_; }

    inline void setAge(unsigned int age) { this->age_ = age; }
    inline unsigned int getAge() const { return age_; }

    inline void setStatus(unsigned int status) { this->status_ = status; }
    inline unsigned int getStatus() const { return status_; }

    inline void setBoss(MafiaMember* boss) { this->boss_ = boss; }
    inline MafiaMember *getBoss() const { return boss_; }

    inline MafiaMember* getRelocatedBoss() { return relocatedBoss_; }
    inline void setRelocatedBoss(MafiaMember *rBoss) { relocatedBoss_ = rBoss; }

    // When this particular member gets put in jail, the bossSubordinatesRelocatedTo_
    // is where this member's subordinates were sent until released from jail
    inline void setBossSubordinatesRelocatedTo(MafiaMember* boss) { this->bossSubordinatesRelocatedTo_ = boss; }
    inline MafiaMember *getBossSubordinatesRelocatedTo() const { return bossSubordinatesRelocatedTo_; }

    inline MafiaMemberRelocatedSubordinateType *getRelocatedSubordinates() { return &relocatedSubordinates_; }
    inline MafiaMemberSubordinateType *getSubordinates() { return &subordinatesByName_; }
    inline MafiaMemberSubordinateType *getAliasSubordinates() { return &subordinatesByAlias_; }
    void addSubordinate(MafiaMember *member);

    void addRelocatedMembers(MafiaMember *boss, MafiaMemberSubordinateType *subordinates);
    void removeRelocatedSubordinates(MafiaMember *boss);
    inline bool isBoss() {return subordinatesByName_.empty() ? false : true; }
    inline unsigned int getNumDirectSubordinates() { return subordinatesByName_.size(); }

    MafiaMember *findSubordinateByName(const string &name);
    MafiaMember *findRelocatedSubordinateByName(const string &name);
    MafiaMember *findSubordinateByAlias(const string &name);
    MafiaMember *findRelocatedSubordinateByAlias(const string &name);

private:
    string name_;
    string alias_; // AKA
    unsigned int age_;
    unsigned int status_;
    MafiaMember *boss_;
    MafiaMember *relocatedBoss_; // used when current boss is in jail
    MafiaMember *bossSubordinatesRelocatedTo_;
    MafiaMemberSubordinateType subordinatesByName_;
    MafiaMemberSubordinateType subordinatesByAlias_;
    // making a map since there can be multiple relocations to this member
    MafiaMemberRelocatedSubordinateType relocatedSubordinates_;

    MafiaMember(); // not allowing the default ctor
};

#endif	/* MAFIAMEMBER_H */

