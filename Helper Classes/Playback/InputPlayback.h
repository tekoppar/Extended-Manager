#pragma once

class InputPlayback : public Global
{
public:
	static InputPlayback _Instance;

	bool StartPlayback = false;
	bool FinishedPlayback = false;

	virtual void Cleanup() override;
	virtual void Update() override;

	void Playback();
	void GenerateInputs();
	void AddInput(Input input);
	void Reset();
	bool ReadPlaybackFile();

private:

	std::vector<Input> Inputs;
	std::vector<Input> GeneratedInputs;
	int Frame = 0;
	int InputIndex = 0;
};