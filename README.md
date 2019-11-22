## Windows Agent in C++

[![Issues](https://img.shields.io/github/issues/dabasajay/windows-agent.svg?color=%231155cc)](https://github.com/dabasajay/windows-agent/issues)
[![Forks](https://img.shields.io/github/forks/dabasajay/windows-agent.svg?color=%231155cc)](https://github.com/dabasajay/windows-agent/network)
[![Stars](https://img.shields.io/github/stars/dabasajay/windows-agent.svg?color=%231155cc)](https://github.com/dabasajay/windows-agent/stargazers)
[![Ajay Dabas](https://img.shields.io/badge/Ajay-Dabas-825ee4.svg)](https://dabasajay.github.io/)

In this project, I made a windows agent using C++ to send logs and receive commands from the server and execute them. It runs as a process and continuously communicates with the server over TCP connection.

## Files
<ul type="square">
	<li>client.cpp: client side code</li>
	<li>server.cpp: server side code</li>
	<li>clientv2.cpp: client side code version 2</li>
	<li>serverv2.cpp: server side code version 2</li>
</ul>

## Procedure
<ul type="square">
	<li>Compile clientv2.cpp and serverv2.cpp into executables using compiler</li>
	<li>run server.exe and enter the ip address and port number to setup a server in listening mode</li>
	<li>run client.exe and enter the ip address and port number on which server is hosted to connect to it and receive commands</li>
	<li>The server can send messages to the client through terminal and the client show and take action based on the message</li>
</ul>

## Executables Size
<ul type="square">
	<li>client.exe : <strong>11.0 KB</strong></li>
	<li>server.exe : <strong>10.5 KB</strong></li>
</ul>

## Supported Commands in serverv2
<ul type="square">
	<li><strong>sendlog</strong>: Send the log of current window title of client to server which saves the in a text file.</li>
	<li><strong>logoffuser</strong>: Logoff current client</li>
	<li><strong>restartuser</strong>: Restart client's machine</li>
	<li><strong>shutdownuser</strong>: Shutdown client's machine</li>
</ul>
