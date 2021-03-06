# ESP32 motor control over the Internet
How to run a motor in both directions with a web user interface

See https://www.sabulo.com/sb/3d-printing-2/the-donald-duck-hypnotizing-machine-with-iot/ for details on how to build this.

The required parts are

* L298H bridge: https://www.ebay.com/itm/New-L298N-DC-Stepper-Motor-Driver-Module-Dual-H-Bridge-Control-Board-for-Arduino/202147507453?hash=item2f10ee2cfd:g:UvkAAOSwwE5WYWZ8
* DC motor with or without gears, for example  https://www.ebay.com/itm/Gear-Motor-For-Arduino-Intelligent-Car-Gear-Motor-TT-Motor-Robot-DC-3V-6V-1-48-/381607363504
* access to PHP web server for the user interface
* an ESP32 SoC, such as https://www.ebay.com/itm/Espressif-ESP32-WLAN-Dev-Kit-Board-Development-Bluetooth-Wifi-v1-WROOM32-NodeMCU/253059783728?hash=item3aeb89dc30:g:5-8AAOSwAThb3MaZ
* 9V battery

The system consists of one C language INO file, which is to be edited for your network access parts, and a PHP application with four files. 

The ESP32 is connected to a 9V battery and to the DC motor via the L298H bridge. The battery is also wired to the bridge. 

This is the connection scheme, but the Arduino Micro is just a placeholder - Fritzing doesn't have ESP32 yet.

![connection scheme](donald%20scheme.PNG)

On the website, there is a folder called speed, and in it, the file index.php, and a style sheet. The file creates this user interface:

![user interface](speed%20control.PNG)

Every time you click on the buttons, the system changes the contents of the file speedcontrol.txt and as the ESP32 is set to read the file twice a second, its speed changes according to the value in the file.

Click the image for video.

[![Watch the video](Capture.PNG)](https://www.youtube.com/watch?v=sizY2kcHO2Y)


