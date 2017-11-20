class xint
{
	std::vector<unsigned char> digits;
	int temp;

public:
	bool operator =(std::string &str);
	bool operator =(std::vector<unsigned char> &num);
	int addnum(int a, int b, int &carry);
	int getqnr(int a, int &carry);
	void xint::operator *=(unsigned long long num);
	void xint::operator *=(xint num);
	xint operator *(xint num);
	xint operator +(xint num);
	xint xint::operator +(std::vector<unsigned char> &num1);
	bool resolvedigits(std::vector<unsigned char> &vec);
	bool dadd(int &num);
	bool inc();
	bool dec();
	std::vector<unsigned char> getVector();
	std::vector<unsigned char> getNumVector(std::string &str);
	std::vector<unsigned char> getNumVector(unsigned int &num);
	std::vector<unsigned char> getNumVector(unsigned long &num);
	std::vector<unsigned char> getNumVector(unsigned long long &num);
	void dispVec()
	{
		for (auto it = digits.rbegin(); it != digits.rend(); it++)
		{
			std::cout << *it;
		}
	}
	unsigned long getVecSize()
	{
		unsigned long temp;
		temp = 0;
		for (auto it = digits.begin(); it != digits.end(); it++)
		{
			temp++;
		}
		return temp;
	}
	friend std::ostream & operator <<(std::ostream &os, const xint &xi);
	bool isNum(std::string &str);
	int getInteger(char c);
};

bool xint::operator =(std::string &str)
{
	if (!isNum(str)) return false;
	digits.clear();
	for (auto it = str.rbegin(); it != str.rend(); it++)
	{
		digits.push_back(getInteger(*it));
	}
	return true;
}

bool xint::operator =(std::vector<unsigned char> &num)
{
	digits.clear();
	for (auto it = num.begin(); it != num.end(); it++)
	{
		digits.push_back(*it);
	}
	return true;
}

int xint::addnum(int a, int b, int &carry)
{
	a += b;
	carry = (a / 10 > 0) ? a / 10 : 0;
	return a % 10;
}

int xint::getqnr(int a, int &carry)
{
	carry = (a / 10 > 0) ? a / 10 : 0;
	return a % 10;
}


void xint::operator *=(unsigned long long num)
{
	std::vector<unsigned char> _temp, num1 = getNumVector(num);
	size_t num1size = num1.size();
	int currentnum1 = 0;
	std::vector<std::vector<unsigned char>> _toadd;
	temp = 0;
	for (auto it = num1.begin(); it != num1.end(); it++)
	{
		_temp.clear();
		for (int i = 0; i < currentnum1; i++)
		{
			_temp.push_back(0);
		}
		for (auto digit = digits.begin(); digit != digits.end(); digit++)
		{
			_temp.push_back(*digit * *it);
		}
		resolvedigits(_temp);
		_toadd.push_back(_temp);
		currentnum1++;
	}
	_temp.clear();
	digits.clear();
	for (auto it2 = _toadd.begin(); it2 != _toadd.end(); it2++)
	{
		*this = *this + *it2;
	}
}

void xint::operator *=(xint num)
{
	std::vector<unsigned char> _temp, num1 = num.getVector();
	size_t num1size = num1.size();
	int currentnum1 = 0;
	std::vector<std::vector<unsigned char>> _toadd;
	temp = 0;
	for (auto it = num1.begin(); it != num1.end(); it++)
	{
		_temp.clear();
		for (int i = 0; i < currentnum1; i++)
		{
			_temp.push_back(0);
		}
		for (auto digit = digits.begin(); digit != digits.end(); digit++)
		{
			_temp.push_back((*digit) * (*it));
		}
		resolvedigits(_temp);
		_toadd.push_back(_temp);
		currentnum1++;
	}
	_temp.clear();
	digits.clear();
	for (auto it2 = _toadd.begin(); it2 != _toadd.end(); it2++)
	{
		*this = *this + *it2;
	}
}

xint xint::operator *(xint num)
{
	std::vector<unsigned char> _temp, num1 = num.getVector();
	int currentnum1 = 0;
	std::vector<std::vector<unsigned char>> _toadd;
	temp = 0;
	for (auto it = num1.begin(); it != num1.end(); it++)
	{
		_temp.clear();
		for (int i = 0; i < currentnum1; i++)
		{
			_temp.push_back(0);
		}
		for (auto digit = digits.begin(); digit != digits.end(); digit++)
		{
			_temp.push_back(*digit * *it);
		}
		resolvedigits(_temp);
		_toadd.push_back(_temp);
		currentnum1++;
	}
	_temp.clear();
	for (auto it2 = _toadd.begin(); it2 != _toadd.end(); it2++)
	{
		*this = *this + *it2;
	}
	return *this;
}

xint xint::operator +(xint num)
{
	std::vector<unsigned char> _temp;
	std::vector<unsigned char> num1 = num.getVector();
	temp = 0;
	int tempcounter = 0;
	if (digits.size() > num1.size())
	{
		for (auto it = digits.begin(), it2 = num1.begin(); it != digits.end(); it++, it2++)
		{
			if (it2 == num1.end())
			{
				while (it != digits.end())
				{
					_temp.push_back(*it);
					if (temp > 0)
					{
						_temp[tempcounter] += temp;
						_temp[tempcounter] = getqnr(_temp[tempcounter], temp);
					}
					tempcounter++;
					it++;
				}
				break;
			}
			else
			{
				_temp.push_back(0);
				if (temp > 0)
				{
					_temp[tempcounter] += temp;
					temp = 0;
				}
				_temp[tempcounter] += addnum(*it, *it2, temp);
				tempcounter++;
			}
		}
	}
	else if (digits.size() < num1.size())
	{
		for (auto it = digits.begin(), it2 = num1.begin(); it2 != num1.end(); it++, it2++)
		{
			if (it == digits.end())
			{
				while (it2 != num1.end())
				{
					_temp.push_back(*it2);
					if (temp > 0)
					{
						_temp[tempcounter] += temp;
						_temp[tempcounter] = getqnr(_temp[tempcounter], temp);
					}
					tempcounter++;
					it2++;
				}
				break;
			}
			else
			{
				_temp.push_back(0);
				if (temp > 0)
				{
					_temp[tempcounter] += temp;
					temp = 0;
				}
				_temp[tempcounter] += addnum(*it, *it2, temp);
				tempcounter++;
			}
		}
	}
	else
	{
		temp = 0;
		for (auto it = digits.begin(), it2 = num1.begin(); it != digits.end(); it++, it2++)
		{
			_temp.push_back(0);
			if (temp > 0)
			{
				_temp[tempcounter] += temp;
				temp = 0;
			}
			_temp[tempcounter] += addnum(*it, *it2, temp);
			tempcounter++;
		}
	}
	if (temp > 0)
		_temp.push_back(temp);
	xint tem;
	tem = _temp;
	return tem;
}

xint xint::operator +(std::vector<unsigned char> &num1)
{
	std::vector<unsigned char> _temp;
	temp = 0;
	int tempcounter = 0;
	if (digits.size() > num1.size())
	{
		for (auto it = digits.begin(), it2 = num1.begin(); it != digits.end(); it++, it2++)
		{
			if (it2 == num1.end())
			{
				while (it != digits.end())
				{
					_temp.push_back(*it);
					if (temp > 0)
					{
						_temp[tempcounter] += temp;
						_temp[tempcounter] = getqnr(_temp[tempcounter], temp);
					}
					tempcounter++;
					it++;
				}
				break;
			}
			else
			{
				_temp.push_back(0);
				if (temp > 0)
				{
					_temp[tempcounter] += temp;
					temp = 0;
				}
				_temp[tempcounter] += addnum(*it, *it2, temp);
				tempcounter++;
			}
		}
	}
	else if (digits.size() < num1.size())
	{
		for (auto it = digits.begin(), it2 = num1.begin(); it2 != num1.end(); it++, it2++)
		{
			if (it == digits.end())
			{
				while (it2 != num1.end())
				{
					_temp.push_back(*it2);
					if (temp > 0)
					{
						_temp[tempcounter] += temp;
						_temp[tempcounter] = getqnr(_temp[tempcounter], temp);
					}
					tempcounter++;
					it2++;
				}
				break;
			}
			else
			{
				_temp.push_back(0);
				if (temp > 0)
				{
					_temp[tempcounter] += temp;
					temp = 0;
				}
				_temp[tempcounter] += addnum(*it, *it2, temp);
				tempcounter++;
			}
		}
	}
	else
	{
		temp = 0;
		for (auto it = digits.begin(), it2 = num1.begin(); it != digits.end(); it++, it2++)
		{
			_temp.push_back(0);
			if (temp > 0)
			{
				_temp[tempcounter] += temp;
				temp = 0;
			}
			_temp[tempcounter] += addnum(*it, *it2, temp);
			tempcounter++;
		}
	}
	if (temp > 0)
		_temp.push_back(temp);
	xint tem;
	tem = _temp;
	return tem;
}

bool xint::resolvedigits(std::vector<unsigned char> &vec)
{
	temp = 0;
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		if (temp > 0)
		{
			*it += temp;
			temp = 0;
		}
		temp = *it / 10;
		*it = *it % 10;
	}
	if (temp > 0)
		vec.push_back(temp);
	return true;
}

bool xint::dadd(int &num)
{
	digits.push_back(num);
	return true;
}

bool xint::inc()
{
	temp = 0;
	int begin = 0, toinc = 0;
	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		if (begin == 0)
		{
			*it += 1;
			begin = 1;
		}
		if (toinc == 1)
		{
			*it += temp;
			toinc = 0;
			temp = 0;
		}
		if (*it >= 10)
		{
			temp = *it / 10;
			*it = *it % 10;
			toinc = 1;
		}
		else
		{
			break;
		}
	}
	if (temp > 0)
	{
		digits.push_back(temp);
	}
	return true;
}

bool xint::dec()
{
	int borrow = 0;
	int todec = 0;
	if (*(digits.end() - 1) == 0) return false;

	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		if (todec == 0)
		{
			if (*it > 0)
			{
				(*it)--;
				todec = 1;
				if (it == digits.end() - 1 && *it == 0 && digits.size() == 1)
				{
					//digits.clear();
					return true;
				}
				break;
			}
			else
			{
				*it = 9;
				borrow = 1;
			}
		}
		if (borrow > 1)
		{
			while (it != digits.end())
			{
				if (*it > 0)
				{
					(*it)--;
					borrow = 0;
					break;
				}
				else
				{
					*it = 9;
					it--;
				}
				it++;
			}
		}
	}
	while (*(digits.end() - 1) == 0 && !digits.empty())
	{
		digits.pop_back();
	}
	return true;
}

std::vector<unsigned char> xint::getVector()
{
	return digits;
}

std::vector<unsigned char> xint::getNumVector(std::string &str)
{
	std::vector<unsigned char> _temp;
	_temp.clear();
	for (auto it = str.rbegin(); it != str.rend(); it++)
	{
		_temp.push_back(getInteger(*it));
	}
	return _temp;
}

std::vector<unsigned char> xint::getNumVector(unsigned int &num)
{
	std::vector<unsigned char> _temp;
	_temp.clear();
	while (num >= 10)
	{
		temp = num % 10;
		num /= 10;
		_temp.push_back(temp);
	}
	temp = num % 10;
	if (temp > 0)
	{
		_temp.push_back(temp);
	}
	return _temp;
}

std::vector<unsigned char> xint::getNumVector(unsigned long &num)
{
	std::vector<unsigned char> _temp;
	_temp.clear();
	while (num >= 10)
	{
		temp = num % 10;
		num /= 10;
		_temp.push_back(temp);
	}
	temp = num % 10;
	if (temp > 0)
	{
		_temp.push_back(temp);
	}
	return _temp;
}

std::vector<unsigned char> xint::getNumVector(unsigned long long &num)
{
	std::vector<unsigned char> _temp;
	_temp.clear();
	while (num >= 10)
	{
		temp = num % 10;
		num /= 10;
		_temp.push_back(temp);
	}
	temp = num % 10;
	if (temp > 0)
	{
		_temp.push_back(temp);
	}
	return _temp;
}

std::ostream &operator <<(std::ostream &os, const xint &xi)
{
	for (auto it = xi.digits.rbegin(); it != xi.digits.rend(); it++)
	{
		os << static_cast<int>(*it);
	}
	return os;
}

bool xint::isNum(std::string &str)
{
	for (auto it = str.begin(); it != str.end(); it++)
	{
		if (*it != '0' && *it != '1' && *it != '2' && *it != '3' && *it != '4' && *it != '5' && *it != '6' && *it != '7' && *it != '8' && *it != '9')
		{
			return false;
		}
	}
	return true;
}

int xint::getInteger(char c)
{
	return atoi(&c);
}
