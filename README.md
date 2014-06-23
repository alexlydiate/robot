the Robot of Paradise
=====

A c++ roving robot project for Linux and Arduino
-----

This is the software for my ongoing mobile robot project.

My intent is to make a machine that can locate a person in a room, travel to them avoiding any obstacles and then identify them.

Don't ask me why.

The ./arduino directory contains the Arduino sketch which receives instruction from the main program, which can be found in the ./linux directory and built using Make.  I'm using a Raspberry Pi onboard my robot to run this - anything that can run Linux should be able to do it as long as it can hook up to the Arduino with USB.

Currently, this program provides remote keyboard control in a terminal, so you can SSH into the robot and drive it about to your heart's content.  Utilising OpenCV it can also autonomously track human faces using a tilt/pan servo set up with a Web cam strapped on and connected to the Linux box - in my case, the Raspberry Pi.

I'm going to put up a project page somewhere on the Web in due course, but in the meantime I'm noting the progress on [Google+](https://plus.google.com/u/0/+AlexLydiate/posts).

