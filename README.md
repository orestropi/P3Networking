# P3Networking
checkpoint 1:
https://ia.wpi.edu/cs3516/resources.php?page=show_project&id=4
Use make all in the folder directory to compile the program called clientServer
Then to run server run "./clientServer" in the folder directory
Then (in a new terminal) run the client using "./clientServer <any paramater(s) you want>" in the folder directory
As shown below a hello world message will be displayed showing how the program working, as well as logging the ttl increament
![image](https://user-images.githubusercontent.com/73619173/145138669-75ccf52a-9498-4d6b-a459-e052eb2af354.png)
use make clean to delete all executables

All tasks 1-4 should be completed for checkpoint 1


Final Submission:
Firstly, our routers can accurately talk to each other. We went to Craig's office hours and after half an hour of bug fixing we couldn't get our routers to send packets to the RIGHT person, they correctly send it to the WRONG person. He told us to roll with it and move on to other parts of the project because it was likely a very very small logic error causing the problems in routing pull. Table setting and table pulling are fine when reading the config, but not when sending. Just a quirk of the code.

After using "make all" to create executables you can create diffrent routers and host using command lne arguments as well as a config.txt file. 

How to create router ./clientServer router <{1,2, or 3} -> based on which router from the config file you want to create>

How to create router ./clientServer <anything> <{1,2, or 3} -> based on which host from the config file you want to create>
  
In the example below the router was created before the host. They are able to communicate populated UDP packets.
  
The send config file was alredy in the file system, but this is not necessary as our program will scan for it constantly (you can add the file while the host is running)
  
![image](https://user-images.githubusercontent.com/73619173/146284141-540857ee-5b23-43d5-aa75-8f03ec5294b4.png)

