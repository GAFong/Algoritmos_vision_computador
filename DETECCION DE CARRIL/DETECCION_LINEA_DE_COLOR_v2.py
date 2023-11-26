# DETECCION DE LINEA

import sensor, image, time, math, pyb, json,mjpeg
from pyb import UART

#UART
uart = UART(3, 115200, timeout_char=1000) # RX P5, TX P4
uart.init(115200, bits=8, parity=None, stop=1, timeout_char=1000)

#CONFIGURACIONES
###############################################################################
COLOR_LINE_FOLLOWING = True # False para escala de grises, True para color
COLOR_THRESHOLDS = [( 94, 100,  -27,    1,   20,  127)] # LINEA AMARILLA
GRAYSCALE_THRESHOLDS = [(240, 255)] # LINEA BLANCA
COLOR_HIGH_LIGHT_THRESHOLDS = [(80, 100, -10, 10, -10, 10)]
GRAYSCALE_HIGH_LIGHT_THRESHOLDS = [(250, 255)]
BINARY_VIEW = False
DO_NOTHING = False # Solo para capturar frames
FRAME_SIZE = sensor.QQVGA # 160x120
FRAME_REGION = 0.75 # (0 - 1.0).
FRAME_WIDE = 1.0

AREA_THRESHOLD = 16 # Aumentar para falsas detecciones
PIXELS_THRESHOLD = 16 # Aumentar para falsas detecciones de pixeles
MAG_THRESHOLD = 10 #  Aumentar para falsas detecciones
MIXING_RATE = 0.2

#SETUP
###############################################################################
FRAME_REGION = max(min(FRAME_REGION, 1.0), 0.0)
FRAME_WIDE = max(min(FRAME_WIDE, 1.0), 0.0)
MIXING_RATE = max(min(MIXING_RATE, 1.0), 0.0)
device = None


# HAAR CASCADE
#########################################################################################
# By default this will use all stages, lower satges is faster but less accurate.
face_cascade = image.HaarCascade("stop.cascade", stages=25)
a = 0

#CAMARA SETUP

sensor.reset()
sensor.set_pixformat(sensor.RGB565 if COLOR_LINE_FOLLOWING else sensor.GRAYSCALE)
sensor.set_framesize(FRAME_SIZE)
sensor.set_vflip(False)
sensor.set_hmirror(False)
#sensor.set_windowing((int((sensor.width() / 2) - ((sensor.width() / 2) * FRAME_WIDE)), int(sensor.height() * (1.0 - FRAME_REGION)), \
#                     int((sensor.width() / 2) + ((sensor.width() / 2) * FRAME_WIDE)), int(sensor.height() * FRAME_REGION)))
sensor.skip_frames(time = 200)
if COLOR_LINE_FOLLOWING: sensor.set_auto_gain(False)
if COLOR_LINE_FOLLOWING: sensor.set_auto_whitebal(False)
clock = time.clock()
old_time = pyb.millis()

#ENCENDER LED EN BLANCO
RED_LED_PIN = 1
GREEN_LED_PIN = 2
BLUE_LED_PIN = 3
#pyb.LED(RED_LED_PIN).on()
#pyb.LED(GREEN_LED_PIN).on()
#pyb.LED(BLUE_LED_PIN).on()


#m = mjpeg.Mjpeg("video.mjpeg")

while(True):
    clock.tick()
    img = sensor.snapshot()
    #img.binary(COLOR_HIGH_LIGHT_THRESHOLDS if COLOR_LINE_FOLLOWING else GRAYSCALE_HIGH_LIGHT_THRESHOLDS, zero = True)
    img.histeq()

    if BINARY_VIEW: img = img.binary(COLOR_THRESHOLDS if COLOR_LINE_FOLLOWING else GRAYSCALE_THRESHOLDS)
    if BINARY_VIEW: img.erode(1, threshold = 5).dilate(1, threshold = 1)
    if DO_NOTHING: continue

    #m.add_frame(sensor.snapshot())
    # We call get regression below to get a robust linear regression of the field of view.
    # This returns a line object which we can use to steer the robocar.
    line = img.get_regression(([(50, 100, -128, 127, -128, 127)] if BINARY_VIEW else COLOR_THRESHOLDS) if COLOR_LINE_FOLLOWING \
        else ([(127, 255)] if BINARY_VIEW else GRAYSCALE_THRESHOLDS), \
        area_threshold = AREA_THRESHOLD, pixels_threshold = PIXELS_THRESHOLD, \
        robust = True)



        # Find objects.
        # Note: Lower scale factor scales-down the image more and detects smaller objects.
        # Higher threshold results in a higher detection rate, with more false positives.
    objects = img.find_features(face_cascade, threshold=0.4, scale_factor=1.15)

        # Draw objects
    for r in objects:
        img.draw_rectangle(r)
        a = a+1
        print(a)
        print("stop")

    print_string = ""
    if line and (line.magnitude() >= MAG_THRESHOLD):
        img.draw_line(line.line(), color = (255, 0, 0) if COLOR_LINE_FOLLOWING else 127)

        new_time = pyb.millis()
        delta_time = new_time - old_time
        old_time = new_time

        cy = img.height() / 2
        cx = (line.rho() - (cy * math.sin(math.radians(line.theta()))))/math.cos(math.radians(line.theta()))

        cx_middle = cx - (img.width() / 2)
        cx_normal = cx_middle / (img.width() / 2)
        data = {
                "theta": line.theta(),  # Valor del primer sensor
                "rho": line.rho()  # Valor del segundo sensor
            }

        # Serializa el objeto JSON a una cadena
        json_str = json.dumps(data)

        # Envía la cadena a través de UART
        uart.write(json_str + '\n')
        print(json_str)


        #print_string = "Stop %d Line Ok -, normal %f - line t: %d, r: %d" % \
            #(a, cx_normal, line.theta(), line.rho())

    else:
        print_string = "Stop %d Line Lost - " % (a )


    print("FPS %f - %s" % (clock.fps(), print_string))


