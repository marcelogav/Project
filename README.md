# Project
Final Project for course EE P 520 - Spring 2021

OVERVIEW

Project option 3: A leader yellow Robot being followed by many little blue robots.

CHALLENGES

1- Leader robot should move in an infinite loop and be able to overcome all obstacles, using the field sensors and taking the right decision to move left or right according to most available space in the 2 option. Physics aspects were very difficult to understand and control. I did not find the model used in Enviro that could explain how to associate friction parameters, with force/torque and resultant vectorial velocity. My implementation is not working completelly well.

2 - Using sensors were particularly challenge as they seems to be not being updated fast enough for the if/else logic I've tried to implement originally. The random movements are also another factor to increase complex of the solution. We tried to avoid collisions by defining security distances using sensors, but this was not really efficient all the time.

INSTALLATION

This project was developed using Enviro. To compile the code using the docker image from Prof Klavins, please copy the code in your local folder and run the following command to instantiate the docker environment:

            docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash

Then, from the container you will be able to compile the code using the follow command lines:

            make
            enviro


USING THE PROJECT

Leader:

Leader movement starts autonomously. It was planned to use 3 field sensors and once it identifies a blocking ahead, he would decide to turn left or right based on the most available space among the two options.
If you click in any space open in the screen, the Leader will be immediately moved to that position, with the new direction in the opposed way before the click.

Follower(s):

Followers will be activated individually.
Go and click in the blue robot you want to follow the leader.
Followers will have a velocity proportional to the distance to the leader. For example, click in a follower just after leader departure, and click another follower few seconds later. Second follower will move faster to catch up at the beginning of the run.
Finally, followers will keep a safe distance from the leader, and will try to avoid collisions among themselves as well, but most of the time, not possible to avoid. :-)

If Robots get stuck, just click on screen to redefine the leader position, or, you can also re-start by re-instantiate Enviro in the docker container.
 
