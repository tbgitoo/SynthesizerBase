
#include "include/OboeAudioPlayer.h"
#include "include/Synthesizer.h"


namespace synthesizerBase {

    bool Synthesizer::isPlaying() const {

        return _isPlaying;
    }

   void Synthesizer::setAudioSource(AudioSource* source){
        if(_audioPlayer != nullptr)
        {
            _audioPlayer->setAudioSource(source);
        }
    }

    AudioSource* Synthesizer::getAudioSource(){
        if(_audioPlayer != nullptr)
        {
            return(_audioPlayer->getAudioSource());
        }
        return nullptr;
    };





}  // namespace wavetablesynthesizer
