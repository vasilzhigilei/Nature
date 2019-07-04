Nature
===============
A basic project to help me learn C++. Deer consume trees and multiply past carrying capacity.

Deer color corresponds to deer health, brighter red is a healthier, younger deer, while darker deer are hungry and/or older. After a certain age, deer find other mate-worthy deer to reproduce with. Mate-worthyness is dependent on health, a combination of age and hunger levels.

Trees mature and spawn saplings around them until they die of old age.

![Version 2.0 screenshot](https://github.com/vasilzhigilei/Nature/blob/master/nature_ver2.PNG)
###### *[Version 2.0 simulation in the early stages of the run]*

History
-------

##### Version 2.0 (4 July, 2019)
* Complete overhaul of logic systems
* Introduction of priorities and "targets" for deer decision making and movement
* Creation of the Eukaryote class, all other classes (Deer, Tree) derived from it
* Tree spawning improved, trees grow in size and have maturity logic
* Deer don't always have to keep eating and reproducing, may run around if conditions allow
* Deer attempt to avoid collisions and overlapping with one another (more for visual purposes)

##### Version 1.0 (12 June, 2019)
* Initial commit of basic deer/tree functionality and simulation
