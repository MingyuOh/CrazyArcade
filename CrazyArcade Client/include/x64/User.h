#pragma once
#include "CoreSTD.h"

class User
{
private:
	int			m_iID;
	T_STR		m_szAccount;
	T_STR		m_szPassword;
	T_STR		m_szNickName;
	T_STR		m_szEmail;
public:
	bool		CreateUser(T_STR account, T_STR password, T_STR nickName, T_STR email);

	void		SetID(const int id);
	void		SetAccount(const T_STR account);
	void		SetPassword(const T_STR password);
	void		SetNickName(const T_STR nickName);
	void		SetEmail(const T_STR email);

	int			GetID();
	T_STR		GetAccount();
	T_STR		GetPassword();
	T_STR		GetNickName();
	T_STR		GetEmail();
public:
	User();
	~User();
};

