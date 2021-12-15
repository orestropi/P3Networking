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


final:
Firstly, our routers can accurately talk to each other. We went to Craig's office hours and after half an hour of bug fixing we couldn't get our routers to send packets to the RIGHT person, they correctly send it to the WRONG person. He told us to roll with it and move on to other parts of the project because it was likely a very very small logic error causing the problems in routing pull. Table setting and table pulling are fine when reading the config, but not when sending. Just a quirk of the code.
