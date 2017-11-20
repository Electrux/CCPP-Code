class TextHandler:public sf::Drawable
{
	std::string text, typwhat, typwhat2, _count;
	sf::Text temptext, typehere, typewhat, typewhat2, counts;
	std::vector<sf::Text> drawtext;
	int count;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(typehere, states);
		target.draw(typewhat, states);
		target.draw(typewhat2, states);
		target.draw(counts, states);
		for (auto it = drawtext.begin(); it != drawtext.end(); ++it)
		{
			target.draw(*it, states);
		}
	}
	void SetDrawText(std::string &text, float variation = 0)
	{
		temptext.setString(text);
		temptext.setPosition((float)10 + variation, (float)470);
		drawtext.push_back(temptext);
		int tempcount = count;
		bool deletefront = false;
		for (auto it = drawtext.begin(); it != drawtext.end(); ++it)
		{
			if ((470 - (tempcount * 20)) <= 20)
			{
				deletefront = true;
			}
			else
				it->setPosition(it->getPosition().x, (float)(470 - (tempcount * 20)));
			tempcount--;
		}
		if (deletefront == true)
		{
			drawtext.erase(drawtext.begin());
		}
		else
			count++;
	}
	public:
		TextHandler()
		{
			count = 0;
			temptext.setFont(font);
			temptext.setFillColor(sf::Color::White);
			temptext.setCharacterSize(15);

			typehere.setFont(font);
			typehere.setFillColor(sf::Color::White);
			typehere.setCharacterSize(15);
			typehere.setPosition((float)10, (float)510);

			typewhat.setFont(font);
			typewhat.setFillColor(sf::Color::White);
			typewhat.setCharacterSize(15);
			typewhat.setPosition((float)10, (float)530);

			typewhat2.setFont(font);
			typewhat2.setFillColor(sf::Color::White);
			typewhat2.setCharacterSize(15);
			typewhat2.setPosition((float)10, (float)550);

			counts.setFont(font);
			counts.setFillColor(sf::Color::Green);
			counts.setCharacterSize(15);
			counts.setPosition((float)10, (float)10);

			typehere.setString("Your message:");
			typewhat.setString("");
			typewhat.setString("");
			typwhat.clear();
			typwhat2.clear();
			_count = "Count: Updating...";
			counts.setString(_count);
		}
		void AddText(std::string &ttext)
		{
			text = ttext;
			std::string linetext;
			std::vector<std::string> alllines;
			bool firstline = false;
			int linecount = 0, letters = 0, netletters = GetStringSize(text), templinecount = 1;
			if (netletters <= 90)
			{
				alllines.push_back(text);
			}
			else
			{
				for (auto it = text.begin(); it != text.end(); ++it)
				{
					if (letters > 90 && firstline == false)
					{
						letters = 0;
						alllines.push_back(linetext);
						linetext.clear();
						linecount++;
						firstline = true;
					}
					else if (letters >= 84 && firstline == true)
					{
						letters = 0;
						alllines.push_back(linetext);
						linetext.clear();
						linecount++;
					}
					else if ((netletters - ((linecount * 84))) <= 84)
					{
						linetext += FetchFrom(text, it);
						alllines.push_back(linetext);
						linecount++;
						break;
					}
					linetext += *it;
					letters++;
				}
			}
			for (auto it = alllines.begin(); it != alllines.end(); ++it)
			{
				if (templinecount > 1)
					SetDrawText(*it, 80);
				else
					SetDrawText(*it);
				templinecount++;
			}
		}
		std::string FetchFrom(std::string &_text, std::string::iterator _it)
		{
			std::string temp;
			bool found = false;
			for (auto it = _text.begin(); it != text.end(); ++it)
			{
				if (found == true)
					temp += *it;
				if (it == _it)
				{
					temp += *it;
					found = true;
				}
			}
			return temp;
		}
		void UpdateTypeWhat(char c)
		{
			if (c != 8)
			{
				if (GetStringSize(typwhat) >= 90)
				{
					typwhat2 += c;
				}
				else
				{
					typwhat += c;
				}
			}
			else if (!typwhat.empty())
			{
				if (!typwhat2.empty())
				{
					typwhat2.pop_back();
				}
				else
				{
					typwhat.pop_back();
				}
			}
			typewhat.setString(typwhat);
			typewhat2.setString(typwhat2);
		}
		void UpdateCount(std::string &__count)
		{
			_count = "Count: " + __count;
			counts.setString(_count);
		}
		int GetStringSize(std::string &str)
		{
			int num = 0;
			for (auto it = str.begin(); it != str.end(); ++it)
			{
				num++;
			}
			return num;
		}
		void ClearTyped()
		{
			typwhat.clear();
			typewhat.setString("");
			typwhat2.clear();
			typewhat2.setString("");
		}
		std::string GetTyped()
		{
			return typwhat + typwhat2;
		}
		bool getDelimitedStrings(std::string &str,std::vector<std::string> *_dest, int args = 3, char delim = ' ')
		{
			std::string temp;
			int delimcounter = 0;
			for (std::string::iterator it = str.begin(); it != str.end(); it++)
			{
				if ((*it == delim || delimcounter == args - 1))
				{
					if (delimcounter == args - 1)
					{
						_dest->push_back(cutStringFrom(&str, &it));
						delimcounter++;
						break;
					}
					_dest->push_back(temp);
					temp.clear();
					delimcounter++;
				}
				else
				{
					temp += (*it);
				}
			}
			return (delimcounter == args) ? true : false;
		}
		std::string cutStringFrom(std::string *str, std::string::iterator *it)
		{
			std::string temp;
			int reach = 0;
			for (std::string::iterator it2 = str->begin(); it2 != str->end(); it2++)
			{
				if (!reach)
				{
					if (*it == it2)
					{
						reach = 1;
						temp += *it2;
					}
				}
				else
					temp += *it2;
			}
			return temp;
		}
};