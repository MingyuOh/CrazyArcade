#include "DataBase.h"

bool DataBase::LoadUserData()
{
	if (_wfopen_s(&m_fpRead, L"../../data/User.txt", L"rt, ccs=UTF-8") != 0)
	{
		return false;
	}

	User user;
	int id = 0;
	TCHAR account[MAX_PATH] = { 0, };
	TCHAR password[MAX_PATH] = { 0, };
	TCHAR nickName[MAX_PATH] = { 0, };
	TCHAR email[MAX_PATH] = { 0, };

	while (!feof(m_fpRead))
	{
		fwscanf_s(m_fpRead, L"%d", &id);
		fwscanf_s(m_fpRead, L"%s", &account, _countof(account));
		fwscanf_s(m_fpRead, L"%s", &password, _countof(password));
		fwscanf_s(m_fpRead, L"%s", &nickName, _countof(nickName));
		fwscanf_s(m_fpRead, L"%s\n", &email, _countof(email));

		user.SetID(id);
		user.SetAccount(account);
		user.SetPassword(password);
		user.SetNickName(nickName);
		user.SetEmail(email);

		m_UserList.push_back(user);
	}

	fclose(m_fpRead);
	SAFE_ZERO(m_fpRead);

	return true;
}

bool DataBase::SaveUserData()
{
	if (_wfopen_s(&m_fpWrite, L"../../data/User.txt", L"wt, ccs=UTF-8") != 0)
	{
		return false;
	}

	for(auto& user : m_UserList)
	{
		fwprintf(m_fpWrite, L"%d ", user.GetID());
		fwprintf_s(m_fpWrite, L"%s ", user.GetAccount().c_str());
		fwprintf_s(m_fpWrite, L"%s ", user.GetPassword().c_str());
		fwprintf_s(m_fpWrite, L"%s ", user.GetNickName().c_str());
		fwprintf_s(m_fpWrite, L"%s\n", user.GetEmail().c_str());
	}

	fclose(m_fpWrite);
	SAFE_ZERO(m_fpWrite);

	return true;
}

bool DataBase::SignUp(User user)
{
	if (_wfopen_s(&m_fpWrite, L"../../data/User.txt", L"at, ccs=UTF-8") != 0)
	{
		return false;
	}

	assert(m_fpWrite);

	int id = m_UserList.size() + 1;
	user.SetID(id);

	fwprintf_s(m_fpWrite, L"%d ", user.GetID());
	fwprintf_s(m_fpWrite, L"%s ", user.GetAccount().c_str());
	fwprintf_s(m_fpWrite, L"%s ", user.GetPassword().c_str());
	fwprintf_s(m_fpWrite, L"%s ", user.GetNickName().c_str());
	fwprintf_s(m_fpWrite, L"%s\n", user.GetEmail().c_str());

	fclose(m_fpWrite);
	SAFE_ZERO(m_fpWrite);

	return true;
}

bool DataBase::SignIn(T_STR account, T_STR password)
{
	for (auto& user : m_UserList)
	{
		if (user.GetAccount() == account)
		{
			if (user.GetPassword() == password)
			{
				m_pCurrentUser = &user;
				return true;
			}
		}
	}
	return false;
}

bool DataBase::CheckDuplicationAccount(T_STR account)
{
	for (auto& user : m_UserList)
	{
		if (user.GetAccount() == account)
		{
			return true;
		}
	}
	return false;
}

bool DataBase::CheckDuplicationNickName(T_STR nickName)
{
	for (auto& user : m_UserList)
	{
		if (user.GetNickName() == nickName)
		{
			return true;
		}
	}
	return false;
}

bool DataBase::VerifyPassword(T_STR password, T_STR passwordConfirm)
{
	if (password == passwordConfirm)
	{
		return true;
	}
	return false;
}

void DataBase::InsertUser(User user)
{
	m_UserList.push_back(user);
}

void DataBase::SetCurrentUser(User* user)
{
	m_pCurrentUser = user;
}

User* DataBase::GetCurrentUser()
{
	return m_pCurrentUser;
}

User* DataBase::GetUserToID(const int id)
{
	for (int index = 0; index < m_UserList.size(); index++)
	{
		if (m_UserList[index].GetID() == id)
		{
			return &m_UserList[index];
		}
	}
	return nullptr;
}

User* DataBase::GetUserToAccount(const T_STR account)
{
	for (int index = 0; index < m_UserList.size(); index++)
	{
		if (m_UserList[index].GetAccount() == account)
		{
			return &m_UserList[index];
		}
	}
	return nullptr;
}

User* DataBase::GetUserToNickName(const T_STR nickName)
{
	for (int index = 0; index < m_UserList.size(); index++)
	{
		if (m_UserList[index].GetNickName() == nickName)
		{
			return &m_UserList[index];
		}
	}
	return nullptr;
}

User* DataBase::GetUserToEmail(const T_STR email)
{
	for (int index = 0; index < m_UserList.size(); index++)
	{
		if (m_UserList[index].GetEmail() == email)
		{
			return &m_UserList[index];
		}
	}
	return nullptr;
}

DataBase::DataBase()
{
	SAFE_ZERO(m_fpRead);
	SAFE_ZERO(m_fpWrite);
	SAFE_ZERO(m_pCurrentUser);
}

DataBase::~DataBase()
{

}