# SynthesizerBase: A very basic framework for building Android Apps with synthesizing capacity

## Origin of the project

This is a very much simplified and reduced version of Jan Wilczek's wave table synthesizer (https://github.com/JanWilczek/android-wavetable-synthesizer). If you are looking for
Jan Wilczek's code and tutorial, please go to his github page (again, at https://github.com/JanWilczek/android-wavetable-synthesizer).

Also, you can check out his tutorial, which is very thorough and helpful.

[>>> Read the tutorial on TheWolfSound.com <<<](https://thewolfsound.com/android-synthesizer-1-app-architecture/)

## Project Goal

The goal of this minimalistic fork is to provide an absolutely minimal C++ base class hierarchy that can be extended to various synthesizers. 
That can be generic wavetable synthesizers as done by Jan Wilczek, you could also base it on fluidsynth, as you whish. We were simply looking for a convenient and solid
base architecture for various synthesizers, and seeing Jan Wilczek's systematic approach, tried to extract the very core essence of it, for extension in other projects.

## Dependencies

For this to work, you need to configure oboe (i.e. https://github.com/google/oboe). A first possibility is via gradle dependency, but we found this to be less stable, a more complex but ultimately at least in 
our case more reliable solution was inclusion via the github submodule mechanism.

