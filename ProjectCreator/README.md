# Electrux-Codes

This is a project creation tool for C/C++ ( currently ).
The program, using command line arguments, creates directory structure
for any project which you want to make.

To use this program, a few command line arguments given below must be
remembered:

	--lang <language code>

		This argument specifies the language which is to be used to
		create the project.
		Current valid language codes are:
			c
			c++


	--name <Project_Name>

		This argument specifies the name of the project which will be
		made. For the sake of ease, the project name MUST NOT contain
		any spaces in between.


	--dir <directory>

		Note: Optional argument.

		This argument specifies the name of the directory using either
			relative paths:
				example: ~/Test
			or absolute paths:
				example: /Users/$USER/

		If this argument is not provided, it will
		automatically set the path relative to current directory.


	--libs <comma separated library codes>

		This argument specifies the libraries which are to be used
		with the project. Currently supports:
			SFML,
			SDL2 ( with SDL2_image, SDL2_ttf as optionals ).

		To use the libs, use the following:

			Library		Code
			SFML		sfml
			SDL2		sdl2
			SDL2_image	sdl2img
			SDL2_ttf	sdl2ttf

		NOTE: You must have installed the library on your system
			beforehand.



Final example:
	./ProjectCreator --language c++ --name Test --dir ~ --libs sdl2,sdl2img
