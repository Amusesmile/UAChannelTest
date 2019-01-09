/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
UachannelTestAudioProcessorEditor::UachannelTestAudioProcessorEditor (UachannelTestAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

UachannelTestAudioProcessorEditor::~UachannelTestAudioProcessorEditor()
{
}

//==============================================================================
void UachannelTestAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);

	float y = 0;
	float spacing = 20;
	
	g.drawText("number of input buses: " + String(processor.getBusesLayout().inputBuses.size()), 0, y += spacing, 200, 40, juce::Justification::left);
	g.drawText("total input channels: " + String(processor.getTotalNumInputChannels()), 0, y += spacing, 200, 40, juce::Justification::left);
	
	y += spacing;
	
	g.drawText("number of output buses: " + String(processor.getBusesLayout().outputBuses.size()), 0, y += spacing, 200, 40, juce::Justification::left);
	g.drawText("total output channels: " + String(processor.getTotalNumOutputChannels()), 0, y += spacing, 200, 40, juce::Justification::left);
	
	y += spacing;
	
	for(int i = 0;i<processor.getBusesLayout().inputBuses.size();i++)
	{
		g.drawText("input bus " + String(i) + " channels: " + String(processor.getBusesLayout().getChannelSet(true, i).size()), 0, y += spacing, 200, 40, juce::Justification::left);
	}
	
	y += spacing;
	
	for(int i = 0;i<processor.getBusesLayout().outputBuses.size();i++)
	{
		g.drawText("output bus " + String(i) + " channels: " + String(processor.getBusesLayout().getChannelSet(false, i).size()), 0, y += spacing, 200, 40, juce::Justification::left);
	}
}

void UachannelTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
