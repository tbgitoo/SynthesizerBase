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
// ----------------------------------------------------------------------------

#ifndef MIDI_SYNTH_AUDIOSOURCECONSUMER_H
#define MIDI_SYNTH_AUDIOSOURCECONSUMER_H

#include "AudioSource.h"

namespace synthesizerBase {
    /**
     * Base interface class for classes such as audio players that make use of an AudioSource for
     * generating the audio data.
     */
    class AudioSourceConsumer {
    public:
        /**
         * Set the audio data source
         * @param source The audio data source that will provide audio data on callback
         */
        virtual void setAudioSource(AudioSource* source)=0;

        /**
         * Get the currently set audio data source
         * @return The audio data source that will provide audio data on callback
         */
        virtual AudioSource* getAudioSource()=0;


    };
}  // namespace synthesizerBase

#endif


