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
| ext | string| pdf | Format of the produced plots|

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


# Better Poster Latex Template

The **Better Poster** is [Mike Morrison](https://twitter.com/mikemorrison)'s response to the traditional academic poster. In his own words:
> Every field in science uses the same, old, wall-of-text poster design. If we can improve the knowledge transfer efficiency of that design even by a little bit, it could have massive ripple effects on all of science.
> 
> Also, poster sessions tend to suck, so here's my pitch to make them more efficient AND more fun with a new approach to designing scientific posters/academic posters that is both more usable, and easier to create!

 - If you want to learn more about the reasons behind the design and how it improves upon more typical academic poster templates, I recommend Mike's [video](https://www.youtube.com/watch?v=1RwJbhkCA58&feature=youtu.be).
 - If you want to see how people are using the Better Poster design, see [#betterposter](https://twitter.com/hashtag/betterposter?src=hash) on twitter.
 - If you want the original PowerPoint template, you can find it [here](https://t.co/6WRGQK63g6).
 - If you want to start using the LaTeX template instead, download the repository and keep reading!

<kbd>
<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/example.png" width="600px" />
</kbd>

## Documentation
The template has been implemented as a LaTeX class, `betterposter.cls`. You can load it into your `tex` file by using the command
```
\documentclass{betterposter}
```

### The `\betterposter` command

The main command provided by the `betterposter` class is `\betterposter`. The command takes three arguments: the content of the central, left and right columns, respectively. You type  the content in, and the command takes care of the formatting.
```
\betterposter{
% content of the main column
}{
% content of the left column
}{
% content of the right column
}
```

### The `\maincolumn` command

The `\maincolumn` command takes care of the formatting of the main column. It takes two arguments: the content of the main section (for the main point of the poster), and the content of the bottom section (destined for the QR code).
```
\maincolumn{
% main point of the poster
}{
% QR code
}
```

### The `\qrcode` command

The `\qrcode` command formats the QR code for the poster. It takes three arguments: the path for the QR code image, the path for a small icon (a smartphone by default), and the caption ("Take a picture to download the full paper" by default).
```
\qrcode{path/to/image}{path/to/icon}{
% caption
}
```

<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/doc/qrwithcaption.png" height="200px" />

Alternatively, the `\compactqrcode` command renders a more compact link by omitting the small icon.
```
\compactqrcode{path/to/image}{
% caption
}
```

<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/doc/compactqrwithcaption.png" height="200px" />

#### Generating QR Codes

You should include a QR code that links to a relevant document which complements the poster (your paper, a website containing simulations or data...) There are many free QR code tools available, I have used [www.qr-code-generator.com](https://www.qr-code-generator.com/).

The example included in the template points to this repository:

<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/doc/qrcode.png" height="200px" />

You can also create QR codes which contain a logo:

<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/doc/qrcodeARXIV.png" height="200px" />

### Class Options

The `betterposter` class accepts three options which change the paper size:
 - `a0paper`, for A0, the default size.
 - `a1paper`, for A1.
 - `a2paper`, for A2.

These options behave like the usual LaTeX class options, for instance:
```
\documentclass[a0paper]{betterposter}
```
#### Other Class Options
The `betterposter` class extends the basic `article` class. Any options you give `betterposter`, other than the ones mentioned above, will be passed directly to `article`. For instance,
```
\documentclass[a0paper,fleqn]{betterposter}
```
will let `betterposter` deal with the `a0paper` option, but will pass `fleqn` directly to `article`.

### Custom Formatting Options
These commands should be placed before `\begin{document}`.

#### Column Width
You can customise the width of the columns:
 - The left column, `\setlength{\leftbarwidth}{value}`.
 - The right column, `\setlength{\rightbarwidth}{value}`.
 - The main column automatically resizes to the rest of the space available.

#### Column Margins
You can change the margins of the columns:
 - The vertical margin of the side columns, `\setlength{\columnmarginvertical}{value}`.
 - The horizontal margin of the side columns, `\setlength{\columnmarginhorizontal}{value}`.
 - The vertical margin of the side columns, `\setlength{\maincolumnmarginvertical}{value}`.
 - The horizontal margin of the side columns, `\setlength{\maincolumnmarginhorizontal}{value}`.

#### Font Sizes
The `\fontsize` command takes two arguments, the `size` (the size of the font in `pt`) and the `baselineskip` (usually you want `baselineskip` to be roughly 1.25 times the `size`.

You can change specific font sizes:
 - The text font, `\renewcommand{\fontsizestandard}{\fontsize{28}{35} \selectfont}`.
 - The main column font, `\renewcommand{\fontsizemain}{\fontsize{28}{35} \selectfont}`.
 - The title font, `\renewcommand{\fontsizetitle}{\fontsize{28}{35} \selectfont}`.
 - The author font, `\renewcommand{\fontsizeauthor}{\fontsize{28}{35} \selectfont}`.
 - The section font, `\renewcommand{\fontsizesection}{\fontsize{28}{35} \selectfont}`.

Additionally, you can change the font size of a specific text segment by placing the text in brackets as:
```
{\fontsize{28}{35} \selectfont Your text goes here}
```

#### Colours

The class defines the theme colours of the original design:
 - `empirical`: ![#f03c15](https://placehold.it/15/004D40/000000?text=+) `(0,77,64)`,
 - `theory`: ![#f03c15](https://placehold.it/15/1A237E/000000?text=+) `(26,35,126)`,
 - `methods`: ![#f03c15](https://placehold.it/15/8C1616/000000?text=+) `(140,22,22)`,
 - `intervention`: ![#f03c15](https://placehold.it/15/FFD54F/000000?text=+) `(255,213,79)`,

as well as `imperialblue`: ![#f03c15](https://placehold.it/15/003E74/000000?text=+) `(0,62,116)`.

You can change the background and the font colours:
 - Background of side columns, `\renewcommand{\columnbackgroundcolor}{black}`.
 - Font of side columns, `\renewcommand{\columnfontcolor}{gray}`.
 - Background of main column, `\renewcommand{\maincolumnbackgroundcolor}{empirical}`.
 - Font of main column, `\renewcommand{\maincolumnfontcolor}{gray}`.


## Acknowledgements

| Item | Author | Preview |
|:-------:|:-------:|:------:|
|[Original Better Poster Design](https://t.co/6WRGQK63g6)|[Mike Morrison](https://twitter.com/mikemorrison)|<img src="https://pbs.twimg.com/media/D2o9U6iX0AEkolp.jpg" height="150px" />|
|[Smartphone icon](https://www.flaticon.com/free-icon/smartphone_65680)|[Freepik](https://www.flaticon.com/authors/freepik)|<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/img/smartphoneBlack.png" height="150px" />|
|[Ducklings](https://www.pexels.com/photo/selective-focus-photo-of-flock-of-ducklings-perching-on-gray-concrete-pavement-1300355/)|[Magda Ehlers](https://www.pexels.com/@magda-ehlers-pexels)|<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/img/ducklings.jpg" height="150px" />|
|[Linear regression](http://www.texample.net/tikz/examples/linear-regression/)|Henri Menke|<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/img/tikzexample1.png" height="150px" />|
|[Commutative diagram](http://www.texample.net/tikz/examples/commutative-diagram/)|[Stefan Kottwitz](http://texblog.net/)|<img src="https://raw.githubusercontent.com/rafaelbailo/betterposter-latex-template/master/img/tikzexample2.png" height="150px" />|
|[Imperial College London logo](https://www.imperial.ac.uk/brand-style-guide/visual-identity/the-imperial-logo/)|[Imperial College London](https://www.imperial.ac.uk/)|<img src="https://www.imperial.ac.uk/ImageCropToolT4/imageTool/uploaded-images/White-on-navy--tojpeg_1495792347019_x1.jpg" height="150px" />|


