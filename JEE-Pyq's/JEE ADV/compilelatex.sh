#!/bin/bash

# Define the LaTeX file you want to compile
LATEX_FILE="main.tex"

# Check if the LaTeX file exists
if [ ! -f "$LATEX_FILE" ]; then
    echo "Error: File $LATEX_FILE not found!"
    exit 1
fi

# Run pdflatex on the LaTeX file
pdflatex "$LATEX_FILE"
evince main.pdf &
