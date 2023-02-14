#include "User.h"

bool User::CreateUser(T_STR account, T_STR password, T_STR nickName, T_STR email)
{
	m_szAccount = account;
	m_szPassword = password;
	m_szNickName = nickName;
	m_szEmail = email;
	return true;
}


void User::SetID(const int id)
{
	m_iID = id;
}

void User::SetAccount(const T_STR account)
{
	m_szAccount = account;
}

void User::SetPassword(const T_STR password)
{
	m_szPassword = password;
}

void User::SetNickName(const T_STR nickName)
{
	m_szNickName = nickName;
}

void User::SetEmail(const T_STR email)
{
	m_szEmail = email;
}

int User::GetID()
{
	return m_iID;
}

T_STR User::GetAccount()
{
	return m_szAccount;
}

T_STR User::GetPassword()
{
	return m_szPassword;
}

T_STR User::GetNickName()
{
	return m_szNickName;
}

T_STR User::GetEmail()
{
	return m_szEmail;
}

User::User()
{
	m_szAccount = _T("");
	m_szPassword = _T("");
	m_szNickName = _T("");
	m_szEmail = _T("");
}

User::~User()
{

}