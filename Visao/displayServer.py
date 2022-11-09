#!/usr/bin/env python3

import imageServer
import numpy as np
import cv2

host = '0.0.0.0'
src = imageServer.ImageTransferService()

# Check Redis is running
print(src.ping())

while True:
	im = src.receiveImage()
	cv2.imshow('Image',im)
	cv2.waitKey(1)
