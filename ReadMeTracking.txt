To start streaming video cliclk "Play".
Now You have several posibilities:
->You can choose Mode 1 - check a checkBox - and next click on  arbitrary  pixel on a video
	Your pixel will be now tracked.
-> chooding Mode 2- Porgram automatically  try to find the most distinctive  color
	and track it;
-> You can use both modes at the same time or non of them;
-> When You choose one of the modes, a Homogrpahy is computed, and then  focal dimensions too;
	It enables to compute a  pitch and yaw angle of a ray between camera focal point and 3D point
	Focal dimensions are  evaluated  when a tracked object was selected. This process is  computed 
	when one of the modes is choosen for the first time;
-> You can also  save  a video with a deafult name. Remember, that You can only save  video, when  it 
	is streaming;
-> if You want to once again choose  a color or try to find  most distinctive pixel- just  uncheck checkBoxes.

Files:

main.cpp -  main file which start the program
mainwindow.ui - graphical interface of the main window,
mainwinodw.h -  file of main window, that contain all all methods of the window 
methods3d.h - file  gives possibilities to   compute 3d realted  features
player.h -  play/save vide and  find a most distinctive pixel and follow it drawing circle around
trackingmethods.h - gives  differen posiibilities to track  objects		
ShowVideo.pro - file contain all dependencies
