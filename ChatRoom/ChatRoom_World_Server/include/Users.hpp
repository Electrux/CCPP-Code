class Users :public sf::TcpSocket
{
	std::string name;
public:
	void EnterName(std::string __name)
	{
		name = __name;
	}
	void Enter(std::string __name)
	{
		name = __name;
	}
	std::string GetName()
	{
		return name;
	}
};