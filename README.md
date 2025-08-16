# SuperEMMETT

A playful virtual machine for learning about CPUs, RAM, and compilers — and for having fun experimenting with them.

# Overview

SuperEMMETT features a simulated RAM, CPU, and compiler.
The compiler translates source code into bytecode, which is then executed by the CPU.
To keep things approachable, certain simplifications are made compared to real hardware.

You can write programs in a simplified assembly-like language, and over time, more sophisticated features will be introduced.
All is made in the same language, so the language can be as simple as assembly, with tint of more complex part of code in it.
# CPU

The CPU aim to be a simplified version of the MOS 6502 processor.
The instruction set is not identical to the original: opcodes have been modified, with some commands added or removed.

The goal is to support multiple CPU implementations running in parallel, with the ability to fork processes for experimentation.

Iterations are used as the unit of measurement, so parallelism is quantified based on the number of iterations.