# Rebec
Rebec is a programming language that compiles to R313 assembly. Compiled programs can be ran in the R313 virtual machine. The R313 virtual machine is a turing complete single-instruction virtual machine based on the reverse-substract skip-on-borrow (RSSB) architecture.

## Building

The Makefile can be used to build this software. The compiled file will appear in the "build" folder.

## Use

In the "example" folder is an example Rebec program called "name.rbc" which can be compiled using the "rebec" (or "rebec.exe") which appears in the "build" folder. 

`./rebec name.rbc > name.asm`

the compiled file is an R313 assembly file which must be assembled and finally run inside of the R313 virtual machine.
