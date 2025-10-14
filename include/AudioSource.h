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
// The concept for this class partly stems from
// https://github.com/JanWilczek/android-wavetable-synthesizer . The repository is under
// a GPL v3.0 license.
// ----------------------------------------------------------------------------


#ifndef AudioSource_H
#define AudioSource_H

#include <oboe/Oboe.h>

namespace synthesizerBase {

/**
 * @brief Generic base class for an audio source
 *
 * The audio source provides methods for filling an audio buffer. This class is intended to be used as part of
 * an AudioPlayer object. The AudioPlayer object orchestrates the interaction with the audio driver system (here,
 * oboe), the specific responsibility of the AudioSource is to provide the data
 * <br />
 * This class is virtual and provides a minimalistic common interface for audio sources. Functionality is implemented
 * in daughter classes
 */

class AudioSource {
 public:
  virtual ~AudioSource() = default;

    /**
       * @brief Main audio callback function: A buffer is ready for processing, fill it with audio data
       *
       * This function is will be invoked by a chain of callbacks when the audio driver needs new audio data<br />
       *
       * audioData represents a pre-reserved float array of length framesCount*channelCount, with a block
       * structure with channelCount blocks of each block consisting of framesCount consecutive floats. I.e.
       * This can for example be achieved with an array of the structure float[channelCount][framesCount]. Oboe
       * expects that the values provided be in the interval -1.0 to +1.0
       * @param audioData Pointer to the start of the audio data buffer, preallocated by oboe, of length
       *                  framesCount*channelCount and with an intended blockwise structure float[channelCount][framesCount]
       * @param framesCount Number of samples to be supplied in each channel
       * @param channelCount Number of channels, e.g., number of blocks. Mono=1, Stereo=2
       */
  virtual void onAudioReady(float* audioData, int32_t framesCount, oboe::ChannelCount channelCount)=0;

  /**
   * Notify the audio source that the audio playing via the audio driver system has stopped
   */

  virtual void onPlaybackStopped() = 0;
};


}  // namespace SynthesizerBase

#endif
