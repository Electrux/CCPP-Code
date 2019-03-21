FROM base/devel:2019.01.01

RUN pacman -Sy vim valgrind git bc --needed --noconfirm
RUN git clone https://github.com/Electrux/Alacrity-Lang.git
WORKDIR /Alacrity-Lang
RUN ./bootstrap.sh
