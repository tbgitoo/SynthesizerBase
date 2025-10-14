#include "include/OboeAudioPlayer.h"

#include <utility>
#include "include/AudioSource.h"
#include <stdio.h>
#include <stdlib.h>


using namespace oboe;

namespace synthesizerBase {
#ifndef NDEBUG
    static std::atomic<int> instances{0};
#endif

    OboeAudioPlayer::OboeAudioPlayer(synthesizerBase::AudioSource* source,
                                     int samplingRate)
            :  _samplingRate(samplingRate) { _source = source;

    }

    OboeAudioPlayer::~OboeAudioPlayer() {

        OboeAudioPlayer::stop();
    }

    int32_t OboeAudioPlayer::play() {

        AudioStreamBuilder builder;
        const auto result =
                builder.setPerformanceMode(PerformanceMode::LowLatency)
                        ->setDirection(Direction::Output)
                        ->setSampleRate(_samplingRate)
                        ->setDataCallback(this)
                        ->setSharingMode(SharingMode::Exclusive)
                        ->setFormat(AudioFormat::Float)
                        ->setChannelCount(channelCount)
                        ->setSampleRateConversionQuality(SampleRateConversionQuality::Best)
                        ->openStream(_stream);
               builder.setFramesPerCallback(defaultAudioFrameSize);
               builder.setChannelCount(defaultAudioChannelNumber);

        if (result != Result::OK) {
            return static_cast<int32_t>(result);
        }

        const auto playResult = _stream->requestStart();

        return static_cast<int32_t>(playResult);
    }

    void OboeAudioPlayer::stop() {


        if (_stream) {
            _stream->stop();
            _stream->close();
            _stream.reset();
        }
        _source->onPlaybackStopped();
    }

    DataCallbackResult OboeAudioPlayer::onAudioReady(oboe::AudioStream* audioStream,
                                                     void* audioData,
                                                     int32_t framesCount) {
        auto* floatData = reinterpret_cast<float*>(audioData);



        _source->onAudioReady(floatData,framesCount,channelCount);

        return oboe::DataCallbackResult::Continue;
    }

    int32_t OboeAudioPlayer::getChannelCount() {
        if (_stream)
        {
            if(_stream->getChannelCount()>0)
            return(_stream->getChannelCount());
        }
        return(0); // unknown at this point of time

    }

    int32_t OboeAudioPlayer::getFramesPerDataCallback() {
        if (_stream) {
            if(_stream->getFramesPerDataCallback()>0)
            return (_stream->getFramesPerDataCallback());
        }
        return(0); // unknown at this point of time
    }


}  // namespace synthesizerBase
