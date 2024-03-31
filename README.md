# Network

### Windows Network Library
#### C++20 MSVC

##### Network
* Pure Virtual Class로 Network interface

##### TcpStream
* Network를 상속받은 구현체로 주로 동기적인 처리와 BSD 소켓과 호환성을 고려함
  
##### AsyncStream
* Network를 상속받은 구현체로 비동기처리를 주로사용
* WSAOVERLAPPED 를 가지고 있다

##### Listener
* Pure Virtual Class인 Network를 상속받은 또 다른 Pure Virtual Class이며 Listenter interface

##### TcpListener
* Listener를 상속받은 구현체로 동기적인 처리를 위한 Listener

##### AsyncListener
* Listener를 상속받은 구현체로 비동기적인 처리를 위한 Listener
* IOCP를 사용해 처리
