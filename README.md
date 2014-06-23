the Robot of Paradise
=====

A c++ roving robot project for Linux and Arduino
-----

This is the software for my ongoing mobile robot project.

My intent is to make a machine that can locate a person in a room, travel to them avoiding any obstacles and then identify them.

Don't ask me why.

The ./arduino directory contains the Arduino sketch which receives instruction from the main program, which can be found in the ./linux directory and built using Make.  I'm using a Raspberry Pi onboard my robot to run this - anything that can run Linux should be able to do it as long as it can hook up to the Arduino with USB.

Currently, this program provides remote keyboard control in a terminal, so you can SSH into the robot and drive it about to your heart's content.  The keyboard mappings can be found and set in settings.h.

It can also autonomously identify and target human faces using a tilt/pan servo set up with a Web cam strapped on and connected to the Linux box - in my case, the Raspberry Pi.

The next phases of development of the software will be 

1. **Integrating sensors** - I have two sonar modules and three PIRs to play with.
2. **Manual Driving** via Intrumentation Alone - I figure, if I am ever going to give the beast enough intelligence to complete the mission I had better have at least the same amount myself.
3. **Autonomous Control** - which is the really fun bit :)

I've a bunch of hardware and system hurdles to jump, too, and I'll chat about them on
a project page somewhere on the Web that I'll put up in due course; in the meantime I'm noting the progress on [Google+](https://plus.google.com/u/0/+AlexLydiate/posts).

