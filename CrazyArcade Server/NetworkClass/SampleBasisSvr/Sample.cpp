#include "Server.h"

void main()
{
	I_Server.Init();

	while (1)
	{
		if (I_Server.m_Acceptor.Run() == false)
			break;

		I_Server.Frame();
	}
}