void ChatEngine::PollEvent()
{
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			Close();
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
				Close();
			if (event.key.code == sf::Keyboard::Return)
			{
				if (!alltext.GetTyped().empty())
				{
					if (iscmd == false)
					{
						connection.SendMessage(alltext.GetTyped());
					}
					else if (iscmd == true)
					{
						sf::Packet temppack;
						if (GenerateCommand(alltext.GetTyped(), temppack))
						{
							connection.SendPacket(temppack);
						}
					}
					alltext.ClearTyped();
				}
				iscmd = false;
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128 && (static_cast<char>(event.text.unicode) != '\r') && (static_cast<char>(event.text.unicode) != '/') && (event.text.unicode != 27)/*BackSpace*/)
			{
				alltext.UpdateTypeWhat(static_cast<char>(event.text.unicode));
			}
			if (static_cast<char>(event.text.unicode) == '/')
			{
				if (iscmd == false && alltext.GetTyped().empty() == true)
				{
					iscmd = true;
				}
				alltext.UpdateTypeWhat(static_cast<char>(event.text.unicode));
			}
		}
	}
}