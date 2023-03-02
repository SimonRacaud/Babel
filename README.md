# Description
Low level, UDP, audio streaming application.
Durung this project, we developed our own applicative protocol on top of UDP to transmit the audio. 

The project consists in a client/server architecture voice over IP application, similar to Skype or TeamSpeak.

The project is OS independent (Unix system and Windows).

### Technologies:
- portaudio, opus: Audio processing and compression
- Asio: Networking
- Qt: GUI
- sqlite_orm: Database

# Documentation
- [Diagrams](./doc/)
- [Network Tram](./DocTram/)

# Requirements

## Conan install

```shell
pip install --user conan
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan config set general.revisions_enabled=1
```

## Qt install (linux)

- Ubuntu
```shell
sudo apt-get install qtbase5-dev qtdeclarative5-dev
```
- Fedora 34
```shell 
sudo dnf install qt5-qtbase-devel
```

# Build on linux
```shell
mkdir build && (cd build && conan install .. --build=missing && cmake .. && make)
```
or
```shell
./build.sh re
```
### Preview
![GUI](/.github/gui.png)
