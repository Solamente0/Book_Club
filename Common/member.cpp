#include "member.h"

Member::Member():ID(0), blocked(false) {};
Member::Member(const QString& username, const QString& password, const QString& securityAnswer): 
ID(0), username(username), password(password), securityAnswer(securityAnswer), blocked(false){}

int Member::getId() const{return ID;}
void Member::setId(int id) {ID = id;}
QString Member::getUsername() const{return username;}
void Member::setUsername(const QString& name) {username = name;}
QString Member::getPassword() const{return password;}
void Member::setPassword(const QString& pass) {password = pass;}
QString Member::getSecurityAnswer() const{return securityAnswer;}
bool Member::isBlocked() const{return blocked;}
void Member::setBlocked(bool block) {blocked = block;} 