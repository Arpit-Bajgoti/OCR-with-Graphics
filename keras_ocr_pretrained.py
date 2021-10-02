import keras_ocr
import os
import time
import pyautogui
from textblob import TextBlob

os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
pipeline = keras_ocr.pipeline.Pipeline()
while True:
    status_file = open("C:\TurboC4\TC\BIN\STAT.txt", "r")
    y = status_file.read()
    print(y)
    status_file.close()
    if y == '1':
        myScreenshot = pyautogui.screenshot()
        myScreenshot.save(r'C:\TurboC4\TC\Capture\image.jpg')
        print("Started reading from file")
        image = [keras_ocr.tools.read(img) for img in ["C:\TurboC4\TC\Capture\image.jpg"]]
        predict = pipeline.recognize(image)
        x = TextBlob(predict[0][0][0])
        x = str(x + " ")
        txt_file = open("C:\TurboC4\TC\BIN\PRED.txt", "a")
        txt_file.write(x)
        txt_file.close()
        status_file = open("C:\TurboC4\TC\BIN\STAT.txt", "w")
        status_file.write("0")
        status_file.close()
        print(x)
    else:
        time.sleep(2)
        print("Idle_State...")

