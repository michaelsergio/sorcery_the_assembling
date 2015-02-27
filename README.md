MTG
============

The following layers are used.


Layout Identifier
------------------
A fast table layout identifier layer that returns squares [and stacks].
This outputs layout change events.

Card Identifier Layer.
--------------------------------
Uses phash to identify the proper card.
Reports <identity> <change_event> as an event.
(Need a simple event system to make this work.)


Layout Model
----------------
This implements a generic model for keeping track of objects on a table.
Their is no custom logic here.

MTG model
----------------
This is a scripting layer on top of the basic system.
This needs time and a state engine to function.
This needs to track whats going on and generate events.
Example: If Wrath of God appears, within 10 seconds of WoG being played or
being removed any creature x that is removed should call the x.destroy() event.


Rendering engine
-------------------------
I should be able to do 3d render of whats going on.
There can be many of these.
Send events via message socket.

Event system.
===============
I can roll my own or I could use dbus in some kind of private mode,
Boost Signals 2 gives me an observer pattern.

