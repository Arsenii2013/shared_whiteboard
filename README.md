Coursework project on the course OOP 2 semester. 
Shared whiteboard.
You can draw - circles, squares, curved lines, write text. You can change the color and thickness of these tools. You can undo and redo commands.
There are 2 executable files - a server and a client. The client has graphical tools which generate drawing and undo/redo commands. The client executes these commands on its board, and sends them to the server. The server does not draw its GUI, but stores an image of the board on which it executes the commands it receives. When connected, the client receives the image from the server-as a single command. 
The undo/redo mechanism is not implemented very well. When a command is undone, all clients and the server undo the last command executed. If the client just connected, the last command is to draw an image from the server.
OpenCV was used for drawing, SFML for socket wrapping.
