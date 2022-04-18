/*
  ==============================================================================

    ADSR.h
    Created: 13 Apr 2022 5:55:26pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once

class ADSRClass
{   
private:
    float attack;
    float decay; 
    float sustain;
    float release;
    bool gate;
    float output = 0.0f;
    float attackIncrement;
    float releaseIncrement;
    float decayIncrement;
    float millisecondsToSamples(float milliseconds);
    float sampleRate;
    bool attackStage;
    bool decayStage;
    bool sustainStage;
    bool releaseStage;

public:
    ADSRClass(float samplerate);
    ADSRClass() = default;
    void keyDown();
    void keyUp();
    float ADSRProcess();
    bool isActive();
    void setAttack(int newAttack);
    void setDecay(int newDecay);
    void setSustain(float newSustain);
    void setRelease(int newRelease);
    void setSampleRate(float samplerate) { sampleRate = samplerate; }
};