import cv2
import numpy as np
import RPi.GPIO as GPIO
import time

millis = lambda: int(round(time.time() * 1000))

def getImage(_camera):
	ret, image = _camera.read()

	while(not ret):
		ret, image = _camera.read()
		print("GAH!\n")

	#cv2.imwrite('./imgs/0src.png', image)
	return image

def showImage(_image):
	maxT = 5
	# Display output image
	cv2.imshow('image',_image)

	# Wait longer to prevent freeze for videos.
	tnow=millis()
	while(True):
		if (cv2.waitKey(33) & 0xFF == ord('q')) or millis()-tnow > maxT:
			break

def nothing(x):
	pass

def test(_camera):
	image = getImage(_camera)

	# Create a window
	cv2.namedWindow('image')
	cv2.namedWindow('track')

	boundaries = [
		([17, 15, 100], [50, 56, 200]),
		([86, 31, 4], [220, 88, 50]),
		([25, 146, 190], [62, 174, 250]),
		([103, 86, 65], [145, 133, 128])
	]

	# create trackbars for color change
	cv2.createTrackbar('HMin','track',0,179,nothing) # Hue is from 0-179 for Opencv
	cv2.createTrackbar('SMin','track',0,255,nothing)
	cv2.createTrackbar('VMin','track',0,255,nothing)
	cv2.createTrackbar('HMax','track',0,179,nothing)
	cv2.createTrackbar('SMax','track',0,255,nothing)
	cv2.createTrackbar('VMax','track',0,255,nothing)

	# Set default value for MAX HSV trackbars.
	cv2.setTrackbarPos('HMax', 'track', 179)
	cv2.setTrackbarPos('SMax', 'track', 255)
	cv2.setTrackbarPos('VMax', 'track', 255)

	# Initialize to check if HSV min/max value changes
	hMin = sMin = vMin = hMax = sMax = vMax = 0
	phMin = psMin = pvMin = phMax = psMax = pvMax = 0

	output = image
	wait_time = 33

	while(1):
		image = getImage(_camera)
		# get current positions of all trackbars
		hMin = cv2.getTrackbarPos('HMin','track')
		sMin = cv2.getTrackbarPos('SMin','track')
		vMin = cv2.getTrackbarPos('VMin','track')

		hMax = cv2.getTrackbarPos('HMax','track')
		sMax = cv2.getTrackbarPos('SMax','track')
		vMax = cv2.getTrackbarPos('VMax','track')

		# Set minimum and max HSV values to display
		lower = np.array([hMin, sMin, vMin])
		upper = np.array([hMax, sMax, vMax])

		# Create HSV Image and threshold into a range.
		hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
		mask = cv2.inRange(hsv, lower, upper)
		output = cv2.bitwise_and(image,image, mask= mask)

		# Print if there is a change in HSV value
		if( (phMin != hMin) | (psMin != sMin) | (pvMin != vMin) | (phMax != hMax) | (psMax != sMax) | (pvMax != vMax) ):
			print("(hMin = %d , sMin = %d, vMin = %d), (hMax = %d , sMax = %d, vMax = %d)" % (hMin , sMin , vMin, hMax, sMax , vMax))
			phMin = hMin
			psMin = sMin
			pvMin = vMin
			phMax = hMax
			psMax = sMax
			pvMax = vMax

		# Display output image
		cv2.imshow('image',output)

		# Wait longer to prevent freeze for videos.
		if cv2.waitKey(wait_time) & 0xFF == ord('q'):
			break

	cv2.destroyAllWindows()

def findCone(_imageSrc):
	lowThres = (0, 99, 150)
	highThres = (21,215,255)
	kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))

	hsvImg = cv2.cvtColor(_imageSrc, cv2.COLOR_BGR2HSV)
	thres = cv2.inRange(hsvImg, lowThres, highThres)

	erodedImg = cv2.erode(thres, kernel)
	kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (8,8))
	dilatedImg = cv2.dilate(erodedImg, kernel)
	blurred = cv2.GaussianBlur(dilatedImg, (3,3), 0)
	total = cv2.countNonZero(blurred)

	#print(cv2.__version__[0])
	im, contours, hie = cv2.findContours(blurred, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

	c = None
	if len(contours) != 0:
		c = max(contours, key = cv2.contourArea)
		x,y,w,h = cv2.boundingRect(c)
		#print(x,y)
		cv2.rectangle(blurred, (x,y), (x+w,y+h), (0,255,0),2)
	else:
		print("nonono")

	if(c is not None):
		moments = cv2.moments(c, True)
	else:
		moments = cv2.moments(blurred, True)
	#print("MOMENTS:")
	#print(moments["m10"], moments["m00"])
	num_columns = np.shape(_imageSrc)[1]
	showImage(blurred)
	if(num_columns == 0 or moments["m00"] == 0):
            print("ZERO")
            return 0
	
	return (moments["m10"]/moments["m00"])/num_columns


GPIO.setmode(GPIO.BOARD)
GPIO.setup(16, GPIO.OUT)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(36, GPIO.OUT)
GPIO.setup(38, GPIO.OUT)
GPIO.setup(40, GPIO.OUT)

# camera = cv2.VideoCapture(2)

cams_test = 100
for i in range(-1, cams_test):
    camera = cv2.VideoCapture(i)
    test, frame = camera.read()
    print("i : "+str(i) + "// result: "+ str(test))
    if test:
        print("SUCCESSFULL!")
        break
if not camera.isOpened():
	print("Buh\n")
	exit()

#test(camera)
for x in range(40):
	image = getImage(camera)

while(True):
	res = findCone(getImage(camera))

	#print(res, end="\r")
	res -= 1
	res *= -1
	if(res > 1): res = 1
	if(res < 0): res = 0
	res *= 180
	res = int(res)
	print("\033[F\033[F\033[J")
	print(res)
    
	GPIO.output(16, (res & (1 << 0)) >> 0)
	GPIO.output(18, (res & (1 << 1)) >> 1)
	GPIO.output(22, (res & (1 << 2)) >> 2)
	GPIO.output(24, (res & (1 << 3)) >> 3)
	GPIO.output(36, (res & (1 << 3)) >> 3)
	GPIO.output(38, (res & (1 << 3)) >> 3)
	GPIO.output(40, (res & (1 << 3)) >> 3)


""""
float findCone(Mat img_original, float* accuracy)
{
  Mat img_hsv, dilated, eroded, frame_threshold;
  cvtColor(img_original, img_hsv, CV_BGR2HSV);
  inRange(img_hsv, Scalar(0, 38, 222), Scalar(15, 255, 255), frame_threshold);
  erode(frame_threshold, dilated, getStructuringElement(MORPH_RECT, Size(5, 5)));
  dilate(dilated, eroded, getStructuringElement(MORPH_RECT, Size(8, 8)));
  GaussianBlur(eroded, eroded, Size(3, 3), 0);
  int count = countNonZero(eroded);
  *accuracy = ( (float) count/(float)(eroded.cols * eroded.rows))*100.0;

  Moments m = moments(eroded,true);

  return 50-100*((m.m10/m.m00)/img_original.cols);
}

void* vision_thread(void* args)
{
  int key;
  Mat img_hsv, dilated, eroded ,img_original, frame_threshold;
 img_original = imread("./"+String(argv[1]),IMREAD_COLOR);

  visonArgs* vision_arguments = (visionArgs*) args;
  float* accuracy = (float*) vision_arguments->vis_accuracy;
  float* direction = (float*) vision_arguments->vis_direction;

  direction = findCone(img_original, &accuracy);
//   cout<<"dir: "<<direction<<endl;
//   cout<<"acc: "<<accuracy<<endl;
  waitKey(0);
  return 0;
}"""


