#include "API.h"
#include "Client.h"
#include "Server.h"
int main()
{
	Server* _server = new Server();
	Client* _client = new Client();
	OpenTheRoom(_server, _client, 10024);
	SendMsgMod(_client);
	RecvMsgMod(_client);
	RecvAndSend(_server);
	Sleep(100000);
}