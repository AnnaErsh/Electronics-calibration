# Code to analyze electronics calibration data

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160833984-beaed423-edce-4869-bea9-fea27fe15784.png" alt="peaks" width="400"/>
<img src="https://user-images.githubusercontent.com/34348134/160833988-9c7ec79e-3f7e-4bef-8c74-b20a5172f97f.png" alt="no_cut" width="400"/>

<figcaption align = "center"><b>Event display for electronics calibration and example of calibration peaks
for one pad.</b></figcaption>
</p>
</figure>

The algorithm goes through each pad and finds if there is a calibration signal (yellow pads on the left picture, the calibration signal is shown on the right picture). In the pad with signal, the algorithm identifies each peak. We demand at least ten empty bins between the peaks and at least 100 events in the peak (this can be changed in the config file, but I do not recommend doing it). The pedestal equal to 250 is removed. Data after 3800 are not processed to remove the saturation peak. Each of the peaks is fitted with Gaussian distribution. Then, we plot the mean of each Gaussian distribution dependence on the number of peaks.

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160834742-80342905-c549-4655-b028-835aeff86058.png" alt="plot" width="700"/>
<figcaption align = "center"><b>Example of the calibration line.</b></figcaption>
</p>
</figure>

After all files are processed, the code will plot all calibration lines superimposed, histogram of the slope distribution, and map of slopes and intercepts.

<figure>
<p align="center">
<img src="https://user-images.githubusercontent.com/34348134/160835944-17121826-21ae-4c6d-942f-827ba3572688.png" alt="all" width="400"/>
<img src="https://user-images.githubusercontent.com/34348134/160836146-62650adc-a9cd-4e58-99d8-2195e9ee85a2.png" alt="p13" width="400"/>
<img src="https://user-images.githubusercontent.com/34348134/160835441-0a608053-4fa2-436a-aa3d-81b1f119aaf0.png" alt="p1" width="400"/>
<img src="https://user-images.githubusercontent.com/34348134/160835424-fe749fd3-68a5-4e09-a8d4-24228684d149.png" alt="p0" width="400"/>
<figcaption align = "center"><b>Example of the superimposed calibration lines, slope distribution, map of slopes and map of intersepts.</b></figcaption>
</p>
</figure>

## Getting started

Download the code:
```bash
git clone https://github.com/AnnaErsh/Electronics-calibration.git
```
Make sure the `run.sh` file has execution rights. In the `run.sh`, change `$installdir` variable to the location of this code, and `$file_path` variable to the location of the data that will be analyzed.

The algorithm needs some information about the input data to correctly identify the pad with the signal and the calibration peaks. 

### Parameters

| Parameter name | Possible arguments | Default value | Description |
|:--------------:|:------------------:|:-------------:|:-----------:|
| NPeaks | positive integer | 25 | The number of calibration peaks |
| MinNEvents | positive integer | 100 | The minimum number of events inside the peak required for its identification (use carefully) |
| MinNBins | positive integer | 10 | The minimum required number of empty bins between two peaks (use carefully)|
| NEvents | positive integer | 23990 | The number of events in the signal (actually, a bit less. Used to identify pad with the signal)|
| Cut | positive integer| 3800 | Satiration peak cut. ADC higher than cut is not processed. (better use default value)|
| ifPlotPeaks | bool| false | Flag if each calibration peak with its fit will be plotted separately|
| ext | string| pdf | Format of the produced plots (does not work for final plots for now)|

After setting all parameters to proper values, run the `run.sh` script.

## Results

The `run.sh` will create the tree of the directories with results, loop over data files to perform the calibration, and plot the final figures.

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
|   |-- separation
|   |   `-- macros
|   |-- all_lines.pdf
|   |-- p0_display_.pdf
|   |-- p1_display_.pdf
|   |-- p1_display_relative_.pdf
|   `-- p1_superimposed.pdf
`-- txt
    |-- file_names.txt
    |-- R2021_11_26-15_33_31-000.txt
    `-- ...
```

The `txt` folder contains the list of names of all txt files in this folder `file_names.txt` (needed for the code that prints final results) and `.txt` files with the name of corresponding the root file. These files contain slope, intercept, x and y coordinates of the calibration signal.

>   Example: \
h_1_7 -9.82779 163.686 1 7 \
h_1_15 -1.07458 164.187 1 15 \
h_7_19 -9.43648 165.307 7 19 \
h_7_27 0.75974 162.029 7 27 \
...

The `histograms` folder contains signal maps for each processed file (subfolder `ampl`, first figure on this page), calibration peaks (subfolder `peaks`, second figure), calibration lines (subfolder `lines`, third figure), and histograms of each found and fitted peak, if the `ifPlotPeaks` flag was turned on (subfolder `separation`). Each of these subfolders contains a `macros` folder with automatically generated ROOT macros of all these plots.

> The peaks histogram will not always look as nice as the example. Sometimes there will be a saturation peak.

The final results of the superimposed calibration lines and maps of slope and intercept are directly in the `histograms` folder.

>If you want to change the style of the output histograms, go to `src/Style.h`.

