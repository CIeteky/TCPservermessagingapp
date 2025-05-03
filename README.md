# TCPservermessagingapp
Messaging app using QTcpServer and QTcpSocket
project for my uni C++ class
trying to learn the Qt framework and it's vast amount of libraries
this is a project trying to set up a communication utilizing a TCP server 
# HOW IT WORKS
Use the Messagingapp to create a server in a localhost or a specified host
Use clients to connect to said host and chat 
[Most up to date releases](https://github.com/CIeteky/TCPservermessagingapp/releases/tag/0.0.2)
**Example code to try the functionality of your TCPserver**
create a python file and run the following code:
```
import socket
import time
import random
HOST = '1.1.1.1.1'  # your server's IP
PORT = 6666         # port

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))
    print("Connected to server")

    
    sock.sendall(b"/name PythonClient\n")
    time.sleep(0.5)

    messages = ["Hello World", "If these messages pass through", "Your TCP server can accept input from python clients!"]
    for msg in messages:
        sock.sendall((msg + "\n").encode())
        time.sleep(random.uniform(3, 7)) 

    print("Messages sent.")
```
# INSTALLATION GUIDE 
**Linux**
*before installation make sure to have qtbase5-dev installed, may have different names under different distributions*
**MAKE SURE YOUR SYSTEM IS NOT DEFAULTING TO qmake6 SINCE THIS PROJECT IS USING qmake5 THERE MIGHT BE ISSUES, IF YOU WANNA BE COMPLETELY SAFE CONSIDER RUNNING qmake5 INSTEAD OF qmake**

```
git clone https://github.com/CIeteky/TCPservermessagingapp.git
cd TCPservermessagingapp
qmake
make
./MessagingApp
```
**Windows**
Go to the [releases](https://github.com/CIeteky/TCPservermessagingapp/releases) page and download the latest release

