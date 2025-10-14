// ----------------------------------------------------------------------------
//
//  Copyright (C) 2025 Thomas and Mathis Braschler <thomas.braschler@gmail.com>
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
// This is inspired and in part literally copies sections of the OboeAudioPlayer from Jan Wilczek's tutorial:
// Wavetable synthesizer, at
// https://github.com/JanWilczek/android-wavetable-synthesizer/blob/main/app/src/main/cpp/OboeAudioPlayer.cpp
// The Jan Wilczek's android-wavetable-synthesizer repository is also under a GPL v3.0 license.
//
// ----------------------------------------------------------------------------



#ifndef OboeAudioPlayer_H
#define OboeAudioPlayer_H

#include <oboe/Oboe.h>
#include "AudioPlayer.h"
#include "AudioSource.h"



#define defaultAudioFrameSize 256
#define defaultAudioChannelNumber 1



namespace synthesizerBase {
/**
 * The OboeAudioPlayer class is a specific implementation of the abstract base
 * class AudioPlayer, and uses google's Oboe library for sound generation
 * The basic inner working of this is that when playing,
 * the onAudioReady function is regularly called by the oboe library, and the
 * the task of the OboeAudioplayer is to relay this call to the Audio source by
 * appropriately calling getSample.
 */

    class OboeAudioPlayer : public oboe::AudioStreamDataCallback,
                            public synthesizerBase::AudioPlayer {
    public:
        /**
         * Number of audio channels to be synthesized (1=mono for now)
         */
        static constexpr auto channelCount = oboe::ChannelCount::Mono;

        /** Constructor with audio source
         *
         * @param source The audio source
         * @param samplingRate The required sampling rate, in samples per seconds
         */

        OboeAudioPlayer(synthesizerBase::AudioSource * source, int samplingRate);
        /**
         * Destructor
         */
        ~OboeAudioPlayer();

        /**
         * Intended audio frame size
         */
        static constexpr int defaultFrameSize = defaultAudioFrameSize;

        /**
         * Intended number of channels
         */

        static constexpr int defaultChannels = defaultAudioChannelNumber;

        /**
        * @brief Start playing, by starting to transmit data from the audio source to oboe
         *
         * In detail, a call to this function implies the setup of oboe such that this object is
         * set as the target for the data call back. This means that from the invocation of the
         * play function on, the onAudioReady of this object will be regularly called by the
         * oboe audio thread; in turn, this OboeAudioPlayer object will call the onAudioReady
         * function of the the AudioSource. Overall, these calls serve to make the audio sample data
         * from the AudioSource available to Oboe.
         *
         * @return 0 for success, error code otherwise
        */

        virtual int32_t play() override;

        /** @brief Stop playing
         *
         * Instructs oboe to stop requesting audio data.
         */


        virtual void stop() override;

        /**
       * @brief Callback method following oboe::AudioStreamDataCallback, indicating that audio data should
       * be generated and written to the audio buffer provided.
       *
       *
       * @param audioStream pointer to the associated stream. Not used here, but necessary to comply with
         * oboe::AudioStreamDataCallback
       * @param audioData buffer to put output data
       * @param numFrames number of frames to be put into output
       * @return DataCallbackResult::Continue or DataCallbackResult::Stop
       */

        virtual oboe::DataCallbackResult onAudioReady(oboe::AudioStream* audioStream,
                                              void* audioData,
                                              int32_t framesCount) override;

        /**
         * Number of channels to be provided in the audio data by audio source. 1=mono, 2=stereo, more
         * for specific spatial processing applications
         * @return
         */
        int32_t getChannelCount() override;

        /**
         * Number of audio samples per channel that should be provided. Normally, this does not change
         * between calls to onAudioReady; as a last resort, the framesCount argument of onAudioReady primes,
         * not this function.
         * @return Return the nominal, intended number of audio samples per channel per call to onAudioReady.
         */

        int32_t getFramesPerDataCallback() override;



    protected:

        std::shared_ptr<oboe::AudioStream> _stream; // oboe audio stream, acquired during oboe audio startup
        // and serving to obtain parameters such as the number of frames per callback.

        int _samplingRate; // the audio sampling rate, in samples / second
    };
}  // namespace synthesizerBase

#endif
