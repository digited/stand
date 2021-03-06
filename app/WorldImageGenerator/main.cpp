/*
 *
 *    main.cpp
 *                                    (c) HAL@shurabaP
 *                                        2013/05/14
 *
 * These files are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <iostream>

#include "dsp/AudioBuffer.h"
#include "dsp/Envelope.h"
#include "dsp/Specgram.h"

#include "dsp/seem/SimpleSeem.h"
#include "dsp/ffem/DioFfem.h"
#include "dsp/seem/StarSeem.h"
#include "dsp/seem/PlatinumSeem.h"

#include "dsp/world/ResidualExtractor.h"

#include "io/audio/WaveReader.h"
#include "utility/ToImage.h"

/*!
 *  @brief 波形を WORLD で分析し，分析結果を画像ファイルへと視覚化します．
 */
void analyze(AudioBuffer &buffer, QString path, double msFramePeriod)
{
    Envelope f0;            // 基本周波数列
    Specgram stft;
    Specgram specgram;      // パワースペクトル列
    Specgram residual;      // 励起信号スペクトル列
    Specgram waves;         // 励起信号波形列

    // 推定するよ！
    std::cout << "Calcualting STFT spectrogram" << std::endl;
    SimpleSeem().estimate(&stft, buffer.data(0), buffer.length(), 2048, buffer.format().sampleRate(), msFramePeriod);
    std::cout << "Estimating F0 contour" << std::endl;
    DioFfem().estimate(&f0, buffer.data(0), buffer.length(), buffer.format().sampleRate(), msFramePeriod);
    std::cout << "Estimating Spectrogram" << std::endl;
    StarSeem(&f0).estimate(&specgram, buffer.data(0), buffer.length(), 0, buffer.format().sampleRate(), msFramePeriod);
    std::cout << "Estimating Residual waveforms" << std::endl;
    PlatinumSeem(&f0, &specgram).estimate(&residual, buffer.data(0), buffer.length(), 0, buffer.format().sampleRate(), msFramePeriod);
    ResidualExtractor().extract(&waves, &residual);

    // 書きだすよ！
    ToImage::fromSpecgram(&stft).save(path + ".stft.png");
    ToImage::fromWaveform(f0.data(), f0.size(), f0.size(), 1024).save(path + ".dio.png");
    ToImage::fromSpecgram(&specgram).save(path + ".star.png");
    ToImage::fromSpecgram(&waves, ToImage::LinearScale).save(path + ".platinum.png");
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: WorldImageGenerator [input path] [output path]" << std::endl;
        return -1;
    }

    AudioBuffer audio;
    WaveReader reader;
    double msFramePeriod = 2.0;

    if(!reader.read(&audio, argv[argc - 2]))
    {
        std::cout << "Failed opening the file; " << argv[argc - 2] << std::endl;
        return -1;
    }

    if(audio.isEmpty())
    {
        std::cout << "\"" << argv[argc - 1] << "\" is an empty WAVE file." << std::endl;
        return -1;
    }

    // 本体を実行する．
    analyze(audio, argv[argc - 1], msFramePeriod);

    return 0;
}

