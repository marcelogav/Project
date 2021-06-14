Project option 3: A leader yellow Robot being followed by many little blue robots.

This project was developed using Enviro. To initiate the project, using the image from Prof Klavins, and then in the docker environment:

make
enviro

USING THE PROJECT

Leader:
Leader movement starts autonomously. It was planned to use 3 field sensors and once it identifies a blocking ahead, he would decide to turn left or right based on the most available space among the two options.

If you click in any space open in the screen, the Leader will be immediately moved to that position, with the direction in the opposed way before the click.


Follower(s):
Followers will be activated individually.
Go and click in the blue robot you want to follow the leader.
Followers will have a velocity proportional to the distance to the leader. For example, click in a follower just after leader departure, and clieck another follower few seconds later. Second follower will move faster to catch up at the beginning of the run.
Finally, followers will keep a safe distance from the leader, and will try to avoid collisions among themselves as well, but most of the time, not possible to avoid. :-)


If Robots get stuck, just click on screen to redefine the leader position, or, you can also re-start by re-instantiate enviro in the docker container.