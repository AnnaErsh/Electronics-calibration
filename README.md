# Code to analyse electronics calibration data'

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160833984-beaed423-edce-4869-bea9-fea27fe15784.png" alt="peaks" width="400"/>
<img src="https://user-images.githubusercontent.com/34348134/160833988-9c7ec79e-3f7e-4bef-8c74-b20a5172f97f.png" alt="no_cut" width="400"/>

<figcaption align = "center"><b>Fig.2: Event display for electronics calibration and example of calibration peaks
for one pad.</b></figcaption>
</p>
</figure>


The algorithm identifies each peak. We demand at least ten empty bins between the peaks and at least 100 events in the peak (this can be changed in config file, but I do not recommend to do it).The pedestal equal 250 is removed. Data after 3800 are not processed to remove the saturation peak. Each of the peaks is fitted with Gaussian distribution. Then, we plot the mean of each Gaussian distribution depending on the number of peaks

