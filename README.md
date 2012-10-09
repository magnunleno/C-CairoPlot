C-CairoPlot
===========

A reimplementation of [CairoPlot](http://cairoplot.sourceforge.net/index.html)
in C.

**Attention:** This project is in very early development stage

Examples
--------

Currently C-CairoPlot is short featured and is only capable to plot Horizontal Bar Plots. 

**Default Horizontal Bar Plot**
```C
CP_Series *series = cp_newDataSeries("Basic Bar Plot");
cp_appendData(series, NULL, 4);
cp_appendData(series, NULL, 10);
cp_appendData(series, NULL, 6);

cp_barPlot(NULL, NULL, series, CP_PNG);

cp_destroySeries(series);
```
![Default Horizontal Bar Plot](https://raw.github.com/magnunleno/C-CairoPlot/master/examples/images/horiz_bar_plot.png)

Contributting
-------------

If you want to contribute just fork the repository, make your changes and send me a fork request.

Needed libraries/dependencies:
 * libcairo2-dev
 * libglib2.0-dev
 * check

What is/was CairoPlot
---------------------

[CairoPlot is/was a pure Python plotting
library](https://github.com/rodrigoaraujo01/cairoplot) which used Cairo C/Python API
to create astonishing charts.

It was recognized by it's great aesthetics, originally conceived by [Rodrigo
Araujo](https://github.com/rodrigoaraujo01).

