#pragma once

/***************************************************************
 * This source files comes from the xLights project
 * https://www.xlights.org
 * https://github.com/smeighan/xLights
 * See the github commit history for a record of contributing
 * developers.
 * Copyright claimed based on commit dates recorded in Github
 * License: https://github.com/smeighan/xLights/blob/master/License.txt
 **************************************************************/

#include "RenderableEffect.h"

#include <list>
class RainbowPanel;

#define Rainbow_SCALE_MIN 0
#define Rainbow_SCALE_MAX 100

class RainbowTiming;
class NoteTiming;

class RainbowEffect : public RenderableEffect
{
public:
    RainbowEffect(int id);
    virtual ~RainbowEffect();
    virtual bool CanBeRandom() override
    {
        return false;
    }
    virtual void Render(Effect* effect, const SettingsMap& settings, RenderBuffer& buffer) override;
    static std::vector<float> Parse(wxString& l);
    virtual void SetDefaultParameters() override;
    virtual void SetPanelStatus(Model* cls) override;
    virtual void RenameTimingTrack(std::string oldname, std::string newname, Effect* effect) override;
    virtual int GetColorSupportedCount() const override
    {
        return 5;
    }
    virtual std::list<std::string> CheckEffectSettings(const SettingsMap& settings, AudioManager* media, Model* model, Effect* eff, bool renderCache) override;
    virtual bool AppropriateOnNodes() const override
    {
        return false;
    }
    // Currently not possible but I think changes could be made to make it support partial
    // virtual bool CanRenderPartialTimeInterval() const override { return true; }

protected:
    virtual xlEffectPanel* CreatePanel(wxWindow* parent) override;
    void SetPanelTimingTracks();

private:
    RainbowPanel* _panel;
    void RenderRainbow(RenderBuffer& buffer, SequenceElements* elements, const std::string& type, const std::string& MIDITrack, const std::string& stringAppearance, int maxFrets, bool showStrings, bool fade, bool collapse, double stringWaveFactor, double baseWaveFactor, bool varyWavelengthBasedOnFret);
    void DrawRainbow(RenderBuffer& buffer, RainbowTiming* pdata, const std::string& stringAppearance, uint8_t maxFrets, uint8_t strings, bool showStrings, bool fade, bool collapse, double stringWaveFactor, double baseWaveFactor, bool varyWavelengthBasedOnFret);
    std::list<NoteTiming*> LoadTimingTrack(const std::string& track, int intervalMS, const std::string& type, uint8_t maxFrets, uint8_t strings);
    std::list<std::string> ExtractNotes(const std::string& label);
    int ConvertNote(const std::string& note);
    void ConvertStringPos(const std::string& note, uint8_t& string, uint8_t& pos);
    void DrawRainbowOn(RenderBuffer& buffer, uint8_t string, uint8_t fretPos, uint32_t timePos, uint32_t of, uint8_t maxFrets, uint8_t strings, bool showStrings, bool fade, bool collapse);
    void DrawRainbowWave(RenderBuffer& buffer, uint8_t string, uint8_t fretPos, uint32_t timePos, uint32_t of, uint8_t maxFrets, uint8_t strings, bool showStrings, bool fade, bool collapse, double stringWaveFactor, double baseWaveFactor, bool varyWavelengthBasedOnFret);
    void DrawString(RenderBuffer& buffer, uint8_t string, uint8_t strings);
};
