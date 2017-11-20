bool ChatEngine::InitNetwork(sf::IpAddress &ip)
{
	int auth = 0, authres = -1;

	while (auth == 0)
	{
		std::cout << "\nEnter your name: ";
		std::cin >> myname;
		std::cout << "\nEnter your password: ";
		std::cin >> pass;
		std::cout << "\nEstablishing connection...";
		if (!connection.Init(ip, defaultauthport))
		{
			std::cout << "\nConnection to authentication server failed. Please check the Internet connectivity and/or the availability of the server.";
			return false;
		}
		else
		{
			std::cout << "\nConnection established...\nAuthenticating...";
		}
		authres = connection.Authenticate(myname, pass);
		if (authres == Auth::WrongPass)
		{
			std::cout << "\nPassword incorrect! Please retry.";
		}
		else if (authres == Auth::AlreadyLogged)
		{
			std::cout << "\nSomeone with this username and password have already logged. Your account may be compromised. Please contact the server admin.";
		}
		else if (authres == Auth::Registered)
		{
			std::cout << "\nRegistered with this username and password.\nConnecting to the world server. Please wait...";
			auth = 1;
		}
		else
		{
			auth = 1;
			std::cout << "\nAuthenticated!\nConnecting to the world server...";
		}
	}
	connection.Disconnect();
	if (!connection.Init(ip, defaultworldport))
	{
		std::cout << "\nConnection to world server failed. Please check the Internet connectivity and/or the availability of the server.";
		return false;
	}
	if (!connection.WorldServerConnect())
	{
		std::cout << "\nCould not finalize connection with world server. Please check the Internet connectivity and/or the availability of the server.";
		return false;
	}
	else
	{
		std::cout << "\nConnected! You are now online...";
	}
	return true;
}