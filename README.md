dimorph
=======

Contrast Enhancement of directional features using Directional Morphology

The executable (windows, cygwin and linux versions) is provided. Source code for main program is not provided

To run "dimorph.c",

$: ./dimorph

o/p: Enter the input file name     //(.pgm file)     //here we need to give the name of input image file and it should be in ".pgm" format
				   //to change any image to ".pgm" format, use GIMP

After giving input file name, the output file is created in the same directory with name "result.raw" and "result.pgm"
To view the ".raw" file, we need "imod" software  

To download imod, goto "http://bio3d.colorado.edu/imod/"

".pgm" output is also created. But the output is correctly viewed in imod only. Use ".pgm" output file to see pixels values  in any text-editor.





To run gabor filter code, 

	1.First, we need to run "gabor.c" on input image file, which should be in ".pgm" format. Then 16 output files are created in ".raw" format. These 16 files are outputs corresponding to each of 16 structuring elements we have taken.
	
	2.Now run "g_mean.c". It will ask the input image in ".raw" format. Use "pgm_raw.c" to convert ".pgm" file to ".raw" file. Then it will automatically take the created 16 output files of "gabor.c" and give the output in "g_result.raw". View "g_result.raw" using imod to see the output.
