This is the README for the Capstone 2018/2019 Group 23 Wizards Chess [XinC2] project.

Authors for this project include David Gingles, Sebastian Aravena, and Matthew Vandermeer

The code is designed for A Raspberry Pi 3 with the 
speech-recognition(https://pypi.org/project/SpeechRecognition/) 
library installed with pocketsphinx on python2 along with an 
ElevenEngineering XInC2 dev board. It is likely that another 
processor could substitute for the XInC or the entire project 
could be run from the Raspberry Pi

this code can be considered final and working but not finished
due to time constraints

in order for the speech recongnition to work properly the 
following changes will have to be made:
/home/pi/.local/lib/python2.7/site-packages/speech_recognition/pocketsphinx-data/en-US
- add .lm and .dic files
In ~/speech_recognition change init.py to reflect changes

There is code gathered from other sources, any borrowed code 
has had the header comments left intact

I'm probably forgetting something but this is the final change 
I'm making to the repo
