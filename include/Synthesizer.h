// ----------------------------------------------------------------------------
//
//  Copyright (C) 2025 Mathis and Thomas Braschler <thomas.braschler@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Parts of the concept, and some of the basic functions, are inspired or modified from:
// https://github.com/JanWilczek/android-wavetable-synthesizer/blob/main/app/src/main/cpp/WavetableSynthesizer.cpp ,
// The android-wavetable-synthesizer repository is also under a GPL v3.0 license.
// ----------------------------------------------------------------------------

#ifndef Synthesizer_H
#define Synthesizer_H


#include "AudioPlayer.h"
#include "AudioSourceConsumer.h"
#include <memory>





namespace synthesizerBase {

    constexpr auto samplingRate = 48000;
    /**
     * @brief Virtual base class for an audio synthesizer
     *
     * This is an abstract base class for audio synthesizer<br />
     * A synthesizer as defined here conceptually reunits two key elements:<br />
     * - the Audioplayer, considered unique across the app, which transmits data to the physical audio output<br />
     * - the AudioSource which is used to provide the samples to the Audioplayer<br />
     * Here, internally, the AudioSource is not stored separately but reference is made to the
     * AudioSource connected to the Audioplayer.
     */

    class Synthesizer : public AudioSourceConsumer {
    public:

        /**
         * Start playing audio
         */
        virtual void play()=0;

        /**
         * Stop playing audio
         */
        virtual void stop()=0;

        /**
         * Is the synthesizer presently playing? Even if playing, you may here no sound, for example
         * if only 0 values are being transmitted to the audio system or if the physical audio volume is off.
         * @return True if transmitting data to the audio driver system, false otherwise.
         */
        virtual bool isPlaying() const;

        /**
         * Set the overall volume of the synthesizer
         * @param volume Volume gain, on linear scale. Typically in the range of 0 to 1
         */
        virtual void setVolume(float volume)=0;

        /**
         * Set the audio data source
         * @param source Audio data source
         */
        virtual void setAudioSource(AudioSource* source) override;

        /**
         * Get the currently configured audio data source
         * @return The currently configured audio data source
         */
        virtual AudioSource* getAudioSource() override;





    protected:
        std::unique_ptr<synthesizerBase::AudioPlayer> _audioPlayer; // audio player for transmitting data to the audio driver
        std::atomic<bool> _isPlaying{false}; // are we playing, that is, transmitting data to the audio driver?
    };
}  // synthesizerBase

#endif
