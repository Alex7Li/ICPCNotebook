Ohio State ACM-ICPC Notebook
============================

This is a repository for the OSU ACM-ICPC teams.

It hosts a notebook that can be printed out and used during contests. 
Look at notebook.html or notebook.pdf.

Generating team notebook
========================
The included Python scripts can generate the notebook in PDF or HTML format. Both scripts read the contents of the notebook from `contents.txt`.

PDF version
-----------
Requires: [Python 2/3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

The LaTeX template that the script uses is `notebook.tex`. It recognizes common file extensions for C/C++/Java/Python and applies syntax highlighting. In order to change the color scheme or add additional languages, both `notebook.tex` and `generate_pdf.py` should be modified accordingly.

To generate (on Linux):
```Linux:
sudo apt install latexmk
python3 generate_pdf.py
```

HTML version
------------
Requires: [Python 2/3](https://www.python.org/), [enscript](https://www.gnu.org/software/enscript/)

Syntax highlighting is handled solely by enscript, and in order to change the color schemes, either the default options of enscript or `generate_html.py` should be edited accordingly.

To generate (on Linux):
```
sudo apt install enscript
python3 generate_html.py
```
Links
=====
* [CPC OSU Site](https://cpcosu.github.io/)