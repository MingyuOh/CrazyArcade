#pragma once
#include "User.h"

class DataBase : public Singleton<DataBase>
{
private:
	friend class Singleton<DataBase>;
private:
	FILE*			m_fpRead;
	FILE*			m_fpWrite;
	User*			m_pCurrentUser;
	vector<User>	m_UserList;
public:
	bool			LoadUserData();
	bool			SaveUserData();

	bool			SignUp(User user);
	bool			SignIn(T_STR account, T_STR password);

	bool			CheckDuplicationAccount(T_STR account);
	bool			CheckDuplicationNickName(T_STR nickName);
	bool			VerifyPassword(T_STR password, T_STR passwordConfirm);

	void			InsertUser(User user);
	void			SetCurrentUser(User* user);

	User*			GetCurrentUser();
	User*			GetUserToID(const int id);
	User*			GetUserToAccount(const T_STR account);
	User*			GetUserToNickName(const T_STR nickName);
	User*			GetUserToEmail(const T_STR email);
public:
	DataBase();
	~DataBase();
};
#define I_DB DataBase::GetInstance()

