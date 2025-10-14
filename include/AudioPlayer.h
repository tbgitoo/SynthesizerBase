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
// The general concept for this class and also the class name and some specific functions are inspired or taken
// directly from
// from https://github.com/JanWilczek/android-wavetable-synthesizer . The repository is under
// a GPL v3.0 license.
// ----------------------------------------------------------------------------


/* This is the abstract base class for Audioplayers
 * Audioplayers need a source that provides the audio samples, of type AudioSource
 * They call the AudioSource in regular time intervals to get the samples,
 * and send them to the loudspeaker driver. In Android, there can be different
 * implementations of the Audio system such as Oboe and others.
 * The details of implementation are left to daughter classes of this abstract base class
 *
 * Of note, the AudioSource member "_source" is solely defined through the interface AudioSource
 * and so whatever else it does (e.g. simulations, midi messaging, really, whatever) does not direclty
 * matter for the purpose of the Audioplayer
 */


#ifndef AudioPlayer_H
#define AudioPlayer_H

#include <stdint.h>
#include "AudioSource.h"
#include "AudioSourceConsumer.h"

namespace synthesizerBase {
    /** @brief Virtual base class for an audio player.
     *
     * An audio player is an object that permits to play
     * sound by using an AudioSource for the generating the audio data and transmitting it to an audio driver systems
     * such as oboe, upon request by the audio driver system<br />
     * The specific responsibility of the AudioPlayer is to orchestrate the interaction between the audio driver and
     * the AudioSource. It does not provide audio data on its own, but suitably invokes the onAudioReady method on
     * the AudioSource.
     */
class AudioPlayer: public AudioSourceConsumer{
 public:
  virtual ~AudioPlayer() = default;

  /**
   * @brief Start playing, by starting to transmit data from the audio source to the audio driver
   *
   * A call to this function also implies the setup of the audio driver such that it can orchestrate
   * the callbacks for acquiring the audio data in real time.
   * @return 0 for success, error code otherwise
   */
  virtual int32_t play() = 0;

  /** @brief Stop playing
   *
   * Instructs the underlying audio system that no more data should be requested, and audio
   * output should be stopped
   */

  virtual void stop() = 0;

  /**
   * @brief Set the audio source
   *
   * The role of the AudioSource is to provide the audio data. The cascade of call backs is that the audio driver framework,
   * here oboe, is configured to invoke the driver-defined callback in the audio player implementation. In the
   * implementation here, the AudioPlayer used is OboeAudioPlayer, which aside from this base class also inherits from
   * oboe::AudioStreamDataCallback such that it can respond to the callback from the oboe framework when data is needed
   * When the audioPlayer is called back from the oboe framework, it onovkes the onAudioReady method on the
   * AudioSource object it posses. The AudioSource object is then responsible for filling the data for the oboe
   * @param source Audio source
   */
  void setAudioSource(AudioSource* source) override;

  /**
   * Get the audio source
   * @return the currently set audio data source
   */

  AudioSource* getAudioSource() override;

  /**
   * Get the number of audio channels currently configured
   * @return The number of audio channels currently configured. 1=mono, 2=stereo, more
   *                                     for special spatialization approaches
   */
  virtual int32_t getChannelCount()=0; // We do not know the way the number of active audio channels (1=mono, 2=stereo, more
                                       // for special spatialization approaches) in advance, nor the way it can be retrieved
                                       // from the particular audio

  /**
   * Get the number of frames per callback. Number of "frames", that is, of samples per channel, that needs
   * to be provided to the audio driver system via the audio source
   * @return Number of frames appropriate for the audio driver system
   */
  virtual int32_t getFramesPerDataCallback()=0;

protected:
    AudioSource * _source; // The audio data source
};
}  // namespace synthesizerBase

#endif
