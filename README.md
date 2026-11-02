# audio_visualizer_wireless_input
## Problem Background
The client is unsatisfied with their current living room lighting setup. They tried LED strips with constant white light and found them uninteresting. They also tried lights that cycle through colors and found them unreliable. To create a more appealing living room environment they have requested lights that are reactive to music.

## Constraints
- the power and control components of the system must not exeed 30cm x 30cm x 30cm so that it can be out of view
- the system lighting must be inconspicuous enough that it can stay installed without detracting from the living room's visual appeal
  
## Design requrements
- the design must be robust against background noise in the room
- the client must be able to operate the system without assistance

## Evaluation creteria
- visual appeal of lights
- number of different light settings
- total illuminated area

## Design Process
The most hard to meet requirement for this project is making the design robust against background noise. This consideration was used to evaluate the following design options for the method of inputting sound data to the light control algorithm.

### Microphone input
The most common approach to music-controlled light systems is using a microphone input for the light control agorithm. This approach runs the risk of ambient background noise degrading the audio signal from the speaker playing the audio. Due to this risk, this design option was avoided.

### Direct input
One way to avoid the signal integraty concerns of a microphone input is to directly input the audio signal originating from a laptop or smart phone directly into the light-control algorithm. This requires an audio signal to be transmitted both to a speaker and to a microcontroler responsible for contorlling the lights. 

- Wired input to speaker, wired input to microcontorller

- Wired input to speaker, wireless input to microcontroler
- Wireless input to speaker, wired input to microcontroller
- Wireless input to speaker, wierless input to microcontroller

