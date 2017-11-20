# Chat Room

Requirements:
SQLite Amalgamation version

SFML library for C++ (Used version 2.3.2)

C++11 compliant compiler (made in VS 2015)




Chat Room.
You can talk on global chat (default) or use one of the commands (in commands.txt) to create and manage your own groups and talk in them.

Contains 3 parts:
1. Authentication server - The server to which the client first connects to and checks your credentials (create new account if unregistered, login if already registered, retry if incorrect login).

2. World server - Central server through which all communication takes place and the client connects to it at all times.

3. Client - The client, Interface with which you can chat.


You just have to type the message directly when the black GUI screen opens up after going through the credentials in client.

All the groups and accounts created are saved in /Groups/<group-name>.db file and <account-name>.db file.



NOTE: The folder Groups MUST be created by yourself before running the application or the application will behave abnormally.

NOTE 2: There is still a lot of work to be done on the client and server side.

Directory is:
    C:\<user-name>.db
and
    C:\Groups\<groups>.db

For changing the base directory, you need to change the defaultdbdir global variable in:
    Auth-server/includes/Data.hpp
    World-server/includes/Data.hpp
