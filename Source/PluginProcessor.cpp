/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
UachannelTestAudioProcessor::UachannelTestAudioProcessor()
: AudioProcessor (BusesProperties().withInput  ("Input",     AudioChannelSet::stereo())
				  .withOutput ("Output",    AudioChannelSet::stereo())
				  .withOutput ("Low",    AudioChannelSet::stereo())
				  .withOutput ("Mid",    AudioChannelSet::stereo())
				  .withOutput ("High",    AudioChannelSet::stereo())
				  .withInput  ("Sidechain", AudioChannelSet::stereo()))
{
}

UachannelTestAudioProcessor::~UachannelTestAudioProcessor()
{
}

//==============================================================================
const String UachannelTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool UachannelTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool UachannelTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool UachannelTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double UachannelTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int UachannelTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int UachannelTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void UachannelTestAudioProcessor::setCurrentProgram (int index)
{
}

const String UachannelTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void UachannelTestAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void UachannelTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void UachannelTestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool UachannelTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
	
	int input = layouts.getMainInputChannelSet().size();
	int sidechain = layouts.getChannelSet(true, 1).size();
	int output = layouts.getChannelSet(false, 0).size();
	int outputBusses = layouts.outputBuses.size();
	//AudioChannelSet::stereo()
	
	if (layouts.getMainInputChannelSet()  == AudioChannelSet::disabled()
		|| layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
	{
		return false;
	}
	
	if(layouts.inputBuses.size() > 2 || (outputBusses != 1 && outputBusses != 4))
	{
		return false;
	}
	
	if(input > 2 || sidechain > 2 || output > 2)
	{
		return false;
	}
	
	if(input == 2 && output == 1)
	{
		//don't allow stereo->mono track in PT
		return false;
	}
	
	if(outputBusses == 4)
	{
		//first make sure they're all the same size
		int matchSize = layouts.getChannelSet(false, 1).size();
		if(layouts.getChannelSet(false, 2).size() != matchSize)
		{
			return false;
		}
		if(layouts.getChannelSet(false, 3).size() != matchSize)
		{
			return false;
		}
		
		for(int i = 1;i<4;i++)
		{
			//ok we allow mono main and stereo aux for Logic but not stereo main and mono aux
			int auxSize = layouts.getChannelSet(false, i).size();
			if(output == 1)
			{
				if(auxSize != 1 && auxSize != 2)
				{
					return false;
				}
			}
			else
			{
				if(auxSize != 2)
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

void UachannelTestAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	/*
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
	 */
}

//==============================================================================
bool UachannelTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* UachannelTestAudioProcessor::createEditor()
{
    return new UachannelTestAudioProcessorEditor (*this);
}

//==============================================================================
void UachannelTestAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void UachannelTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UachannelTestAudioProcessor();
}
