//
// Created by thoma on 04/04/2025.
//

#include "include/AudioPlayer.h"

namespace synthesizerBase {

    void AudioPlayer::setAudioSource(AudioSource *source) {
        _source = source;
    }

    AudioSource* AudioPlayer::getAudioSource()
    {
        return(_source);
    }




}
