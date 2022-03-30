# Code to analyse electronics calibration data'

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160833984-beaed423-edce-4869-bea9-fea27fe15784.png" alt="peaks" width="400"/>
<img src="https://user-images.githubusercontent.com/34348134/160833988-9c7ec79e-3f7e-4bef-8c74-b20a5172f97f.png" alt="no_cut" width="400"/>

<figcaption align = "center"><b>Event display for electronics calibration and example of calibration peaks
for one pad.</b></figcaption>
</p>
</figure>


The algorithm goes trough each pad and finds if there is a calibration signal (yellow pads on the left picture, the calibration signal is shown on the right picture). In the pad with signal, the algorithm identifies each peak. We demand at least ten empty bins between the peaks and at least 100 events in the peak (this can be changed in config file, but I do not recommend to do it).The pedestal equal 250 is removed. Data after 3800 are not processed to remove the saturation peak. Each of the peaks is fitted with Gaussian distribution. Then, we plot the mean of each Gaussian distribution dependence on the number of peaks.

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160834742-80342905-c549-4655-b028-835aeff86058.png" alt="plot" width="700"/>
<figcaption align = "center"><b>Example of the calibration line.</b></figcaption>
</p>
</figure>
