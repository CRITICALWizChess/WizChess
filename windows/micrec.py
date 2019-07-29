import speech_recognition as sr

# obtain audio from the microphone
r = sr.Recognizer()
with sr.Microphone(device_index=1) as source:
    print("Listening")
    audio = r.listen(source)

# recognize speech using Sphinx
try:
    print(r.recognize_sphinx(audio))
except sr.UnknownValueError:
    print("Sphinx could not understand audio")
except sr.RequestError as e:
    print("Sphinx error; {0}".format(e))
