_The app is written in Visual C++, using the OpenCV library ([OpenCV official website](http://opencv.org/))._ <br>
For the face detection process, the implementation of the Viola-Jones algorithm was being used.


This program uses the OpenCV library to detect faces present in an image. Paul Viola and Michael Jones presented an approach for object detection which minimizes computation time while achieving high detection accuracy. The approach was used to construct a face detection system which is approximately 15 faster than any previous approach.


The Viola-Jones detector is a strong, binary classifier build of several weak detectors.Each weak detector is an extremely simple binary classifier.
During the learning stage, a cascade of weak detectors is trained so as to gain the desired hit rate / miss rate (or precision / recall) using Adaboost To detect objects, the original image is partitioned in several rectangular patches, each of which is submitted to the cascade

If a rectangular image patch passes through all of the cascade stages, then it is classified as “positive” The process is repeated at different scales







![k1tpt](https://user-images.githubusercontent.com/32521929/31375991-fad4439a-adc0-11e7-9da6-147e93d544a7.png)

Actually, at a low level, the basic component of an object detector is just something required to say if a certain sub-region of the original image contains an istance of the object of interest or not. That is what a binary classifier does.
The basic, weak classifier is based on a very simple visual feature (those kind of features are often referred to as “Haar-like features”)





![ssxnc](https://user-images.githubusercontent.com/32521929/31376044-2f05030c-adc1-11e7-938a-d91cfceb21e9.png)









Haar-like features consist of a class of local features that are calculated by subtracting the sum of a subregion of the feature from the sum of the remaining region of the feature.









![diagt](https://user-images.githubusercontent.com/32521929/31376070-4faf56e8-adc1-11e7-9e17-04d546641070.png)








These feature are characterised by the fact that they are easy to calculate and with the use of an integral image, very efficient to calculate.

Lienhart introduced an extended set of twisted Haar-like feature (see image)











![r4k9g](https://user-images.githubusercontent.com/32521929/31376104-6c4bb49a-adc1-11e7-8bde-af7aac118ec0.png)

















These are the standard Haar-like feature that have been twisted by 45 degrees. Lienhart did not originally make use of the twisted checker board Haar-like feature (x2y2) since the diagonal elements that they represent can be simply represented using twisted features, however it is clear that a twisted version of this feature can also be implemented and used.

These twisted Haar-like features can also be fast and efficiently calculated using an integral image that has been twisted 45 degrees. The only implementation issue is that the twisted features must be rounded to integer values so that they are aligned with pixel boundaries. This process is similar to the rounding used when scaling a Haar-like feature for larger or smaller windows, however one difference is that for a 45 degrees twisted feature, the integer number of pixels used for the height and width of the feature mean that the diagonal coordinates of the pixel will be always on the same diagonal set of pixels.














![hbty8](https://user-images.githubusercontent.com/32521929/31376128-88aab47e-adc1-11e7-8e90-be78e837fba1.png)















This means that the number of different sized 45 degrees twisted features available is significantly reduced as compared to the standard vertically and horizontally aligned features.

So we have something like: 















![npgml](https://user-images.githubusercontent.com/32521929/31376173-ab2a683c-adc1-11e7-8713-af30ec75f1f1.png)
















About the formula, the Fast computation of Haar-like features using integral images looks like:















![v7x9c](https://user-images.githubusercontent.com/32521929/31376209-cb761618-adc1-11e7-9b3a-854c31d63e6b.png)
































Thus, the ViolaJones is implemented using c++ and face-detection is done.
