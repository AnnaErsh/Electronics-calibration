# Code to analyse electronics calibration data

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

After all files are processed, the code will plot all calibration lines superimposed, histogram of the slope distribution and map of slopes and intersepts.

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160835944-17121826-21ae-4c6d-942f-827ba3572688.png" alt="all" width="240"/>
<img src="https://user-images.githubusercontent.com/34348134/160836146-62650adc-a9cd-4e58-99d8-2195e9ee85a2.png" alt="p13" width="240"/>
<img src="https://user-images.githubusercontent.com/34348134/160835424-fe749fd3-68a5-4e09-a8d4-24228684d149.png" alt="p0" width="240"/>
<img src="https://user-images.githubusercontent.com/34348134/160835441-0a608053-4fa2-436a-aa3d-81b1f119aaf0.png" alt="p1" width="240"/>
<figcaption align = "center"><b>Example of the superimposed calibration lines, slope distribution, map of slopes and map of intersepts.</b></figcaption>
</p>
</figure>

## Getting started

Download the code:
```bash
git clone https://github.com/AnnaErsh/Electronics-calibration.git
```
Make sure `run.sh` file has execution rights. In the `run.sh`, change `$installdir` variable to the location of this code, and `$file_path` variable to the location of the data that will be analyzed.

The algorithm needs some information about the input data in order to identify pad with the signal and the calibration peaks correctly. 

### Parameters

| Parameter name | Possible arguments | Default value | Description |
|:--------------:|:------------------:|:-------------:|:-----------:|
| NPeaks | positive integer | 25 | The number of calibration peaks |
| MinNEvents | positive integer | 100 | The minimum number of events inside the peak, required for its identification (use carefully) |
| MinNBins | positive integer | 10 | The minimum required number of empty bins between two peaks (use carefully)|
| NEvents | positive integer | 23990 | Number of events in the signal (actually, a bit less. Used to identify pad with the signal)|
| ifPlotPeaks | bool| false | Flag if each calibration peak with its fit will be plotted separately|
| ext | string| pdf | Format of the produced plots|

After setting all parameters to proper values, run the `run.sh` script.

## Results

The `run.sh` will create the tree of the directories with results, loop over data files to perform the calibration and plot the final figures.

Here is the file structure of the results:
```
results/
|-- histograms
|   |-- ampl
|   |   |-- macros
|   |   |   |-- h_ampl_R2021_11_26-15_33_31-000.C
|   |   |   `-- ...
|   |   |-- h_ampl_R2021_11_26-15_33_31-000.pdf
|   |   `-- ...
|   |-- lines
|   |   |-- macros
|   |   |   |-- line_h_9_4_R2021_11_26-16_23_35-000.C
|   |   |   `-- ...
|   |   |-- line_h_0_14_R2021_11_26-17_26_14-000.pdf
|   |   `-- ...
|   |-- peaks
|   |   |-- macros
|   |   |   |-- h_9_4_R2021_11_26-16_23_35-000.C
|   |   |   `-- ...
|   |   |-- h_19_14_R2021_11_26-17_19_58-000.pdf
|   |   `-- ...
|   `-- separation
|       `-- macros
`-- txt
    |-- file_names.txt
    |-- R2021_11_26-15_33_31-000.txt
    `-- ...
```

In the `txt` folder contains the list of names of all txt files in this folder `file_names.txt` (needed for the code that prints final results) and `.txt` files with the name of corresponding the root file. These files contain slope, intercept, x and y coordinates of the calibration signal.

!!! note "Example"
    h_1_7 -9.82779 163.686 1 7
    h_1_15 -1.07458 164.187 1 15
    h_7_19 -9.43648 165.307 7 19
    h_7_27 0.75974 162.029 7 27
    h_10_4 -2.1209 162.573 10 4
    h_10_12 4.97333 164.164 10 12
    h_16_16 0.554809 162.855 16 16
    h_16_24 20.5307 166.844 16 24
    h_19_7 -19.5769 163.54 19 7
    h_19_15 -3.28134 162.082 19 15
    h_25_19 1.91749 160.654 25 19
    h_25_27 -14.4817 164.907 25 27
    h_28_4 -11.2452 162.291 28 4
    h_28_12 7.57043 163.039 28 12
    h_34_16 0.4478 157.718 34 16
    h_34_24 -6.80059 162.099 34 24


