# weatherballoon
AERSP 440 - Aerospace Software Engineering project

This project was developed in AERSP 440 - Aerospace Software Engineering at Penn State University.  The code in this project is built to run autonomously with the given hardware.  This flight software was written using object-oriented programming in C++ and the user interface was developed using a browser and was written using PHP, HTML, and CSS.  Aside from running autonomously, the user interface also allows certain functionalities of the flight software to be overwritten and performed manually.

The objectives of this project were to collect pressure, temperature, latitude, longitude, and altitude data every 5 seconds as well as take, collect, and display onboard pictures every 10 seconds.  In addition the surveillance package was to drop a red ribbon at 1000 feet AGL, drop a black and white ribbon at 2000 feet AGL, and separate from the weather balloon at 3000 feet AGL.  Finally, the data was to be taken from the package after retrieval.

The package communicated with the ground station using Wi-Fi Point-to-Point communication.  This communication method was how the user interface retrieved data from the package.
