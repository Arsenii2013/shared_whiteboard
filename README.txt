Course project on the OOP course 2 semester.
Shared whiteboard.
You can draw - circles, squares, curved lines, write text. You can change the color and thickness of these tools. You can undo and redo commands.
There are 2 executable files - server and client. The client has graphical tools which generate drawing and undo/redo commands. The client executes these commands on its board, and sends them to the server. The server does not draw its GUI, but keeps an image of the board on which it executes the received commands. When connected, the client receives the image from the server-as a single command. 
The undo/redo mechanism is not very well implemented. When a command is undone, all clients and the server undo the last executed command. If the client just connected, the last command is to draw an image from the server.
