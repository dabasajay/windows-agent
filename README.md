# networking
Networking programs in C++.

In this project, I made a windows agent using C++ to send logs and receive commands from server and execute them. It runs as a process and continuously communicate with server over TCP connection.

<h2>Files</h2>
<ul>
	<li>client.cpp: client side code</li>
	<li>server.cpp: server side code</li>
	<li>clientv2.cpp: client side code version 2</li>
	<li>serverv2.cpp: server side code version 2</li>
</ul>

<h4>Procedure</h4>
<ul>
	<li>Compile clientv2.cpp and serverv2.cpp into executables using compiler</li>
	<li>run server.exe and enter the ip address and port number to setup a server in listening mode</li>
	<li>run client.exe and enter the ip address and port number on which server is hosted to connect to it and receive commands</li>
	<li>The server can send messages to the client through terminal and the client show and take action based on the message</li>
</ul>

<h4>Executables Size</h4>
<ul>
	<li>client.exe : <strong>11.0 KB</strong></li>
	<li>server.exe : <strong>10.5 KB</strong></li>
</ul>

<h4>Supportde Commands in serverv2</h4>
<ul>
	<li><strong>sendlog</strong>: Send the log of current window title of client to server which saves the in a text file.</li>
	<li><strong>logoffuser</strong>: Logoff current client</li>
	<li><strong>restartuser</strong>: Restart client's machine</li>
	<li><strong>shutdownuser</strong>: Shutdown client's machine</li>
</ul>