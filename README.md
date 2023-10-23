# P3Networking
How to run:

Use make all in the folder directory to compile the program called clientServer
Then to run server run "./clientServer" in the folder directory
Then (in a new terminal) run the client using "./clientServer <any paramater(s) you want>" in the folder directory
As shown below a hello world message will be displayed showing how the program working, as well as logging the ttl increament
![image](https://user-images.githubusercontent.com/73619173/145138669-75ccf52a-9498-4d6b-a459-e052eb2af354.png)
use make clean to delete all executables

Final:

After using "make all" to create executables you can create diffrent routers and host using command lne arguments as well as a config.txt file. 

How to create router ./clientServer router <{1,2, or 3} -> based on which router from the config file you want to create>

How to create router ./clientServer <anything> <{1,2, or 3} -> based on which host from the config file you want to create>
  
In the example below the router was created before the host. They are able to communicate populated UDP packets.
  
The send config file was alredy in the file system, but this is not necessary as our program will scan for it constantly (you can add the file while the host is running)
  
![image](https://user-images.githubusercontent.com/73619173/146284141-540857ee-5b23-43d5-aa75-8f03ec5294b4.png)
  
  Below is an example of routers communicating with each other. First, initialize routers. then initialize hosts. 
  
  Hosts will send messages to routers, and routers to routers, and routers to hosts, as seen on the line directly above the last "Hello Message Sent" in each window.
  
  ![networks P3](https://user-images.githubusercontent.com/95599575/146302168-21162863-63d6-4015-89f6-a902dba8cb44.PNG)
  
  Top left: Host 1 (IP 1.2.3.1 / 10.0.2.104), Top Right: Router 1 (IP 10.0.2.101), Bottom left : Router 3 (IP 10.0.2.103), Bottom Right : Host 3 (IP 7.8.9.1 / 10.0.2.106)

