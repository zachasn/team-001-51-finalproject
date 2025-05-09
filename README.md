# Team 001-51 Members

    Zachariah Hassan (hassa844) - Data Collection Manager
    Arnav Nayak (nayak086) - Shipping Priority
    Kyle Rumpza (rumpz020) - Ciphered Mail and Interception
    Michael VerBout (verbo032) - Severe Weather

# Overview

# Instructions

# Requirements

### Data Collection Manager:

* The Data Collection Manager shall track the number of packages each drone delivered.

* If an adversary drone successfully decrypts a classified package, The Data Collection Manager shall notify the user and update the number of packages lost to an adversary drone.

* The Data Collection Manager shall track the number of packages lost to an adversary drone.

* When a package is successfully delivered, The Data Collection Manager shall notify the user of the total distance traveled to deliver the package.

* When the user presses the "Export Data" button, the Data Collection Manager shall save the data to a csv file.

### Shipping Priority:

* The Shipping System shall let users pick a priority level (No Rush, Standard, or Expedited) for each package.

* The Shipping System shall keep a shipping list that shows all scheduled packages.

* The Shipping System shall show the shipping queue on the control panel with each package’s priority and delivery status.

* When a user schedules a new package, the Shipping System shall set its priority to Standard if no priority has been selected by the user.

* When a user changes a package’s priority, the Shipping System shall move the package to the right spot in the queue based on its new priority.

* When a package is picked up by a drone, the Shipping System shall lock the package’s priority so it can’t be changed.

* If a user tries to change a package’s priority after it’s picked up, then the Shipping System shall show an error message and keep the priority the same.

* If a user tries to schedule a package without picking a priority, then the Shipping System shall show an error message telling the user that the priority type is not selected and would automatically be set to Standard if the user clicks the Continue button.

* While a package is not picked up yet, the Shipping System shall allow users to change its priority.

* While a package is picked up but not delivered, the Shipping System shall show it in the queue with an “On the way” status.

* Where a detailed queue view is included, the Shipping System shall show extra details like package names and destinations in the queue on the control panel.

* While a package is in the queue and not picked up, if a user tries to set an invalid priority (anything not No Rush, Standard, or Expedited), then the Shipping System shall keep the old priority and show an error message.

* While notifications are included, When a new package is scheduled with Expedited priority, if there are already other Expedited packages, then the Shipping System shall place the new package at the end of the Expedited section.

### Ciphered Mail and Interception:

* The \<system\> shall \<ensure only one Sky Reaper drone exists\> 

* The \<system\> shall \<support multiple delivery drones operating at once\> 

* WHEN \<A new user creates an encrypted delivery\> the \<system\> shall \<allow them to select their encryption algorithm\> 

* WHEN \<Drone enters a Sky Reapers radius\> the \<system\> shall \<Have the Sky Reaper lock on to the Drone and moves towards it\> 

* WHEN \<Sky Reaper intercepts a Drone\> the \<system\> shall \<attempt to decrypt the package using brute-force\> 

* WHEN \<a Drone is in the same area as a Sky Reaper Drone\> the \<system\> shall \<ensure the drone doesn’t immediately take the package back\> 

* IF \<Sky Reaper Drone intercepts a Drone carrying a package\> \<brute-force cracking attempt is successful\> THEN the \<system\> shall \<confiscate the drone’s package (mail) and the delivery fails\> 

* IF \<Sky Reaper Drone intercepts a Drone carrying a package\> \<brute-force cracking attempt is unsuccessful\> THEN the \<system\> shall \<have the Sky Reaper drone disengage and the drone continues its delivery\> 

* WHILE \<the simulation is running\> the \<system\> shall \<continue to scan for nearby drones in a fixed radius\> 

* WHILE \<Sky Reaper drone is pursuing a Delivery\> the \<system\> shall \<not pursue another delivery drone\> 

* WHERE \<Encryption is enabled\> the \<system\> shall \<assign a specific probability to be cracked\> 

* WHILE \<Sky Reaper drone is pursuing a drone\> WHEN \<Sky Reaper Drone detects another drone within its fixed radius\> the \<system\> shall \<ensure the Sky Reaper drone continues to pursue the first drone only\> 

### Severe Weather:

* The WeatherControl (Singleton) shall accumulate/track time internally.

* The wind disturbances shall only be applied horizontally.

* When the accumulated delta time reaches or exceeds the update interval attribute, the wind will be updated.

* When each drone updates, the drone will have its position affected by the wind.

* When each drone is affected by the wind, the amount of displacement will be scaled by a factor determined by random noise.

* When the drone’s damage decorator’s time accumulation reaches or exceeds 1 second, the decorator shall apply damage logic to the drone, reducing its durability and speed.

* If the magnitude of the wind exceeds 200, it shall be adjusted accordingly such that its magnitude equals 200 instead.

* While the simulation is running there will only exist one instance of the weather control class.

* While the simulation is running the drones shall be wrapped in a Damage decorator. 

# Design

# Sprint Retrospective
 
# Jira Board

# UML

### Severe Weather
![Severe Weather UML Diagram](./images/SevereWeatherUML.png "Severe Weather UML")

# Docker

# Youtube Presentation