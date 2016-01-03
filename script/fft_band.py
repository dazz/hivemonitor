#!/usr/bin/python

from __future__ import print_function
import os
import numpy as np
import matplotlib.pyplot as plt

import scipy
from scipy import fft, arange, fftpack, signal, stats
from pylab import log
import scipy.io.wavfile as wav


def getSpectrum(y,Fs):
 """
 Plots a Single-Sided Amplitude Spectrum of y(t)
 """
 n = len(y) # length of the signal
 k = arange(n)
 T = n/Fs
 #frq = scipy.fftpack.fftfreq(n, Fs)# two sides frequency range
 frq = k/T
 frq = frq[range(n/2)] # one side frequency range
 #log(abs(fft(y)).T)
 Y = log(abs(fft(y.T)))
 #Y = abs(fft(y)) # fft computing and normalization
 Y = Y.T[:n/2]
 return (frq, Y)


if __name__=="__main__":
    import argparse
    parser = argparse.ArgumentParser(description='print fft from wave file')
    parser.add_argument('wavefile', type=str, help='file name')
    parser.add_argument('highpass', type=int, help='high pass')
    parser.add_argument('lowpass', type=int, help='low pass')

    args = parser.parse_args()

    read_time_wave = wav.read(args.wavefile)
    time_wave=read_time_wave[1]
    sampling_frequency=read_time_wave[0]

    (frq_1, fft_signal)=getSpectrum(time_wave, sampling_frequency)
    frq = frq_1[::3]
    li, hi = frq[args.highpass == frq][0], frq[args.lowpass==frq][0]

    computed_signal = fft_signal[3*li:3*hi]

    #plt.plot(computed_signal)
    #plt.show()

    fft_samples = np.reshape(computed_signal, (-1, 3))
    fft_mean = np.mean(fft_samples, axis=1)

    #plt.plot(np.arange(li,hi), fft_mean)
    #plt.show()

    print (np.mean(fft_mean))